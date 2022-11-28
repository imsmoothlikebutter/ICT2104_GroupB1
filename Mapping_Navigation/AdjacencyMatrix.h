#ifndef ADJACENCYMATRIX
#define ADJACENCYMATRIX
#include <stdbool.h>


typedef struct graph graph;
graph* createGraph(int rows,int columns);
void destroyGraph(graph* graph);
void printEdges(graph* graph);
bool addEdge(graph* graph, int from_node, int to_node);
bool hasEdge(graph* graph, int from_node, int to_node);
bool addBarcode(graph* graph, int from_node, int to_node);
bool hasBarcode(graph* graph, int from_node, int to_node);
bool addHump(graph* graph, int from_node, int to_node);
bool hasHump(graph* graph, int from_node, int to_node);
bool addDirection(graph* graph, int from_node, int to_node, char direction, char orientation);
bool addDirectionNorth(graph* graph, int from_node, int to_node , char direction);
char hasDirectionNorth(graph* graph, int from_node, int to_node);
bool addDirectionSouth(graph* graph, int from_node, int to_node , char direction);
char hasDirectionSouth(graph* graph, int from_node, int to_node);
bool addDirectionWest(graph* graph, int from_node, int to_node , char direction);
char hasDirectionWest(graph* graph, int from_node, int to_node);
bool addDirectionEast(graph* graph, int from_node, int to_node , char direction);
char hasDirectionEast(graph* graph, int from_node, int to_node);
void whatDirectionDoITake(graph* graph, int from_node, int to_node);
void printDirectionsWhenNorth(graph* graph);
void printDirectionsWhenSouth(graph* graph);
void printDirectionsWhenWest(graph* graph);
void printDirectionsWhenEast(graph* graph);
void printBarcodes(graph* graph);
void printHumps(graph* graph);
void printGraph(graph* graph);
void printMap(graph* graph, int rows, int columns);
void printAllMatrix(graph* graph);
bool checkAllNodesHasAtLeast1Edge(graph* graph);
void bytesConsumedByMap();
bool hasTraveledGrid(graph* map, int destination);
int nextGrid(int currentGrid,int columns, char direction, char orientation);
void updateGridVisited(graph* map, int destination);
void printGridVisited(graph* map);

#endif // !ADJACENCYMATRIX
