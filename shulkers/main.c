#include <stdio.h>
#include "../cubiomes/finders.h"

#define MINECRAFT_VERSION MC_1_17
#define WORLD_SEED 4776164391216949839

#define REGX 0

#define REGZ_MIN 2
#define REGZ_MAX 100

int main() {
    Generator g;
    setupGenerator(&g, MINECRAFT_VERSION, 0);
    applySeed(&g, DIM_END, WORLD_SEED);

    StructureConfig sconf_endcity;
    getStructureConfig(End_City, MINECRAFT_VERSION, &sconf_endcity);

    SurfaceNoise sn;
    initSurfaceNoise(&sn, MINECRAFT_VERSION, WORLD_SEED);

    Pos pos;

    for (int regZ = REGZ_MIN; regZ < REGZ_MAX; regZ++) {

        int is_valid = getStructurePos(End_City, MINECRAFT_VERSION, WORLD_SEED, REGX, regZ, &pos);
        if (is_valid && isViableEndCityTerrain(&g, &sn, pos.x, pos.z)) {
            //pos = getFeaturePos(sconf_endcity, WORLD_SEED, REGX, regZ);
            printf("End City Position: (%d, %d)\n", pos.x, pos.z);
        }
    }

    return 0;
}