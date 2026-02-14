#include "pokemon.h"

int findNextAlivePokemon(Player *player)
{
    for (int i = 0; i < 6; i++)
    {
        if (player->pokemons[i].currentHP > 0)
        {
            return i;
        }
    }
    return -1;
}

void game(Player *player1, Player *player2)
{

    // Game, iki Playerın aktif Pokémon’larını alır,
    // biri bitene kadar savaşı döndürür.
    printf("Game started!\n");

    while ((*player1).currentIndex < 6 && (*player2).currentIndex < 6)
    {

        printf("\n================ NEW ROUND ================\n");
        printf("Player 1 current Pokemon: %s (%d/%d HP)\n",
               player1->pokemons[player1->currentIndex].name,
               player1->pokemons[player1->currentIndex].currentHP,
               player1->pokemons[player1->currentIndex].maxHP);

        printf("Player 2 current Pokemon: %s (%d/%d HP)\n",
               player2->pokemons[player2->currentIndex].name,
               player2->pokemons[player2->currentIndex].currentHP,
               player2->pokemons[player2->currentIndex].maxHP);
        Round(player1, player2);

        if (player1->pokemons[player1->currentIndex].currentHP <= 0)
        {
            int next = findNextAlivePokemon(player1);
            if (next == -1)
            {
                printf("Player 2 won!\n");
                return;
            }
            player1->currentIndex = next;
            printf("Player 1 - Your Pokémon fainted, automatically changed to: %s\n",
                   player1->pokemons[player1->currentIndex].name);
        }
        if (player2->pokemons[player2->currentIndex].currentHP <= 0)
        {
            int next = findNextAlivePokemon(player2);
            if (next == -1)
            {
                printf("Player 1 won!\n");
                return;
            }
            player2->currentIndex = next;
            printf("Player 2 - Your Pokémon fainted, automatically changed to: %s\n",
                   player2->pokemons[player2->currentIndex].name);
        }
    }
    if (player1->currentIndex == 6)
    {
        printf("Player 2 won!\n");
    }
    else
    {
        printf("Player 1 won!\n");
    }
}

void Round(Player *player1, Player *player2)
{

    int choice1;
    int choice2;
    int moveChoice1 = -1;
    int moveChoice2 = -1;
    //-1 değerini, o round’da bir move seçilmediğini belirtmek için kullandım;
    // çünkü geçerli indeksler 0’dan başlıyor.

    printf("Player1:\n");
    do
    {
        printf("1 - Attack\n2 - Change Pokemon\n");
        scanf("%d", &choice1);
        if (choice1 < 1 || choice1 > 2)
            printf("Invalid choice! Please enter 1 or 2.\n");
    } while (choice1 < 1 || choice1 > 2);

    if (choice1 == 1)
    {
        Pokemon *p = &player1->pokemons[player1->currentIndex];

        printf("Choose a move:\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d - %-12s", i + 1, p->moves[i].name);
            if (i % 2 == 1)
                printf("\n");
        }
        printf("Please select a move: \n");

        do
        {
            scanf("%d", &moveChoice1);
            if (moveChoice1 < 1 || moveChoice1 > 4)
                printf("Invalid move! Please select a number between 1 and 4: ");
        } while (moveChoice1 < 1 || moveChoice1 > 4);
        moveChoice1--;
    }

    else if (choice1 == 2)
    {
        int change;
        int realIndex[6];
        int count = 0;

        printf("Choose a Pokemon:\n");
        for (int i = 0; i < 6; i++)
        {
            if (player1->pokemons[i].currentHP > 0)
            {
                count++;
                printf("%d - %-12s", count, player1->pokemons[i].name); // yan yana
                if (count % 2 == 0)
                    printf("\n"); // her iki Pokémon'dan sonra satır atla
                realIndex[count - 1] = i;
            }
        }
        printf("Please select a Pokemon: \n");

        do
        {
            scanf("%d", &change);
            if (change < 1 || change > count)
                printf("Invalid choice! Please select a number between 1 and %d: ", count);
        } while (change < 1 || change > count);

        player1->currentIndex = realIndex[change - 1];
    }

    printf("Player2:\n");
    do
    {
        printf("1 - Attack\n  2- Change Pokemon\n");
        scanf("%d", &choice2);
        if (choice2 < 1 || choice2 > 2)
            printf("Invalid choice! Please enter 1 or 2.\n");
    } while (choice2 < 1 || choice2 > 2);

    if (choice2 == 1)
    {
        Pokemon *p = &player2->pokemons[player2->currentIndex];

        printf("Choose a move:\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d - %-12s", i + 1, p->moves[i].name);
            if (i % 2 == 1)
                printf("\n");
        }
        printf("Please select a move: \n");

        do
        {
            scanf("%d", &moveChoice2);
            if (moveChoice2 < 1 || moveChoice2 > 4)
                printf("Invalid move! Please select a number between 1 and 4: ");
        } while (moveChoice2 < 1 || moveChoice2 > 4);
        moveChoice2--;
    }
    else if (choice2 == 2)
    {
        int change;
        int realIndex[6];
        int count = 0;

        printf("Choose a Pokemon:\n");
        for (int i = 0; i < 6; i++)
        {
            if (player2->pokemons[i].currentHP > 0)
            {
                count++;
                printf("%d - %-12s", count, player2->pokemons[i].name);
                if (count % 2 == 0)
                    printf("\n");
                realIndex[count - 1] = i;
            }
        }
        printf("Please select a Pokemon: \n");

        do
        {
            scanf("%d", &change);
            if (change < 1 || change > count)
                printf("Invalid choice! Please select a number between 1 and %d: ", count);
        } while (change < 1 || change > count);

        player2->currentIndex = realIndex[change - 1];
    }

    Pokemon *p1 = &player1->pokemons[player1->currentIndex];
    Pokemon *p2 = &player2->pokemons[player2->currentIndex];

    /* İkisi de attack seçtiyse */
    if (choice1 == 1 && choice2 == 1)
    {

        if (p1->speed > p2->speed)
        {
            applyDamage(p1, p2, p1->moves[moveChoice1]);

            if (p2->currentHP > 0)
            {
                applyDamage(p2, p1, p2->moves[moveChoice2]);
            }
        }
        else
        {
            applyDamage(p2, p1, p2->moves[moveChoice2]);

            if (p1->currentHP > 0)  
            {
                applyDamage(p1, p2, p1->moves[moveChoice1]);
            }
        }
    }

    else if (choice1 == 1 && choice2 == 2)
    {
        applyDamage(p1, p2, p1->moves[moveChoice1]);
    }

    else if (choice1 == 2 && choice2 == 1)
    {
        applyDamage(p2, p1, p2->moves[moveChoice2]);
    }
}

void applyDamage(Pokemon *attacker, Pokemon *defender, Move move)
{
    int atk, def;
    float typeEffect1 = 1.0f;
    float typeEffect2 = 1.0f;
    float STAB = 1.0f;

    // Kategoriye göre hangi stat kullanılacak?
    if (move.category == PHYSICAL) {
        atk = attacker->attack;
        def = defender->defense;
    } else {
        atk = attacker->spAtk;
        def = defender->spDef;
    }

    // Tip etkilerini kontrol et
    for (int i = 0; i < 19; i++) {
        if (strcmp(move.type.effects[i].defenderType, defender->types[0].name) == 0) {
            typeEffect1 = move.type.effects[i].multiplier;
            break;
        }
    }
    
    // İkinci tip "None" değilse onu da hesapla
    if (strcmp(defender->types[1].name, "None") != 0) {
        for (int i = 0; i < 19; i++) {
            if (strcmp(move.type.effects[i].defenderType, defender->types[1].name) == 0) {
                typeEffect2 = move.type.effects[i].multiplier;
                break;
            }
        }
    }

    // STAB kontrolü
    if (strcmp(move.type.name, attacker->types[0].name) == 0 ||
        strcmp(move.type.name, attacker->types[1].name) == 0) {
        STAB = 1.5f;
    }

    /* Hasar hesaplama */
    float damage = move.power * ((float)atk / (float)def) * typeEffect1 * typeEffect2 * STAB;

    defender->currentHP -= (int)damage;
    if (defender->currentHP < 0) defender->currentHP = 0;

    // moveChoice yerine doğrudan move.name kullanıyoruz
    printf("%s used %s!\n", attacker->name, move.name);
    printf("%s took %d damage. Current HP: %d/%d\n",
           defender->name, (int)damage, defender->currentHP, defender->maxHP);
}