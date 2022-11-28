#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#define ROWS 3
#define COLUMNS 3

int main(){
    char forward = 'F';
    char left = 'L';
    char right = 'R';
    char reverse = 'B';
    char orientation ='N'; //relative compass
    //whenever car turns left, orientation becomes East
    //whenever car turns right, orientation becomes West
    //char* orientationptr = &orientation;
    graph* map = createGraph(ROWS,COLUMNS);
    //example on a 3x3 map. Start at grid 4
    //node 4 to 5. right side clear
    // 0 1 2
    // 3 4 5
    // 6 7 8
    addEdge(map, 4,5);
    addDirection(map, 4,5,right,orientation);
    orientation = 'E';
    addEdge(map,5,8);
    addDirection(map, 5,8, right, orientation);
    orientation = 'S';
    addEdge(map, 8,7);
    addDirection(map,8,7,right,orientation);
    orientation = 'W';
    addEdge(map, 7,6);
    addDirection(map, 7,6,forward,orientation);
    addEdge(map, 6,3);
    addDirection(map, 6,3,right,orientation);
    orientation = 'N';
    addEdge(map, 3,0);
    addDirection(map, 3,0,forward,orientation);
    addEdge(map,0,1);
    addDirection(map, 0,1,right,orientation);
    orientation = 'E';
    addEdge(map,1,2);
    addDirection(map,1,2,forward,orientation);

    //printing all different matrices
    //printEdges(map);
    //printing the graph in dot format
    //rintGraph(map);

    //printing the graph in a grid map format
    printMap(map, ROWS, COLUMNS);
    //printf("Current car orientation: %c\n",orientation);

    //whatDirectionDoITake(map, 0,1);


    clock_t t;
    t = clock();
    printf("BFS Algo: \n");
    BFS(map, 6, 4);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("BFS took %f seconds to execute\n\n", time_taken);

    clock_t t2;
    t2 = clock();
    printf("DFS Algo: \n");
    DFS(map, 6,4,6);
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
    printf("DFS took %f seconds to execute\n\n", time_taken2);

    clock_t t3;
    t3 = clock();
    printf("Dijsktra Algo: \n");
    int* dijkstraNodes = dijkstraTraversal(map,6, 4, ROWS, COLUMNS);
    int numberOfNodesInDijkstra = getDijkstraNodes();

    t3 = clock() - t3;
    double time_taken3 = ((double)t3)/CLOCKS_PER_SEC; // in seconds
    printf("Dijsktra took %f seconds to execute\n\n", time_taken3);

    //freeing mem
    destroyGraph(map);
    //free(dijkstraNodes);
    //return 0;
}
