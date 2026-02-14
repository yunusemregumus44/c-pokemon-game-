#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "pokemon.h"

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[]);
void initializeTypes(Type Types[]);
void initializeMoves(Move Moves[], Type Types[]);
void initializePokemons(Pokemon Pokemons[], Move Moves[], Type Types[]);
void initializePlayer(Pokemon Pokemons[], Player *player1, Player *player2);

#endif
