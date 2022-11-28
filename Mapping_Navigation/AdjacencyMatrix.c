#include "AdjacencyMatrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma pack(1)

typedef struct graph{
    int* gridVisited;
    int numOfNodes;
    bool** edges;
    bool** barcodes;
    bool** humps;
    char** directionsWhenNorth;
    char** directionsWhenSouth;
    char** directionsWhenWest;
    char** directionsWhenEast;
}graph;

graph* createGraph(int rows,int columns){
    graph* result = malloc(sizeof(graph));
    if(result != NULL){
        result->numOfNodes = rows*columns;
        //allocate mem for EdgesMatrix
        //Rows
        result->edges = calloc(sizeof(bool*),result->numOfNodes);
        if(result->edges == NULL){
            destroyGraph(result);
            printf("EdgesMatrix cannot be created(1)");
        }
        //columns
        for (int i = 0; i < result->numOfNodes; i++){
            result->edges[i] = calloc(sizeof(bool*),result->numOfNodes);
            if(result->edges[i] == NULL){
                destroyGraph(result);
                printf("EdgesMatrix cannot be created(2)");
            }
        }
        //allocate mem for BarcodeMatrix
        result->barcodes = calloc(sizeof(bool*),result->numOfNodes);
        if(result->barcodes == NULL){
            destroyGraph(result);
            printf("BarcodesMatrix cannot be created(1)");
        }
        for (int i = 0; i < result->numOfNodes; i++){
            result->barcodes[i] = calloc(sizeof(bool*),result->numOfNodes);
            if(result->barcodes[i] == NULL){
                destroyGraph(result);
                printf("BarcodesMatrix cannot be created(2)");
            }
        }
        //allocate mem for HumpsMatrix
        result->humps = calloc(sizeof(bool*),result->numOfNodes);
        if(result->humps == NULL){
            destroyGraph(result);
            printf("HumpsMatrix cannot be created(1)");
        }
        for (int i = 0; i < result->numOfNodes; i++){
            result->humps[i] = calloc(sizeof(bool*),result->numOfNodes);
            if(result->humps[i] == NULL){
                destroyGraph(result);
                printf("HumpsMatrix cannot be created(2)");
            }
        }
        result->directionsWhenNorth = calloc(sizeof(char*),result->numOfNodes);
        if(result->directionsWhenNorth == NULL){
            destroyGraph(result);
            printf("DirectionsWhenNorthMatrix cannot be created(1)");
        }
        //columns
        for (int i = 0; i < result->numOfNodes; i++){
            result->directionsWhenNorth[i] = calloc(sizeof(char*),result->numOfNodes);
            if(result->directionsWhenNorth[i] == NULL){
                destroyGraph(result);
                printf("DirectionsWhenNorthMatrix cannot be created(2)");
            }
        }
        result->directionsWhenSouth = calloc(sizeof(char*),result->numOfNodes);
        if(result->directionsWhenSouth == NULL){
            destroyGraph(result);
            printf("DirectionsWhenSouthMatrix cannot be created(1)");
        }
        //columns
        for (int i = 0; i < result->numOfNodes; i++){
            result->directionsWhenSouth[i] = calloc(sizeof(char*),result->numOfNodes);
            if(result->directionsWhenSouth[i] == NULL){
                destroyGraph(result);
                printf("DirectionsWhenSouthMatrix cannot be created(2)");
            }
        }
        result->directionsWhenWest = calloc(sizeof(char*),result->numOfNodes);
        if(result->directionsWhenWest == NULL){
            destroyGraph(result);
            printf("DirectionsWhenWestMatrix cannot be created(1)");
        }
        //columns
        for (int i = 0; i < result->numOfNodes; i++){
            result->directionsWhenWest[i] = calloc(sizeof(char*),result->numOfNodes);
            if(result->directionsWhenWest[i] == NULL){
                destroyGraph(result);
                printf("DirectionsWhenWestMatrix cannot be created(2)");
            }
        }
        result->directionsWhenEast = calloc(sizeof(char*),result->numOfNodes);
        if(result->directionsWhenEast == NULL){
            destroyGraph(result);
            printf("DirectionsWhenEastMatrix cannot be created(1)");
        }
        //columns
        for (int i = 0; i < result->numOfNodes; i++){
            result->directionsWhenEast[i] = calloc(sizeof(char*),result->numOfNodes);
            if(result->directionsWhenEast[i] == NULL){
                destroyGraph(result);
                printf("DirectionsWhenEastMatrix cannot be created(2)");
            }
        }
        result->gridVisited = calloc(sizeof(int), result->numOfNodes);
        //sometimes calloc will not initialized everything to zero, so we 
        //explicitly have to initliase it.
        for (int i = 0; i < result->numOfNodes; i++){
            result->gridVisited[i] = -99;
            for (int j = 0; j < result->numOfNodes; j++){
                result->edges[i][j] = false;
                result->barcodes[i][j] = false;
                result->humps[i][j] = false;
                result->directionsWhenNorth[i][j] = 'N';
                result->directionsWhenSouth[i][j] = 'N';
                result->directionsWhenWest[i][j] = 'N';
                result->directionsWhenEast[i][j] = 'N';
            }
        }
    }
    return result;
}

void destroyGraph(graph* graph){
    if(graph->edges == NULL){
        free(graph);
    }
    for(int i = 0; i < graph->numOfNodes; i++){
        free(graph->edges[i]);
    }
    free(graph->edges);
}

void printEdges(graph* graph){
    printf("Edges Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf("%02d\n",graph->edges[i][j]);
            }
            else{
                printf("%02d ",graph->edges[i][j]);
            }
        }
    }
}
void printDirectionsWhenNorth(graph* graph){
    printf("DirectionsWhenNorth Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf(" %c\n",graph->directionsWhenNorth[i][j]);
            }
            else{
                printf(" %c ",graph->directionsWhenNorth[i][j]);
            }
        }
    }
}

void printDirectionsWhenSouth(graph* graph){
    printf("DirectionsWhenSouth Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf(" %c\n",graph->directionsWhenSouth[i][j]);
            }
            else{
                printf(" %c ",graph->directionsWhenSouth[i][j]);
            }
        }
    }
}

void printDirectionsWhenWest(graph* graph){
    printf("DirectionsWhenWest Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf(" %c\n",graph->directionsWhenWest[i][j]);
            }
            else{
                printf(" %c ",graph->directionsWhenWest[i][j]);
            }
        }
    }
}

void printDirectionsWhenEast(graph* graph){
    printf("DirectionsWhenEast Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf(" %c\n",graph->directionsWhenEast[i][j]);
            }
            else{
                printf(" %c ",graph->directionsWhenEast[i][j]);
            }
        }
    }
}

void printBarcodes(graph* graph){
    printf("Barcode Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf("%02d\n",graph->barcodes[i][j]);
            }
            else{
                printf("%02d ",graph->barcodes[i][j]);
            }
        }
    }
}
void printHumps(graph* graph){
    printf("Humps Matrix:\n");
    printf("   ");
    for(int i = 0; i<graph->numOfNodes; i++){
        if(i == graph->numOfNodes-1){
            printf("%02d\n", i);
        }
        else{
            printf("%02d ", i);
        }
    }
    for(int i = 0 ; i < graph->numOfNodes; i++){
        printf("%02d ", i);
        for(int j = 0; j < graph->numOfNodes; j++){
            if(j == graph->numOfNodes - 1){
                printf("%02d\n",graph->humps[i][j]);
            }
            else{
                printf("%02d ",graph->humps[i][j]);
            }
        }
    }
}

bool addDirection(graph* graph, int from_node, int to_node, char direction, char orientation){
    if(hasDirectionNorth(graph, from_node, to_node)!='N' && hasDirectionSouth(graph, from_node, to_node)!='N' 
    && hasDirectionWest(graph, from_node, to_node)!='N' && hasDirectionEast(graph, from_node, to_node)!='N'){
        return false;
    }
    else{
        if(orientation == 'N'){
            if(direction == 'F'){
                addDirectionNorth(graph, from_node, to_node, direction);
                addDirectionSouth(graph, from_node,to_node, 'B');
                addDirectionWest(graph, from_node,to_node,'R');
                addDirectionEast(graph,from_node,to_node,'L');
            }
            else if(direction == 'B'){
                addDirectionNorth(graph, from_node, to_node, direction);
                addDirectionSouth(graph, from_node,to_node, 'F');
                addDirectionWest(graph, from_node,to_node,'L');
                addDirectionEast(graph,from_node,to_node,'R');
            }
            else if(direction == 'L'){
                addDirectionNorth(graph, from_node, to_node, direction);
                addDirectionSouth(graph, from_node,to_node, 'R');
                addDirectionWest(graph, from_node,to_node,'F');
                addDirectionEast(graph,from_node,to_node,'B');
            }
            else if(direction == 'R'){
                addDirectionNorth(graph, from_node, to_node, direction);
                addDirectionSouth(graph, from_node,to_node, 'L');
                addDirectionWest(graph, from_node,to_node,'B');
                addDirectionEast(graph,from_node,to_node,'F');
            }   
        }
        else if(orientation == 'S'){
            if(direction == 'F'){
                addDirectionSouth(graph, from_node, to_node,direction);
                addDirectionNorth(graph,from_node,to_node, 'B');
                addDirectionWest(graph, from_node, to_node,'L');
                addDirectionEast(graph,from_node,to_node,'R');
            }
            else if(direction == 'B'){
                addDirectionSouth(graph, from_node, to_node,direction);
                addDirectionNorth(graph,from_node,to_node, 'F');
                addDirectionWest(graph, from_node, to_node,'R');
                addDirectionEast(graph,from_node,to_node,'L');
            }
            else if(direction == 'L'){
                addDirectionSouth(graph, from_node, to_node,direction);
                addDirectionNorth(graph,from_node,to_node, 'R');
                addDirectionWest(graph, from_node, to_node,'B');
                addDirectionEast(graph,from_node,to_node,'F');
            }
            else if(direction == 'R'){
                addDirectionSouth(graph, from_node, to_node,direction);
                addDirectionNorth(graph,from_node,to_node, 'L');
                addDirectionWest(graph, from_node, to_node,'F');
                addDirectionEast(graph,from_node,to_node,'B');
            }
        }
        else if(orientation == 'W'){
            if(direction == 'F'){
                addDirectionWest(graph,from_node,to_node,direction);
                addDirectionNorth(graph,from_node,to_node,'L');
                addDirectionSouth(graph,from_node,to_node, 'R');
                addDirectionEast(graph, from_node,to_node, 'B');
            }
            else if(direction == 'B'){
                addDirectionWest(graph,from_node,to_node,direction);
                addDirectionNorth(graph,from_node,to_node,'R');
                addDirectionSouth(graph,from_node,to_node, 'L');
                addDirectionEast(graph, from_node,to_node, 'F');
            }
            else if(direction == 'L'){
                addDirectionWest(graph,from_node,to_node,direction);
                addDirectionNorth(graph,from_node,to_node,'B');
                addDirectionSouth(graph,from_node,to_node, 'F');
                addDirectionEast(graph, from_node,to_node, 'R');
            }
            else if(direction == 'R'){
                addDirectionWest(graph,from_node,to_node,direction);
                addDirectionNorth(graph,from_node,to_node,'F');
                addDirectionSouth(graph,from_node,to_node, 'B');
                addDirectionEast(graph, from_node,to_node, 'L');
            }
        }
        else if(orientation == 'E'){
            if(direction == 'F'){
                addDirectionEast(graph,from_node,to_node,direction);
                addDirectionNorth(graph, from_node,to_node,'R');
                addDirectionSouth(graph,from_node, to_node,'L');
                addDirectionWest(graph,from_node,to_node,'B');
            }
            else if(direction == 'B'){
                addDirectionEast(graph,from_node,to_node,direction);
                addDirectionNorth(graph, from_node,to_node,'L');
                addDirectionSouth(graph,from_node, to_node,'R');
                addDirectionWest(graph,from_node,to_node,'F');
            }
            else if(direction == 'L'){
                addDirectionEast(graph,from_node,to_node,direction);
                addDirectionNorth(graph, from_node,to_node,'F');
                addDirectionSouth(graph,from_node, to_node,'B');
                addDirectionWest(graph,from_node,to_node,'R');
            }
            else if(direction == 'R'){
                addDirectionEast(graph,from_node,to_node,direction);
                addDirectionNorth(graph, from_node,to_node,'B');
                addDirectionSouth(graph,from_node, to_node,'F');
                addDirectionWest(graph,from_node,to_node,'L');
            }
        }
        return true;
    }
}

bool addDirectionNorth(graph* graph, int from_node, int to_node , char direction){
    if(hasDirectionNorth(graph, from_node, to_node) != 'N'){
        return false;
    }
    else{
        graph->directionsWhenNorth[from_node][to_node] = direction;
        if(direction == 'F'){
            graph->directionsWhenNorth[to_node][from_node] = 'B';
        }
        else if(direction == 'B'){
            graph->directionsWhenNorth[to_node][from_node] = 'F';
        }
        else if(direction == 'L'){
            graph->directionsWhenNorth[to_node][from_node] = 'R';
        }
        else if(direction == 'R'){
            graph->directionsWhenNorth[to_node][from_node] = 'L';
        }
        //printf("Direction Added!\n");
        return true;
    }
}
char hasDirectionNorth(graph* graph, int from_node, int to_node){
    return graph->directionsWhenNorth[from_node][to_node];
}

bool addDirectionSouth(graph* graph, int from_node, int to_node , char direction){
    if(hasDirectionSouth(graph, from_node, to_node) != 'N'){
        return false;
    }
    else{
        graph->directionsWhenSouth[from_node][to_node] = direction;
        if(direction == 'F'){
            graph->directionsWhenSouth[to_node][from_node] = 'B';
        }
        else if(direction == 'B'){
            graph->directionsWhenSouth[to_node][from_node] = 'F';
        }
        else if(direction == 'L'){
            graph->directionsWhenSouth[to_node][from_node] = 'R';
        }
        else if(direction == 'R'){
            graph->directionsWhenSouth[to_node][from_node] = 'L';
        }
        //printf("Direction Added!\n");
        return true;
    }
}
char hasDirectionSouth(graph* graph, int from_node, int to_node){
    return graph->directionsWhenSouth[from_node][to_node];
}

bool addDirectionWest(graph* graph, int from_node, int to_node , char direction){
    if(hasDirectionWest(graph, from_node, to_node) != 'N'){
        return false;
    }
    else{
        graph->directionsWhenWest[from_node][to_node] = direction;
        if(direction == 'F'){
            graph->directionsWhenWest[to_node][from_node] = 'B';
        }
        else if(direction == 'B'){
            graph->directionsWhenWest[to_node][from_node] = 'F';
        }
        else if(direction == 'L'){
            graph->directionsWhenWest[to_node][from_node] = 'R';
        }
        else if(direction == 'R'){
            graph->directionsWhenWest[to_node][from_node] = 'L';
        }
        //printf("Direction Added!\n");
        return true;
    }
}
char hasDirectionWest(graph* graph, int from_node, int to_node){
    return graph->directionsWhenWest[from_node][to_node];
}

bool addDirectionEast(graph* graph, int from_node, int to_node , char direction){
    if(hasDirectionEast(graph, from_node, to_node) != 'N'){
        return false;
    }
    else{
        graph->directionsWhenEast[from_node][to_node] = direction;
        if(direction == 'F'){
            graph->directionsWhenEast[to_node][from_node] = 'B';
        }
        else if(direction == 'B'){
            graph->directionsWhenEast[to_node][from_node] = 'F';
        }
        else if(direction == 'L'){
            graph->directionsWhenEast[to_node][from_node] = 'R';
        }
        else if(direction == 'R'){
            graph->directionsWhenEast[to_node][from_node] = 'L';
        }
        //printf("Direction Added!\n");
        return true;
    }
}
char hasDirectionEast(graph* graph, int from_node, int to_node){
    return graph->directionsWhenEast[from_node][to_node];
}

bool addEdge(graph* graph, int from_node, int to_node){
    if(hasEdge(graph, from_node, to_node)){
        return false;
    }
    else{
        graph->edges[from_node][to_node] = true;
        graph->edges[to_node][from_node] = true;
        //printf("Edge Added!\n");
        return true;
    }
}
bool hasEdge(graph* graph, int from_node, int to_node){
    return graph->edges[from_node][to_node];
}

bool addBarcode(graph* graph, int from_node, int to_node){
    if(hasBarcode(graph, from_node, to_node)){
        return false;
    }
    else{
        graph->barcodes[from_node][to_node] = true;
        graph->barcodes[to_node][from_node] = true;
        //printf("Barcode Added!\n");
        return true;
    }
}
bool hasBarcode(graph* graph, int from_node, int to_node){
    return graph->barcodes[from_node][to_node];
}

bool addHump(graph* graph, int from_node, int to_node){
    if(hasHump(graph, from_node, to_node)){
        return false;
    }
    else{
        graph->humps[from_node][to_node] = true;
        graph->humps[to_node][from_node] = true;
        //printf("Hump Added!\n");
        return true;
    }
}
bool hasHump(graph* graph, int from_node, int to_node){
    return graph->humps[from_node][to_node];
}

void printGraph(graph* graph){
    printf("graph {\n");
    for (int from = 0; from < graph->numOfNodes; from++){
        for (int to = 0; to < graph->numOfNodes; to++){
            if(graph->edges[from][to]){
                printf("%d -- %d", from, to);
                if(graph->humps[from][to]){
                    printf("[label=\"h\"]");
                }
                if(graph->barcodes[from][to]){
                    printf("[label=\"b\"]");
                }
                printf(";\n");
            }
        }
    }
    printf("}\n");
}

void printMap(graph* graph, int rows, int columns){
    int map[rows][columns];
    int counter = 0;
    for(int i=0; i<rows;i++){
        for(int j = 0; j<columns; j++){
            map[i][j] = counter++;
        }
    }
    printf("\n");
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(j == columns-1){
                printf("(%03d)", map[i][j]);
                if(hasEdge(graph,map[i][j],map[i][j+1])){
                    printf("-");
                    if(hasBarcode(graph,map[i][j],map[i][j+1])){
                        printf("b");
                    }
                    else if(hasHump(graph,map[i][j],map[i][j+1])){
                        printf("h");
                    }
                    else{
                        printf("-");
                    }
                    printf("-");
                }
                printf("\n");
                for(int k = 0; k < columns; k++){
                    if(hasEdge(graph, map[i][k],map[i+1][k])){
                        printf("|");
                        if(hasHump(graph, map[i][k],map[i+1][k])){
                            printf("h");
                        }
                        else if(hasBarcode(graph, map[i][k],map[i+1][k])){
                            printf("b");
                        }
                        else{
                            printf("|");
                        }
                        printf("|     ");
                    }
                    else{
                        if(i != rows-1){
                            printf("|X|     ");
                        }
                    }
                }
                printf("\n");
            }
            else{
                printf("(%03d)", map[i][j]);
                if(hasEdge(graph,map[i][j],map[i][j+1])){
                    printf("-");
                    if(hasBarcode(graph,map[i][j],map[i][j+1])){
                        printf("b");
                    }
                    else if(hasHump(graph,map[i][j],map[i][j+1])){
                        printf("h");
                    }
                    else{
                        printf("-");
                    }
                    printf("-");
                }
                else{
                    printf("-X-");
                }
            }
        }
    }
}

void printAllMatrix(graph* graph){
    printEdges(graph);
    printHumps(graph);
    printBarcodes(graph);
    printDirectionsWhenNorth(graph);
    printDirectionsWhenSouth(graph);
    printDirectionsWhenWest(graph);
    printDirectionsWhenEast(graph);
}

void whatDirectionDoITake(graph* graph, int from_node, int to_node){
    printf("From grid %d to %d\n", from_node, to_node);
    if(hasDirectionNorth(graph,from_node,to_node)!='N'){
        printf("If North: Go %c\n",graph->directionsWhenNorth[from_node][to_node]);
    }
    else{
        printf("If North: NULL\n");
    }
    if(hasDirectionSouth(graph,from_node,to_node)!='N'){
        printf("If South: Go %c\n",graph->directionsWhenSouth[from_node][to_node]);
    }
    else{
        printf("If South: NULL\n");
    }
    if(hasDirectionWest(graph,from_node,to_node)!='N'){
        printf("If West: Go %c\n",graph->directionsWhenWest[from_node][to_node]);
    }
    else{
        printf("If West: NULL\n");
    }
    if(hasDirectionEast(graph,from_node,to_node)!='N'){
        printf("If East: Go %c\n",graph->directionsWhenEast[from_node][to_node]);
    }
    else{
        printf("If East: NULL\n");
    }
    
}

bool checkAllNodesHasAtLeast1Edge(graph* graph){
    int counter = 0;
    for(int i = 0; i < graph->numOfNodes; i++){
        int counter2 =0;
        for(int j =0; j< graph->numOfNodes; j++){
            if(graph->edges[i][j] == true){
                counter2 += 1;
            }
            if(j == graph->numOfNodes-1 && counter2 != 0){
                counter += 1;
            }
        }
        //printf("Node %d has %d edges.\n",i,counter2);
    }
    //printf("Counter: %d\n",counter);
    if(counter == graph->numOfNodes){
        printf("All Nodes have at least 1 edge!\n");
        return true;
    }
    else{
        printf("Some nodes don't have an edge!\n");
        return false;
    }
}

void bytesConsumedByMap(){
    printf("Bytes consumed: %lu\n",sizeof(struct graph));
}

int nextGrid(int currentNode,int columns, char direction, char orientation){
  int nextGrid;
  if(orientation == 'N'){
    if(direction == 'F'){
      nextGrid = currentNode - columns;
      return nextGrid;
    }
    else if(direction == 'B'){
      nextGrid = currentNode + columns;
      return nextGrid;
    }
    else if(direction == 'R'){
      nextGrid = currentNode + 1;
      return nextGrid;
    }
    else if(direction == 'L'){
      nextGrid = currentNode - 1;
      return nextGrid;
    }
  }
  else if(orientation == 'S'){
    if(direction == 'F'){
      nextGrid = currentNode + columns;
      return nextGrid;
    }
    else if(direction == 'B'){
      nextGrid = currentNode - columns;
      return nextGrid;
    }
    else if(direction == 'R'){
      nextGrid = currentNode - 1;
      return nextGrid;
    }
    else if(direction == 'L'){
      nextGrid = currentNode + 1;
      return nextGrid;
    }
  }
  else if(orientation == 'E'){
    if(direction == 'F'){
      nextGrid = currentNode + 1;
      return nextGrid;
    }
    else if(direction == 'B'){
      nextGrid = currentNode - 1;
      return nextGrid;
    }
    else if(direction == 'R'){
      nextGrid = currentNode + columns;
      return nextGrid;
    }
    else if(direction == 'L'){
      nextGrid = currentNode - columns;
      return nextGrid;
    }
  }
  else if(orientation == 'W'){
    if(direction == 'F'){
      nextGrid = currentNode - 1;
      return nextGrid;
    }
    else if(direction == 'B'){
      nextGrid = currentNode + 1;
      return nextGrid;
    }
    else if(direction == 'R'){
      nextGrid = currentNode - columns;
      return nextGrid;
    }
    else if(direction == 'L'){
      nextGrid = currentNode + columns;
      return nextGrid;
    }
  }
  return -99;
}

bool hasTraveledGrid(graph* map, int destination){
    bool traveled;
    for(int i = 0; i<map->numOfNodes;i++){
        if(map->gridVisited[i] == destination){
            traveled = true;
        }
        else{
            map->gridVisited[i] = destination;
            traveled = false;
        }
    }
    return traveled;
}

void updateGridVisited(graph* map, int destination){
    bool valid = false;
    int index;
    for(int i =0; i<map->numOfNodes;i++){
        if(map->gridVisited[i] == -99){
            valid = true;
            index = i;
        }
        if(map->gridVisited[i] == destination){
            printf("Visited\n");
            valid = false;
        }
    }
    if(valid){
        map->gridVisited[index] = destination;
        printf("Updated Visited Grid\n");
    }
}

void printGridVisited(graph* map){
    printf("Grid Visited: ");
    for(int i=0; i<map->numOfNodes;i++){
        printf("%d,",map->gridVisited[i]);
    }
    printf("\n");
}


