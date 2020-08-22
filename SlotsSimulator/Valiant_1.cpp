#include "stdafx.h"
#include <stdio.h>
#include "utils.h"
#include "Valiant_1.h"

/*
Valiant
*/
void Game_Params_Calc_Type::CalculateParams(Game_Params_Type * params) {
	// pre calculated sums
	memset(this, 0, sizeof(Game_Params_Calc_Type));
	for (int j = 0; j < MULTIPLIER_OPTIONS; j++) {
		MultiplierWeights += params->MultiplierWeights[1][j];
	}
}

void Game_Type::Drawings() {
	int i, j, pos, wi_count;

	if (free_spin_current[paid_spin] == 1) {
		memset(expanded_wild, false, sizeof(expanded_wild));
		memset(screen.list, 0, sizeof(screen.list));
	}

	for (i = 0; i < game_state.width; i++) {
		for (j = 0; j < game_state.height[i]; j++) {
			if (!expanded_wild[i]) {
				if (screen.grid[i][j] == WI) {
					screen.grid[i][j] = LF;
				}
			}
		}
	}

	for (i = 0; i < game_state.width; i++) {
		pos = (int)rnd.RANDOM(game_state.reel_length[i]);
		positions_reels[i] = pos;
		for (j = 0; j < game_state.height[i]; j++) {
			if (expanded_wild[i]) {
				screen.grid[i][j] = WI;
				continue;
			}
			if (screen.grid[i][j] != LF) {
				screen.grid[i][j] = game_state.reels[i][(pos + j) % game_state.reel_length[i]];
			}
		}
	}
	free_spin_current[paid_spin] = 0;
	if ((spin_type_now == free_respin) && (free_spin_current[free_respin] == 12) && !free_spin_lightning_ind)
	{
		int wild_count[WIDTH];


		for (i = 0; i < game_state.width; i++) {
			if (!expanded_wild[i]) {
				wild_count[i] = 0;
				for (j = 0; j < game_state.height[i]; j++) {
					if (screen.grid[i][j] == WI || screen.grid[i][j] == LF) {
						wild_count[i]++;
					}
				}
				if (wild_count[i] == game_state.height[i])
				{
					free_spin_lightning_ind = true;
					break;
				}
			}
		}
		if (!free_spin_lightning_ind) {
			int wild_count_max_column;
			wild_count_max_column = 0;
			for (i = 1; i < game_state.width; i++) {
				if (wild_count[i] > wild_count[wild_count_max_column])
				{
					wild_count_max_column = i;
				}
			}
			for (j = 0; j < game_state.height[wild_count_max_column]; j++) {
				if ((screen.grid[wild_count_max_column][j] != WI) && (screen.grid[wild_count_max_column][j] != LF)) {
					screen.grid[wild_count_max_column][j] = WI;
				}
			}

		}

	}
}
//----------------------------------------------------------------------------

void Game_Type::LinesAnalysis(){
	int i, j, k;
	int win_symb;
	int win, win_cur;
	int pos[WIDTH];
	bool used[HEIGHT];
	int matches_count[SYMBOLS][WIDTH];
	int matches[SYMBOLS][WIDTH][HEIGHT];
	int matches_lenth[SYMBOLS];
	int wild_count[WIDTH];

	win_lines = 0;

	memset(wild_count, 0, sizeof(wild_count));
	memset(matches_lenth, 0, sizeof(matches_lenth));
	memset(matches_count, 0, sizeof(matches_count));

	for (i = 0; i < game_state.width; i++)
	{
		for (j = 0; j < game_state.height[i]; j++) {
			if (screen.grid[i][j] == WI) {
				wild_count[i] ++;
			}
		}
	}

	for (i = 0; i < game_state.width; i++) {
		for (k = 0; k < SYMBOLS; k++) {
			for (j = 0; j < game_state.height[i]; j++)
			{
				if (screen.grid[i][j] == k) {
					matches_lenth[k] = 1;
				}
			}
		}
		if (wild_count[i] == 0) { break; }
	}

	for (k = 0; k < SYMBOLS; k++) {
		if (matches_lenth[k] > 0) {
			for (i = 0; i < game_state.width; i++) {
				for (j = 0; j < game_state.height[i]; j++) {
					if (screen.grid[i][j] == k || screen.grid[i][j] == WI) {
						matches[k][i][matches_count[k][i]] = j;
						matches_count[k][i]++;
						matches_lenth[k] = i+1;
					}
				}
				if (matches_count[k][i] == 0) {
					break;
				}
			}
		}
	}

	
	for (k = 0; k < SYMBOLS; k++) {
		if (matches_lenth[k] == 0) {
			continue;
		}
		if (game_state.data->paytable[k][matches_lenth[k]] == 0) {
			continue;
		}
		int multiplier = (multiplier_now == 0) ? 1 : multiplier_now;

		win = game_state.bet_unit * game_state.data->paytable[k][matches_lenth[k]] * multiplier;
		memset(pos, 0, sizeof(pos));
		
	
		while (1) {
			bool specific_symbpol = false;
			for (j = 0; j < matches_lenth[k]; j++) {
				if (screen.grid[j][matches[k][j][pos[j]]] == k) {
					specific_symbpol = true;
					break;
				}
			}

			if (specific_symbpol) {
				win_cur = win;
				win_spin += win_cur;
				winlines_desc[win_lines].is_win = true;
				winlines_desc[win_lines].length = matches_lenth[k];
				winlines_desc[win_lines].value = win_cur;
				winlines_desc[win_lines].symbol = k;
				winlines_desc[win_lines].multiplier = multiplier;
				for (j = 0; j < matches_lenth[k]; j++) {
					winlines_desc[win_lines].where_symbols[j] = matches[k][j][pos[j]];
				}

				win_lines += 1;
			}

			//moving to next line
			j = matches_lenth[k] - 1;
			while (j >= 0 && pos[j] == matches_count[k][j] - 1) {
				pos[j] = 0;
				j--;
			}
			if (j < 0) {
				break;
			}
			pos[j]++;
		}
	}
}

void Game_Type::ScatterAnalysis() {
	int i, j, k;
	int scatter_count = 0;

	if (spin_type_now != lighting_spin) {
		for (i = 0; i < game_state.width; i++)
		{
			for (j = 0; j < game_state.height[i]; j++) {
				if (screen.grid[i][j] == SC) {
					scatter_count++;
				}
			}
		}

		if (scatter_count >= 3)
		{
			free_spins_order[free_respin] = 12;
			free_spin_current[free_respin] = 0;
			free_spin_current[paid_spin] = 1;
			spin_type_next = free_respin;
			free_spin_lightning_ind = false;
		}
	}
}

void Game_Type::Lightning() {
	int i, j;

	int wild_count;

	for (i = 0; i < game_state.width; i++) {
		if (!expanded_wild[i]) {
			wild_count = 0;
			for (j = 0; j < game_state.height[i]; j++) {
				if (screen.grid[i][j] == WI || screen.grid[i][j] == LF) {
					wild_count++;
				}
			}
			if (wild_count == game_state.height[i])
			{
				if (spin_type_now == free_respin || spin_type_now == lighting_free_spin) {
					expanded_wild[i] = true;
					free_spins_order[lighting_free_spin] = 3;
					free_spin_current[lighting_free_spin] = 0;
					spin_type_next = lighting_free_spin;
					win_lightning = 0;
				}
				if (spin_type_now == paid_spin || spin_type_now == lighting_spin) {
					expanded_wild[i] = true;
					free_spins_order[lighting_spin] = 3;
					free_spin_current[lighting_spin] = 0;
					spin_type_next = lighting_spin;
					win_lightning = 0;
				}
				if (spin_type_now == free_respin)
				{
					free_spin_lightning_ind = true;
				}
				if (spin_type_now == free_respin || spin_type_now == lighting_free_spin)
				{
					multiplier_next = multiplier_now + 
						rnd.random_weighted_val(game_state.data->params.MultiplierWeights[0],
						game_state.data->params.MultiplierWeights[1],
							game_state.data->params_calc.MultiplierWeights, MULTIPLIER_OPTIONS);
				}
			}
		}
	}

}

//----------------------------------------------------------------------------

void Game_Type::OneSpinExecute()  //executing of one game
{
// Changing next to current
	spin_type_now = spin_type_next;
	multiplier_now = multiplier_next;
	game_state.SetSpinType(spin_type_now);
	spin_type_next = paid_spin;

	if (free_spins_order[lighting_spin] == 0) {
		free_spin_current[lighting_spin] = 0;
	}

	if (free_spins_order[free_respin] == 0) {
		free_spin_current[free_respin] = 0;
	}

	if (free_spins_order[lighting_free_spin] == 0) {
		free_spin_current[lighting_free_spin] = 0;
	}

	if (spin_type_now != lighting_free_spin) {
		multiplier_now = 0;
	}

	win_spin = 0;

	if (spin_type_now != paid_spin)
	{
		free_spin_current[spin_type_now] ++;
	}

	Drawings();
	LinesAnalysis();
	ScatterAnalysis();
	Lightning();

	if (spin_type_now == lighting_spin)
	{
		win_lightning += win_spin;
		if ((win_lightning == 0) && (free_spin_current[lighting_spin] >= 3))
		{
			free_spins_order[lighting_spin] ++;
		}
	}

	if (spin_type_now == lighting_free_spin)
	{
		win_lightning += win_spin;
		if ((win_lightning == 0) && (free_spin_current[lighting_free_spin] >= 3))
		{
			free_spins_order[lighting_free_spin] ++;
		}
	}

	win_game = 0;

	if (spin_type_now == paid_spin) {
		win_seq = win_game = 0;
	}

	if (free_spin_current[free_respin] < free_spins_order[free_respin]) {
		spin_type_next = free_respin;
	}

	if (free_spin_current[free_respin] < free_spins_order[free_respin]) {
		if (spin_type_next == paid_spin) {
			free_spin_current[paid_spin] = 1;
			multiplier_next = 0;
		}
	}

	if (free_spin_current[lighting_spin] < free_spins_order[lighting_spin]) {
		spin_type_next = lighting_spin;
	}

	if (free_spin_current[lighting_free_spin] < free_spins_order[lighting_free_spin]) {
		spin_type_next = lighting_free_spin;
	}

	if (spin_type_next == paid_spin && spin_type_now != paid_spin) {
		free_spin_current[paid_spin] = 1;
		multiplier_next = 0;
	}
	
	win_seq += win_spin;
	// spin_type_next is paid_spin or it is set by LightningAnalysis()
}
//----------------------------------------------------------------------------
