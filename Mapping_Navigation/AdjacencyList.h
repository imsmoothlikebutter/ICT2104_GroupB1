#ifndef ADJACENCYLIST
#define ADJACENCYLIST

#include <stdbool.h>


typedef struct node node;
typedef struct graph graph;
void destroyGraph(graph* map);
graph* createGraph(int mapRow, int mapColumn);
node* createNode(int nodeNumber);
void addEdge(graph* map, int from, int to, char direction, char orientation);
void addBarcode(graph* map, int fromNode, int toNode);
void addHump(graph* map, int fromNode, int toNode);
void printGraph(graph* map);
void printBarcodes(graph* map);
void setDirections(node* newNode, char direction, char orientation);
char oppositeDirection(char direction);
void printMap(graph* map, int row, int column);
bool checkIfNodeIsConnected(graph* map, int from, int to);
bool checkForBarcode(graph* map, int fromNode, int toNode);
bool checkForHump(graph* map, int fromNode, int toNode);
void bytesConsumedByMap();

#endif // !ADJACENCYLIST
