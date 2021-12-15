#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Input: variable name
//Output: variable index or -1(doesn't exist)
int variableNameToIndex(char name[]) {
    int index = -1;

    for(int i = 1; i <= Vars.varsNumber; i++) {
        if(strcmp(name, Vars.var[i].name) == 0) {
            index=i;
        }
    }

    return index;

}

// ----------- BLOCK LOGIC FUNCTIONS -----------

void startBlockLogic(LogicBlock *block) {
    return;

}

void stopBlockLogic(LogicBlock *block) {
    return;

}

void inputBlockLogic(LogicBlock *block) {
    long double finalValue = stod(block->varFullExpression); //*toDo: change to full expression

    Vars.var[block->varId].value = finalValue;
}

void outputBlockLogic(LogicBlock *block) {
    cout << Vars.var[block->varId].value << ' ';

}

void assignBlockLogic(LogicBlock *block) {
    long double finalValue = stod(block->varFullExpression); //*toDo: change to full expression

    Vars.var[block->varId].value = finalValue;
}

bool decisionBlockLogic(LogicBlock *block) {
    bool finalExpressionTruthValue = false; //*toDo: change to full expression
    return finalExpressionTruthValue;

}
// ----------- END OF BLOCK LOGIC FUNCTIONS -----------


// ----------- BLOCK ADD FUNCTIONS -----------

//Input: -
//Create and add a START block to the code list
void addStartBlock(LogicBlock *& parentBlockPointer) {
    LogicBlock *block = new LogicBlock;
    block->typeId = START_BLOCK;

    code.numberOfBlocks=1;
    code.first = block;
    code.last = block;
}

//Input: "next" pointer of previous block,
//Create and add a STOP block to the code list
void addStopBlock(LogicBlock *& parentBlockPointer) {
    LogicBlock *block = new LogicBlock;
    block->typeId = STOP_BLOCK;

    code.numberOfBlocks++;
    parentBlockPointer = block;
    code.last = block;
    return;

}

//Input: - (not finished)
//Create and add an INPUT block to the code list
void addInputBlock(LogicBlock *& parentBlockPointer) {
    char newVarName[VAR_NAME_SIZE];
    long double newVarValue; //*toDo: change to full expression
    int newVarId;
    cout << "Introduceti numele variabilei: ";
    cin >> newVarName;
    cout << "Introduceti valoarea: ";
    cin >> newVarValue; //*toDo: change to full expression

    newVarId = variableNameToIndex(newVarName);
    if(newVarId == -1) {
        Vars.varsNumber++;
        newVarId = Vars.varsNumber;
        strcpy(Vars.var[Vars.varsNumber].name, newVarName);
    }

    LogicBlock *block = new LogicBlock;
    block->typeId = INPUT_BLOCK;
    block->varId = newVarId;
    char temporaryExpression[50];
    itoa(newVarValue, temporaryExpression, 10);
    strcpy(block->varFullExpression, temporaryExpression); //*toDo: change to full expression

    code.numberOfBlocks++;
    parentBlockPointer = block;
    code.last = block;

}

//Input: - (not finished)
//Create and add an OUTPUT block to the code list
void addOutputBlock(LogicBlock *& parentBlockPointer) {
    char name[VAR_NAME_SIZE];

    cout << "Introduceti numele variabilei: ";
    cin >> name;
    int varId = variableNameToIndex(name);

    LogicBlock *block = new LogicBlock;
    block->typeId = OUTPUT_BLOCK;
    if(varId != -1) {
        block->varId = varId;
    } else {
        cerr << "Variablia inexistenta";
    }

    code.numberOfBlocks++;
    parentBlockPointer = block;
    code.last = block;

}

//Input: - (not finished)
//Create and add an ASSIGN block to the code list
void addAssignBlock(LogicBlock *& parentBlockPointer) {
    char varName[VAR_NAME_SIZE];
    long double varValue; //*toDo: change to full expression

    cout << "Introduceti numele variabilei: ";
    cin >> varName;
    cout << "Introduceti valoarea: ";
    cin >> varValue; //*toDo: change to full expression

    int varId = variableNameToIndex(varName);
    if(varId == -1) {
        Vars.varsNumber++;
        varId = Vars.varsNumber;
        strcpy(Vars.var[Vars.varsNumber].name, varName);
    }

    LogicBlock *block = new LogicBlock;
    block->typeId = ASSIGN_BLOCK;
    block->varId = varId;
    char temporaryExpression[50];
    itoa(varValue, temporaryExpression, 10);
    strcpy(block->varFullExpression, temporaryExpression); //*toDo: change to full expression

    code.numberOfBlocks++;
    parentBlockPointer = block;
    code.last = block;

}

//Input: - (not finished)
//Create and add a DECISION block to the code list
void addDecisionBlock(LogicBlock *& parentBlockPointer) {
    char ifCondition[VAR_EXPRESSION_SIZE];
    cout << "Introduceti conditia: ";
    cin >> ifCondition;

    LogicBlock *block = new LogicBlock;
    block->typeId = DECISION_BLOCK;
    strcpy(block->varFullExpression, ifCondition);

    code.numberOfBlocks++;
    parentBlockPointer = block;
    code.last = block;

}
// ----------- END OF BLOCK ADD FUNCTIONS -----------

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

// Input: block type Id
// Calls the logic function for the needed block
void addBlockCaller(int blockType, LogicBlock *& parentBlockPointer) {
    switch (blockType) {
        case START_BLOCK:
            addStartBlock(parentBlockPointer);
            break;
        case INPUT_BLOCK:
            addInputBlock(parentBlockPointer);
            break;
        case OUTPUT_BLOCK:
            addOutputBlock(parentBlockPointer);
            break;
        case ASSIGN_BLOCK:
            addAssignBlock(parentBlockPointer);
            break;
        case DECISION_BLOCK:
            addDecisionBlock(parentBlockPointer);
            break;
        case STOP_BLOCK:
            addStopBlock(parentBlockPointer);
            break;
        default:
            cout << "Instructiune incorecta\n";
    }

}

//Input: The first block of the list
//Iterates trough the list and calls the logic functions for each block
void codeIterator(LogicBlock *block) {
    while(block != NULL){
        switch (block->typeId) {
            case START_BLOCK:
                cout << "start ";
                startBlockLogic(block);
                block=block->next;
                break;
            case INPUT_BLOCK:
                cout << "input ";
                inputBlockLogic(block);
                block=block->next;
                break;
            case OUTPUT_BLOCK:
                cout << "output ";
                outputBlockLogic(block);
                block=block->next;
                break;
            case ASSIGN_BLOCK:
                cout << "assign ";
                assignBlockLogic(block);
                block=block->next;
                break;
            case DECISION_BLOCK: {
                cout << "decision ";
                bool truthValue = decisionBlockLogic(block);
                if(truthValue) {
                    block=block->tru;
                } else {
                    block=block->fls;
                }
                break;
            }
            case STOP_BLOCK:
                cout << "stop ";
                stopBlockLogic(block);
                block=block->next;
                break;
            default:
                cerr << "Instructiune incorecta\n";
        }
    }
}

//Shows the used variables
void varTester() {
    cout << '\n';
    for(int i = 1; i <= Vars.varsNumber; i++) {
        cout << Vars.var[i].name << ' ' << Vars.var[i].value << ' ';
    }
    cout << '\n';
}

void codeCreator() {
    int blockType = EMPTY_BLOCK;
    char blockName[10];

    while(blockType != STOP_BLOCK) {
        cout << "Introduceti instructiunea: ";
        cin >> blockName;
        blockType = blockNameToTypeConverter(blockName);
        if(blockType == DECISION_BLOCK) {
            addBlockCaller(blockType, code.last->next);
            LogicBlock *decisionBlock = new LogicBlock;
            decisionBlock = code.last;
            cout << "IF: Introduceti instructiunea: ";
            cin >> blockName;
            if(strcmp(blockName, "stopif")){
                blockType = blockNameToTypeConverter(blockName);
                addBlockCaller(blockType, decisionBlock->tru);
                cout << "IF: Introduceti instructiunea: ";
                cin >> blockName;
                while(strcmp(blockName, "stopif")){
                    blockType = blockNameToTypeConverter(blockName);
                    addBlockCaller(blockType, code.last->next);
                    cout << "IF: Introduceti instructiunea: ";
                    cin >> blockName;
                }
            }

            cout << "ELSE: Introduceti instructiunea: ";
            cin >> blockName;
            if(strcmp(blockName, "stopelse")){
                blockType = blockNameToTypeConverter(blockName);
                addBlockCaller(blockType, decisionBlock->fls);
                cout << "ELSE: Introduceti instructiunea: ";
                cin >> blockName;
                while(strcmp(blockName, "stopelse")){
                    blockType = blockNameToTypeConverter(blockName);
                    addBlockCaller(blockType, code.last->next);
                    cout << "ELSE: Introduceti instructiunea: ";
                    cin >> blockName;
                }
            }
        } else {
            addBlockCaller(blockType, code.last->next);
        }
    }
}
