#ifndef __MACRO_H__
#define __MACRO_H__

#include <assert.h>
#include <random>

#define MAX_STEP_CNT 2000
#define WORLD_SIZE 50
#define UAV_COUNT 8
#define OBJECT_COUNT 2
#define COMM_PROB 40
#define MAX_COMM_CNT 120
#define RANDOM_BLOCK_COUNT_ONESIDE 25
#define SETTLED_BLOCK_COUNT_ONESIDE 20
#define SCAN_RANGE 2
inline int random_(int x) {
    return rand() % (x) + 1;
}
#endif
