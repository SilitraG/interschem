#include <iostream>
#include <cstring>
#include "victor.h"
#include "florin.h"

// Example video: https://www.youtube.com/watch?v=uxsv5s4Gcw0
using namespace std;

//Block type
#define EMPTY_BLOCK 0
#define START_BLOCK 1
#define INPUT_BLOCK 2
#define OUTPUT_BLOCK 3
#define ASSIGN_BLOCK 4
#define DECISION_BLOCK 5
#define STOP_BLOCK 6

struct variables {
    int id;
    char name[30];
    long int value;
}var[101];

struct logicBlocks {
    float xPos, yPos;
    int typeId;
    char typeName[10];
};

int main()
{
    int blockType = EMPTY_BLOCK;
    char blockName[10];

    while(blockType != STOP_BLOCK) {
        cout << "Introduceti instructiunea: ";
        cin >> blockName;
        blockType = blockTypeDecider(blockName);
        //blockTypeCaller(blockType);
    }

    return 0;
}
