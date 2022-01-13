#include <SFML/Graphics.hpp>

void appWindow()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interschem", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font arialMedium;
    if (!arialMedium.loadFromFile("Fonts/Arial-Medium.ttf"))
    {
        cerr << "Font error";
    }

    drawNewBlock(sf::Vector2f(200, 100), START_BLOCK, arialMedium);
    drawAppMenu(arialMedium);
    drawAppOutput(arialMedium);
    drawAddBlockMenu(arialMedium);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed: // Keyboard keys
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                }
                break;

            case sf::Event::TextEntered: // Keyboard text
                if(code.appProps.userInput.inputIsActive) {
                    updateUserInputString(event.text.unicode);
                }
                break;

            case sf::Event::MouseButtonPressed: // Mouse pressed buttons
                switch (event.key.code) {
                case sf::Mouse::Left:
                    code.appProps.mouseIsPressed = true;
                    if(code.appProps.userInput.inputIsActive == false) {
                        if(mouseIsOnAddBlock() != -1){
                            addBlockIsPressedHandler(mouseIsOnAddBlock(), arialMedium);
                        }

                    }
                    if(mouseIsOnBlockMenuButton() == -1) {
                        code.appProps.blockMenu.blockMenuIsActive = false;
                    }
                    break;
                case sf::Mouse::Right:
                    break;
                }
                break;

            case sf::Event::MouseButtonReleased: // Mouse released buttons
                if(code.appProps.userInput.inputIsActive != false && mouseIsOnItem(code.appProps.userInput.userInputBackground.getPosition(), code.appProps.userInput.userInputBackground.getSize()) == false) {
                    userInputButtonIsPressedHandler(1);
                }
                switch (event.key.code) {
                case sf::Mouse::Left:
                    if(mouseIsOnUserInputButton() != -1) {
                        userInputButtonIsPressedHandler(mouseIsOnUserInputButton());
                    }
                    if(code.appProps.userInput.inputIsActive == false) {
                        if(mouseIsOnBlockMenuButton() != -1) {
                            blockMenuButtonIsPressedHandler(mouseIsOnBlockMenuButton(), arialMedium);
                        }
                        if(mouseIsOnAppOutputButton() != -1) {
                            appOutputButtonIsPressedHandler(mouseIsOnAppOutputButton());
                        }
                        if(mouseIsOnAppMenuButton() != -1) {
                            menuButtonIsPressedHandler(mouseIsOnAppMenuButton(), arialMedium);
                        }
                    } else {
                        if(mouseIsOnUserInputField() != -1) {
                            code.appProps.userInput.activeField = mouseIsOnUserInputField();
                        }
                    }
                    code.appProps.mouseIsPressed = false;
                    code.appProps.block.blockIsBeingMoved = false;
                    code.appProps.addBlockMenu.blockIsBeingAdded = false;
                    break;
                case sf::Mouse::Right:
                    code.appProps.blockMenu.blockMenuIsActive = false;
                    if(code.appProps.userInput.inputIsActive == false) {
                        if(mouseIsOnBlock() != -1) {
                            updateBlockMenu(mouseIsOnBlock(), arialMedium);
                        }
                    }
                    break;
                }
                break;

            case sf::Event::MouseMoved: // Mouse has moved
                code.appProps.mousePos.x = event.mouseMove.x;
                code.appProps.mousePos.y = event.mouseMove.y;
                code.appProps.mouseIsMoving = true;
                break;
            }
        }

        if(code.appProps.mouseIsPressed && code.appProps.userInput.inputIsActive == false) {
            if(code.appProps.block.blockIsBeingMoved) {
                moveBlock(code.appProps.block.blockIsBeingMoved);
            }
            else if(mouseIsOnBlock() != -1) {
                moveBlock(mouseIsOnBlock());
            }
        }
        code.appProps.mouseIsMoving = false;
        window.clear(sf::Color::WINDOW_COLOR);
        /// DRAWING ZONE ///
        displayAppMenu(window);
        displayAppOutput(window);
        displayAddBlockMenu(window);
        displayAllLogicBlocks(window);
        displayBlockMenu(window);
        displayUserInput(window);
        displayAppTitle(window, arialMedium);
        /// END OF DRAWING ZONE ///

        window.display();
    }

}
