#include <stdio.h>
#include<stdlib.h>
#include <pico/stdlib.h>
#include <string.h>
#include "AdjacencyMatrix.h"
#include "hardware/gpio.h"
#define ROWS 4
#define COLUMNS 4
#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E'
#define WEST 'W'

void ifReachStartingPoint(graph* map, int startingPoint, int currentPosition,char startingPointDirectionTaken,bool* frontSensor,bool*leftSensor,bool*rightSensor,char startingOrientation, char orientation){
    if(currentPosition == startingPoint){
        if(startingOrientation == orientation){
            if(startingPointDirectionTaken == 'F'){
                *frontSensor = true;
            }
            if(startingPointDirectionTaken == 'R'){
                *rightSensor = true;
            }
            if(startingPointDirectionTaken == 'L'){
                *leftSensor = true;
            }
        }
        printf("Reached Starting Point!\n");
    }
}

void moveForward(graph* map,int* currentPosition, char orientation, int* beforePosition,bool barcode, bool hump){
    printf("Moving Forward\n");
    int tempFromNode = *currentPosition;
    *currentPosition = nextGrid(*currentPosition,COLUMNS,'F',orientation);
    addEdge(map,tempFromNode, *currentPosition);
    addDirection(map, tempFromNode, *currentPosition, 'F',orientation);
    if(barcode){
        addBarcode(map, tempFromNode, *currentPosition);
    }
    if(hump){
        addHump(map, tempFromNode, *currentPosition);
    }
}

void turnRight(graph* map,int* currentPosition, char orientation, int* beforePosition,bool barcode, bool hump){
    printf("Turning Right\n");
    *beforePosition = *currentPosition;
    int tempFromNode = *currentPosition;
    *currentPosition = nextGrid(*currentPosition,COLUMNS,'R',orientation);
    addEdge(map,tempFromNode, *currentPosition);
    addDirection(map, tempFromNode, *currentPosition, 'R',orientation);
    if(barcode){
        addBarcode(map, tempFromNode, *currentPosition);
    }
    if(hump){
        addHump(map, tempFromNode, *currentPosition);
    }
}

void turnLeft(graph* map,int* currentPosition, char orientation, int* beforePosition,bool barcode, bool hump){
    printf("Turning Left\n");
    *beforePosition = *currentPosition;
    int tempFromNode = *currentPosition;
    *currentPosition = nextGrid(*currentPosition,COLUMNS,'L',orientation);
    addEdge(map,tempFromNode, *currentPosition);
    addDirection(map, tempFromNode, *currentPosition, 'L',orientation);
    if(barcode){
        addBarcode(map, tempFromNode, *currentPosition);
    }
    if(hump){
        addHump(map, tempFromNode, *currentPosition);
    }
}

void reverseRight(graph* map,int* currentPosition, char orientation, int* beforePosition){
    printf("Reversing Right\n");
    int temp = *currentPosition;
    *currentPosition = *beforePosition;
    *beforePosition = temp;

}

void reverseLeft(graph* map,int* currentPosition, char orientation, int* beforePosition){
    printf("Reversing Left\n");
    int temp = *currentPosition;
    *currentPosition = *beforePosition;
    *beforePosition = temp;
}

void reverseBack(graph* map,int* currentPosition, char orientation, int* beforePosition){
    printf("Reverse\n");
    int temp = *currentPosition;
    *currentPosition = nextGrid(*currentPosition,COLUMNS,'B',orientation);
    *beforePosition = temp;
}

int main(){
    stdio_init_all();
    bool frontSensor,leftSensor,rightSensor,barcode,hump;
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    int currentPosition,beforePosition,startingPoint;
    char startingPointDirectionTaken;
    char startingPointDirectionTaken2;
    char startingPointDirectionTaken3;
    char directionTaken;
    char reverseDirectionTaken[3];
    char forward = 'F';
    char left = 'L';
    char right = 'R';
    char reverse = 'B';
    char startingOrientation = 'N';
    char orientation ='N'; //relative compass
    //whenever car turns left, orientation becomes East
    //whenever car turns right, orientation becomes West
    //char* orientationptr = &orientation;
    char userInput[2];
    bool userInputValid = false;
    bool mapping = false;
    gpio_put(LED_PIN, 1);
    sleep_ms(2000);
    printf("Set Starting Point to start Mapping:\n");
    while(!userInputValid){
        gets(userInput);
        printf("String: %s\n",userInput);
        currentPosition= atoi(userInput);
        if(currentPosition < ROWS*COLUMNS){
            printf("VALID STARTING POINT!\n");
            userInputValid = true;
            beforePosition = currentPosition;
            startingPoint = currentPosition;
        }else{
            printf("Please Enter Valid Starting Point!\n");
        }
    }
    printf("Current Position: %d\n",currentPosition);


    graph* map = createGraph(ROWS,COLUMNS);
    //Moving from grid 10 to 6;
    frontSensor = false;
    leftSensor = false;
    rightSensor = false;
    orientation = NORTH;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        startingPointDirectionTaken = 'F';
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        startingPointDirectionTaken = 'R';
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        startingPointDirectionTaken = 'L';
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 6 to 7;
    orientation = NORTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = false;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 7 to 6;
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 6 to 5;
    orientation = NORTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = false;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 5 to 4;
    orientation = WEST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = false;
    leftSensor = false;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = WEST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 4 to 0;
    frontSensor = true;
    leftSensor = false;
    rightSensor = false;
    barcode = false;
    hump = true;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = NORTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 0 to 1;
    frontSensor = true;
    leftSensor = true;
    rightSensor = false;
    barcode = false;
    hump = false; 
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 1 to 2;
    frontSensor = false;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 2 to 3;
    frontSensor = false;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 3 to 2;
    frontSensor = true;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 2 to 1;
    frontSensor = true;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //Moving from grid 1 to 0;
    frontSensor = true;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 0 to 4;
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = true;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 4 to 8;
    orientation = SOUTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = false;
    leftSensor = false;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 8 to 12;
    orientation = SOUTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = false;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 12 to 13;
    orientation = SOUTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = false;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 13 to 14;
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = false;
    leftSensor = false;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };    
    //Moving from grid 14 to 10;
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = false;
    rightSensor = true;
    barcode = true;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 10 to 11;
    orientation = NORTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    //frontSensor = true;
    leftSensor = false;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 11 to 15;
    orientation = EAST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = true;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 15 to 11;
    orientation = SOUTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation); 
    frontSensor = true;
    leftSensor = true;
    rightSensor = true;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 11 to 10;
    orientation = SOUTH;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = true;
    leftSensor = true;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    //Moving from grid 10 to ?;
    orientation = WEST;
    ifReachStartingPoint(map,startingPoint,currentPosition,startingPointDirectionTaken,&frontSensor,&leftSensor,&rightSensor,startingOrientation,orientation);
    frontSensor = false;
    leftSensor = false;
    rightSensor = false;
    barcode = false;
    hump = false;
    if(frontSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'F';
        strcpy("B",reverseDirectionTaken);
        moveForward(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'R';
        strcpy("RR",reverseDirectionTaken);
        turnRight(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == false){
        beforePosition = currentPosition;
        directionTaken = 'L';
        strcpy("RL",reverseDirectionTaken);
        turnLeft(map,&currentPosition, orientation,&beforePosition,barcode,hump);
        printf("Current Position: %d, Before Position: %d, Direction Taken: %c\n",currentPosition,beforePosition,directionTaken);
    }
    if(frontSensor == true && rightSensor == true && leftSensor == true){
        if(directionTaken == 'R'){
            reverseRight(map,&currentPosition, orientation,&beforePosition);
            rightSensor = true;
        }
        if(directionTaken == 'L'){
            reverseLeft(map,&currentPosition, orientation,&beforePosition);
            leftSensor = true;
        }
        if(directionTaken == 'F'){
            reverseBack(map,&currentPosition, orientation,&beforePosition);
            frontSensor = true;
        }
        printf("Current Position: %d, Before Position: %d, Direction Taken: Reverse %c\n",currentPosition,beforePosition,directionTaken);
    }
    updateGridVisited(map, beforePosition);
    if(checkAllNodesHasAtLeast1Edge(map)){
        updateGridVisited(map,currentPosition);
        printf("Mapping Ended!\n");
    };
    

    // 0 1 2 3
    // 4 5 6 7
    // 8 9 10 11
    



    //printing all different matrices
    //printEdges(map);
    //printing the graph in dot format
    //printGraph(map);

    //bytesConsumedByMap();

    //printing the graph in a grid map format

    //whatDirectionDoITake(map, 0,1);


    printf("\n\n\n");
    printAllMatrix(map);
    printGridVisited(map);
    printMap(map, ROWS, COLUMNS);
    bytesConsumedByMap();
    //freeing mem
    destroyGraph(map);
    //free(dijkstraNodes);
    //return 0;
}
