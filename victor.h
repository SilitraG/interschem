#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Input: variable name
//Output: variable index or -1(doesn't exist)
int variableNameToIndex(char varName[]) {
    for(int i = 1; i <= code.vars.varsNumber; i++) {
        if(strcmp(varName, code.vars.var[i].name) == 0) {
            return i;
        }
    }

    return -1;

}

//Input: variable name
//Output: id of the variable
int addVariable(char varName[]) {
    if(variableNameToIndex(varName) != -1) {
        return variableNameToIndex(varName);
    }
    code.vars.varsNumber++;
    strcpy(code.vars.var[code.vars.varsNumber].name, varName);
    return code.vars.varsNumber;
}

//Input:  blockId of decision block, T/F path
//Starts a connection from decision master block
void startConnectionDecision(int blockId, bool path) {
    code.appProps.connection.masterBlockId = blockId;
    code.appProps.connection.path = path;

}

//Input: master blockId
//Starts a connection
void startConnection(int blockId) {
    //cout << "Connection blockId: " << blockId << ' ';
    if(code.appProps.connection.masterBlockId == false) {
        code.appProps.connection.masterBlockId = blockId;
    }

}

void appendCharToString(char chars[], string &s) {
    for (int i = 0; i < strlen(chars); i++) {
        if(int(chars[i]) != 8) {
            s = s + chars[i];
        } else if(!s.empty()) {
            s.resize(s.size() - 1);
        }
    }

}

/// ----------- BLOCK ADD FUNCTIONS -----------

//Input: -
//Create and add a START block to the code list
void addStartBlock(int blockId) {
    code.allBlocks[blockId]->typeId = START_BLOCK;
    code.first = code.allBlocks[blockId];

}

/// ----------- END OF BLOCK ADD FUNCTIONS -----------

// Input: block Name
// Output: block type Id
int blockNameToTypeConverter(char blockName[]) {
    if(strcmp(blockName, "start") == 0) {
        return START_BLOCK;
    }
    if(strcmp(blockName, "input") == 0) {
        return INPUT_BLOCK;
    }
    if(strcmp(blockName, "output") == 0) {
        return OUTPUT_BLOCK;
    }
    if(strcmp(blockName, "assign") == 0) {
        return ASSIGN_BLOCK;
    }
    if(strcmp(blockName, "decision") == 0) {
        return DECISION_BLOCK;
    }
    if(strcmp(blockName, "stop") == 0) {
        return STOP_BLOCK;
    }
    return EMPTY_BLOCK;

}

string blockTypeToString(int blockType) {
    switch (blockType) {
        case START_BLOCK:
            return "START";
        case INPUT_BLOCK:
            return "INPUT";
        case OUTPUT_BLOCK:
            return "OUTPUT";
        case ASSIGN_BLOCK:
            return "ASSIGN";
        case DECISION_BLOCK:
            return "DECISION";
        case STOP_BLOCK:
            return "STOP";
        default:
            cerr << "Instructiune incorecta\n";
    }
}

//Input: The first block of the list
//Iterates trough the list
void codeIterator(LogicBlock *block) {
    if(block != NULL){
        switch (block->typeId) {
            case START_BLOCK:
                cout << "start ";
                break;
            case INPUT_BLOCK:
                cout << "input ";
                break;
            case OUTPUT_BLOCK:
                cout << "output ";
                break;
            case ASSIGN_BLOCK:
                cout << "assign ";
                break;
            case DECISION_BLOCK: {
                cout << "decision ";
                bool truthValue = true;//decisionBlockLogic(block);
                //if(truthValue) {
                //    block=block->tru;
                //} else {
                //    block=block->fls;
                //}
                break;
            }
            case STOP_BLOCK:
                cout << "stop ";
                break;
            default:
                cerr << "Instructiune incorecta\n";
        }
        if(block->typeId == DECISION_BLOCK) {
            codeIterator(block->tru);
            codeIterator(block->fls);
        } else {
            codeIterator(block->next);
        }
    }

}

//Shows the used variables
void varTester(int &numberOfLines, char codeOutput[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE]) {
    //cout << '\n';
    char varValue[51];
    for(int i = 1; i <= code.vars.varsNumber; i++) {
        numberOfLines++;
        strcat(codeOutput[numberOfLines], "  ");
        strcat(codeOutput[numberOfLines], code.vars.var[i].name);
        strcat(codeOutput[numberOfLines], "  ");
        itoa(code.vars.var[i].value, varValue, 10);
        strcat(codeOutput[numberOfLines], varValue);
        //cout << code.vars.var[i].name << ' ' << code.vars.var[i].value << ' ';
    }
    //cout << '\n';
}
