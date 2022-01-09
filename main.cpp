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
#define MAX_NUMBER_OF_CODE_LINE 200
#define MAX_LINE_OF_CODE_SIZE 255

//Window & app
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_COLOR Black

//Block
#define BLOCK_SIZE_X 100
#define BLOCK_SIZE_Y 40
#define BLOCK_TEXT_SIZE 16
#define START_BLOCK_COLOR sf::Color::Red
#define STOP_BLOCK_COLOR sf::Color::Red
#define GENERIC_BLOCK_COLOR sf::Color::Red
#define BLOCK_TEXT_COLOR sf::Color::White

//Block menu
#define BLOCK_MENU_BUTTON_SIZE_X 150
#define BLOCK_MENU_BUTTON_SIZE_Y 30
#define BLOCK_MENU_BORDER_THICKNESS 2
#define MENU_COLOR sf::Color::Blue
#define MENU_BUTTON_COLOR sf::Color::White
#define MENU_BUTTON_TEXT_COLOR sf::Color::Black
#define MENU_TEXT_SIZE 13
#define MENU_BLOCK_CONNECTION "START CONNECTION"
#define MENU_BLOCK_T_CONNECTION "START T CONNECTION"
#define MENU_BLOCK_F_CONNECTION "START F CONNECTION"
#define MENU_BLOCK_FINISH_CONNECTION "END CONNECTION"
#define MENU_BLOCK_CHANGE_VARIABLE "SET VARIABLE"
#define MENU_BLOCK_CHANGE_EXPRESSION "SET EXPRESSION"
#define MENU_BLOCK_DELETE "DELETE"

//App output
#define APP_OUTPUT_SIZE_X 350
#define APP_OUTPUT_SIZE_Y WINDOW_HEIGHT
#define APP_OUTPUT_POS_X (WINDOW_WIDTH-APP_OUTPUT_SIZE_X)
#define APP_OUTPUT_POS_Y 0
#define APP_OUTPUT_BORDER_THICKNESS 4
#define APP_OUTPUT_COLOR sf::Color(169,169,169)
#define APP_OUTPUT_BUTTON_COLOR sf::Color::White
#define APP_OUTPUT_BUTTON_TEXT_COLOR sf::Color::Black
#define APP_OUTPUT_BUTTON_TEXT_SIZE 15
#define APP_OUTPUT_RUN_CODE "RUN CODE"
#define APP_OUTPUT_GENERATE_CODE "GENERATE CODE"

//Block add menu
#define ADD_BLOCK_MENU_SIZE_X 140
#define ADD_BLOCK_MENU_POS_X 0
#define ADD_BLOCK_MENU_POS_Y 0
#define ADD_BLOCK_MENU_COLOR sf::Color(169,169,169)
#define ADD_BLOCK_MENU_TEXT_SIZE BLOCK_TEXT_SIZE
#define ADD_BLOCK_MENU_TEXT_COLOR sf::Color::Black
#define UNDERLINE_COLOR sf::Color::Black

//App menu
#define APP_MENU_SIZE_X (WINDOW_WIDTH-APP_OUTPUT_SIZE_X)
#define APP_MENU_SIZE_Y (50+2*APP_OUTPUT_BORDER_THICKNESS)
#define APP_MENU_POS_X 0
#define APP_MENU_POS_Y 0
#define APP_MENU_COLOR sf::Color(169,169,169)
#define NUMBER_OF_APP_MENU_BUTTONS 5

//User input
#define USER_INPUT_SIZE_X 600
#define USER_INPUT_SIZE_Y 300
#define USER_INPUT_POS_X (ADD_BLOCK_MENU_SIZE_X+(WINDOW_WIDTH-APP_OUTPUT_SIZE_X-USER_INPUT_SIZE_X-ADD_BLOCK_MENU_SIZE_X)/2)
#define USER_INPUT_POS_Y ((WINDOW_HEIGHT-USER_INPUT_SIZE_Y)/2)
#define USER_INPUT_BACKGROUND_COLOR sf::Color::White
#define USER_INPUT_BACKGROUND_BORDER_COLOR sf::Color(169,169,169)
#define USER_INPUT_BACKGROUND_BORDER_THICKNESS 4
#define USER_INPUT_FIELD_SIZE_X 350
#define USER_INPUT_FIELD_SIZE_Y 40
#define USER_INPUT_FIELD_POS_X (USER_INPUT_POS_X+200)
#define USER_INPUT_FIELD_TITLE_X (USER_INPUT_POS_X+30)
#define USER_INPUT_BUTTON_SIZE_X 130
#define USER_INPUT_BUTTON_SIZE_Y 50
#define USER_INPUT_BUTTON_POS_Y (USER_INPUT_POS_Y+USER_INPUT_SIZE_Y-70)


#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

// Interschem - 18
// Example video: https://www.youtube.com/watch?v=uxsv5s4Gcw0
// Example video: https://www.youtube.com/watch?v=dNKjpnduJy4
// Example video: https://www.youtube.com/watch?v=Hr3xLdh7Tt0
using namespace std;

struct BlockConnectionPath {
    bool hasConnection=false; //true if block has atleast one connection
    int numberOfLinesNext=0; //Total number of lines for next path
    sf::Vertex nextPath[6][2]; //[line number][point of a line(0 or 1)]
    int numberOfLinesTru=0; //Total number of lines for true path
    sf::Vertex truPath[6][2]; //[line number][point of a line(0 or 1)]
    int numberOfLinesFls=0; //Total number of lines for false path
    sf::Vertex flsPath[6][2]; //[line number][point of a line(0 or 1)]
};

struct LogicBlock {
    sf::RectangleShape block; //Visual block
    sf::Text blockTitle; //Visual text inside the block
    sf::Vector2f blockPos; //Position of the block
    int typeId=EMPTY_BLOCK; //Block type (check def)
    int varId=-1; //Variable ID for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK
    char varFullExpression[VAR_EXPRESSION_SIZE]={NULL}; //Full math expression for INPUT_BLOCK, ASSIGN_BLOCK and OUTPUT_BLOCK or DECISION_BLOCK condition
    BlockConnectionPath connectionPath; //All the slave graphical connections
    int numberOfPrevs=0;
    LogicBlock *prev[MAX_NUMBER_OF_BLOCKS]={NULL}; //All previous blocks
    LogicBlock *next=NULL; //Next block
    LogicBlock *tru=NULL; //Next block if true (for DECISION_BLOCK)
    LogicBlock *fls=NULL; //Next block if false (for DECISION_BLOCK)
};

struct BlockProps {
    int blockIsBeingMoved=0; //0 if no block is being moved or blockId otherwise
    float xDif=0; //Distance between mouse and block origin
    float yDif=0; //Distance between mouse and block origin
};

struct BlockMenuProps {
    int blockMenuIsActive=false; // 0 if inactive or blockId otherwise
    int numberOfButtons=0; //Number of blocks for specific menu
    sf::Vector2f menuPos; // Position of the menu Background
    sf::RectangleShape menuBackground;
    sf::RectangleShape menuButtons[5];
    sf::Text menuButtonsTitle[5];
};

struct BlockConnection {
    int masterBlockId=0; // blockId of the master block or 0 if no connection is being made
    int slaveBlockId=0; // blockId of the master block or 0 if no connection is being made
    bool path=false; // T/F path if the master block is DECISION_BLOCK
};

struct AddBlockMenu {
    int blockIsBeingAdded=false; // true if a block is in "add mode" or false otherwise
    sf::RectangleShape addBlockMenuBackground; // Background for the "add block" menu
    sf::Text menuTitle; // Add Block Menu title
    sf::RectangleShape dummyBlock[6]; //Dummy visual block (only visual, not movable)
    sf::Text dummyBlockTitle[6]; //Visual text inside the dummy block
    sf::Vertex underline[2];
};

struct AppMenu {
    sf::RectangleShape appMenuBackground;
    sf::RectangleShape appMenuButton[NUMBER_OF_APP_MENU_BUTTONS];
    sf::Text appMenuButtonText[NUMBER_OF_APP_MENU_BUTTONS];
};

struct AppOutput {
    sf::RectangleShape appOutputBackground;
    sf::RectangleShape appOutputArea;
    sf::RectangleShape appOutputButton[3];
    sf::Text appOutputButtonText[3];
};

struct UserInput {
    int inputIsActive=false; // id of the block or false
    int activeField=1; // id of the active input field
    int numberOfFields=1;
    sf::RectangleShape userInputBackground;
    sf::Text userInputTitle;
    sf::RectangleShape userInputField[3];
    sf::Text userInputText[3];
    sf::Text fieldTitle[3];
    sf::String userInputString[3];
    sf::RectangleShape userInputButton[3];
    sf::Text userInputButtonText[3];
};

struct WindowProps {
    bool mouseIsPressed=false;
    bool mouseIsMoving=false;
    BlockProps block; //For moving a block
    BlockMenuProps blockMenu; //For the menu of each block
    BlockConnection connection; //For making a connection
    AddBlockMenu addBlockMenu; //For the menu where you can add a new block
    AppMenu appMenu; //Global menu for the app
    AppOutput appOutput; //Code output
    UserInput userInput;
    sf::Vector2f mousePos; //Mouse position
};

struct Variables {
    int varsNumber=0; //Total number of variables
    struct Variable {
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
     ///////////////// TESTE FLORIN /////////////////
    /////verificare functie postfixat
    /*
    char s[256];
    strcpy(s,"30+2*(10+5)+7");
    ///Ar trebui sa obtin 3215+*+7+
    int val = calcul_expresie_f(s);
    cout << val;
    cout << "\n\n";
    strcpy(s, "30 / 3 == 5 * 2");
    if(valoare_adevar_expresie(s))
    {
        cout << "Adevarat";
    }
    else
    {
        cout << "True";
    }
    cout << "\n\n";
    char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE];
    int code_line_size = 0;
    output_code(code.first, code.vars, code_text, code_line_size);
    */
    return 0;
}
