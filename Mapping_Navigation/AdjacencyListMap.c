#include <stdlib.h>
//#include <pico/stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "AdjacencyList.h"
//#include "hardware/gpio.h"
#define ROW 4
#define COLUMN 4
#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E'
#define WEST 'W'
#define FRONT 'F'
#define BACK 'B'
#define RIGHT 'R'
#define LEFT 'L'

// 0 1
// 2 3

// 0 1 2
// 3 4 5
// 6 7 8

int main(){
    //stdio_init_all();
    char currentOrientation = NORTH;
    graph* map = createGraph(ROW, COLUMN);
    addEdge(map,10,6,FRONT,currentOrientation);
    currentOrientation = NORTH;
    addEdge(map,6,7,RIGHT,currentOrientation);
    currentOrientation = NORTH;
    addEdge(map,6,5,LEFT,currentOrientation);
    currentOrientation = WEST;
    addEdge(map,5,4,FRONT,currentOrientation);
    currentOrientation = WEST;
    addEdge(map,4,0,RIGHT,currentOrientation);
    currentOrientation = NORTH;
    addEdge(map,0,1,RIGHT,currentOrientation);
    currentOrientation = EAST;
    addEdge(map,1,2,RIGHT,currentOrientation);
    currentOrientation = EAST;
    addEdge(map,2,3,RIGHT,currentOrientation);
    currentOrientation = SOUTH;
    addEdge(map,4,8,FRONT,currentOrientation);
    currentOrientation = SOUTH;
    addEdge(map,8,12,FRONT,currentOrientation);
    currentOrientation = SOUTH;
    addEdge(map,12,13,LEFT,currentOrientation);
    currentOrientation = EAST;
    addEdge(map,13,14,FRONT,currentOrientation);
    currentOrientation = EAST;
    addEdge(map,14,10,LEFT,currentOrientation);
    currentOrientation = NORTH;
    addEdge(map,10,11,RIGHT,currentOrientation);
    currentOrientation = EAST;
    addEdge(map,11,15,RIGHT,currentOrientation);
    currentOrientation = WEST;
    addEdge(map,10,9,FRONT,currentOrientation);

    printGraph(map);
    //printMap(map,ROW,COLUMN);

    bytesConsumedByMap(map);

    destroyGraph(map);
    return 0;
}