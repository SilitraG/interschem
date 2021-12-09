//Block type Id
#define EMPTY_BLOCK 0
#define START_BLOCK 1
#define INPUT_BLOCK 2
#define OUTPUT_BLOCK 3
#define ASSIGN_BLOCK 4
#define DECISION_BLOCK 5
#define STOP_BLOCK 6

#include <iostream>

// Example video: https://www.youtube.com/watch?v=uxsv5s4Gcw0
using namespace std;


struct Variables {
    int varsNumber=0; //Total number of variables
    struct Variable {
        //int id;
        char name[30]; //Variable name
        long double value; //Variable value
    }Var[50];
}Vars;

struct LogicBlock {
    float xPos, yPos; //Position of the block
    int typeId=0; //Block type (check def)
    //char typeName[10]=NULL; //Block name
    int varId=-1; //Variable ID for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK
    char varFullExpression[50]={NULL}; //Full math expression for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK
    LogicBlock *next=NULL; //Next block
    LogicBlock *tru=NULL; //Next block if true (for DECISION_BLOCK)
    LogicBlock *fls=NULL; //Next block if false (for DECISION_BLOCK)
};

struct BlocksList {
    int numberOfBlocks = 0;
    LogicBlock *first; //First block of the code
    LogicBlock *last; //Last block of the code
}code;

#include "victor.h"
#include "florin.h"

int main()
{
///////////////// TESTE VICTOR /////////////////
    int blockType = EMPTY_BLOCK;
    char blockName[10];

    addStartBlock();

     /*
    while(blockType != STOP_BLOCK) {
        cout << "Introduceti instructiunea: ";
        cin >> blockName;
        blockType = blockNameToTypeConverter(blockName);
        blockTypeLogicCaller(blockType);
    }
     */
     
 ///////////////// TESTE FLORIN /////////////////
 /*   /////verificare functie postfixat
    char s[256];

    strcpy(s,"3+2*(1+5)+7");

    ///Ar trebui sa obtin 3215+*+7+

    calcul_expresie_f(s);
    
*/
    return 0;
}
