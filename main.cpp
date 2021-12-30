//Block type Id
#define EMPTY_BLOCK 0
#define START_BLOCK 1
#define INPUT_BLOCK 2
#define OUTPUT_BLOCK 3
#define ASSIGN_BLOCK 4
#define DECISION_BLOCK 5
#define STOP_BLOCK 6

//Sizes
#define MAX_NUMBER_OF_VARS 51
#define VAR_NAME_SIZE 31
#define VAR_EXPRESSION_SIZE 51
#define MAX_NUMBER_OF_BLOCKS 51

//Graphics
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_COLOR Black
#define START_BLOCK_COLOR Green
#define STOP_BLOCK_COLOR Red
#define GENERIC_BLOCK_COLOR White
#define BLOCK_SIZE_X 100
#define BLOCK_SIZE_Y 40


#include <iostream>
#include <SFML/Graphics.hpp>

// Interschem - 18
// Example video: https://www.youtube.com/watch?v=uxsv5s4Gcw0
// Example video: https://www.youtube.com/watch?v=dNKjpnduJy4
// Example video: https://www.youtube.com/watch?v=Hr3xLdh7Tt0
using namespace std;

struct WindowProps {
    bool mouseIsPressed = false;
    bool mouseIsMoving = false;
    struct BlockProps {
        int blockIsBeingMoved = 0; //0 if no block is being moved or block id otherwise
        float xDif=0; //
        float yDif=0; //Distance between mouse and block origin
    }block;
    sf::Vector2f mousePos; //Mouse position
};

struct Variables {
    int varsNumber=0; //Total number of variables
    struct Variable {
        //int id;
        char name[VAR_NAME_SIZE]; //Variable name
        long double value; //Variable value
    }var[MAX_NUMBER_OF_VARS];
};

struct LogicBlock {
    sf::RectangleShape block;
    sf::Vector2f blockPos; //Position of the block
    int typeId=0; //Block type (check def)
    //char typeName[10]=NULL; //Block name
    int varId=-1; //Variable ID for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK
    char varFullExpression[VAR_EXPRESSION_SIZE]={NULL}; //Full math expression for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK or DECISION_BLOCK condition
    LogicBlock *next=NULL; //Next block
    LogicBlock *tru=NULL; //Next block if true (for DECISION_BLOCK)
    LogicBlock *fls=NULL; //Next block if false (for DECISION_BLOCK)
};

struct BlocksList {
    Variables vars; //The vars created and used by the code
    int numberOfBlocks = 0;
    LogicBlock *allBlocks[MAX_NUMBER_OF_BLOCKS]= {NULL}; //All blocks in adding order
    LogicBlock *first=NULL; //First block of the code
    LogicBlock *last=NULL; //Last block of the code
    WindowProps appProps; //Props for graphics
}code;

#include "struct.h"
#include "florin.h"
#include "victor.h"
#include "victor_graphics.h"
#include "main_graphics.h"

int main()
{
///////////////// TESTE VICTOR /////////////////
    //codeCreator();
    //codeIterator(code.first);
    //varTester();
    appWindow();

 ///////////////// TESTE FLORIN /////////////////
 /*   /////verificare functie postfixat
    char s[256];

    strcpy(s,"3+2*(1+5)+7");

    ///Ar trebui sa obtin 3215+*+7+

    calcul_expresie_f(s);

*/
    return 0;
}
