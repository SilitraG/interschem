#include <iostream>
#include <cstring>

using namespace std;

//Input: variable name
//Output: variables index or -1(doesn't exist)
int variableIndex(char name[]) {
    int index = -1;

    for(int i = 1; i <= Vars.varsNumber; i++) {
        if(strcmp(name, Vars.Var[i].name) == 0) {
            index=i;
        }
    }

    return index;

}

// ----------- BLOCK LOGIC FUNCTIONS -----------

void startBlockLogic() {
    return;

}

void stopBlockLogic() {
    return;

}

void inputBlockLogic() {
    Vars.varsNumber++;

    cout << "Introduceti numele variabilei: ";
    cin >> Vars.Var[Vars.varsNumber].name;
    cout << "Introduceti valoarea: ";
    cin >> Vars.Var[Vars.varsNumber].value;

}

void outputBlockLogic() {
    char name[30];

    cout << "Introduceti numele variabilei: ";
    cin >> name;
    int index = variableIndex(name);

    if(index != -1) {
        cout << Vars.Var[index].value << '\n';
    } else {
        cout << "Variabila inexistenta";
    }

}

void assignBlockLogic() {
    char name[30];

    cout << "Introduceti numele variabilei: ";
    cin >> name;
    int index = variableIndex(name);


    if(index != -1) { // variabila deja exista
        cout << "Introduceti noua valoare: ";
        cin >> Vars.Var[index].value;
    } else { // variabila noua
        Vars.varsNumber++;
        strcpy(Vars.Var[Vars.varsNumber].name, name);
        cout << "Introduceti valoarea: ";
        cin >> Vars.Var[Vars.varsNumber].value;
    }

}

void decisionBlockLogic() {
    return;

}
// ----------- END OF BLOCK LOGIC FUNCTIONS -----------


// ----------- BLOCK ADD FUNCTIONS -----------

//Input: -
//Create and add a START block to the code list
void addStartBlock() {
    LogicBlock *block = new LogicBlock;
    block->varId = START_BLOCK;

    code.numberOfBlocks=1;
    code.first = block;
    code.last = block;
}

//Input: -
//Create and add a STOP block to the code list
void addStopBlock() {
    LogicBlock *block = new LogicBlock;
    block->varId = STOP_BLOCK;

    code.numberOfBlocks++;
    if(code.last->typeId != DECISION_BLOCK) {
        code.last->next = block;
    } else
    code.last = block;
    return;

}

//Input: - (not finished)
//Create and add a INPUT block to the code list
void addInputBlock() {
    Vars.varsNumber++;

    cout << "Introduceti numele variabilei: ";
    cin >> Vars.Var[Vars.varsNumber].name;
    cout << "Introduceti valoarea: ";
    cin >> Vars.Var[Vars.varsNumber].value;

}

//Input: - (not finished)
//Create and add a OUTPUT block to the code list
void addOutputBlock() {
    char name[30];

    cout << "Introduceti numele variabilei: ";
    cin >> name;
    int index = variableIndex(name);

}

//Input: - (not finished)
//Create and add a ASSIGN block to the code list
void addAssignBlock() {
    char name[30];

    cout << "Introduceti numele variabilei: ";
    cin >> name;
    int index = variableIndex(name);

}

//Input: - (not finished)
//Create and add a DECISION block to the code list
void addDecisionBlock() {
    return;

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
// Calls the logic function of the needed block
void blockTypeLogicCaller(int blockType) {
    switch (blockType) {
        case START_BLOCK:
            startBlockLogic();
            break;
        case INPUT_BLOCK:
            inputBlockLogic();
            break;
        case OUTPUT_BLOCK:
            outputBlockLogic();
            break;
        case ASSIGN_BLOCK:
            assignBlockLogic();
            break;
        case DECISION_BLOCK:
            decisionBlockLogic();
            break;
        case STOP_BLOCK:
            stopBlockLogic();
            break;
        default:
            cout << "Instructiune incorecta\n";
    }

}

//Input: The first block of the list
//Iterates trough the list and calls the logic functions for each block
void codeIterator(LogicBlock *start) {
    LogicBlock *block = start;
    while(block->typeId != STOP_BLOCK){

        block=block->next;
    }
}
