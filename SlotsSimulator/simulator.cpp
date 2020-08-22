#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mutex>

#include "utils.h"
#include "Valiant_1.h"
#include "simulator.h"
#include "SlotsSimulator.h"


Simulator_Type simulator;
Simulator_Type* simulators[NUM_SIM];

void init_sim_array() {
	memset(simulators, 0, sizeof(simulators));
}

std::once_flag initSimArray;
Simulator_Type::Simulator_Type() : base_game() {
	std::call_once(initSimArray, init_sim_array);
	ResetSim();
}

Simulator_Type::Simulator_Type(Game_Type* game) : base_game(game->game_state.data) {
	std::call_once(initSimArray, init_sim_array);
	ResetSim();
}

void Simulator_Type::OneSpinRun() {
	base_game.OneSpinExecute();
	if (spin_count == 0) {
		__time64_t ltime;
		_time64(&ltime);
		_localtime64_s(&start, &ltime);
	}
	AnalyzeOneSpin();
}

void Simulator_Type::BulkSpinRun(UINT64 count) {
	while (count > 0 || !base_game.NextBaseSpin()) {
		OneSpinRun();
		if (base_game.IsBaseSpin()) {
			count--;
		}
	}
}

void Simulator_Type::ResetSim() {
	base_game.SetBase();

	spin_count = 0;
	total_win = total_paid = 0;
	balance = 0;
	total_awarded_free_spins = 0;
	max_awarded_free_spins = 0;

	memset(win_stat, 0, sizeof(win_stat));
	memset(win_scatters, 0, sizeof(win_scatters));
	memset(spin_count_by_type, 0, sizeof(spin_count_by_type));
	memset(total_win_by_type, 0, sizeof(total_win_by_type));
	memset(max_win_spin_by_type, 0, sizeof(max_win_spin_by_type));
	memset(spin_count_by_win, 0, sizeof(spin_count_by_win));
	memset(seqs_count_by_win, 0, sizeof(seqs_count_by_win));
	memset(game_count_by_win, 0, sizeof(game_count_by_win));
	memset(seqs_count_by_len, 0, sizeof(seqs_count_by_len));
	memset(bonus_trigger, 0, sizeof(bonus_trigger));

	memset(group_win, 0, sizeof(group_win));
	pos_in_group = 0;
	group_count = 0;
}

UINT64 Simulator_Type::max_win_cap(UINT64 value) {
	if (value < MAX_WIN) {
		return value;
	}
	return MAX_WIN - 1;
}

UINT64 Simulator_Type::max_len_cap(UINT64 len) {
	if (len < MAX_SEQ) {
		return len;
	}
	return MAX_SEQ - 1;
}

void Simulator_Type::AnalyzeOneSpin() {
	total_win += base_game.win_spin;
	balance += base_game.win_spin;
	if (group_count < GROUPS_MAX) {
		group_win[group_count] += base_game.win_spin;
	}
	if (!base_game.IsCollectingSpin()) {
		spin_count_by_type[base_game.GameIdx()] += 1;
		total_win_by_type[base_game.GameIdx()] += base_game.win_spin;
	}

	// Any paid spin
	if (base_game.IsBaseSpin()) {
		spin_count++;
		total_paid += base_game.game_state.bet_game;
		balance -= base_game.game_state.bet_game;
	}

	// End of full game: base spin + all free spins + all cascades + all bonus respins
	if (base_game.NextBaseSpin() && group_count < GROUPS_MAX) {
		pos_in_group++;
		if (pos_in_group == GROUP_SEP) {
			group_count++;
			pos_in_group = 0;
		}
	}
	if (base_game.NextBaseSpin()) {
		game_count_by_win[max_win_cap(base_game.win_game)] += 1;

		if (base_game.win_game > max_win_game) {
			max_win_game = base_game.win_game;
		}
	}

	// Awarded/retriggered free spins
	if (base_game.IsNewBonusAwarded()) {
		bonus_trigger[base_game.GameIdx()][base_game.NextIdx()].cases++;
		bonus_trigger[base_game.GameIdx()][base_game.NextIdx()].awards += 1;
	}

	// spin_count_by_win, max_win
	if (!base_game.IsCollectingSpin()) {
		spin_count_by_win[max_win_cap(base_game.win_spin)]
			[base_game.GameIdx()] += 1;
		if (base_game.win_spin > max_win_spin) {
			max_win_spin = base_game.win_spin;
		}
		if (base_game.win_spin > max_win_spin_by_type[base_game.GameIdx()]) {
			max_win_spin_by_type[base_game.GameIdx()] = base_game.win_spin;
		}
		if (base_game.win_base > max_win_base) {
			max_win_base = base_game.win_base;
		}
	}

	// win_stat
	if (base_game.win_spin != 0) {
		int l;
		for (l = 0; l < base_game.win_lines; l++) {
			if (base_game.winlines_desc[l].is_win) {
				win_stat[base_game.winlines_desc[l].symbol]
					[base_game.winlines_desc[l].length]
				[base_game.GameIdx()]
				[base_game.winlines_desc[l].multiplier].count += 1;
				win_stat[base_game.winlines_desc[l].symbol]
					[base_game.winlines_desc[l].length]
				[base_game.GameIdx()]
				[base_game.winlines_desc[l].multiplier].value += base_game.winlines_desc[l].value;
			}
		}
	}
}

double Simulator_Type::CurrentRTP() {
	if (total_paid == 0) {
		return 0.0;
	}
	return (double)total_win / total_paid * 100.0;
}
double Simulator_Type::CurrentRTP(int slot_variant) {
	if (total_paid == 0) {
		return 0.0;
	}
	return (double)(total_win_by_type[slot_variant]) / total_paid * 100.0;
}
double Simulator_Type::CurrentHitRate() {
	if (spin_count == 0) {
		return 0.0;
	}
	return 100.0 - (double)(game_count_by_win[0]) / spin_count * 100.0;
}
double Simulator_Type::CurrentHitRate(int slot_variant) {
	if (spin_count_by_type[slot_variant] == 0) {
		return 0.0;
	}
	return 100.0 - (double)(spin_count_by_win[0][slot_variant]) /
		spin_count_by_type[slot_variant] * 100.0;
}
double Simulator_Type::CurrentAveragePay() {
	if (0 == spin_count - game_count_by_win[0]) {
		return 0.0;
	}
	return (double)total_win / (spin_count - game_count_by_win[0]);
}
double Simulator_Type::CurrentAveragePay(int slot_variant) {
	if (0 == spin_count_by_type[slot_variant] - spin_count_by_win[0][slot_variant]) {
		return 0.0;
	}
	return (double)total_win_by_type[slot_variant] /
		(spin_count_by_type[slot_variant] - spin_count_by_win[0][slot_variant]);
}
double Simulator_Type::MeanPay() {
	if (spin_count == 0) {
		return 0.0;
	}
	return (double)total_win / spin_count;
}
double Simulator_Type::VarPay() {
	if (spin_count < 2) {
		return 0.0;
	}

	int i;
	double mean = 0.0, M2 = 0.0;
	double delta;
	UINT64 sum_w = 0;
	for (i = 0; i <= max_win_cap(max_win_game); i++) {
		if (game_count_by_win[i] != 0) {
			sum_w += game_count_by_win[i];
			delta = i - mean;
			mean += game_count_by_win[i] * delta / sum_w;
			M2 += game_count_by_win[i] * delta * (i - mean);
		}
	}
	return M2 / (sum_w - 1);
}
double Simulator_Type::StdDevPay() {
	return sqrt(VarPay());
}

