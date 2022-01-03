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

//Graphics sizes
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BLOCK_SIZE_X 100
#define BLOCK_SIZE_Y 40
#define BLOCK_TEXT_SIZE 16
#define MENU_TEXT_SIZE 13
#define BLOCK_MENU_BUTTON_SIZE_X 150
#define BLOCK_MENU_BUTTON_SIZE_Y 30
#define BORDER_THICKNESS 2

//Graphics colors
#define WINDOW_COLOR Black
#define START_BLOCK_COLOR Red
#define STOP_BLOCK_COLOR Red
#define GENERIC_BLOCK_COLOR Red
#define BLOCK_TEXT_COLOR White
#define MENU_COLOR Blue
#define MENU_BUTTON_COLOR White
#define MENU_BUTTON_TEXT_COLOR Black

//Text
#define MENU_BLOCK_CONNECTION "START CONNECTION"
#define MENU_BLOCK_T_CONNECTION "START T CONNECTION"
#define MENU_BLOCK_F_CONNECTION "START F CONNECTION"
#define MENU_BLOCK_FINISH_CONNECTION "END CONNECTION"
#define MENU_BLOCK_CHANGE_VARIABLE "SET VARIABLE"
#define MENU_BLOCK_CHANGE_EXPRESSION "SET EXPRESSION"
#define MENU_BLOCK_DELETE "DELETE"

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

// Interschem - 18
// Example video: https://www.youtube.com/watch?v=uxsv5s4Gcw0
// Example video: https://www.youtube.com/watch?v=dNKjpnduJy4
// Example video: https://www.youtube.com/watch?v=Hr3xLdh7Tt0
using namespace std;

struct LogicBlock {
    sf::RectangleShape block; //Visual block
    sf::Text blockTitle; //Visual text inside the block
    sf::Vector2f blockPos; //Position of the block
    int typeId=EMPTY_BLOCK; //Block type (check def)
    //char typeName[10]=NULL; //Block name
    int varId=-1; //Variable ID for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK
    char varFullExpression[VAR_EXPRESSION_SIZE]={NULL}; //Full math expression for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK or DECISION_BLOCK condition
    struct BlockConnectionPath {
        bool hasConnection=false; //true if block has atleast one connection
        int numberOfLinesNext=0; //Total number of lines for next path
        sf::Vertex nextPath[6][2]; //[line number][point of a line(0 or 1)]
        int numberOfLinesTru=0; //Total number of lines for true path
        sf::Vertex truPath[6][2]; //[line number][point of a line(0 or 1)]
        int numberOfLinesFls=0; //Total number of lines for false path
        sf::Vertex flsPath[6][2]; //[line number][point of a line(0 or 1)]
    }connectionPath;
    LogicBlock *prev=NULL; //Previous block
    LogicBlock *next=NULL; //Next block
    LogicBlock *tru=NULL; //Next block if true (for DECISION_BLOCK)
    LogicBlock *fls=NULL; //Next block if false (for DECISION_BLOCK)
};

struct WindowProps {
    bool mouseIsPressed=false;
    bool mouseIsMoving=false;
    struct BlockMenuProps {
        int blockMenuIsActive=0; // 0 if inactive or blockId otherwise
        int numberOfButtons=0; //Number of blocks for specific menu
        sf::Vector2f menuPos; // Position of the menu Background
        sf::RectangleShape menuBackground;
        sf::RectangleShape menuButtons[5];
        sf::Text menuButtonsTitle[5];
    }blockMenu;
    struct BlockProps {
        int blockIsBeingMoved=0; //0 if no block is being moved or blockId otherwise
        float xDif=0; //Distance between mouse and block origin
        float yDif=0; //Distance between mouse and block origin
    }block;
    struct BlockConnection {
        int masterBlockId=0; // blockId of the master block or 0 if no connection is being made
        int slaveBlockId=0; // blockId of the master block or 0 if no connection is being made
        bool path = false; // T/F path if the master block is DECISION_BLOCK
    }connection;
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
