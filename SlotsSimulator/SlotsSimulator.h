#pragma once

#ifdef SLOTSSIMULATOR_EXPORTS
#define SLOTSSIMULATOR_API __declspec(dllexport)
#else
#define SLOTSSIMULATOR_API __declspec(dllimport)
#endif

//
// DLL exported function
//
extern "C" SLOTSSIMULATOR_API int reload_settings();

extern "C" SLOTSSIMULATOR_API int one_spin_run();
extern "C" SLOTSSIMULATOR_API int bulk_run(UINT64 count, int thread);
extern "C" SLOTSSIMULATOR_API int get_max_threads();
extern "C" SLOTSSIMULATOR_API int bulk_agg_stat();
extern "C" SLOTSSIMULATOR_API int bulk_log_results(char * filename, int maxlen,
	const char * gamename, int gamename_len);
extern "C" SLOTSSIMULATOR_API int get_symbol(int line, int reel);
extern "C" SLOTSSIMULATOR_API int get_cell_tag(int line, int reel);
extern "C" SLOTSSIMULATOR_API int get_spin_message(char * message, int max_len);
extern "C" SLOTSSIMULATOR_API UINT64 get_total_paid();
extern "C" SLOTSSIMULATOR_API UINT64 get_total_win();
extern "C" SLOTSSIMULATOR_API UINT64 get_spin_win();
extern "C" SLOTSSIMULATOR_API int reset_sim();
extern "C" SLOTSSIMULATOR_API int reset_sim_arr();

extern "C" SLOTSSIMULATOR_API int win_line_symbol(int win_line_id);
extern "C" SLOTSSIMULATOR_API int win_line_is_win(int win_line_id);
extern "C" SLOTSSIMULATOR_API int win_line_length(int win_line_id);
extern "C" SLOTSSIMULATOR_API UINT64 win_line_value(int win_line_id);
extern "C" SLOTSSIMULATOR_API int win_line_where(int win_line_id, int reel);
extern "C" SLOTSSIMULATOR_API int get_win_line_maxcount();

extern "C" SLOTSSIMULATOR_API int get_scatter_win();
extern "C" SLOTSSIMULATOR_API int get_scatters_count();

extern "C" SLOTSSIMULATOR_API double get_rtp();
extern "C" SLOTSSIMULATOR_API double get_hit_rate();

extern "C" SLOTSSIMULATOR_API UINT64 get_games_count();
extern "C" SLOTSSIMULATOR_API UINT64 get_games_count_arr();
extern "C" SLOTSSIMULATOR_API UINT64 get_free_spin_win();
extern "C" SLOTSSIMULATOR_API UINT64 get_free_spin_order();

extern "C" SLOTSSIMULATOR_API int get_width();
extern "C" SLOTSSIMULATOR_API int get_height(int reel);
extern "C" SLOTSSIMULATOR_API int get_spin_type();
extern "C" SLOTSSIMULATOR_API int get_spin_type_next();

extern "C" SLOTSSIMULATOR_API int set_bet(int bet);
extern "C" SLOTSSIMULATOR_API INT64 get_balance();
extern "C" SLOTSSIMULATOR_API int set_balance(UINT64 _balance);

extern "C" SLOTSSIMULATOR_API UINT64 get_awarded_free_spins();


