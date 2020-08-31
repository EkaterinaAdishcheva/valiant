// SlotsSimulator.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <math.h>

#include "utils.h"
#include "Valiant_1.h"
#include "simulator.h"
#include "SlotsSimulator.h"

void print_line(FILE * file, int list[], int length);
void print_reels(FILE * file, const wchar_t * title, int(*reel)[REELLENMAX], int reel_len[]);


// Interface to simulator
int one_spin_run() {
	simulator.OneSpinRun();
	return 0;
}
int bulk_run(UINT64 count, int thread) {
	if (thread == 0) {
		simulator.BulkSpinRun(count);
	}
	else {
		thread--;
		if (simulators[thread] == NULL) {
			simulators[thread] = new Simulator_Type(&simulator.base_game);
			simulators[thread]->ResetSim();
		}
		simulators[thread]->BulkSpinRun(count);
	}
	return 0;
}

int get_max_threads() {
	return NUM_SIM + 1;
//	return 1;
}

int bulk_agg_stat() {
	for (int j = 0; j < NUM_SIM; j++) {
		if (!simulators[j]) {
			continue;
		}
		if (!simulators[j]->spin_count) {
			continue;
		}

		simulator.spin_count += simulators[j]->spin_count;
		simulator.total_win += simulators[j]->total_win;
		simulator.total_paid += simulators[j]->total_paid;
		simulator.total_awarded_free_spins += simulators[j]->total_awarded_free_spins;
		if (simulator.max_awarded_free_spins < simulators[j]->max_awarded_free_spins) {
			simulator.max_awarded_free_spins = simulators[j]->max_awarded_free_spins;
		}
		if (simulator.max_win_game < simulators[j]->max_win_game) {
			simulator.max_win_game = simulators[j]->max_win_game;
		}
		if (simulator.max_win_spin < simulators[j]->max_win_spin) {
			simulator.max_win_spin = simulators[j]->max_win_spin;
		}
		if (simulator.max_win_base < simulators[j]->max_win_base) {
			simulator.max_win_base = simulators[j]->max_win_base;
		}

		sum_int64_arr((UINT64*)&simulator.win_stat[0][0][0][0], (UINT64*)&simulators[j]->win_stat[0][0][0][0], sizeof(simulator.win_stat)/sizeof(UINT64));
		sum_int64_arr((UINT64*)&simulator.win_scatters[0][0], (UINT64*)&simulators[j]->win_scatters[0][0], sizeof(simulator.win_scatters) / sizeof(UINT64));
		sum_int64_arr(simulator.spin_count_by_type, simulators[j]->spin_count_by_type, SLOT_VARIANTS);
		sum_int64_arr(simulator.total_win_by_type, simulators[j]->total_win_by_type, SLOT_VARIANTS);
		max_int64_arr(simulator.max_win_spin_by_type, simulators[j]->max_win_spin_by_type, SLOT_VARIANTS);
		sum_int64_arr(&simulator.spin_count_by_win[0][0], &simulators[j]->spin_count_by_win[0][0], sizeof(simulator.spin_count_by_win) / sizeof(UINT64));
		sum_int64_arr(&simulator.seqs_count_by_win[0][0][0], &simulators[j]->seqs_count_by_win[0][0][0], sizeof(simulator.seqs_count_by_win) / sizeof(UINT64));
		sum_int64_arr(simulator.game_count_by_win, simulators[j]->game_count_by_win, Simulator_Type::max_win_cap(simulator.max_win_game) + 1);
		sum_int64_arr((UINT64*)&simulator.seqs_count_by_len[0][0], (UINT64*)&simulators[j]->seqs_count_by_len[0][0], sizeof(simulator.seqs_count_by_len) / sizeof(UINT64));
		sum_int64_arr((UINT64*)&simulator.bonus_trigger[0][0], (UINT64*)&simulators[j]->bonus_trigger[0][0], sizeof(simulator.bonus_trigger) / sizeof(UINT64));


		UINT64 idx = simulators[j]->group_count - 1;
		while (idx >= 0 && simulator.group_count < GROUPS_MAX) {
			simulator.group_win[simulator.group_count] = simulators[j]->group_win[idx--];
			simulator.group_count += 1;
		}

		simulators[j]->ResetSim();
	}
	return 0;
}
int reset_sim() {
	simulator.ResetSim();
	return 0;
}
int reset_sim_arr() {
	simulator.ResetSim();
	for (int j = 0; j < NUM_SIM; j++) {
		if (simulators[j]) {
			simulators[j]->ResetSim();
		}
	}
	return 0;
}

void print_line(FILE * file, int list[], int length) {
	for (int j = 0; j < length; j++) {
		fwprintf_s(file, (j == 0 ? L"%d" : j == length - 1 ? L"\t%d\n" : L"\t%d"), list[j]);
	}
}

// Bulk run output to log file
void print_reels(FILE * file, const wchar_t * title, int (*reel)[REELLENMAX], int reel_len[]) {
	int i, j;
	fwprintf_s(file, title);
	for (i = 0; i < WIDTH; i++) {
		j = 0;
		fwprintf_s(file, L"%d\t-\t%d", reel_len[i], reel[i][j]);
		for (j = 1; j < reel_len[i]; j++) {
			fwprintf_s(file, L"\t%d", reel[i][j]);
		}
		fwprintf_s(file, L"\n");
	}
}

void print_histogram(FILE * file, const wchar_t * title, UINT64 * array, UINT64 ceiling) {
	int j;
	fwprintf_s(file, title);
	for (j = 0; j <= ceiling; j++)
		if (array[j] != 0) {
			fwprintf_s(file, L"%d\t%I64u\t%I64u\n", j,
				array[j],
				array[j] * j
			);
		}
}

int bulk_log_results(char * filename, int maxlen, const char * gamename, int gamename_len) {
	int i, j, k, m;

	FILE * log_file;
	struct tm now;
	wchar_t w_gamename[100];
	wchar_t w_prefix[100];
	wchar_t w_filename[100];
	__time64_t ltime;
	struct __timeb64 tstruct;
	_time64(&ltime);
	_localtime64_s(&now, &ltime);
	_ftime64_s(&tstruct);

	size_t tmp;

	mbstowcs_s(&tmp, w_prefix, 100, filename, gamename_len);
	wsprintf(w_filename, L"%s_%04d-%02d-%02d_%02d%02d%02d.log", w_prefix,
		now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
	_wfopen_s(&log_file, w_filename, L"w");
	wcstombs_s(&tmp, filename, maxlen, w_filename, 100);

	// Header
	mbstowcs_s(&tmp, w_gamename, 100, gamename, 100);
	fwprintf_s(log_file, L"GAME:\t%s\n", w_gamename);
	fwprintf_s(log_file, L"Start\t%04d-%02d-%02d %02d:%02d:%02d (UTC%+03d:%02d)\n", simulator.start.tm_year + 1900,
		simulator.start.tm_mon + 1, simulator.start.tm_mday,
		simulator.start.tm_hour, simulator.start.tm_min, simulator.start.tm_sec,
		(-tstruct.timezone)/60, (-tstruct.timezone)%60);
	fwprintf_s(log_file, L"End\t%04d-%02d-%02d %02d:%02d:%02d (UTC%+03d:%02d)\n", now.tm_year + 1900,
		now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec,
		(-tstruct.timezone) / 60, (-tstruct.timezone) % 60);
	// Major KPIs
	fwprintf_s(log_file, L"GAMES\t%I64u\n", simulator.spin_count);
	fwprintf_s(log_file, L"BET\t%d\n", simulator.base_game.game_state.bet_game);
	fwprintf_s(log_file, L"WIN\t%I64u\n", simulator.total_win);
	fwprintf_s(log_file, L"PAY\t%I64u\n", simulator.total_paid);
	fwprintf_s(log_file, L"MAX WIN GAME\t%I64u", simulator.max_win_game);
	if (simulator.max_win_game >= MAX_WIN) {
		fwprintf_s(log_file, L"\t-- BEWARE OVERLOAD!!\n");
	}
	else {
		fwprintf_s(log_file, L"\n");
	}
	fwprintf_s(log_file, L"MAX WIN SPIN\t%I64u", simulator.max_win_spin);
	if (simulator.max_win_spin >= MAX_WIN) {
		fwprintf_s(log_file, L"\t-- BEWARE OVERLOAD!!\n");
	}
	else {
		fwprintf_s(log_file, L"\n");
	}
	fwprintf_s(log_file, L"MAX BASE WIN\t%I64u\n", simulator.max_win_base);

	double rtp = simulator.CurrentRTP();
	fwprintf_s(log_file, L"RTP\t%.3lf\n", rtp);
	fwprintf_s(log_file, L"Hit Rate\t%.3lf\n", simulator.CurrentHitRate());

	double sd = simulator.StdDevPay();
	fwprintf_s(log_file, L"MEAN PAY\t%.3lf\n", simulator.MeanPay());
	fwprintf_s(log_file, L"STD PAY/RATIO\t%.3lf\t%.3lf\n",
		sd, sd / simulator.base_game.game_state.bet_game);
	fwprintf_s(log_file, L"AVG NONZERO PAY/RATIO\t%.3lf\t%.3lf\n", simulator.CurrentAveragePay(),
		simulator.CurrentAveragePay() / simulator.base_game.game_state.bet_game);

	// Confidence intervals
	sd /= simulator.base_game.game_state.bet_game;
	double n = (double)simulator.spin_count;
//	static double Q[] = {0.674489750196082,
//		1.64485362695147, 1.95996398454005, 2.5758293035489};
//	Coefficients from Chebyshov's inequality
	static double Q[] = {1.41421356237309, 3.16227766016838,
		4.47213595499958, 10.0};
	static const wchar_t * P[] = { L"P50", L"P90", L"P95", L"P99" };
	for (int j = 0; j < sizeof(Q)/sizeof(double); j++) {
		fwprintf_s(log_file,
			L"RTP/SD %s\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n", P[j],
			rtp - 100.0*Q[j]*sd/sqrt(n), rtp + 100.0*Q[j]*sd/sqrt(n),
			sd * ( (n - 1.0)/(n + sqrt(2.0*n)*Q[j]) ),
			sd * ( (n - 1.0)/(n - sqrt(2.0*n)*Q[j]) )
			);
	}

	// Summary by spin types
	fwprintf_s(log_file, L"\tRTP\tHit\tMax\tAverage\tAvgNZ\tTotSpins\tTotWin\n");
	for (int i = 0; i < SLOT_VARIANTS; i++) {
		fwprintf_s(log_file, L"[%d]\t%.3lf\t%.3lf\t%I64u\t%.3lf\t%.3lf\t%I64u\t%I64u\n", i,
			simulator.CurrentRTP(i), simulator.CurrentHitRate(i),
			simulator.max_win_spin_by_type[i],
			(simulator.spin_count_by_type[i] == 0 ? 0.0 :
			(double)simulator.total_win_by_type[i] / simulator.spin_count_by_type[i]),
			simulator.CurrentAveragePay(i),
			simulator.spin_count_by_type[i],
			simulator.total_win_by_type[i]);
	}
	// Trigger/retrigger and max win
	fwprintf_s(log_file, L"BONUS RETRIGGERS\nFROM\tTO\tCase\tAwards\txPaid\txBase\tAvgAward\n");
	for (k = 0; k < SLOT_VARIANTS; k++) {
		for (i = 0; i < SLOT_VARIANTS; i++) {
			if (simulator.bonus_trigger[k][i].awards != 0) {
				fwprintf_s(log_file, L"%d\t%d\t%I64u\t%I64u\t%.2lf\t%.2lf\t%.2lf\n", k, i,
					simulator.bonus_trigger[k][i].cases,
					simulator.bonus_trigger[k][i].awards,
					simulator.spin_count / (double)simulator.bonus_trigger[k][i].cases,
					simulator.spin_count_by_type[k] / (double)simulator.bonus_trigger[k][i].cases,
					simulator.bonus_trigger[k][i].awards / (double)simulator.bonus_trigger[k][i].cases
				);
			}
		}
	}

	// Settings
	fwprintf_s(log_file, L"\nPAYTABLE\n");
	for (i = -1; i < SYMBOLS; i++) {
		for (j = 0; j <= WIDTH; j++) {
			if (i == -1) {
				fwprintf_s(log_file, j == 0 ? L"#x%d" : L"\tx%d", j);
			}
			else {
				fwprintf_s(log_file, L"%d\t", simulator.base_game.game_state.data->paytable[i][j]);
			}
		}
		if (i >= 0) {
			fwprintf_s(log_file, L"// %d\n", i);
		}
		else {
			fwprintf_s(log_file, L"\n");
		}
	}
	fwprintf_s(log_file, L"\nPARAMS\n");
	fwprintf_s(log_file, L"# Lightning mitiplier\n");
	print_line(log_file, simulator.base_game.game_state.data->params.MultiplierWeights[0], MULTIPLIER_OPTIONS);
	print_line(log_file, simulator.base_game.game_state.data->params.MultiplierWeights[1], MULTIPLIER_OPTIONS);
	fwprintf_s(log_file, L"\n");
	fwprintf_s(log_file, L"# Free Spins sequence length\n%d\n\n", simulator.base_game.game_state.data->params.FreeSpins);
	fwprintf_s(log_file, L"# Lightning sequence length\n%d\n\n", simulator.base_game.game_state.data->params.LightningSpins);
	fwprintf_s(log_file, L"# Consolation multiplier\n%d\n\n", simulator.base_game.game_state.data->params.ConsolationPrize);

	fwprintf_s(log_file, L"\nReels (<REELS>)\n");
	print_reels(log_file, L"#Base reels\n", simulator.base_game.game_state.data->reels[0], simulator.base_game.game_state.data->reel_length[0]);
	print_reels(log_file, L"#Base lightning reels\n", simulator.base_game.game_state.data->reels[1], simulator.base_game.game_state.data->reel_length[1]);
	print_reels(log_file, L"#Free game reels\n", simulator.base_game.game_state.data->reels[2], simulator.base_game.game_state.data->reel_length[2]);
	print_reels(log_file, L"#Free lightning reels\n", simulator.base_game.game_state.data->reels[3], simulator.base_game.game_state.data->reel_length[3]);
	fwprintf_s(log_file, L"</REELS>\n\nReel Formula (spec)\n");
	for (k = 0; k < SYMBOLS; k++) {
		for (j = 0; j < REEL_VARIANTS; j++) {
			for (i = 0; i < WIDTH; i++) {
				fwprintf_s(log_file, (i == 0 ? L"%d" : L"\t%d"),
					simulator.base_game.game_state.data->reel_spec[k][j][i]);
			}
			if (j != REEL_VARIANTS - 1) {
				fwprintf_s(log_file, L"\t\t");
			}
		}
		fwprintf_s(log_file, k != SYMBOLS - 1 ? L"\n" : L"\n\n");
	}

	// Spin data
	fwprintf_s(log_file, L"Tables start marker: <TABULAR>\n\nWins by symbols\nSymbol\tWidth\tGType\tMult\tCount\tValue\n");
	for (k = 0; k < SLOT_VARIANTS; k++)
		for (i = 0; i < SYMBOLS; i++)
			for (j = 0; j <= WIDTH; j++)
				for (m = 0; m <= MAXMULT; m++)
					if (simulator.win_stat[i][j][k][m].count != 0 || simulator.win_stat[i][j][k][m].value != 0) {
						fwprintf_s(log_file, L"%d\t%d\t%d\t%d\t%I64u\t%I64u\n",
							i, j, k, m,
							simulator.win_stat[i][j][k][m].count,
							simulator.win_stat[i][j][k][m].value);
					}
	// Win scatters
	fwprintf_s(log_file, L"\nWins from scatters\nWidth\tGType\tCount\tTotal\n");
	for (j = 0; j <= WIDTH; j++)
		for (k = 0; k < SLOT_VARIANTS; k++)
			if (simulator.win_scatters[j][k].value != 0) {
				fwprintf_s(log_file, L"%d\t%d\t%I64u\t%I64u\n",
					j, k,
					simulator.win_scatters[j][k].count,
					simulator.win_scatters[j][k].value);
			}
	fwprintf_s(log_file, L"\nSpins by win\nGType\tWin\tCount\tTotal\n");
	for (i = 0; i <= Simulator_Type::max_win_cap(simulator.max_win_game); i++) {
		for (k = 0; k < SLOT_VARIANTS; k++) {
			if (simulator.spin_count_by_win[i][k] != 0) {
				fwprintf_s(log_file, L"%d\t%d\t%I64u\t%I64u\n",
					k, i, simulator.spin_count_by_win[i][k],
					i*simulator.spin_count_by_win[i][k]);
			}
		}
	}

	// Games data
	print_histogram(log_file, L"\nGames by win\nWin\tCount\tTotal\n", simulator.game_count_by_win,
		Simulator_Type::max_win_cap(simulator.max_win_game));

	// Sequences data
	fwprintf_s(log_file, L"\nSeqs by win\nSType\tSeq win\tUpgr\tSeqs\tTotal\n");
	for (i = 0; i < Simulator_Type::max_win_cap(simulator.max_win_game); i++) {
		for (k = 1; k < SPIN_TYPES; k++) {
			for (j = 0; j <= WIDTH; j++) {
				if (simulator.seqs_count_by_win[i][k][j] != 0) {
					fwprintf_s(log_file, L"%d\t%d\t%d\t%I64u\t%I64u\n", k, i, j,
						simulator.seqs_count_by_win[i][k][j],
						simulator.seqs_count_by_win[i][k][j] * i
					);
				}
			}
		}
	}
	fwprintf_s(log_file, L"\nSeqs by len\nSType\tSeq len\tSeqs\tWin\n");
	for (i = 0; i <= Simulator_Type::max_len_cap(simulator.max_awarded_free_spins); i++) {
		for (k = 1; k < SPIN_TYPES; k++) {
			if (simulator.seqs_count_by_len[i][k].count != 0
				|| simulator.seqs_count_by_len[i][k].value != 0) {

				fwprintf_s(log_file, L"%d\t%d\t%I64u\t%I64u\n",
					k, i,
					simulator.seqs_count_by_len[i][k].count,
					simulator.seqs_count_by_len[i][k].value
				);
			}
		}
	}

	// By groups
	fwprintf_s(log_file, L"\nWin by group\nGRP#\tWin\n");
	for (i = 0; i < simulator.group_count; i++) {
		fwprintf_s(log_file, L"%d\t%I64u\n", i, simulator.group_win[i]);
	}
	
	fclose(log_file);

	return 0;
}

int get_symbol(int line, int reel) {
	if ( simulator.base_game.screen.grid[reel][line] == WI
		&& simulator.base_game.expanded_wild[reel] ) {

		return EW;
	}
	return simulator.base_game.screen.grid[reel][line];
}

int get_cell_tag(int line, int reel) {
	return simulator.base_game.locked_frame[simulator.base_game.SuperType()].grid[reel][line];
}

int get_spin_message(char * message, int max_len) {
	if (simulator.base_game.ñonsolation_ind) {
		sprintf_s(message, max_len, "Consolation prize");
		return 1;
	}
	if (simulator.base_game.multiplier_now != 0) {
		sprintf_s(message, max_len, "Multiplier = %d", simulator.base_game.multiplier_now);
		return 1;
	}
	message[0] = '\0';
	return 0;
}

UINT64 get_total_paid() {
	return simulator.total_paid;
}

UINT64 get_total_win() {
	return simulator.total_win;
}

UINT64 get_spin_win() {
	return simulator.base_game.win_spin;
}

double get_rtp() {
	return simulator.CurrentRTP();
}

double get_hit_rate() {	
	return simulator.CurrentHitRate();
}

UINT64 get_games_count_arr() {
	UINT64 res = simulator.spin_count;
	for (int j = 0; j < NUM_SIM; j++) {
		if (simulators[j]) {
			res += simulators[j]->spin_count;
		}
	}
	return res;
}
UINT64 get_games_count() {
	return simulator.spin_count;
}

UINT64 get_free_spin_win() {
	return simulator.base_game.win_seq;
}

/////////////////////////////////////////////////////////////////////
int get_scatter_win() {
	return 0;
}
int get_scatters_count() {
	return 0;
}

/////////////////////////////////////////////////////////////////////
int win_line_symbol(int win_line_id) {
	return simulator.base_game.winlines_desc[win_line_id].symbol;
}

int win_line_is_win(int win_line_id) {
#ifdef WAY_TO_WIN_GAME
		return (win_line_id < simulator.base_game.win_lines) ? 1 : 0;
#endif
#ifdef PAYLINES_GAME
		return simulator.base_game.winlines_desc[win_line_id].is_win;
#endif
}

int win_line_length(int win_line_id) {
	return simulator.base_game.winlines_desc[win_line_id].length;
}

UINT64 win_line_value(int win_line_id) {
	return simulator.base_game.winlines_desc[win_line_id].value;
}

int win_line_where(int win_line_id, int reel) {
	return simulator.base_game.winlines_desc[win_line_id].where_symbols[reel];
}

int get_win_line_maxcount() {
#ifdef WAY_TO_WIN_GAME
	return simulator.base_game.win_lines;
#endif
#ifdef PAYLINES_GAME
	return PAYLINES;
#endif
}

//////////////////////////////////////////////////
int get_width() {
	return simulator.base_game.game_state.width;
}
int get_height(int reel) {
	return simulator.base_game.game_state.height[reel];
}

int get_spin_type() {
	return simulator.base_game.spin_type_now;
}

int get_spin_type_next() {
	return simulator.base_game.spin_type_next;
}

int set_bet(int bet) {
	simulator.base_game.SetBet(bet);
	return 0;
}

INT64 get_balance() {
	return simulator.balance;
}
int set_balance(UINT64 _balance) {
	simulator.balance = _balance;
	return 0;
}
UINT64 get_awarded_free_spins() {
	int maximum = simulator.base_game.free_spins_awarded[simulator.base_game.spin_type_now];
	if (simulator.base_game.free_spin_order[simulator.base_game.spin_type_now] > maximum)
	{
		maximum = simulator.base_game.free_spin_order[simulator.base_game.spin_type_now];
	}
	return maximum;
}
UINT64 get_free_spin_order() {
	return simulator.base_game.free_spin_order[simulator.base_game.spin_type_now];
}



int get_bonus_option() {
	return 0;
}

int reload_settings() {
	simulator.base_game.game_state.data->LoadData();
	simulator.ResetSim();
	return 0;
}
