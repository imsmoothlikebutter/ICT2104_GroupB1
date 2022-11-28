#ifndef GRAPH
#define GRAPH
#include <stdbool.h>


typedef struct graph graph;
typedef struct queue queue;
typedef struct routeAndLength routeAndLength;
typedef struct node node;
queue* createQueue();
bool queueIsEmpty(queue* queue);
bool queueIsFull(queue* queue);
void enqueue(struct queue* queue, int num);
int dequeue(struct queue* queue);
node* createNode(int n);
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
int* BFS(graph* graph, int startingPoint, int endingPoint);
void DFS(graph* graph, int nodeNum,int endingPoint,int startingPoint);
void recursiveDFS(graph* graph, int nodeNum,int endingPoint, int startingPoint, queue* queue);
void printDFS(graph* graph,int endingPoint, int startingPoint,struct queue* queue);
void printAllMatrix(graph* graph);
bool checkAllNodesHasAtLeast1Edge(graph* graph);
int dijkstraMinDistance(int shortestDistance[], bool shortestSpanTreeSet[], int ROWS, int COLUMNS);
void printRouteOfShortestPath(int parent[], int j, int routeTaken[], int pos, int ROWS, int COLUMNS);
int* printDijkstraSolution(int shortestDistance[], int parent[], int src, int dest, int ROWS, int COLUMNS);
int* dijkstraTraversal(graph* graph, int src, int dest, int ROWS, int COLUMNS);
int getDijkstraNodes();
int nextGrid(int currentNode,int columns, char direction, char orientation);
bool hasTraveledGrid(graph* map, int destination);



#endif // !GRAPH
