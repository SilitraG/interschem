#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Input: variable name
//Output: variable index or -1(doesn't exist)
int variableNameToIndex(char name[]) {
    int index = -1;

    for(int i = 1; i <= code.vars.varsNumber; i++) {
        if(strcmp(name, code.vars.var[i].name) == 0) {
            index=i;
        }
    }

    return index;

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

/// ----------- BLOCK LOGIC FUNCTIONS -----------

void startBlockLogic(LogicBlock *block) {
    return;

}

void stopBlockLogic(LogicBlock *block) {
    return;

}

void inputBlockLogic(LogicBlock *block) {
    //long double finalValue = stod(block->varFullExpression); //*toDo: change to full expression
    long double finalValue = calcul_expresie_f(block->varFullExpression);

    code.vars.var[block->varId].value = finalValue;
}

void outputBlockLogic(LogicBlock *block) {
    cout << code.vars.var[block->varId].value << ' ';

}

void assignBlockLogic(LogicBlock *block) {
    long double finalValue = calcul_expresie_f(block->varFullExpression);

    code.vars.var[block->varId].value = finalValue;
}

bool decisionBlockLogic(LogicBlock *block) {
    bool finalExpressionTruthValue = valoare_adevar_expresie(block->varFullExpression);
    return finalExpressionTruthValue;

}
/// ----------- END OF BLOCK LOGIC FUNCTIONS -----------


/// ----------- BLOCK ADD FUNCTIONS -----------

//Input: -
//Create and add a START block to the code list
void addStartBlock(int blockId) {
    code.numberOfBlocks++;
    code.allBlocks[blockId]->typeId = START_BLOCK;

   // code.first = block;
   // code.last = block;
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
    char newVarExpression[VAR_EXPRESSION_SIZE];
    int newVarId;
    cout << "Introduceti numele variabilei: ";
    cin >> newVarName;
    cout << "Introduceti valoarea: ";
    cin >> newVarExpression;

    newVarId = variableNameToIndex(newVarName);
    if(newVarId == -1) {
        code.vars.varsNumber++;
        newVarId = code.vars.varsNumber;
        strcpy(code.vars.var[code.vars.varsNumber].name, newVarName);
    }

    LogicBlock *block = new LogicBlock;
    block->typeId = INPUT_BLOCK;
    block->varId = newVarId;
    //char temporaryExpression[50];
    //itoa(newVarValue, temporaryExpression, 10);
    strcpy(block->varFullExpression, newVarExpression);

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
    //long double varValue; //*toDo: change to full expression
    char varExpression[VAR_EXPRESSION_SIZE];

    cout << "Introduceti numele variabilei: ";
    cin >> varName;
    cout << "Introduceti valoarea: ";
    cin >> varExpression; //*toDo: change to full expression

    int varId = variableNameToIndex(varName);
    if(varId == -1) {
        code.vars.varsNumber++;
        varId = code.vars.varsNumber;
        strcpy(code.vars.var[code.vars.varsNumber].name, varName);
    }

    LogicBlock *block = new LogicBlock;
    block->typeId = ASSIGN_BLOCK;
    block->varId = varId;
    //char temporaryExpression[50];
    //itoa(varValue, temporaryExpression, 10);
    strcpy(block->varFullExpression, varExpression); //*toDo: change to full expression

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

// Input: block type Id
// Calls the logic function for the needed block
/*void addBlockCaller(int blockType, LogicBlock *& parentBlockPointer) {
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
            cerr << "Instructiune incorecta\n";
    }

} */

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
    for(int i = 1; i <= code.vars.varsNumber; i++) {
        cout << code.vars.var[i].name << ' ' << code.vars.var[i].value << ' ';
    }
    cout << '\n';
}

//Console code input
/*void codeCreator() {
    int blockType = EMPTY_BLOCK;
    char blockName[10];
    LogicBlock *lastIf = new LogicBlock;
    bool precedentWasDecision = false;

    while(blockType != STOP_BLOCK) {
        cout << "Introduceti instructiunea: ";
        cin >> blockName;
        blockType = blockNameToTypeConverter(blockName);
        if(blockType == DECISION_BLOCK) {
            precedentWasDecision = true;
            addBlockCaller(blockType, code.last->next);
            LogicBlock *decisionBlock = new LogicBlock;
            decisionBlock = code.last;
            cout << "IF: Introduceti instructiunea: ";
            cin >> blockName;
            if(strcmp(blockName, "stopif")){
                blockType = blockNameToTypeConverter(blockName);
                addBlockCaller(blockType, decisionBlock->tru);
                lastIf = code.last;
                cout << "IF: Introduceti instructiunea: ";
                cin >> blockName;
                while(strcmp(blockName, "stopif")){
                    blockType = blockNameToTypeConverter(blockName);
                    addBlockCaller(blockType, code.last->next);
                    lastIf = code.last;
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
            if(precedentWasDecision == true) {
                lastIf->next=code.last;
                precedentWasDecision = false;
            }
        }
    }
}*/
