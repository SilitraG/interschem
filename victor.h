//Block type
#define EMPTY_BLOCK 0
#define START_BLOCK 1
#define INPUT_BLOCK 2
#define OUTPUT_BLOCK 3
#define ASSIGN_BLOCK 4
#define DECISION_BLOCK 5
#define STOP_BLOCK 6

void addStartBlock() {

}

void addStopBlock() {

}

void addInputBlock(int varId) {

}

void addOutputBlock(int varId) {

}

void addAssignBlock(int varId) {

}

int blockTypeDecider(char blockName[]) {
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
}

void blockTypeCaller(int blockType) {

}
