#ifndef GAME_H
#define GAME_H

#include "pokemon.h"

void game(Player *player1, Player *player2);
void Round(Player *player1, Player *player2);
void applyDamage(Pokemon *attacker, Pokemon *defender, Move move);

#endif
