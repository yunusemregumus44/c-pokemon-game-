#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char defenderType[20];
    float multiplier;
} TypeEffect;

typedef struct {
    char name[20];
    TypeEffect effects[19]; // 18 + None
} Type;

typedef enum {
    PHYSICAL,
    SPECIAL
} MoveCategory;

typedef struct {
    char name[30];
    Type type;
    MoveCategory category;
    int power;
} Move;

typedef struct {
    char name[30];
    Type types[2];
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    Move moves[4];
} Pokemon;

typedef struct {
    char name[30];
    Pokemon pokemons[6];
    int currentIndex;
} Player;

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[]);
void initializeTypes(Type Types[]);
void initializeMoves(Move Moves[], Type Types[]);
void initializePokemons(Pokemon Pokemons[], Move Moves[], Type Types[]);
void initializePlayer(Pokemon Pokemons[], Player *player1, Player *player2);
void game(Player *player1, Player *player2);
void Round(Player *player1, Player *player2);
void applyDamage(Pokemon *attacker, Pokemon *defender, Move move);

#endif
