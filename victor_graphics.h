
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
                } else {
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

//Input: blockPosition, blockType
//Adds a block to the allBlocks array (only the visual part for now)
void drawNewBlock(sf::Vector2f blockPos, int blockType, sf::Font &textFont) {
    code.numberOfBlocks++;
    code.allBlocks[code.numberOfBlocks] = new LogicBlock;
    code.allBlocks[code.numberOfBlocks]->blockPos = blockPos;
    code.allBlocks[code.numberOfBlocks]->block.setPosition(code.allBlocks[code.numberOfBlocks]->blockPos);
    code.allBlocks[code.numberOfBlocks]->block.setSize(sf::Vector2f(BLOCK_SIZE_X, BLOCK_SIZE_Y));
    if(blockType == START_BLOCK) {
        code.allBlocks[code.numberOfBlocks]->block.setFillColor(sf::Color::START_BLOCK_COLOR);
    } else if(blockType == STOP_BLOCK) {
        code.allBlocks[code.numberOfBlocks]->block.setFillColor(sf::Color::STOP_BLOCK_COLOR);
    } else {
        code.allBlocks[code.numberOfBlocks]->block.setFillColor(sf::Color::GENERIC_BLOCK_COLOR);
    }

    code.allBlocks[code.numberOfBlocks]->blockTitle.setFont(textFont);
    switch (blockType) {
        case START_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("START");
            code.allBlocks[code.numberOfBlocks]->typeId = START_BLOCK;
            break;
        case INPUT_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("INPUT");
            code.allBlocks[code.numberOfBlocks]->typeId = INPUT_BLOCK;
            break;
        case OUTPUT_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("OUTPUT");
            code.allBlocks[code.numberOfBlocks]->typeId = OUTPUT_BLOCK;
            break;
        case ASSIGN_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("ASSIGN");
            code.allBlocks[code.numberOfBlocks]->typeId = ASSIGN_BLOCK;
            break;
        case DECISION_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("DECISION");
            code.allBlocks[code.numberOfBlocks]->typeId = DECISION_BLOCK;
            break;
        case STOP_BLOCK:
            code.allBlocks[code.numberOfBlocks]->blockTitle.setString("STOP");
            code.allBlocks[code.numberOfBlocks]->typeId = STOP_BLOCK;
            break;
        default:
            cerr << "Instructiune incorecta(drawNewBlock)\n";
    }
    code.allBlocks[code.numberOfBlocks]->blockTitle.setCharacterSize(BLOCK_TEXT_SIZE);
    code.allBlocks[code.numberOfBlocks]->blockTitle.setFillColor(sf::Color::BLOCK_TEXT_COLOR);
    code.allBlocks[code.numberOfBlocks]->blockTitle.setPosition(blockPos);

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

void blockMenuButtonIsPressedHandler(int buttonId) {
    int blockType = code.allBlocks[code.appProps.blockMenu.blockMenuIsActive]->typeId;
    string buttonText = code.appProps.blockMenu.menuButtonsTitle[buttonId].getString().toAnsiString();
    //cout << buttonText.compare(MENU_BLOCK_CONNECTION) << '\n';
    if(buttonText.compare(MENU_BLOCK_CONNECTION) == 0) {
        startConnection(code.appProps.blockMenu.blockMenuIsActive);
    } else if(buttonText.compare(MENU_BLOCK_T_CONNECTION) == 0) {
        startConnectionDecision(code.appProps.blockMenu.blockMenuIsActive, true);
    } else if(buttonText.compare(MENU_BLOCK_F_CONNECTION) == 0) {
        startConnectionDecision(code.appProps.blockMenu.blockMenuIsActive, false);
    } else if(buttonText.compare(MENU_BLOCK_FINISH_CONNECTION) == 0) {
        drawNewConnection(code.appProps.blockMenu.blockMenuIsActive);
    } else if(buttonText.compare(MENU_BLOCK_CHANGE_VARIABLE) == 0) {

    } else if(buttonText.compare(MENU_BLOCK_CHANGE_EXPRESSION) == 0) {

    } else if(buttonText.compare(MENU_BLOCK_DELETE) == 0) {
        deleteBlock(code.appProps.blockMenu.blockMenuIsActive);
    }

}

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
/// /////////// END OF CHECK MOUSE POSITION ////////////////////////
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
    if(!code.appProps.block.blockIsBeingMoved) {
        code.appProps.block.xDif = code.appProps.mousePos.x - code.allBlocks[blockId]->block.getPosition().x;
        code.appProps.block.yDif = code.appProps.mousePos.y - code.allBlocks[blockId]->block.getPosition().y;
        code.appProps.block.blockIsBeingMoved = blockId;
    }
    code.allBlocks[blockId]->block.setPosition(code.appProps.mousePos.x - code.appProps.block.xDif, code.appProps.mousePos.y - code.appProps.block.yDif);
    code.allBlocks[blockId]->blockTitle.setPosition(code.appProps.mousePos.x - code.appProps.block.xDif, code.appProps.mousePos.y - code.appProps.block.yDif);
    moveConnections(blockId);

}

void updateBlockMenu(int blockId, sf::Font &textFont) {
    code.appProps.blockMenu.blockMenuIsActive = blockId;
    code.appProps.blockMenu.menuPos = code.appProps.mousePos;
    if(code.appProps.connection.masterBlockId == 0) {
        code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_CONNECTION);
    } else {
        code.appProps.blockMenu.menuButtonsTitle[1].setString(MENU_BLOCK_FINISH_CONNECTION);
    }
    switch (code.allBlocks[blockId]->typeId) {
        case START_BLOCK:
            code.appProps.blockMenu.numberOfButtons = 2;
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
            code.appProps.blockMenu.numberOfButtons = 2;
            break;
        default:
            cerr << "Instructiune incorecta(updateBlockMenu)\n";
    }
    code.appProps.blockMenu.menuButtonsTitle[code.appProps.blockMenu.numberOfButtons].setString(MENU_BLOCK_DELETE);

    code.appProps.blockMenu.menuBackground.setPosition(code.appProps.blockMenu.menuPos);
    code.appProps.blockMenu.menuBackground.setSize(sf::Vector2f(BLOCK_MENU_BUTTON_SIZE_X+2*BORDER_THICKNESS, BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BORDER_THICKNESS)*code.appProps.blockMenu.numberOfButtons));
    code.appProps.blockMenu.menuBackground.setFillColor(sf::Color::MENU_COLOR);

    for(int i = 1; i <= code.appProps.blockMenu.numberOfButtons; i++) {
        //xMenuPos+border, yMenuPos+border+(buttonSize+border)*how many buttons were before
        code.appProps.blockMenu.menuButtons[i].setPosition(sf::Vector2f(code.appProps.blockMenu.menuPos.x+BORDER_THICKNESS, code.appProps.blockMenu.menuPos.y+BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BORDER_THICKNESS)*(i-1)));
        code.appProps.blockMenu.menuButtons[i].setSize(sf::Vector2f(BLOCK_MENU_BUTTON_SIZE_X, BLOCK_MENU_BUTTON_SIZE_Y));
        code.appProps.blockMenu.menuButtons[i].setFillColor(sf::Color::MENU_BUTTON_COLOR);

        code.appProps.blockMenu.menuButtonsTitle[i].setFont(textFont);
        code.appProps.blockMenu.menuButtonsTitle[i].setPosition(sf::Vector2f(code.appProps.blockMenu.menuPos.x+BORDER_THICKNESS, code.appProps.blockMenu.menuPos.y+BORDER_THICKNESS+(BLOCK_MENU_BUTTON_SIZE_Y+BORDER_THICKNESS)*(i-1)));
        code.appProps.blockMenu.menuButtonsTitle[i].setCharacterSize(MENU_TEXT_SIZE);
        code.appProps.blockMenu.menuButtonsTitle[i].setFillColor(sf::Color::MENU_BUTTON_TEXT_COLOR);
    }

}

/// /////////// DISPLAY ////////////////////////
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

/// /////////// END OF DISPLAY ////////////////////////

