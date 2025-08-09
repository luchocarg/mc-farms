#include "sugarcane.h"

void randomTick(struct SugarCaneBlock *b) {
    if (b->height < 3) {
        if (b->age < 15) {
            b->age++;
        } else {
            b->age = 0;
            b->height++;
        }
    }
}

bool shouldRandomTick(void) {
    return ((double)rand() / RAND_MAX) < (3.0 / 4096.0);
}

void allocateField(int length) {
    field = malloc((size_t)WIDTH * sizeof(struct SugarCaneBlock *));
    for (int i = 0; i < WIDTH; i++)
        field[i] = malloc((size_t)length * sizeof(struct SugarCaneBlock));
}

void freeField(void) {
    for (int i = 0; i < WIDTH; i++) free(field[i]);
    free(field);
}

void initField(int length) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < length; y++) {
            field[x][y].age = 0;
            field[x][y].height = 3;

        }
    }
}

void allocateFlyingMachine(){
    flying_machine = malloc(sizeof(struct FlyingMachine));
}

void freeFlyingMachine(){
    free(flying_machine);
}

void initFlyingMachine(){
    flying_machine->pos = -1;
    flying_machine->active = false;
    flying_machine->mtick = 0;
}

void simulateRandomTicks(int length) {
    for (int y = 0; y < length; y++) {
        if (y != flying_machine->pos) {
            for (int x = 0; x < WIDTH; x++) {
                if (shouldRandomTick()) randomTick(&field[x][y]);
            }
        }
    }
}

int harveField(int pos) {
    int total = 0;
    for (int x = 0; x < WIDTH; x++) {
        struct SugarCaneBlock *b = &field[x][pos];
        total += b->height-1;

        b->height = 1;
        b->age = 0;
    }
    return total;
}

int main(){
    srand(777);

    int tick = 0;

    int clock = 20000;
    int length = 20;

    int collected = 0;

    
    allocateField(length);
    initField(length);

    allocateFlyingMachine();
    initFlyingMachine();

    while (tick != (TPS*3600*100)) {
        tick++;

        simulateRandomTicks(length);

        if (tick%clock == 0) flying_machine->active = true;

        if (flying_machine->active) {
            if (flying_machine->mtick < 13) {
                flying_machine->mtick++;
            }
            else {
                flying_machine->mtick = 0;
                flying_machine->pos++;

                collected += harveField(flying_machine->pos);
            }
        }

        if (flying_machine->pos >= length) {
            flying_machine->active = false;
            flying_machine->pos = -1;
            flying_machine->mtick = 0;
        }
    }

    printf("sugarcane: %d\n", collected);

    return 0;
}