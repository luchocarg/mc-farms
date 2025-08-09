#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define TPS 20
#define WIDTH 12
#define INACTIVE 13

struct SugarCaneBlock {
    uint8_t age;
    uint8_t height;
};

struct SugarCaneBlock **field;

struct FlyingMachine {
    int pos;
    bool active;
    uint8_t mtick;
};

struct FlyingMachine *flying_machine;
