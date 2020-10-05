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
	int i, j, pos;

	if ( spin_type_now == paid_spin && spin_type_prev == lighting_spin
		|| spin_type_now == lighting_spin && spin_type_prev == lighting_free_spin) {
		// Clear expanded wilds of frames
		for (i = 0; i < game_state.width; i++) {
			if (expanded_wild[i]) {
				memset(locked_frame[SuperType()].grid[i], false, sizeof(locked_frame[0].grid[0]));
				expanded_wild[i] = false;
			}
		}
	} else if (spin_type_now == free_respin && spin_type_prev == paid_spin
		|| spin_type_now == paid_spin && spin_type_prev == no_spin) {

		// Reset frames on entering free respins or on 1st spin
		memset(locked_frame[SuperType()].list, false, sizeof(locked_frame[0].list));
		memset(expanded_wild, false, sizeof(expanded_wild));
	}
	else if (spin_type_now == paid_spin && spin_type_prev == lighting_free_spin) {
		fill_arr(expanded_wild, false);
	}
	else if (spin_type_now == free_respin && spin_type_prev == lighting_free_spin) {
		for (i = 0; i < game_state.width; i++) {
			if (expanded_wild[i]) {
				expanded_wild[i] = false;
				fill_arr(locked_frame[SuperType()].grid[i], false);
			}
		}
	}
	else {
		// if no reset is done update locked frames to match wilds positions
		for (i = 0; i < game_state.width; i++) {
			if (!expanded_wild[i]) {
				for (j = 0; j < game_state.height[i]; j++) {
					if (screen.grid[i][j] == WI) {
						locked_frame[SuperType()].grid[i][j] = true;
					}
				}
			}
		}
	}

	for (i = 0; i < game_state.width; i++) {
		if (expanded_wild[i]) {
			fill_arr(locked_frame[SuperType()].grid[i], true);
			fill_arr(screen.grid[i], (int)WI);
		} else {
			pos = positions_reels[i] = (int)rnd.RANDOM(game_state.reel_length[i]);
			for (j = 0; j < game_state.height[i]; j++) {
				screen.grid[i][j] = game_state.reels[i][(pos + j) % game_state.reel_length[i]];
			}
		}
	}
		
	// Add expanded wild column on 12th free spin (if it has not occured earlier)
	int wild_count_max_column;
	if ((spin_type_now == free_respin)
		&& (free_spin_order[free_respin] == game_state.data->params.FreeSpins)
		&& !free_spin_lightning_ind) {

		int wild_count[WIDTH];

		for (i = 0; i < game_state.width; i++) {
			wild_count[i] = 0;
			for (j = 0; j < game_state.height[i]; j++) {
				if (screen.grid[i][j] == WI || locked_frame[SuperType()].grid[i][j]) {
					wild_count[i]++;
				}
			}
			if (wild_count[i] == game_state.height[i])
			{
				free_spin_lightning_ind = true;
				break;
			}
			if (i == 0) {
				wild_count_max_column = 0;
			} else if (wild_count[i] > wild_count[wild_count_max_column]) {
				wild_count_max_column = i;
			}
		}
		if (!free_spin_lightning_ind) {
			for (j = 0; j < game_state.height[wild_count_max_column]; j++) {
				if ((screen.grid[wild_count_max_column][j] != WI) && (!locked_frame[SuperType()].grid[wild_count_max_column][j])) {
					screen.grid[wild_count_max_column][j] = WI;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------

void Game_Type::LinesAnalysis(){
	int i, j, k;
	int win;
	int pos[WIDTH];
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
						matches_lenth[k] = i + 1;
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
		int act_multiplier = (multiplier_now == 0) ? 1 : multiplier_now;

		win = game_state.bet_unit * game_state.data->paytable[k][matches_lenth[k]] * act_multiplier;
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
				win_spin += win;
				winlines_desc[win_lines].is_win = true;
				winlines_desc[win_lines].length = matches_lenth[k];
				winlines_desc[win_lines].value = win;
				winlines_desc[win_lines].symbol = k;
				winlines_desc[win_lines].multiplier = act_multiplier;
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
	int i;
	int scatter_count = 0;

	if (spin_type_now != paid_spin) {
		return;
	}

	for (i = 0; i < game_state.cells; i++) {
		if (screen.list[i] == SC) {
			scatter_count++;
		}
	}

	if (scatter_count >= 3) {
		free_spins_awarded[free_respin] = game_state.data->params.FreeSpins;
		free_spin_lightning_ind = false;
	}
}

void Game_Type::Lightning() {
	int i, j;
	int count_expanded = 0;

	for (i = 0; i < game_state.width; i++) {
		if (expanded_wild[i]) {
			count_expanded += 1;
			continue;
		}
		int wild_count = 0, wild_only = 0;
		for (j = 0; j < game_state.height[i]; j++) {
			if (screen.grid[i][j] == WI || locked_frame[SuperType()].grid[i][j]) {
				wild_count++;
			}
			if (screen.grid[i][j] == WI) {
				wild_only++;
			}
		}
		if (wild_only != 0 && (spin_type_now == lighting_spin || spin_type_now == lighting_free_spin)) {
			free_spin_order[spin_type_now] = 0;
		}
		if (wild_count == game_state.height[i]) {
			expanded_wild[i] = true;

			if (spin_type_now == free_respin || spin_type_now == lighting_free_spin) {
				spin_type_next = lighting_free_spin;

				multiplier_next = multiplier_now +
					rnd.random_weighted_val(game_state.data->params.MultiplierWeights[0],
						game_state.data->params.MultiplierWeights[1],
						game_state.data->params_calc.MultiplierWeights,
						MULTIPLIER_OPTIONS);
			}
			else {
				spin_type_next = lighting_spin;
			}
			free_spins_awarded[spin_type_next] = game_state.data->params.LightningSpins;
			free_spin_order[spin_type_next] = 0;

			if (spin_type_now == free_respin) {
				free_spin_lightning_ind = true;
			}
		}
	}
	if (count_expanded == game_state.width) {
		free_spins_awarded[spin_type_now] = free_spin_order[spin_type_now];
	}
}

//----------------------------------------------------------------------------

void Game_Type::OneSpinExecute()  //executing of one game
{
// Changing next to current
	spin_type_prev = spin_type_now;
	spin_type_now = spin_type_next;
	multiplier_now = multiplier_next;

	game_state.SetSpinType(spin_type_now);
	spin_type_next = paid_spin;

	win_spin = 0;
	ñonsolation_ind = false;
	if (spin_type_now == paid_spin) {
		win_game = win_base = 0;
		memset(free_spins_awarded, 0, sizeof(free_spins_awarded));
		memset(free_spin_order, 0, sizeof(free_spin_order));
	}
	if (spin_type_now != lighting_free_spin) {
		win_free = 0;
	}
	if (spin_type_now == paid_spin || spin_type_now == free_respin) {
		win_seq = 0;
	}
	if (spin_type_now == free_respin) {
		free_spins_awarded[lighting_free_spin] = 0;
		free_spin_order[lighting_free_spin] = 0;
	}

	if (spin_type_now == paid_spin || spin_type_now == free_respin) {
		win_lightning = 0;
	}

	if (spin_type_now != paid_spin) {
		free_spin_order[spin_type_now] ++;
	}

	Drawings();
	LinesAnalysis();
	ScatterAnalysis();
	Lightning();

	if (spin_type_now == lighting_spin || spin_type_now == lighting_free_spin)
	{
		win_lightning += win_spin;

		if ((win_lightning == 0) && (free_spin_order[spin_type_now] >= game_state.data->params.LightningSpins))
		{
			win_lightning = win_spin = game_state.data->params.ConsolationPrize * game_state.bet_game;
			ñonsolation_ind = true;
		}
	}


	win_game += win_spin;
	win_seq += win_spin;
	if (spin_type_now == paid_spin || spin_type_now == lighting_spin) {
		win_base += win_spin;
	}
	if (spin_type_now == free_respin || spin_type_now == lighting_free_spin) {
		win_free += win_spin;
	}


	for (int j = 3; j > 0; j--) {
		if (free_spins_awarded[j] > free_spin_order[j]) {
			spin_type_next = j;
			break;
		}
	}

	if (spin_type_next != lighting_free_spin) {
		multiplier_next = 0;
	}
}
//----------------------------------------------------------------------------
