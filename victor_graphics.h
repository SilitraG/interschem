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

//Input: blockPosition, blockType
//Adds a block to the allBlocks array (only the visual part for now)
void drawNewBlock(sf::Vector2f blockPos, int blockType) {
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

}

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
        if(mouseIsOnItem(code.allBlocks[i]->block.getPosition(), code.allBlocks[i]->block.getSize())) {
            return i;
        }
    }
    return -1;

}

void moveBlock(int blockId) {
    //if(mouseIsOnItem(code.allBlocks[blockId]->block.getPosition(), code.allBlocks[blockId]->block.getSize()) || code.appProps.block.blockIsBeingMoved == blockId) {
    if(!code.appProps.block.blockIsBeingMoved) {
        code.appProps.block.xDif = code.appProps.mousePos.x - code.allBlocks[blockId]->block.getPosition().x;
        code.appProps.block.yDif = code.appProps.mousePos.y - code.allBlocks[blockId]->block.getPosition().y;
    }
    code.appProps.block.blockIsBeingMoved = blockId;
    code.allBlocks[blockId]->block.setPosition(code.appProps.mousePos.x - code.appProps.block.xDif, code.appProps.mousePos.y - code.appProps.block.yDif);
    //}

}

void displayAllLogicBlocks(sf::RenderWindow &window) {
    for(int i=1; i<=code.numberOfBlocks; i++) {
            window.draw(code.allBlocks[i]->block);
    }
}
