#pragma once

/*
Cornerstone
*/

/*
Base definitions
*/
#define SYMBOLS  13

enum Symbols {
	WI = 10, // wild
	SC = 11, // scatter
	LF = 12 // locked frame
};

#define SPIN_TYPES 4
enum Spin_Type {
	paid_spin = 0,
	lighting_spin = 1,
	free_respin = 2,
	lighting_free_spin = 3,
};

#define REEL_OPTIONS 1
// Number of different reel set
#define REEL_VARIANTS 3
// Number of different game states: spin types x reel variants
#define SLOT_VARIANTS SPIN_TYPES

#define WIDTH  5
#define HEIGHT 4
#define PAYLINES  1024
// 4096 game, all paylines are assessed
#define REELLENMAX 1000

#define DEFAULT_BET 1

#define MULTIPLIER_OPTIONS 8

//------------------------------------------

/*
Win line description struct
*/
struct LineDescription {
//describes the one line from the point of view of winning
	bool is_win;    // winning or not
	int length;     // sequence length
	int symbol;     // symbol creating a winning
	UINT64 value;   // value of win
	int where_symbols[WIDTH];
	int multiplier; // applied multiplier
};
//------------------------------------------

/*
Game setup
*/

/*
 * Class List
 */
//class Game_Type;
//class Game_State_Type;
//class Game_Data_Type;
//class Game_Params_Type;
//class Game_Params_Calc_Type;

// Game Misc Params: all stuff expect big arrays (like reels)
class Game_Params_Type {
public:
	int MultiplierWeights[2][MULTIPLIER_OPTIONS];

	Game_Params_Type() { ; }
	~Game_Params_Type() { ; }
};
// Game Precalculated Params
class Game_Params_Calc_Type {
public:
	int MultiplierWeights;

	Game_Params_Calc_Type() { ; }
	~Game_Params_Calc_Type() { ; }

	void CalculateParams(Game_Params_Type * params);
};
// Game Data: reelset, paytable + params from abovementioned class
class Game_Data_Type {
public:
	// Pay table
	int paytable[SYMBOLS][WIDTH + 1];

	// Symbols on reels
	int reels[REEL_VARIANTS][WIDTH][REELLENMAX];
	int reel_length[REEL_VARIANTS][WIDTH];
	int reel_spec[SYMBOLS][REEL_VARIANTS][WIDTH];

	Game_Data_Type() { LoadData(); }
	~Game_Data_Type() { ; }
	void LoadData();

	Game_Params_Type params;
	Game_Params_Calc_Type params_calc;
};
// Game State: current scree size, reels, spin type etc
class Game_State_Type {
public:
	int width;
	int height[WIDTH];
	int cells;
	int units_in_game; // (fixed)

	int (*reels)[REELLENMAX];
	int * reel_length;

	Game_State_Type();
	Game_State_Type(Game_Data_Type * data);
	void SetSpinType(int spin_type);
	~Game_State_Type();
	void SetBase();

	int bet_game;    // bet per game
	int bet_unit;    // stake per line or other unit
	void SetBet(int bet);

	Game_Data_Type * data;
	bool my_data;
};
//------------------------------------------

/*
Class implementing main functionality of the game
*/
class Game_Type {
private:
	SlotRandom rnd;
public:
		Game_Type() : game_state(), rnd() {
			SetBase();
		};
		Game_Type(Game_Data_Type * data) : game_state(data), rnd() {
			SetBase();
		};
		~Game_Type(){ ; }

		void SetBase();  //setting base parameters
		Game_State_Type game_state;
		void SetBet(int bet) { game_state.SetBet(bet); }  //setting bet per game

		void Drawings();               // drawings
		int positions_reels[WIDTH];    // reels positions
		union {
			int grid[WIDTH][HEIGHT]; 
			int list[(WIDTH)*(HEIGHT)]; 
		} screen; // symbols on the grid. two ways to access

		bool expanded_wild[WIDTH];

		int multiplier_now;
		int multiplier_next;

		LineDescription winlines_desc[PAYLINES];
		int win_lines;

		void LinesAnalysis(); //calculate base winnings
		void Lightning(); //lightning feature
		void ScatterAnalysis(); //calculate scatters

		// winnings
		UINT64 win_spin;    //summary of wins for current spin
		UINT64 win_seq;     //summary of wins for sequence of feature spins
		UINT64 win_base;    //summary of wins for base game (including cascades)
		UINT64 win_game;	// total win for the game
		UINT64 win_lightning;	// total win for the lightning respin
		bool free_spin_lightning_ind; // indicator that free spins lead to lightning game 


		// Spin mode spec
		int spin_type_now, spin_type_next;        //paid_spin / free_spin
		bool IsBaseSpin();
		bool NextBaseSpin();
		int GameIdx();
		int NextIdx();

		// Free spins counters
		int free_spins_order[SPIN_TYPES];    //remaining free spins number
		int free_spin_current[SPIN_TYPES];    //current free spins number

		bool IsNewBonusAwarded();
		bool IsLastInSequence();
		bool IsCollectingSpin();

		// Major spin iteration method
		void OneSpinExecute();  //execute one spin

};



