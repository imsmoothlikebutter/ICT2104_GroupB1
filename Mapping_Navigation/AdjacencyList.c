#include "AdjacencyList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma pack(1)

typedef struct node{
    int nodeNumber;
    char directionWhenNorth;
    char directionWhenSouth;
    char directionWhenEast;
    char directionWhenWest;
    node* next;
    bool barcode;
    bool hump;
}node;

typedef struct graph{
    int numOfNodes;
    node* head;
    node** adjacencyList;
}graph;

node* createNode(int nodeNumber){
    node* result = malloc(sizeof(node));
    if(result != NULL){
        result->barcode = calloc(sizeof(bool),1);
        result->hump = calloc(sizeof(bool),1);
        result->hump = false;
        result->barcode = false;
        result->nodeNumber = nodeNumber;
        result->directionWhenNorth = '0';
        result->directionWhenSouth = '0';
        result->directionWhenEast = '0';
        result->directionWhenWest = '0';
        result->next = NULL;
    }
    return result;
}

graph* createGraph(int mapRow, int mapColumn){
    graph* result = malloc(sizeof(graph));
    if(result != NULL){
        result->numOfNodes = mapRow * mapColumn;
        result->adjacencyList = calloc(sizeof(node*),result->numOfNodes);
        for(int i = 0; i<result->numOfNodes; i++){
            result->adjacencyList[i] = createNode(i);
        }
        printf("Linked List Graph created!\n");
    }
    return result;
}

void destroyGraph(graph* map){
    for(int i = 0; i<map->numOfNodes;i++){
        free(map->adjacencyList[i]);
    }
    free(map->adjacencyList);
    free(map);
}

void addEdge(graph* map, int fromNode, int toNode, char direction, char orientation){
    //adding Edge for fromNode to toNode
    node* newNode = createNode(toNode);
    newNode->next = map->adjacencyList[fromNode];
    setDirections(newNode, direction, orientation);
    map->adjacencyList[fromNode] = newNode;

    //adding Edge for toNode to fromNode
    newNode = createNode(fromNode);
    newNode->next = map->adjacencyList[toNode];
    setDirections(newNode, oppositeDirection(direction), orientation);
    map->adjacencyList[toNode] = newNode;
}

void addBarcode(graph* map, int fromNode, int toNode){
    node* temp = map->adjacencyList[fromNode];
    while(temp->next != NULL){
        if(temp->nodeNumber == toNode){
            temp->barcode = true;
        }
        temp = temp->next;
    }
    temp = map->adjacencyList[toNode];
    while(temp->next != NULL){
        if(temp->nodeNumber == fromNode){
            temp->barcode = true;
        }
        temp = temp->next;
    }
}

void addHump(graph* map, int fromNode, int toNode){
    node* temp = map->adjacencyList[fromNode];
    while(temp->next != NULL){
        if(temp->nodeNumber == toNode){
            temp->hump = true;
        }
        temp = temp->next;
    }
    temp = map->adjacencyList[toNode];
    while(temp->next != NULL){
        if(temp->nodeNumber == fromNode){
            temp->hump = true;
        }
        temp = temp->next;
    }
}

char oppositeDirection(char direction){
    char returnDirection;
    if(direction == 'F'){
        returnDirection = 'B';
    }
    else if(direction == 'B'){
        returnDirection = 'F';
    }
    else if(direction == 'R'){
        returnDirection = 'L';
    }
    else if(direction == 'L'){
        returnDirection = 'R';
    }
    return returnDirection;
}

void setDirections(node* newNode, char direction, char orientation){
    switch(orientation){
        case 'N':
            newNode->directionWhenNorth = direction;
            switch(direction){
                case 'F':
                    newNode->directionWhenSouth = 'B';
                    newNode->directionWhenEast = 'L';
                    newNode->directionWhenWest = 'R';
                    break;
                case 'B':
                    newNode->directionWhenSouth = 'F';
                    newNode->directionWhenEast = 'R';
                    newNode->directionWhenWest = 'L';
                    break;
                 case 'R':
                    newNode->directionWhenSouth = 'L';
                    newNode->directionWhenEast = 'F';
                    newNode->directionWhenWest = 'B';
                    break;
                case 'L':
                    newNode->directionWhenSouth = 'R';
                    newNode->directionWhenEast = 'B';
                    newNode->directionWhenWest = 'F';
                    break;                   
                }
            break;
        case 'S':
            newNode->directionWhenSouth = direction;
            switch(direction){
                case 'F':
                    newNode->directionWhenNorth = 'B';
                    newNode->directionWhenEast = 'R';
                    newNode->directionWhenWest = 'L';
                    break;
                case 'B':
                    newNode->directionWhenNorth = 'F';
                    newNode->directionWhenEast = 'L';
                    newNode->directionWhenWest = 'R';
                    break;   
                case 'R':
                    newNode->directionWhenNorth = 'L';
                    newNode->directionWhenEast = 'B';
                    newNode->directionWhenWest = 'F';
                    break;
                case 'L':
                    newNode->directionWhenNorth = 'R';
                    newNode->directionWhenEast = 'F';
                    newNode->directionWhenWest = 'B';
                    break;                                                            
            }
            break;
        case 'E':
            newNode->directionWhenEast = direction;
            switch(direction){
                case 'F':
                    newNode->directionWhenNorth = 'R';
                    newNode->directionWhenSouth = 'L';
                    newNode->directionWhenWest = 'B';
                    break;
                case 'B':
                    newNode->directionWhenNorth = 'L';
                    newNode->directionWhenSouth = 'R';
                    newNode->directionWhenWest = 'F';
                    break;
                case 'R':
                    newNode->directionWhenNorth = 'B';
                    newNode->directionWhenSouth = 'F';
                    newNode->directionWhenWest = 'L';
                    break;
                case 'L':
                    newNode->directionWhenNorth = 'F';
                    newNode->directionWhenSouth = 'B';
                    newNode->directionWhenWest = 'R';
                    break;
            }
            break;
        case 'W':
            newNode->directionWhenWest = direction;
            switch(direction){
                case 'F':
                    newNode->directionWhenNorth = 'L';
                    newNode->directionWhenSouth = 'R';
                    newNode->directionWhenEast = 'B';
                    break;
                case 'B':
                    newNode->directionWhenNorth = 'R';
                    newNode->directionWhenSouth = 'L';
                    newNode->directionWhenEast = 'F';
                    break;
                case 'R':
                    newNode->directionWhenNorth = 'F';
                    newNode->directionWhenSouth = 'B';
                    newNode->directionWhenEast = 'L';
                    break;
                case 'L':
                    newNode->directionWhenNorth = 'B';
                    newNode->directionWhenSouth = 'F';
                    newNode->directionWhenEast = 'R';
                    break;
            }
            break;
    }
}

void printGraph(graph* map){
    printf("\nNode X: Node(North,South,East,West)\n");
    for(int i = 0; i<map->numOfNodes;i++){
        node* temp = map->adjacencyList[i];
        printf("Node %d: ", i);
        while (temp){
            printf("%d(%c,%c,%c,%c)B:%d,H:%d ", temp->nodeNumber,temp->directionWhenNorth,temp->directionWhenSouth,temp->directionWhenEast,temp->directionWhenWest,temp->barcode,temp->hump);
            if(temp->next != NULL){
                printf("<- ");
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

bool checkIfNodeIsConnected(graph* map, int fromNode, int toNode){
    bool returnBool;
    node* temp = map->adjacencyList[fromNode];
    while(temp->next != NULL){
        //printf("Checking next node\n");
        //printf("Node Number: %d\n", temp->nodeNumber);
        if(temp->nodeNumber == toNode){
            //printf("Node found!\n");
            returnBool = true;
        }
        temp = temp->next;
    }
    //if(returnBool == true){
    //    printf("%d and %d is connected!\n",fromNode, toNode);
    //}
    //else{
    //    printf("%d and %d is not connected!\n",fromNode,toNode);
    //}
    return returnBool;
}

bool checkForBarcode(graph* map, int fromNode, int toNode){
    bool returnBool;
    node* temp = map->adjacencyList[fromNode];
    while(temp->next != NULL){
        //printf("Checking next node\n");
        //printf("Node Number: %d\n", temp->nodeNumber);
        if(temp->nodeNumber == toNode){
            //printf("Node found!\n");
            if(temp->barcode == true){
                returnBool = true;
            }
        }
        temp = temp->next;
    }
    //if(returnBool == true){
    //    printf("%d and %d has barcode in between!\n",fromNode, toNode);
    //}
    //else{
    //    printf("%d and %d has barcode in between!\n",fromNode,toNode);
    //}
    return returnBool;
}

bool checkForHump(graph* map, int fromNode, int toNode){
    bool returnBool;
    node* temp = map->adjacencyList[fromNode];
    while(temp->next != NULL){
        //printf("Checking next node\n");
        //printf("Node Number: %d\n", temp->nodeNumber);
        if(temp->nodeNumber == toNode){
            //printf("Node found!\n");
            if(temp->hump == true){
                returnBool = true;
            }
        }
        temp = temp->next;
    }
    //if(returnBool == true){
    //    printf("%d and %d has hump in between!\n",fromNode, toNode);
    //}
    //else{
    //    printf("%d and %d has hump in between!\n",fromNode,toNode);
    //}
    return returnBool;
}

void printMap(graph* map, int row, int column){
    int printedMap[row][column];
    int nodesCounter = 0;
    printf("\n");
    for(int i = 0; i<row; i++){
        for(int j = 0; j<column; j++){
            printedMap[i][j] = nodesCounter++;
        }
    }
    for(int i = 0; i<row; i++){
        for(int j = 0; j<column; j++){
            if(j == column-1){
                printf("%03d\n",printedMap[i][j]);
                for(int k=0;k<column;k++){
                    if(i != row-1){
                        if(checkIfNodeIsConnected(map,printedMap[i][k],printedMap[i+1][k])){
                            printf("|");
                            if(checkForBarcode(map,printedMap[i][k],printedMap[i+1][k])){
                                printf("b");
                            }
                            else if(checkForHump(map,printedMap[i][k],printedMap[i+1][k])){
                                printf("h");
                            }
                            else{
                                printf("|");
                            }
                            printf("|   ");
                        }
                        else{
                            printf("|X|   ");
                        }
                    }
                }
                printf("\n");
            }
            else{
                printf("%03d",printedMap[i][j]);
                if(checkIfNodeIsConnected(map, printedMap[i][j],printedMap[i][j+1])){
                    printf("-");
                    if(checkForBarcode(map, printedMap[i][j],printedMap[i][j+1])){
                        printf("b");
                    }
                    else if(checkForHump(map, printedMap[i][j],printedMap[i][j+1])){
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

void bytesConsumedByMap(graph* map){
    printf("\n");
    printf("Bytes consumed by a node: %lu\n",sizeof(struct node));
    printf("Bytes consumed by %d nodes: %lu\n",map->numOfNodes,sizeof(struct node)*map->numOfNodes);
    printf("Bytes consumed by Graph: %lu\n",sizeof(struct graph));
}



