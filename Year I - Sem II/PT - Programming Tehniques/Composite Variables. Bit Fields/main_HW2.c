#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char extraENDL; // catches missed endlines by scanf

typedef enum _animalType {
    insect = 0,
    bird = 1,
    mammal = 2,
    fish = 3
}animalType;

typedef struct animal {
    char *name;
    animalType flag:2;
    union {
        struct{
            unsigned legs;
            double lifeSpan;
        }insect;
        struct{
            float flightSpeed;
            float wingLength;
            char migration;
        }bird;
        struct{
            float weight;
            float height;
            char foodType;
        }mammal;
        struct{
            float weight;
            int swimDepth;
            float saltPerc;
        }fish;
    }type;
}animal_t;

/// -------------- OPTION PRINTING FUNCTIONS --------------

void printOptions(){
    printf("Choose  Option:\n");
    printf("0. Exit\n");
    printf("1. Add\n");
    printf("2. Delete\n");
    printf("3. Lookup\n");
    printf("4. Replace\n");
    printf("5. Print Database\n");
}

void printAnimalOptions(){
    printf("Choose Animal Type:\n");
    printf("1 -> Insect\n");
    printf("2 -> Bird\n");
    printf("3 -> Mammal\n");
    printf("4 -> Fish\n");
}

/// -------------- GETTING FUNCTIONS --------------

char* getName(){
    extraENDL = getchar();
    printf("* Animal/Species Name: ");
    char *name = malloc(0);

    int i = 0;
    for ( char c = getchar(); c != '\n' ; c = getchar() ){
        name = realloc(name, (i + 2)*sizeof(char));
        name[i] = c;
        i++;
    }
    name[i] = '\0';

    return name;
}

animal_t getAnimal(){
    animalType option;
    animal_t animal;

    do{
        printf("\nAnimal Type: ");
        scanf("%u", &option);
    }while( option < 1 || option > 4);
    animal.flag = option - 1;

    animal.name = getName();

    switch ( animal.flag ){
        case insect:
            printf("Insect:\n");
            printf("- Nr of Legs (legs :)): ");
            scanf("%u", &animal.type.insect.legs);
            printf("- Life Span (days): ");
            scanf("%lf", &animal.type.insect.lifeSpan);
            break;

        case bird:
            printf("Bird:\n");
            printf("- Flight Speed (km/h): ");
            scanf("%f", &animal.type.bird.flightSpeed);
            printf("- Wing Length (cm): ");
            scanf("%f", &animal.type.bird.wingLength);
            printf("- Migration Habbits (Y/N): ");
            extraENDL = getchar();
            scanf("%c", &animal.type.bird.migration);
            break;

        case mammal:
            printf("Mammal:\n");
            printf("- Weight (kg): ");
            scanf("%f", &animal.type.mammal.weight);
            printf("- Height (cm): ");
            scanf("%f", &animal.type.mammal.height);
            extraENDL = getchar();
            printf("- Food Type (c - carnivorous; h - herbivorous; o - omnivorous): ");
            scanf("%c", &animal.type.mammal.foodType);
            break;

        case fish:
            printf("Fish:\n");
            printf("- Weight (kg): ");
            scanf("%f", &animal.type.fish.weight);
            printf("- Swim Depth (m): ");
            scanf("%d", &animal.type.fish.swimDepth);
            printf("- Salt Percentage: ");
            scanf("%f", &animal.type.fish.saltPerc);
            break;

        default:
            printf("error");
    }

    return animal;
}

/// -------------- ANIMAL PRINTING FUNCTIONS --------------

void printName(char *name){
    for ( int i = 0; name[i] != '\0' ; i++ ){
        printf("%c", name[i]);
    }
}

void printAnimal(animal_t animal){
    printf("* Animal/Species Name: ");
    printName(animal.name);
    printf("\n");

    switch ( animal.flag ){
        case insect:
            printf("Insect:\n");
            printf("- Nr of Legs: %u legs\n", animal.type.insect.legs);
            printf("- Life Span: %lf days\n", animal.type.insect.lifeSpan);
            break;

        case bird:
            printf("Bird:\n");
            printf("- Flight Speed: %.2f km/h\n", animal.type.bird.flightSpeed);
            printf("- Wing Length: %.3f cm\n", animal.type.bird.wingLength);
            printf("- Migration Habbits: ");
            switch (animal.type.bird.migration){
                case 'Y':
                case 'y': printf("yes\n");break;
                case 'N':
                case 'n': printf("nope\n");break;
                default : printf("N/A\n");break;
            }
            break;

        case mammal:
            printf("Mammal:\n");
            printf("- Weight: %.3f cm\n", animal.type.mammal.weight);
            printf("- Height: %.3f cm\n", animal.type.mammal.height);
            printf("- Food Type: ");
            switch (animal.type.mammal.foodType){
                case 'C':
                case 'c': printf("carnivorous\n");break;
                case 'H':
                case 'h': printf("herbivorous\n");break;
                case 'O':
                case 'o': printf("omnivorous\n");break;
                default : printf("N/A\n");break;
            }
            break;

        case fish:
            printf("Fish:\n");
            printf("- Weight: %.3f kg\n", animal.type.fish.weight);
            printf("- Swim Depth: %d m\n", animal.type.fish.swimDepth);
            printf("- Salt Percentage: %.2f%%\n", animal.type.fish.saltPerc);
            break;

        default:
            printf("error");
    }
    printf("\n");
}

/// -------------- ANIMAL FINDING FUNCTION --------------

int findAnimal(animal_t *database, unsigned size, char *name){
    for (int i = 0; i < size; i++){
        if ( strcasecmp(database[i].name, name) == 0 ){
            return i;
        }
    }
    return -1;
}

/// -------------- DATABASE OPTIONS --------------

void addAnimals(animal_t **database, unsigned *size){
    unsigned nr;
    int i = (*size);

    printf("Nr of animals to add: ");
    scanf("%u", &nr);

    printAnimalOptions();

    (*size) += nr;
    *database = (animal_t*)realloc(*database, ((*size)) * sizeof(animal_t));

    for ( ; i < (*size) ; i++ ){
        (*database)[i] = getAnimal();
    }
}

void petAnimal(){
    printf("Animal is happy now! UwU\n");
}

void removeAnimal(animal_t **database, unsigned *size, char *name){
    int index = findAnimal((*database), (*size), name);

    if ( index != -1 ){
        for ( ; index < (*size) - 1 ; index++){
            (*database)[index] = (*database)[index + 1];
        }

        printf("Removed ");
        printName(name);
        printf(" from database!\n");

        (*size)--;
        *database = (animal_t*)realloc(*database, (*size) * sizeof(animal_t));
    }
    else {
       printf("Animal not found!");
    }
}

void lookupAnimal(animal_t *database, unsigned size, char *name){
    int index = findAnimal(database, size, name);

    if ( index != -1 ){
        printAnimal(database[index]);
    }
    else {
        printf("Animal not found!");
    }
}

void replaceAnimal(animal_t *database, unsigned size, char *name){
    int index = findAnimal(database, size, name);

    if ( index != -1 ){
        database[index] = getAnimal();
    }
    else {
        printf("Animal not found!");
    }
}

void printDB(animal_t *database, unsigned size){
    for (int i = 0; i < size; i++){
        printf("%d.", i + 1);
        printAnimal(database[i]);
    }
}

/// ------------------------------------------

int main(){
    unsigned option = 1;

    animal_t *animalDB = malloc(1*sizeof(animal_t));
    unsigned DBsize = 0;

    printOptions();

    while ( option ){
        //petAnimal();
        printf("\nOption: ");
        scanf("%u", &option);

        switch ( option ){
            case 0: break;
            case 1:
                printf("ADD ANIMAL\n");
                addAnimals(&animalDB, &DBsize);
                break;
            case 2:
                printf("REMOVE ANIMAL\n");
                removeAnimal(&animalDB, &DBsize, getName());
                break;
            case 3:
                printf("LOOKUP ANIMAL\n");
                lookupAnimal(animalDB, DBsize, getName());
                break;
            case 4:
                printf("REPLACE ANIMAL\n");
                replaceAnimal(animalDB, DBsize, getName());
                break;
            case 5:
                printf("PRINT DATABASE\n");
                printDB(animalDB, DBsize);
                break;
            default:
                printf("Invalid Option!");
                break;
      }
  }

  free(animalDB);

  return 0;
}
