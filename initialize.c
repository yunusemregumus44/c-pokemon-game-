#include "initialize.h"
#include "pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[]){

    initializeTypes(Types);
    initializeMoves(Moves, Types);
    initializePokemons(Pokemons, Moves, Types);
}

void initializeTypes(Type Types[]){

    FILE *file=fopen("types.txt","r");
    if(file ==NULL){
        printf("types.txt could not be opened\n");
        exit(1);
    }

    for(int i=0; i<18; i++){
        fscanf(file,"%s",Types[i].name);

        for(int j=0; j<18; j++){
         fscanf(file,"%s %f" ,
            Types[i].effects[j].defenderType,
            &Types[i].effects[j].multiplier);    
        }
        strcpy(Types[i].effects[18].defenderType, "None");
        Types[i].effects[18].multiplier = 1.0f;//None tipi çarpma işlemini etkilememesi için 
        //multiplier değeri 1 olarak(multiplier değişkeni float oldugu icin f) atanmıştır.
        //defenderType bir char dizisi olduğu için string atamasını strcpy ile yaptım.
    }

    fclose(file);
}

void initializeMoves(Move Moves[],Type Types[]){
    FILE *file = fopen("moves.txt","r");
    if(file==NULL){
        printf("moves.txt could not be opened\n");
        exit(1);
    }
    char line[100];
    for (int i = 0; i < 486; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;

        char typeName[20];
        char categoryStr[20];

        // Satırı parçalara ayırıyoruz
        sscanf(line, "%s %s %s %d", Moves[i].name, typeName, categoryStr, &Moves[i].power);

        // Type eşlemesi
        for (int j = 0; j < 18; j++) {
            if (strcmp(typeName, Types[j].name) == 0) {
                Moves[i].type = Types[j];
                break;
     }
        } 
//Move tipini string olarak değil, Types dizisindeki indeks olarak tuttum.
//Bu sayede damage hesaplamasında doğrudan typeEffect’e erişebiliyorum.

    if(strcmp(categoryStr,"Physical")==0){
        Moves[i].category = PHYSICAL;
        } else {
            Moves[i].category = SPECIAL;
        }
    if (strlen(Moves[i].name) == 0) {
            printf("Warning: Move %d has empty name!\n", i);
        }
    }
    fclose(file);
    }
        
    void initializePokemons(Pokemon Pokemons[],Move Moves[],Type Types[]){
    FILE *file = fopen("pokemon.txt","r");
    if(file==NULL){
        printf("pokemon.txt could not be opened\n");
        exit(1);
    }   
    int i;
    for(i=0; i<1015;i++){    

       char type1Name[20];
       char type2Name[20];

        fscanf(file,"%s %s %s %d %d %d %d %d %d ",
            Pokemons[i].name,type1Name ,type2Name,
            &Pokemons[i].maxHP,&Pokemons[i].attack,
            &Pokemons[i].defense,&Pokemons[i].spAtk,
            &Pokemons[i].spDef,&Pokemons[i].speed);

    Pokemons[i].currentHP= Pokemons[i].maxHP;

    for (int t = 0; t < 18; t++) {
        if (strcmp(type1Name, Types[t].name) == 0) {
            Pokemons[i].types[0] = Types[t];
            break;
            }
        }

    if (strcmp(type2Name, "-") == 0) {
            strcpy(Pokemons[i].types[1].name, "None");
            for (int k = 0; k < 19; k++) {
                Pokemons[i].types[1].effects[k] = Types[0].effects[k]; // None type effect
            }
        } else {
            for (int t = 0; t < 18; t++) {
                if (strcmp(type2Name, Types[t].name) == 0) {
                    Pokemons[i].types[1] = Types[t];
                 break;
     }
            }
        }

    int used[486] = {0};
            for (int m = 0; m < 4; m++) {
            int r;
            do {
                r = rand() % 486;
            } while (used[r] || strlen(Moves[r].name) == 0); // boş move seçme
            used[r] = 1;
            Pokemons[i].moves[m] = Moves[r];
        }
}
    fclose(file);
}

void initializePlayer(Pokemon Pokemons[],Player *player1, Player *player2){
    //initializePlayer fonksiyonu, oyuncunun ismini ayarlar, rastgele ve benzersiz 6 Pokémon atar
    // ve oyunun başlangıcı için currentIndex’i sıfırlar.

    int used1[1015]= {0};
    for(int i=0; i<6;i++){
        int r;
        do{
            r=rand()%1015;

        }while(used1[r]);

        used1[r]=1;
        player1->pokemons[i]=Pokemons[r];
    }
    player1->currentIndex = 0;

    int used2[1015]= {0};
    for(int i=0; i<6;i++){
        int r;
        do{
            r=rand()%1015;

        }while(used2[r]);

        used2[r]=1;
        player2->pokemons[i]=Pokemons[r];
    }
    player2->currentIndex = 0;
 }