#include "stdafx.h"
#include <stdio.h>
#include "utils.h"
#include "Valiant_1.h"

/*
Cornerstone
*/


/*
Game setup
*/
//----------------------------------------------------------------------

/*
Game state
*/
Game_State_Type::Game_State_Type() {
	data = new Game_Data_Type();
	my_data = true;
	SetBase();
}
Game_State_Type::Game_State_Type(Game_Data_Type * data) {
	this->data = data;
	my_data = false;
	SetBase();
}
Game_State_Type::~Game_State_Type() {
	if (my_data) {
		delete data;
	};
}

void Game_State_Type::SetBase() {
	units_in_game = 10;
	width = WIDTH;
	cells = 0;
	for (int j = 0; j < width; j++) {
		height[j] = HEIGHT;
		cells += height[j];
	}

	SetSpinType(paid_spin);
	SetBet(DEFAULT_BET);
}
void Game_State_Type::SetSpinType(int spin_type) {
	width = WIDTH;
	int reel = spin_type;
	if (reel < REEL_VARIANTS) {
		reels = data->reels[reel];
		reel_length = data->reel_length[reel];
	}
}
void Game_State_Type::SetBet(int bet_unit) {
	this->bet_unit = bet_unit;
	this->bet_game = bet_unit * units_in_game;
}

/*
Class Game_Type
*/
void Game_Data_Type::LoadData() {
	int i, j, k;
	// read reels
	int tmp[REELLENMAX * (1 + REEL_VARIANTS * WIDTH)], idx = 0;
	read_int_file(L"reels.txt", tmp);
	memset(reel_spec, 0, sizeof(reel_spec));
	for (i = 0; i < REEL_VARIANTS; i++) {
		for (j = 0; j < WIDTH; j++) {
			reel_length[i][j] = tmp[idx++];
			for (k = 0; k < reel_length[i][j]; k++) {
				reels[i][j][k] = tmp[idx++];
				reel_spec[reels[i][j][k]][i][j] += 1;
			}
		}
	}

	// read paytable
	read_int_file(L"paytable.txt", &paytable[0][0]);

	// read free spin weights and counts
	read_int_file(L"params.txt", (int*)&params);

	// pre calculated sums
	params_calc.CalculateParams(&params);
}

void Game_Type::SetBase() {
	game_state.SetBase();

	win_lines = 0;
	win_spin = win_seq = win_base = win_game = 0;
	spin_type_next = paid_spin;
	spin_type_now = spin_type_prev = no_spin;

	fill_arr(free_spins_awarded, 0);
	fill_arr(free_spin_order, 0);
	fill_arr(locked_frame[0].list, false);
	fill_arr(locked_frame[1].list, false);
	fill_arr(expanded_wild, false);
	
	win_lightning = 0;
	free_spin_lightning_ind = false;
	multiplier_now = multiplier_next = 0;
}
//----------------------------------------------------------------------

int Game_Type::GameIdx() {
	return spin_type_now;
}
int Game_Type::NextIdx() {
	return spin_type_next;
}
bool Game_Type::IsBaseSpin() {
	return spin_type_now == paid_spin;
}
bool Game_Type::NextBaseSpin() {
	return spin_type_next == paid_spin;
}
bool Game_Type::IsLastInSequence() {
	return spin_type_next == paid_spin && spin_type_now == lighting_spin;
}
int Game_Type::SuperType() {
	return spin_type_now == paid_spin || spin_type_now == lighting_spin
		? 0 : 1;
}


//----------------------------------------------------------------------

bool Game_Type::IsNewBonusAwarded() {
	return spin_type_now == paid_spin && spin_type_next != paid_spin
		|| spin_type_now == free_respin && spin_type_next == lighting_free_spin;
}

bool Game_Type::IsCollectingSpin() {
	return false;
/*	return spin_type_now == lighting_spin && spin_type_next == lighting_spin
		|| spin_type_now == lighting_free_spin && spin_type_next == lighting_free_spin;
*/
}
