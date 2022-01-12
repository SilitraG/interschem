/// /////////// CHECK MOUSE POSITION ////////////////////////
//Input: item(block, button etc) top left position and size
//Output: True/False
bool mouseIsOnItem(sf::Vector2f itemPos, sf::Vector2f itemSize) {
    if(code.appProps.mousePos.x < itemPos.x || code.appProps.mousePos.y < itemPos.y){
        return 0;
    }
    if(code.appProps.mousePos.x > itemPos.x+itemSize.x || code.appProps.mousePos.y > itemPos.y+itemSize.y) {
        return 0;
    }
    return 1;

}

//Input: -
//Output: id of the most visible block or -1
int mouseIsOnBlock() {
    for(int i=code.numberOfBlocks; i>=1; i--) {
        if(mouseIsOnItem(code.allBlocks[i]->block.getPosition(), code.allBlocks[i]->block.getSize()) && code.allBlocks[i]->typeId != 0) {
            return i;
        }
    }
    return -1;

}

//Input: -
//Output: id of the button or -1(if the menu is inactive or no button is selected)
int mouseIsOnBlockMenuButton() {
    if(code.appProps.blockMenu.blockMenuIsActive) {
        for(int i = 1; i <= code.appProps.blockMenu.numberOfButtons; i++) {
            if(mouseIsOnItem(code.appProps.blockMenu.menuButtons[i].getPosition(), code.appProps.blockMenu.menuButtons[i].getSize())) {
                //cout << code.appProps.blockMenu.blockMenuIsActive << ' ' << i << '\n';
                return i;
            }
        }
    }
    return -1;

}

//Input: -
//Output: id of the button or -1(if no button is selected)
int mouseIsOnAppOutputButton() {
    for(int i = 1; i <= 2; i++) {
        if(mouseIsOnItem(code.appProps.appOutput.appOutputButton[i].getPosition(), code.appProps.appOutput.appOutputButton[i].getSize())) {
            return i;
        }
    }
    return -1;

}

//Input: -
//Output: id of the dummy block or -1
int mouseIsOnAddBlock() {
    if(mouseIsOnItem(code.appProps.addBlockMenu.addBlockMenuBackground.getPosition(), code.appProps.addBlockMenu.addBlockMenuBackground.getSize())) {
        for(int i = 1; i <= 5; i++) {
            if(mouseIsOnItem(code.appProps.addBlockMenu.dummyBlock[i].getPosition(), code.appProps.addBlockMenu.dummyBlock[i].getSize())) {
                return i;
            }
        }
    }
    return -1;

}

//Input: -
//Output: id of the button or -1(if no button is selected)
int mouseIsOnUserInputButton() {
    for(int i = 1; i <= 2; i++) {
        if(mouseIsOnItem(code.appProps.userInput.userInputButton[i].getPosition(), code.appProps.userInput.userInputButton[i].getSize())) {
            return i;
        }
    }
    return -1;

}

//Input: -
//Output: id of the button or -1(if no button is selected)
int mouseIsOnUserInputField() {
    if(code.appProps.userInput.inputIsActive) {
        for(int i = 1; i <= 2; i++) {
            if(mouseIsOnItem(code.appProps.userInput.userInputField[i].getPosition(), code.appProps.userInput.userInputField[i].getSize())) {
                return i;
            }
        }
    }
    return -1;

}

int mouseIsOnAppMenuButton() {
    for(int i = 1; i <= NUMBER_OF_APP_MENU_BUTTONS; i++) {
        if(mouseIsOnItem(code.appProps.appMenu.appMenuButton[i].getPosition(), code.appProps.appMenu.appMenuButton[i].getSize())) {
            return i;
        }
    }
    return -1;

}

/// /////////// END OF CHECK MOUSE POSITION ////////////////////////

//Input: blockId
//Rearranges the blocks in the allBlocks array so that "blockId" is displayed on the top
void rearrangeBlocks(int newTopBlockId) {
    if(code.appProps.block.blockIsBeingMoved) {
        if(code.appProps.block.blockIsBeingMoved == newTopBlockId) {
            code.appProps.block.blockIsBeingMoved = code.numberOfBlocks;
        } else if(code.appProps.block.blockIsBeingMoved > newTopBlockId) {
            code.appProps.block.blockIsBeingMoved--;
        }
    }
    LogicBlock *blockCopy = new LogicBlock;
    blockCopy = code.allBlocks[newTopBlockId];
    for(int i = newTopBlockId; i < code.numberOfBlocks; i++) {
        code.allBlocks[i] = code.allBlocks[i+1];
    }
    code.allBlocks[code.numberOfBlocks] = blockCopy;

}

//Deletes blockId block
void deleteBlock(int blockId) {
    code.allBlocks[blockId]->typeId = EMPTY_BLOCK;
    code.allBlocks[blockId]->varId = -1;
    code.allBlocks[blockId]->varFullExpression[0] = NULL;
    code.allBlocks[blockId]->connectionPath.hasConnection = false;
    code.allBlocks[blockId]->connectionPath.numberOfLinesNext = 0;
    code.allBlocks[blockId]->connectionPath.numberOfLinesTru = 0;
    code.allBlocks[blockId]->connectionPath.numberOfLinesFls = 0;
    code.allBlocks[blockId]->next = NULL;
    code.allBlocks[blockId]->tru = NULL;
    code.allBlocks[blockId]->fls = NULL;
    for(int i = 1; i <= code.allBlocks[blockId]->numberOfPrevs; i++) {
        if(code.allBlocks[blockId]->prev[i]!=NULL) {
            if(code.allBlocks[blockId]->prev[i]->typeId == DECISION_BLOCK) {
                if(code.allBlocks[blockId]->prev[i]->tru == code.allBlocks[blockId]) {
                    code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesTru = 0;
                }
                if(code.allBlocks[blockId]->prev[i]->fls == code.allBlocks[blockId]) {
                    code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesFls = 0;
                }
            } else {
                code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesNext = 0;
            }
            if(code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesTru == 0 && code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesFls == 0 && code.allBlocks[blockId]->prev[i]->connectionPath.numberOfLinesNext == 0) {
                code.allBlocks[blockId]->prev[i]->connectionPath.hasConnection = false;
            }
        }

        code.allBlocks[blockId]->prev[i] = NULL;
    }

}

void deleteAllBlocks() {
    for(int i = 1; i <= code.numberOfBlocks; i++) {
        if(code.allBlocks[i]->typeId != START_BLOCK) {
            deleteBlock(i);
        }
    }
    code.numberOfBlocks = 1;
    for(int i = 1; i <= code.vars.varsNumber; i++) {
        code.vars.var[i].name[0]=NULL;
        code.vars.var[i].value=0;
    }
    code.vars.varsNumber = 0;

}

void drawAppMenu(sf::Font &textFont) {
    code.appProps.appMenu.appMenuBackground.setPosition(sf::Vector2f(APP_MENU_POS_X, APP_MENU_POS_Y));
    code.appProps.appMenu.appMenuBackground.setSize(sf::Vector2f(APP_MENU_SIZE_X, APP_MENU_SIZE_Y));
    code.appProps.appMenu.appMenuBackground.setFillColor(APP_MENU_COLOR);

    code.appProps.appMenu.appMenuButton[1].setPosition(sf::Vector2f(ADD_BLOCK_MENU_SIZE_X+APP_OUTPUT_BORDER_THICKNESS, APP_OUTPUT_BORDER_THICKNESS));
    code.appProps.appMenu.appMenuButton[2].setPosition(sf::Vector2f(ADD_BLOCK_MENU_SIZE_X+2*APP_OUTPUT_BORDER_THICKNESS+APP_MENU_BUTTON_SIZE_X, APP_OUTPUT_BORDER_THICKNESS));
    code.appProps.appMenu.appMenuButton[3].setPosition(sf::Vector2f(APP_OUTPUT_POS_X-APP_MENU_BUTTON_SIZE_X, APP_OUTPUT_BORDER_THICKNESS));

    for(int i = 1; i <= NUMBER_OF_APP_MENU_BUTTONS; i++) {
        code.appProps.appMenu.appMenuButton[i].setSize(sf::Vector2f(APP_MENU_BUTTON_SIZE_X, APP_MENU_BUTTON_SIZE_Y));
        code.appProps.appMenu.appMenuButton[i].setFillColor(APP_MENU_BUTTON_COLOR);
        code.appProps.appMenu.appMenuButton[i].setOutlineThickness(APP_OUTPUT_BORDER_THICKNESS);
        code.appProps.appMenu.appMenuButton[i].setOutlineColor(APP_OUTPUT_COLOR);

        code.appProps.appMenu.appMenuButtonText[i].setPosition(sf::Vector2f(code.appProps.appMenu.appMenuButton[i].getPosition().x, code.appProps.appMenu.appMenuButton[i].getPosition().y));
        code.appProps.appMenu.appMenuButtonText[i].setFillColor(APP_OUTPUT_BUTTON_TEXT_COLOR);
        code.appProps.appMenu.appMenuButtonText[i].setFont(textFont);
        code.appProps.appMenu.appMenuButtonText[i].setStyle(sf::Text::Bold);
        code.appProps.appMenu.appMenuButtonText[i].setCharacterSize(APP_OUTPUT_BUTTON_TEXT_SIZE);
    }
        code.appProps.appMenu.appMenuButtonText[1].setString("IMPORT CODE");
        code.appProps.appMenu.appMenuButtonText[2].setString("EXPORT CODE");
        code.appProps.appMenu.appMenuButtonText[3].setString("CLEAR BLOCKS");

}

void drawAppOutput(sf::Font &textFont) {
    code.appProps.appOutput.appOutputBackground.setPosition(sf::Vector2f(APP_OUTPUT_POS_X, APP_OUTPUT_POS_Y));
    code.appProps.appOutput.appOutputBackground.setSize(sf::Vector2f(APP_OUTPUT_SIZE_X, APP_OUTPUT_SIZE_Y));
    code.appProps.appOutput.appOutputBackground.setFillColor(APP_OUTPUT_COLOR);

    for(int i = 1; i <= 2; i++) {
        code.appProps.appOutput.appOutputButton[i].setSize(sf::Vector2f((APP_OUTPUT_SIZE_X-3*APP_OUTPUT_BORDER_THICKNESS)/2, APP_MENU_SIZE_Y-2*APP_OUTPUT_BORDER_THICKNESS));
        code.appProps.appOutput.appOutputButton[i].setPosition(sf::Vector2f(APP_OUTPUT_POS_X+APP_OUTPUT_BORDER_THICKNESS*i+code.appProps.appOutput.appOutputButton[i].getSize().x*(i-1), APP_OUTPUT_POS_Y+APP_OUTPUT_BORDER_THICKNESS));
        code.appProps.appOutput.appOutputButton[i].setFillColor(APP_OUTPUT_BUTTON_COLOR);

        code.appProps.appOutput.appOutputButtonText[i].setPosition(sf::Vector2f(APP_OUTPUT_POS_X+APP_OUTPUT_BORDER_THICKNESS*i+code.appProps.appOutput.appOutputButton[i].getSize().x*(i-1), APP_OUTPUT_POS_Y+APP_OUTPUT_BORDER_THICKNESS));
        code.appProps.appOutput.appOutputButtonText[i].setFillColor(APP_OUTPUT_BUTTON_TEXT_COLOR);
        code.appProps.appOutput.appOutputButtonText[i].setFont(textFont);
        code.appProps.appOutput.appOutputButtonText[i].setStyle(sf::Text::Bold);
        code.appProps.appOutput.appOutputButtonText[i].setCharacterSize(APP_OUTPUT_BUTTON_TEXT_SIZE);
    }
    code.appProps.appOutput.appOutputButtonText[1].setString(APP_OUTPUT_RUN_CODE);
    code.appProps.appOutput.appOutputButtonText[2].setString(APP_OUTPUT_GENERATE_CODE);

    code.appProps.appOutput.appOutputArea.setSize(sf::Vector2f(APP_OUTPUT_SIZE_X-2*APP_OUTPUT_BORDER_THICKNESS, APP_OUTPUT_SIZE_Y-APP_MENU_SIZE_Y-2*APP_OUTPUT_BORDER_THICKNESS));
    code.appProps.appOutput.appOutputArea.setPosition(sf::Vector2f(APP_OUTPUT_POS_X+APP_OUTPUT_BORDER_THICKNESS, APP_OUTPUT_POS_Y+APP_MENU_SIZE_Y+APP_OUTPUT_BORDER_THICKNESS));
    code.appProps.appOutput.appOutputArea.setFillColor(APP_OUTPUT_BUTTON_COLOR);

    for(int i = 1; i < MAX_NUMBER_OF_CODE_LINE; i++) {
        code.appProps.appOutput.codeOutput[i].setPosition(sf::Vector2f(code.appProps.appOutput.appOutputArea.getPosition().x, code.appProps.appOutput.appOutputArea.getPosition().y+13*(i-1)));
        code.appProps.appOutput.codeOutput[i].setFillColor(APP_OUTPUT_BUTTON_TEXT_COLOR);
        code.appProps.appOutput.codeOutput[i].setFont(textFont);
        code.appProps.appOutput.codeOutput[i].setCharacterSize(APP_OUTPUT_BUTTON_TEXT_SIZE);
    }

}

// Draws the "Add Block" menu + the blocks inside it
void drawAddBlockMenu(sf::Font &textFont) {
    int noOfDBlocks = 5; // Number of dummy blocks
    code.appProps.addBlockMenu.addBlockMenuBackground.setPosition(sf::Vector2f(ADD_BLOCK_MENU_POS_X, ADD_BLOCK_MENU_POS_Y));
    code.appProps.addBlockMenu.addBlockMenuBackground.setSize(sf::Vector2f(ADD_BLOCK_MENU_SIZE_X, WINDOW_HEIGHT-ADD_BLOCK_MENU_POS_Y));
    code.appProps.addBlockMenu.addBlockMenuBackground.setFillColor(ADD_BLOCK_MENU_COLOR);
    code.appProps.addBlockMenu.underline[0] = sf::Vertex(sf::Vector2f(0, APP_MENU_SIZE_Y), UNDERLINE_COLOR);
    code.appProps.addBlockMenu.underline[1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH, APP_MENU_SIZE_Y), UNDERLINE_COLOR);

    code.appProps.addBlockMenu.menuTitle.setFont(textFont);
    code.appProps.addBlockMenu.menuTitle.setString("ADD A BLOCK");
    code.appProps.addBlockMenu.menuTitle.setCharacterSize(ADD_BLOCK_MENU_TEXT_SIZE);
    code.appProps.addBlockMenu.menuTitle.setFillColor(ADD_BLOCK_MENU_TEXT_COLOR);
    code.appProps.addBlockMenu.menuTitle.setPosition(sf::Vector2f((ADD_BLOCK_MENU_SIZE_X-code.appProps.addBlockMenu.menuTitle.getLocalBounds().width)/2, ADD_BLOCK_MENU_POS_Y+(WINDOW_HEIGHT-ADD_BLOCK_MENU_POS_Y-noOfDBlocks*BLOCK_SIZE_Y)/noOfDBlocks*0.2));

    for(int i = 1; i <= noOfDBlocks; i++) {
        code.appProps.addBlockMenu.dummyBlock[i].setPosition(sf::Vector2f((ADD_BLOCK_MENU_SIZE_X-BLOCK_SIZE_X)/2, ADD_BLOCK_MENU_POS_Y+(WINDOW_HEIGHT-ADD_BLOCK_MENU_POS_Y-noOfDBlocks*BLOCK_SIZE_Y)/noOfDBlocks*i+20));
        code.appProps.addBlockMenu.dummyBlock[i].setSize(sf::Vector2f(BLOCK_SIZE_X, BLOCK_SIZE_Y));
        code.appProps.addBlockMenu.dummyBlock[i].setFillColor(GENERIC_BLOCK_COLOR);

        code.appProps.addBlockMenu.dummyBlockTitle[i].setPosition(sf::Vector2f((ADD_BLOCK_MENU_SIZE_X-BLOCK_SIZE_X)/2, ADD_BLOCK_MENU_POS_Y+(WINDOW_HEIGHT-ADD_BLOCK_MENU_POS_Y-noOfDBlocks*BLOCK_SIZE_Y)/noOfDBlocks*i+20));
        code.appProps.addBlockMenu.dummyBlockTitle[i].setCharacterSize(BLOCK_TEXT_SIZE);
        code.appProps.addBlockMenu.dummyBlockTitle[i].setFillColor(BLOCK_TEXT_COLOR);
        code.appProps.addBlockMenu.dummyBlockTitle[i].setFont(textFont);
    }
    code.appProps.addBlockMenu.dummyBlock[noOfDBlocks].setFillColor(STOP_BLOCK_COLOR);

    code.appProps.addBlockMenu.dummyBlockTitle[1].setString("INPUT");
    code.appProps.addBlockMenu.dummyBlockTitle[2].setString("OUTPUT");
    code.appProps.addBlockMenu.dummyBlockTitle[3].setString("ASSIGN");
    code.appProps.addBlockMenu.dummyBlockTitle[4].setString("DECISION");
    code.appProps.addBlockMenu.dummyBlockTitle[5].setString("STOP");

}

//Input: blockPosition, blockType
//Adds a block to the allBlocks array (only the visual part for now)
void drawNewBlock(sf::Vector2f blockPos, int blockType, sf::Font &textFont) {
    code.numberOfBlocks++;
    int blockId = code.numberOfBlocks;
    code.allBlocks[blockId] = new LogicBlock;
    code.allBlocks[blockId]->blockPos = blockPos;
    code.allBlocks[blockId]->block.setPosition(code.allBlocks[blockId]->blockPos);
    code.allBlocks[blockId]->block.setSize(sf::Vector2f(BLOCK_SIZE_X, BLOCK_SIZE_Y));
    code.allBlocks[blockId]->blockExpression.setFont(textFont);
    if(blockType == START_BLOCK) {
        code.allBlocks[blockId]->block.setFillColor(START_BLOCK_COLOR);
    } else if(blockType == STOP_BLOCK) {
        code.allBlocks[blockId]->block.setFillColor(STOP_BLOCK_COLOR);
    } else {
        code.allBlocks[blockId]->block.setFillColor(GENERIC_BLOCK_COLOR);
    }

    code.allBlocks[blockId]->blockTitle.setFont(textFont);
    switch (blockType) {
        case START_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("START");
            addStartBlock(blockId);
            break;
        case INPUT_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("INPUT");
            code.allBlocks[blockId]->typeId = INPUT_BLOCK;
            ///TESTARE
            ///strcpy(code.allBlocks[blockId]->varFullExpression,"a == 4");
            break;
        case OUTPUT_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("OUTPUT");
            code.allBlocks[blockId]->typeId = OUTPUT_BLOCK;
            break;
        case ASSIGN_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("ASSIGN");
            code.allBlocks[blockId]->typeId = ASSIGN_BLOCK;
            ///TESTARE
            ///strcpy(code.allBlocks[blockId]->varFullExpression,"bej + 1");
            break;
        case DECISION_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("DECISION");
            code.allBlocks[blockId]->typeId = DECISION_BLOCK;
            ///TESTARE
            ///strcpy(code.allBlocks[blockId]->varFullExpression,"b == 4");
            break;
        case STOP_BLOCK:
            code.allBlocks[blockId]->blockTitle.setString("STOP");
            code.allBlocks[blockId]->typeId = STOP_BLOCK;
            break;
        default:
            cerr << "Instructiune incorecta(drawNewBlock)\n";
    }
    code.allBlocks[blockId]->blockTitle.setCharacterSize(BLOCK_TEXT_SIZE);
    code.allBlocks[blockId]->blockTitle.setFillColor(BLOCK_TEXT_COLOR);
    code.allBlocks[blockId]->blockTitle.setPosition(blockPos);

}

void drawNewConnection(int slaveBlockId) {
    int masterBlockId = code.appProps.connection.masterBlockId;
    sf::Vector2f masterBlockPos = code.allBlocks[masterBlockId]->block.getPosition();
    sf::Vector2f slaveBlockPos = code.allBlocks[slaveBlockId]->block.getPosition();

    code.allBlocks[masterBlockId]->connectionPath.hasConnection = true;
    if(code.allBlocks[masterBlockId]->typeId == DECISION_BLOCK) {
        // Check if master block is already in a connection
        if(code.allBlocks[masterBlockId]->tru != NULL && code.appProps.connection.path == true) {
            for(int i = 1; i <= code.allBlocks[masterBlockId]->tru->numberOfPrevs; i++) {
                if(code.allBlocks[masterBlockId]->tru->prev[i] == code.allBlocks[masterBlockId]) {
                    code.allBlocks[masterBlockId]->tru->prev[i] = NULL;
                    break;
                }
            }
        } else if(code.allBlocks[masterBlockId]->fls != NULL && code.appProps.connection.path == false) {
            for(int i = 1; i <= code.allBlocks[masterBlockId]->fls->numberOfPrevs; i++) {
                if(code.allBlocks[masterBlockId]->fls->prev[i] == code.allBlocks[masterBlockId]) {
                    code.allBlocks[masterBlockId]->fls->prev[i] = NULL;
                    break;
                }
            }
        }

        if(code.appProps.connection.path) {
            code.allBlocks[masterBlockId]->tru = code.allBlocks[slaveBlockId];
            code.allBlocks[masterBlockId]->connectionPath.numberOfLinesTru = 0;
            code.allBlocks[masterBlockId]->connectionPath.numberOfLinesTru++;
            code.allBlocks[masterBlockId]->connectionPath.truPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesTru][0] = sf::Vertex(sf::Vector2f(masterBlockPos.x, masterBlockPos.y+BLOCK_SIZE_Y));
            code.allBlocks[masterBlockId]->connectionPath.truPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesTru][1] = sf::Vertex(sf::Vector2f(slaveBlockPos.x+BLOCK_SIZE_X/2, slaveBlockPos.y));
        } else {
            code.allBlocks[masterBlockId]->fls = code.allBlocks[slaveBlockId];
            code.allBlocks[masterBlockId]->connectionPath.numberOfLinesFls = 0;
            code.allBlocks[masterBlockId]->connectionPath.numberOfLinesFls++;
            code.allBlocks[masterBlockId]->connectionPath.flsPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesFls][0] = sf::Vertex(sf::Vector2f(masterBlockPos.x+BLOCK_SIZE_X, masterBlockPos.y+BLOCK_SIZE_Y));
            code.allBlocks[masterBlockId]->connectionPath.flsPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesFls][1] = sf::Vertex(sf::Vector2f(slaveBlockPos.x+BLOCK_SIZE_X/2, slaveBlockPos.y));
        }
    } else {
        // Check if master block is already in a connection
        if(code.allBlocks[masterBlockId]->next != NULL) {
          for(int i = 1; i <= code.allBlocks[masterBlockId]->next->numberOfPrevs; i++) {
                if(code.allBlocks[masterBlockId]->next->prev[i] == code.allBlocks[masterBlockId]) {
                    code.allBlocks[masterBlockId]->next->prev[i] = NULL;
                    break;
                }
            }
        }

        code.allBlocks[masterBlockId]->next = code.allBlocks[slaveBlockId];
        code.allBlocks[masterBlockId]->connectionPath.numberOfLinesNext = 0;
        code.allBlocks[masterBlockId]->connectionPath.numberOfLinesNext++;
        code.allBlocks[masterBlockId]->connectionPath.nextPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesNext][0] = sf::Vertex(sf::Vector2f(masterBlockPos.x+BLOCK_SIZE_X/2, masterBlockPos.y+BLOCK_SIZE_Y));
        code.allBlocks[masterBlockId]->connectionPath.nextPath[code.allBlocks[masterBlockId]->connectionPath.numberOfLinesNext][1] = sf::Vertex(sf::Vector2f(slaveBlockPos.x+BLOCK_SIZE_X/2, slaveBlockPos.y));
    }

    // Check if slave block is already in a connection
    /*if(code.allBlocks[slaveBlockId]->prev != NULL) { ///BUG: Two or more blocks can't point at the same block (fixed)
        if(code.allBlocks[slaveBlockId]->prev->typeId == DECISION_BLOCK) {
            if(code.allBlocks[slaveBlockId]->prev->tru == code.allBlocks[slaveBlockId]) {
               code.allBlocks[slaveBlockId]->prev->tru = NULL;
               code.allBlocks[slaveBlockId]->prev->connectionPath.numberOfLinesTru = 0;
            } else {
                code.allBlocks[slaveBlockId]->prev->fls = NULL;
                code.allBlocks[slaveBlockId]->prev->connectionPath.numberOfLinesFls = 0;
            }
        } else {
            code.allBlocks[slaveBlockId]->prev->next = NULL;
            code.allBlocks[slaveBlockId]->prev->connectionPath.numberOfLinesNext = 0;
        }
    }
    */
    code.allBlocks[slaveBlockId]->numberOfPrevs++; ///To Do: Check if there are any empty prevs
    code.allBlocks[slaveBlockId]->prev[code.allBlocks[slaveBlockId]->numberOfPrevs] = code.allBlocks[masterBlockId];

    code.appProps.connection.masterBlockId = false;

}

void updateBlockMenu(int blockId, sf::Font &textFont) {
    code.appProps.blockMenu.blockMenuIsActive = blockId;
    code.appProps.blockMenu.menuPos = code.appProps.mousePos;
    if(code.appProps.connection.masterBlockId == false) {
        code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_CONNECTION);
    } else {
        code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_FINISH_CONNECTION);
    }
    switch (code.allBlocks[blockId]->typeId) {
        case START_BLOCK:
            code.appProps.blockMenu.numberOfButtons = 1;
            break;
        case INPUT_BLOCK:
            code.appProps.blockMenu.numberOfButtons = 3;
            code.appProps.blockMenu.menuButtonsTitle[2].setString(MENU_BLOCK_CHANGE_EXPRESSION);
            break;
        case OUTPUT_BLOCK:
            code.appProps.blockMenu.numberOfButtons = 3;
            code.appProps.blockMenu.menuButtonsTitle[2].setString(MENU_BLOCK_CHANGE_VARIABLE);
            break;
        case ASSIGN_BLOCK:
            code.appProps.blockMenu.numberOfButtons = 3;
            code.appProps.blockMenu.menuButtonsTitle[2].setString(MENU_BLOCK_CHANGE_EXPRESSION);
            break;
        case DECISION_BLOCK:
            if(code.appProps.connection.masterBlockId == 0) {
                code.appProps.blockMenu.numberOfButtons = 4;
                code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_T_CONNECTION);
                code.appProps.blockMenu.menuButtonsTitle[2].setString(MENU_BLOCK_F_CONNECTION);
                code.appProps.blockMenu.menuButtonsTitle[3].setString(MENU_BLOCK_CHANGE_EXPRESSION);
            } else {
                code.appProps.blockMenu.numberOfButtons = 3;
                code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_FINISH_CONNECTION);
                code.appProps.blockMenu.menuButtonsTitle[2].setString(MENU_BLOCK_CHANGE_EXPRESSION);
            }
            break;
        case STOP_BLOCK:
            if(code.appProps.connection.masterBlockId == false) {
                code.appProps.blockMenu.numberOfButtons = 1;
            } else {
                code.appProps.blockMenu.numberOfButtons = 2;
            }
            break;
        default:
            cerr << "Instructiune incorecta(updateBlockMenu)\n";
    }
    if(code.allBlocks[blockId]->typeId != START_BLOCK) {
        code.appProps.blockMenu.menuButtonsTitle[code.appProps.blockMenu.numberOfButtons].setString(MENU_BLOCK_DELETE);
    }

    code.appProps.blockMenu.menuBackground.setPosition(code.appProps.blockMenu.menuPos);
    code.appProps.blockMenu.menuBackground.setSize(sf::Vector2f(BLOCK_MENU_BUTTON_SIZE_X+2*BLOCK_MENU_BORDER_THICKNESS, BLOCK_MENU_BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BLOCK_MENU_BORDER_THICKNESS)*code.appProps.blockMenu.numberOfButtons));
    code.appProps.blockMenu.menuBackground.setFillColor(MENU_COLOR);

    for(int i = 1; i <= code.appProps.blockMenu.numberOfButtons; i++) {
        //xMenuPos+border, yMenuPos+border+(buttonSize+border)*how many buttons were before
        code.appProps.blockMenu.menuButtons[i].setPosition(sf::Vector2f(code.appProps.blockMenu.menuPos.x+BLOCK_MENU_BORDER_THICKNESS, code.appProps.blockMenu.menuPos.y+BLOCK_MENU_BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BLOCK_MENU_BORDER_THICKNESS)*(i-1)));
        code.appProps.blockMenu.menuButtons[i].setSize(sf::Vector2f(BLOCK_MENU_BUTTON_SIZE_X, BLOCK_MENU_BUTTON_SIZE_Y));
        code.appProps.blockMenu.menuButtons[i].setFillColor(MENU_BUTTON_COLOR);

        code.appProps.blockMenu.menuButtonsTitle[i].setFont(textFont);
        code.appProps.blockMenu.menuButtonsTitle[i].setPosition(sf::Vector2f(code.appProps.blockMenu.menuPos.x+BLOCK_MENU_BORDER_THICKNESS, code.appProps.blockMenu.menuPos.y+BLOCK_MENU_BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BLOCK_MENU_BORDER_THICKNESS)*(i-1)));
        code.appProps.blockMenu.menuButtonsTitle[i].setCharacterSize(MENU_TEXT_SIZE);
        code.appProps.blockMenu.menuButtonsTitle[i].setFillColor(MENU_BUTTON_TEXT_COLOR);
    }

}

void updateUserInputScreen(int blockId, sf::Font &textFont) {
    code.appProps.userInput.inputIsActive = blockId;
    code.appProps.userInput.activeField = 1;
    code.appProps.userInput.numberOfFields = 2;
    if(code.allBlocks[blockId]->typeId == DECISION_BLOCK || code.allBlocks[blockId]->typeId == OUTPUT_BLOCK) {
        code.appProps.userInput.numberOfFields = 1;
    }

    code.appProps.userInput.userInputBackground.setPosition(sf::Vector2f(USER_INPUT_POS_X, USER_INPUT_POS_Y));
    code.appProps.userInput.userInputBackground.setSize(sf::Vector2f(USER_INPUT_SIZE_X, USER_INPUT_SIZE_Y));
    code.appProps.userInput.userInputBackground.setFillColor(USER_INPUT_BACKGROUND_COLOR);
    code.appProps.userInput.userInputBackground.setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
    code.appProps.userInput.userInputBackground.setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

    code.appProps.userInput.userInputTitle.setPosition(sf::Vector2f(USER_INPUT_POS_X, USER_INPUT_POS_Y));
    code.appProps.userInput.userInputTitle.setString(blockTypeToString(code.allBlocks[blockId]->typeId));
    code.appProps.userInput.userInputTitle.setFont(textFont);
    code.appProps.userInput.userInputTitle.setCharacterSize(20);
    code.appProps.userInput.userInputTitle.setStyle(sf::Text::Bold);
    code.appProps.userInput.userInputTitle.setFillColor(sf::Color::Black);

    for(int i = 1; i <= code.appProps.userInput.numberOfFields; i++) {
        code.appProps.userInput.fieldTitle[i].setPosition(sf::Vector2f(USER_INPUT_FIELD_TITLE_X, USER_INPUT_POS_Y+80*i+10+(code.appProps.userInput.numberOfFields==1?40:0)));
        code.appProps.userInput.fieldTitle[i].setFont(textFont);
        code.appProps.userInput.fieldTitle[i].setCharacterSize(15);
        code.appProps.userInput.fieldTitle[i].setStyle(sf::Text::Bold);
        code.appProps.userInput.fieldTitle[i].setFillColor(sf::Color::Black);

        code.appProps.userInput.userInputField[i].setPosition(sf::Vector2f(USER_INPUT_FIELD_POS_X, code.appProps.userInput.fieldTitle[i].getPosition().y-10));
        code.appProps.userInput.userInputField[i].setSize(sf::Vector2f(USER_INPUT_FIELD_SIZE_X, USER_INPUT_FIELD_SIZE_Y));
        code.appProps.userInput.userInputField[i].setFillColor(sf::Color::White);
        code.appProps.userInput.userInputField[i].setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
        code.appProps.userInput.userInputField[i].setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

        code.appProps.userInput.userInputText[i].setPosition(sf::Vector2f(USER_INPUT_FIELD_POS_X, code.appProps.userInput.fieldTitle[i].getPosition().y-2));
        code.appProps.userInput.userInputText[i].setFont(textFont);
        code.appProps.userInput.userInputText[i].setCharacterSize(20);
        code.appProps.userInput.userInputText[i].setFillColor(sf::Color::Black);
    }

    int blockType = code.allBlocks[blockId]->typeId;
    if(blockType == DECISION_BLOCK) {
        code.appProps.userInput.fieldTitle[1].setString("SET CONDITION:");

        code.appProps.userInput.userInputText[1].setString(code.allBlocks[blockId]->varFullExpression);
        code.appProps.userInput.userInputString[1] = code.allBlocks[blockId]->varFullExpression;
    } else {
        if(blockType == INPUT_BLOCK || blockType == ASSIGN_BLOCK) {
            code.appProps.userInput.fieldTitle[1].setString("VARIABLE NAME:");
            code.appProps.userInput.fieldTitle[2].setString("VARIABLE VALUE:");

            if(code.allBlocks[blockId]->varId != -1) {
                char varName[VAR_NAME_SIZE];
                strcpy(varName, code.vars.var[code.allBlocks[blockId]->varId].name);
                code.appProps.userInput.userInputText[1].setString(varName);
                strcpy(varName, code.appProps.userInput.userInputString[1].toAnsiString().c_str());
            }
            code.appProps.userInput.userInputText[2].setString(code.allBlocks[blockId]->varFullExpression);
            code.appProps.userInput.userInputString[2] = code.allBlocks[blockId]->varFullExpression;
        } else if(blockType == OUTPUT_BLOCK) {
            code.appProps.userInput.fieldTitle[1].setString("VARIABLE NAME:");

            if(code.allBlocks[blockId]->varId != -1) {
                char varName[VAR_NAME_SIZE];
                strcpy(varName, code.vars.var[code.allBlocks[blockId]->varId].name);
                code.appProps.userInput.userInputText[1].setString(varName);
                strcpy(varName, code.appProps.userInput.userInputString[1].toAnsiString().c_str());
            }
            code.appProps.userInput.userInputText[2].setString(code.allBlocks[blockId]->varFullExpression);
            code.appProps.userInput.userInputString[2] = code.allBlocks[blockId]->varFullExpression;
        }
    }

    for(int i = 1; i <= 2; i++) {
        code.appProps.userInput.userInputButton[i].setSize(sf::Vector2f(USER_INPUT_BUTTON_SIZE_X, USER_INPUT_BUTTON_SIZE_Y));
        code.appProps.userInput.userInputButton[i].setPosition(sf::Vector2f(USER_INPUT_POS_X+(USER_INPUT_SIZE_X-2*USER_INPUT_BUTTON_SIZE_X-200)/2+(200+USER_INPUT_BUTTON_SIZE_X)*(i-1),USER_INPUT_BUTTON_POS_Y));
        code.appProps.userInput.userInputButton[i].setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
        code.appProps.userInput.userInputButton[i].setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

        code.appProps.userInput.userInputButtonText[i].setPosition(code.appProps.userInput.userInputButton[i].getPosition());
        code.appProps.userInput.userInputButtonText[i].setFont(textFont);
        code.appProps.userInput.userInputButtonText[i].setCharacterSize(15);
        code.appProps.userInput.userInputButtonText[i].setStyle(sf::Text::Bold);
        code.appProps.userInput.userInputButtonText[i].setFillColor(sf::Color::Black);
    }

    code.appProps.userInput.userInputButtonText[1].setString("CANCEL");
    code.appProps.userInput.userInputButtonText[2].setString("SUBMIT");
}

void updateUserInputImportScreen(sf::Font &textFont) {
    code.appProps.userInput.inputIsActive = -1;
    code.appProps.userInput.activeField = 1;
    code.appProps.userInput.numberOfFields = 1;

    code.appProps.userInput.userInputBackground.setPosition(sf::Vector2f(USER_INPUT_POS_X, USER_INPUT_POS_Y));
    code.appProps.userInput.userInputBackground.setSize(sf::Vector2f(USER_INPUT_SIZE_X, USER_INPUT_SIZE_Y));
    code.appProps.userInput.userInputBackground.setFillColor(USER_INPUT_BACKGROUND_COLOR);
    code.appProps.userInput.userInputBackground.setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
    code.appProps.userInput.userInputBackground.setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

    code.appProps.userInput.userInputTitle.setPosition(sf::Vector2f(USER_INPUT_POS_X, USER_INPUT_POS_Y));
    code.appProps.userInput.userInputTitle.setString("IMPORT");
    code.appProps.userInput.userInputTitle.setFont(textFont);
    code.appProps.userInput.userInputTitle.setCharacterSize(20);
    code.appProps.userInput.userInputTitle.setStyle(sf::Text::Bold);
    code.appProps.userInput.userInputTitle.setFillColor(sf::Color::Black);

    code.appProps.userInput.fieldTitle[1].setPosition(sf::Vector2f(USER_INPUT_FIELD_TITLE_X, USER_INPUT_POS_Y+90+(code.appProps.userInput.numberOfFields==1?40:0)));
    code.appProps.userInput.fieldTitle[1].setFont(textFont);
    code.appProps.userInput.fieldTitle[1].setCharacterSize(15);
    code.appProps.userInput.fieldTitle[1].setStyle(sf::Text::Bold);
    code.appProps.userInput.fieldTitle[1].setFillColor(sf::Color::Black);

    code.appProps.userInput.userInputField[1].setPosition(sf::Vector2f(USER_INPUT_FIELD_POS_X, code.appProps.userInput.fieldTitle[1].getPosition().y-10));
    code.appProps.userInput.userInputField[1].setSize(sf::Vector2f(USER_INPUT_FIELD_SIZE_X, USER_INPUT_FIELD_SIZE_Y));
    code.appProps.userInput.userInputField[1].setFillColor(sf::Color::White);
    code.appProps.userInput.userInputField[1].setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
    code.appProps.userInput.userInputField[1].setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

    code.appProps.userInput.userInputText[1].setPosition(sf::Vector2f(USER_INPUT_FIELD_POS_X, code.appProps.userInput.fieldTitle[1].getPosition().y-2));
    code.appProps.userInput.userInputText[1].setFont(textFont);
    code.appProps.userInput.userInputText[1].setCharacterSize(20);
    code.appProps.userInput.userInputText[1].setFillColor(sf::Color::Black);

    code.appProps.userInput.fieldTitle[1].setString("FILE NAME:");

    for(int i = 1; i <= 2; i++) {
        code.appProps.userInput.userInputButton[i].setSize(sf::Vector2f(USER_INPUT_BUTTON_SIZE_X, USER_INPUT_BUTTON_SIZE_Y));
        code.appProps.userInput.userInputButton[i].setPosition(sf::Vector2f(USER_INPUT_POS_X+(USER_INPUT_SIZE_X-2*USER_INPUT_BUTTON_SIZE_X-200)/2+(200+USER_INPUT_BUTTON_SIZE_X)*(i-1),USER_INPUT_BUTTON_POS_Y));
        code.appProps.userInput.userInputButton[i].setOutlineThickness(USER_INPUT_BACKGROUND_BORDER_THICKNESS);
        code.appProps.userInput.userInputButton[i].setOutlineColor(USER_INPUT_BACKGROUND_BORDER_COLOR);

        code.appProps.userInput.userInputButtonText[i].setPosition(code.appProps.userInput.userInputButton[i].getPosition());
        code.appProps.userInput.userInputButtonText[i].setFont(textFont);
        code.appProps.userInput.userInputButtonText[i].setCharacterSize(15);
        code.appProps.userInput.userInputButtonText[i].setStyle(sf::Text::Bold);
        code.appProps.userInput.userInputButtonText[i].setFillColor(sf::Color::Black);
    }

    code.appProps.userInput.userInputButtonText[1].setString("CANCEL");
    code.appProps.userInput.userInputButtonText[2].setString("OPEN");
}

void updateUserInputString(char userChar) {
    int activeField = code.appProps.userInput.activeField;
    if((int)userChar == 8 && code.appProps.userInput.userInputString[activeField].getSize() != 0) { // if backspace is pressed
        code.appProps.userInput.userInputString[activeField].erase(code.appProps.userInput.userInputString[activeField].getSize() - 1, 1);
    } else if((int)userChar != 8){
        code.appProps.userInput.userInputString[activeField] += userChar;
    }
    code.appProps.userInput.userInputText[activeField].setString(code.appProps.userInput.userInputString[activeField]);

    ///TESTS
    //char test[101];
    //strcpy(test, code.appProps.userInput.userInputString[activeField].toAnsiString().c_str());
    //cout <<test << ' ';

}

void updateAppOutput(int numberOfLines, char outputText[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE]) {
    for(int i = 1; i < MAX_NUMBER_OF_CODE_LINE; i++) {
        code.appProps.appOutput.codeOutput[i].setString("");
    }
    for(int i = 1; i <= numberOfLines; i++) {
        string line = "";
        appendCharToString(outputText[i], line);
        code.appProps.appOutput.codeOutput[i].setString(line);
    }
}

void addBlockIsPressedHandler(int buttonId, sf::Font &textFont) {
    drawNewBlock(code.appProps.addBlockMenu.dummyBlock[buttonId].getPosition(), buttonId+1, textFont);
    code.appProps.addBlockMenu.blockIsBeingAdded = true;

}

void blockMenuButtonIsPressedHandler(int buttonId, sf::Font &textFont) {
    int blockType = code.allBlocks[code.appProps.blockMenu.blockMenuIsActive]->typeId;
    string buttonText = code.appProps.blockMenu.menuButtonsTitle[buttonId].getString().toAnsiString();

    if(buttonText.compare(MENU_BLOCK_CONNECTION) == 0) {
        startConnection(code.appProps.blockMenu.blockMenuIsActive);
    } else if(buttonText.compare(MENU_BLOCK_T_CONNECTION) == 0) {
        startConnectionDecision(code.appProps.blockMenu.blockMenuIsActive, true);
    } else if(buttonText.compare(MENU_BLOCK_F_CONNECTION) == 0) {
        startConnectionDecision(code.appProps.blockMenu.blockMenuIsActive, false);
    } else if(buttonText.compare(MENU_BLOCK_FINISH_CONNECTION) == 0) {
        drawNewConnection(code.appProps.blockMenu.blockMenuIsActive);
    } else if(buttonText.compare(MENU_BLOCK_CHANGE_VARIABLE) == 0) {
        updateUserInputScreen(code.appProps.blockMenu.blockMenuIsActive, textFont);
    } else if(buttonText.compare(MENU_BLOCK_CHANGE_EXPRESSION) == 0) {
        updateUserInputScreen(code.appProps.blockMenu.blockMenuIsActive, textFont);
    } else if(buttonText.compare(MENU_BLOCK_DELETE) == 0) {
        deleteBlock(code.appProps.blockMenu.blockMenuIsActive);
    }
    code.appProps.blockMenu.blockMenuIsActive = false;

}

void appOutputButtonIsPressedHandler(int buttonId) {
    if(buttonId == 1) { // Run Code Button
        int numberOfLines=0;
        char codeOutput[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE]={NULL};
        run_code(code.first, codeOutput, numberOfLines);
        varTester(numberOfLines, codeOutput);
        updateAppOutput(numberOfLines, codeOutput);
    } else { // Generate Code Button

        char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE]; ///indexat de la 1
        int code_line_size;
        output_code(code.first, code_text, code_line_size); ///codul ce urmeaza a fi afisat in interfata grafica se regaseste in code_text[][]
        updateAppOutput(code_line_size, code_text);
    }
}

void userInputButtonIsPressedHandler(int buttonId) {
    if(buttonId == 1) { // cancel button

    } else { // submit button
        if(code.appProps.userInput.inputIsActive != -1) { // for blocks input
            int blockId = code.appProps.userInput.inputIsActive;
            int blockType = code.allBlocks[blockId]->typeId;
            int varId;
            char varName[VAR_NAME_SIZE];
            string expression;

            code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
            code.allBlocks[blockId]->blockExpression.setCharacterSize(BLOCK_TEXT_SIZE);
            code.allBlocks[blockId]->blockExpression.setFillColor(BLOCK_TEXT_COLOR);
            if(blockType == INPUT_BLOCK || blockType == ASSIGN_BLOCK) {
                strcpy(varName, code.appProps.userInput.userInputString[1].toAnsiString().c_str());
                varId = addVariable(varName);
                code.allBlocks[blockId]->varId = varId;
                strcpy(code.allBlocks[blockId]->varFullExpression, code.appProps.userInput.userInputString[2].toAnsiString().c_str());

                appendCharToString(code.vars.var[varId].name, expression);
                appendCharToString(" = ", expression);
                appendCharToString(code.allBlocks[blockId]->varFullExpression, expression);
                code.allBlocks[blockId]->blockExpression.setString(expression);
            } else if(blockType == OUTPUT_BLOCK) {
                strcpy(varName, code.appProps.userInput.userInputString[1].toAnsiString().c_str());
                varId = addVariable(varName);
                code.allBlocks[blockId]->varId = varId;

                appendCharToString(code.vars.var[varId].name, expression);
                code.allBlocks[blockId]->blockExpression.setString(expression);
            } else if(blockType == DECISION_BLOCK) {
                strcpy(code.allBlocks[blockId]->varFullExpression, code.appProps.userInput.userInputString[1].toAnsiString().c_str());

                appendCharToString(code.allBlocks[blockId]->varFullExpression, expression);
                code.allBlocks[blockId]->blockExpression.setString(expression);
            }
        } else { // for import input
            //deleteAllBlocks();
            char fileName[MAX_FILE_NAME_LENGTH];
            strcpy(fileName, code.appProps.userInput.userInputString[1].toAnsiString().c_str());
            cin_from_binary_file(fileName);
        }
    }
    code.appProps.userInput.userInputString[1].clear();
    code.appProps.userInput.userInputString[2].clear();
    code.appProps.userInput.userInputText[1].setString("");
    code.appProps.userInput.userInputText[2].setString("");
    code.appProps.userInput.inputIsActive = false;

}

void menuButtonIsPressedHandler(int buttonId, sf::Font &textFont) {
    if(buttonId == 1) { // Import code
        updateUserInputImportScreen(textFont);
    } else if(buttonId == 2) { // Export code
        cout_to_binary_file();
    } else if(buttonId == 3) { // Clear blocks
        deleteAllBlocks();
    }

}

void moveConnections(int blockId) {
    sf::Vector2f blockPos = code.allBlocks[blockId]->block.getPosition();

    if(code.allBlocks[blockId]->connectionPath.hasConnection) {
        if(code.allBlocks[blockId]->typeId == DECISION_BLOCK) {
            if(code.allBlocks[blockId]->connectionPath.numberOfLinesTru != 0) {
                code.allBlocks[blockId]->connectionPath.truPath[1][0] = sf::Vertex(sf::Vector2f(blockPos.x, blockPos.y+BLOCK_SIZE_Y));
            }
            if(code.allBlocks[blockId]->connectionPath.numberOfLinesFls != 0) {
                code.allBlocks[blockId]->connectionPath.flsPath[1][0] = sf::Vertex(sf::Vector2f(blockPos.x+BLOCK_SIZE_X, blockPos.y+BLOCK_SIZE_Y));
            }
        } else {
            if(code.allBlocks[blockId]->connectionPath.numberOfLinesNext != 0) {
                code.allBlocks[blockId]->connectionPath.nextPath[1][0] = sf::Vertex(sf::Vector2f(blockPos.x+BLOCK_SIZE_X/2, blockPos.y+BLOCK_SIZE_Y));
            }
        }
    }

    for(int i = 1; i <= code.allBlocks[blockId]->numberOfPrevs; i++) {
        if(code.allBlocks[blockId]->prev[i]!=NULL) {
            if(code.allBlocks[blockId]->prev[i]->typeId == DECISION_BLOCK) {
                if(code.allBlocks[blockId]->prev[i]->tru == code.allBlocks[blockId]) {
                    code.allBlocks[blockId]->prev[i]->connectionPath.truPath[1][1] = sf::Vertex(sf::Vector2f(blockPos.x+BLOCK_SIZE_X/2, blockPos.y));
                }
                if(code.allBlocks[blockId]->prev[i]->fls == code.allBlocks[blockId]) {
                    code.allBlocks[blockId]->prev[i]->connectionPath.flsPath[1][1] = sf::Vertex(sf::Vertex(sf::Vector2f(blockPos.x+BLOCK_SIZE_X/2, blockPos.y)));
                }
            } else {
                code.allBlocks[blockId]->prev[i]->connectionPath.nextPath[1][1] = sf::Vertex(sf::Vector2f(blockPos.x+BLOCK_SIZE_X/2, blockPos.y));
            }
        }
    }

}

void moveBlock(int blockId) {
    if(mouseIsOnItem(sf::Vector2f(0,0), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
        sf::FloatRect blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
        sf::FloatRect addBlockMenuBounds = code.appProps.addBlockMenu.addBlockMenuBackground.getGlobalBounds();
        sf::FloatRect appMenuBounds = code.appProps.appMenu.appMenuBackground.getGlobalBounds();
        sf::FloatRect appOutputBounds = code.appProps.appOutput.appOutputBackground.getGlobalBounds();

        if(!blockBounds.intersects(addBlockMenuBounds)) {
            if(code.appProps.addBlockMenu.blockIsBeingAdded == true) {
                code.appProps.addBlockMenu.blockIsBeingAdded = false;
            } else {
                if(!code.appProps.block.blockIsBeingMoved) {
                    code.appProps.block.xDif = code.appProps.mousePos.x - code.allBlocks[blockId]->block.getPosition().x;
                    code.appProps.block.yDif = code.appProps.mousePos.y - code.allBlocks[blockId]->block.getPosition().y;
                    code.appProps.block.blockIsBeingMoved = blockId;
                }
                code.allBlocks[blockId]->block.setPosition(code.appProps.mousePos.x - code.appProps.block.xDif, code.appProps.mousePos.y - code.appProps.block.yDif);
                code.allBlocks[blockId]->blockTitle.setPosition(code.allBlocks[blockId]->block.getPosition());
                code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
                moveConnections(blockId);
                blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
            }

        }

        if(blockBounds.intersects(addBlockMenuBounds) ){
            if(code.appProps.addBlockMenu.blockIsBeingAdded == false) {
                code.allBlocks[blockId]->block.setPosition(sf::Vector2f(ADD_BLOCK_MENU_SIZE_X, code.allBlocks[blockId]->block.getPosition().y));
                code.allBlocks[blockId]->blockTitle.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition()));
                code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
                moveConnections(blockId);
                blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
            } else {
                if(!code.appProps.block.blockIsBeingMoved) {
                    code.appProps.block.xDif = code.appProps.mousePos.x - code.allBlocks[blockId]->block.getPosition().x;
                    code.appProps.block.yDif = code.appProps.mousePos.y - code.allBlocks[blockId]->block.getPosition().y;
                    code.appProps.block.blockIsBeingMoved = blockId;
                }
                code.allBlocks[blockId]->block.setPosition(code.appProps.mousePos.x - code.appProps.block.xDif, code.appProps.mousePos.y - code.appProps.block.yDif);
                code.allBlocks[blockId]->blockTitle.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition()));
                code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
                moveConnections(blockId);
                blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
            }
        }

        if(blockBounds.intersects(appOutputBounds)) {
            code.allBlocks[blockId]->block.setPosition(sf::Vector2f(code.appProps.appOutput.appOutputBackground.getPosition().x-BLOCK_SIZE_X, code.allBlocks[blockId]->block.getPosition().y));
            code.allBlocks[blockId]->blockTitle.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition()));
            code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
            moveConnections(blockId);
            blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
        }

        if(blockBounds.intersects(appMenuBounds)) {
            code.allBlocks[blockId]->block.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition().x, APP_MENU_SIZE_Y));
            code.allBlocks[blockId]->blockTitle.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition()));
            code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
            moveConnections(blockId);
            blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
        }

        if(code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y > WINDOW_HEIGHT) {
            code.allBlocks[blockId]->block.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition().x, WINDOW_HEIGHT-BLOCK_SIZE_Y));
            code.allBlocks[blockId]->blockTitle.setPosition(sf::Vector2f(code.allBlocks[blockId]->block.getPosition()));
            code.allBlocks[blockId]->blockExpression.setPosition(code.allBlocks[blockId]->block.getPosition().x, code.allBlocks[blockId]->block.getPosition().y+BLOCK_SIZE_Y/2);
            moveConnections(blockId);
            blockBounds = code.allBlocks[blockId]->block.getGlobalBounds();
        }
    }

}

/// /////////// DISPLAY ////////////////////////
void displayAppOutput(sf::RenderWindow &window) {
    window.draw(code.appProps.appOutput.appOutputBackground);
    window.draw(code.appProps.appOutput.appOutputArea);
    for(int i = 1; i <= 2; i++) {
        window.draw(code.appProps.appOutput.appOutputButton[i]);
        window.draw(code.appProps.appOutput.appOutputButtonText[i]);
    }
    for(int i = 1; i < MAX_NUMBER_OF_CODE_LINE; i++) {
        window.draw(code.appProps.appOutput.codeOutput[i]);
    }
}

void displayAppMenu(sf::RenderWindow &window) {
    window.draw(code.appProps.appMenu.appMenuBackground);
    for(int i = 1; i <= NUMBER_OF_APP_MENU_BUTTONS; i++) {
        window.draw(code.appProps.appMenu.appMenuButton[i]);
        window.draw(code.appProps.appMenu.appMenuButtonText[i]);
    }

}

void displayAddBlockMenu(sf::RenderWindow &window) {
    window.draw(code.appProps.addBlockMenu.addBlockMenuBackground);
    window.draw(code.appProps.addBlockMenu.menuTitle);
    window.draw(code.appProps.addBlockMenu.underline, 2, sf::Lines);
    for(int i = 1; i <= 5; i++) {
        window.draw(code.appProps.addBlockMenu.dummyBlock[i]);
        window.draw(code.appProps.addBlockMenu.dummyBlockTitle[i]);
    }
}

void displayConnection(int blockId, sf::RenderWindow &window) {
    if(code.allBlocks[blockId]->connectionPath.hasConnection) {
        if(code.allBlocks[blockId]->typeId == DECISION_BLOCK) {
            for(int i = 1; i <= code.allBlocks[blockId]->connectionPath.numberOfLinesTru; i++) {
                window.draw(code.allBlocks[blockId]->connectionPath.truPath[i], 2, sf::Lines);
            }
            for(int i = 1; i <= code.allBlocks[blockId]->connectionPath.numberOfLinesFls; i++) {
                window.draw(code.allBlocks[blockId]->connectionPath.flsPath[i], 2, sf::Lines);
            }
        } else {
            for(int i = 1; i <= code.allBlocks[blockId]->connectionPath.numberOfLinesNext; i++) {
                window.draw(code.allBlocks[blockId]->connectionPath.nextPath[i], 2, sf::Lines);
            }
        }
    }

}

void displayAllLogicBlocks(sf::RenderWindow &window) {
    for(int i=1; i <= code.numberOfBlocks; i++) {
        if(code.allBlocks[i]->typeId != EMPTY_BLOCK) {
            window.draw(code.allBlocks[i]->block);
            window.draw(code.allBlocks[i]->blockTitle);
            window.draw(code.allBlocks[i]->blockExpression);
            displayConnection(i, window);
        }
    }

}

void displayBlockMenu(sf::RenderWindow &window) {
    if(code.appProps.blockMenu.blockMenuIsActive) {
        window.draw(code.appProps.blockMenu.menuBackground);
        for(int i = 1; i <= code.appProps.blockMenu.numberOfButtons; i++) {
            window.draw(code.appProps.blockMenu.menuButtons[i]);
            window.draw(code.appProps.blockMenu.menuButtonsTitle[i]);
        }
    }

}

void displayUserInput(sf::RenderWindow &window) {
    if(code.appProps.userInput.inputIsActive) {
        window.draw(code.appProps.userInput.userInputBackground);
        window.draw(code.appProps.userInput.userInputTitle);
        for(int i = 1; i <= code.appProps.userInput.numberOfFields; i++) {
            window.draw(code.appProps.userInput.userInputField[i]);
            window.draw(code.appProps.userInput.fieldTitle[i]);
            window.draw(code.appProps.userInput.userInputText[i]);
        }

        for(int i = 1; i <= 2; i++) {
            window.draw(code.appProps.userInput.userInputButton[i]);
            window.draw(code.appProps.userInput.userInputButtonText[i]);
        }
    }
}

void displayAppTitle(sf::RenderWindow &window, sf::Font &textFont) {
    sf::Text appTitle;
    appTitle.setString("INTERSCHEM");
    appTitle.setFont(textFont);
    appTitle.setCharacterSize(45);
    appTitle.setFillColor(sf::Color::Red);
    appTitle.setPosition(sf::Vector2f(465, 2));
    appTitle.setStyle(sf::Text::Bold);
    window.draw(appTitle);
}
/// /////////// END OF DISPLAY ////////////////////////
