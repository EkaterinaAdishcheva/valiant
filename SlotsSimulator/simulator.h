#pragma once

#include "Valiant_1.h"

#define NUM_SIM 16

#define MAX_WIN (3000000)
#define MAX_SEQ (WIDTH + 1)
#define GROUPS_MAX 10000
#define GROUP_SEP 100000
#define MAXMULT 1


struct win_stat_t {
	UINT64 count;
	UINT64 value;
};
struct trigger_stat_t {
	UINT64 cases;
	UINT64 awards;
};
class Simulator_Type {
public:
	Game_Type base_game;

	UINT64 spin_count;
	UINT64 spin_count_by_type[SLOT_VARIANTS];
	UINT64 total_awarded_free_spins;
	UINT64 max_awarded_free_spins;

	UINT64 total_win;
	UINT64 total_paid;
	UINT64 balance;
	UINT64 total_win_by_type[SLOT_VARIANTS];

	win_stat_t win_stat[SYMBOLS][WIDTH + 1][SLOT_VARIANTS][MAXMULT + 1];
	win_stat_t win_scatters[WIDTH + 1][SLOT_VARIANTS];
	UINT64 spin_count_by_win[MAX_WIN][SLOT_VARIANTS];
	UINT64 seqs_count_by_win[MAX_WIN][SPIN_TYPES];
	UINT64 game_count_by_win[MAX_WIN];
	win_stat_t seqs_count_by_len[MAX_SEQ][SPIN_TYPES];
	UINT64 max_win_spin_by_type[SLOT_VARIANTS];
	UINT64 max_win_spin, max_win_game, max_win_base, max_win_free, max_win_seq;

	UINT64 group_win[GROUPS_MAX];
	UINT64 group_count, pos_in_group;

	trigger_stat_t bonus_trigger[SLOT_VARIANTS][SLOT_VARIANTS];

	Simulator_Type();
	Simulator_Type(Game_Type* game);
	~Simulator_Type() { ; }

	struct tm start;
	void OneSpinRun();
	void BulkSpinRun(UINT64 count);
	void ResetSim();
	void AnalyzeOneSpin();

	double CurrentRTP();
	double CurrentRTP(int slot_variant);
	double CurrentHitRate();
	double CurrentHitRate(int slot_variant);
	double CurrentAveragePay();
	double CurrentAveragePay(int slot_variant);
	double MeanPay();
	double VarPay();
	double StdDevPay();

	static UINT64 max_win_cap(UINT64 value);
	static UINT64 max_len_cap(UINT64 len);
};
extern Simulator_Type simulator;
extern Simulator_Type* simulators[NUM_SIM];