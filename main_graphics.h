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

    drawAppMenu(arialMedium);
    drawAppOutput(arialMedium);
    drawAddBlockMenu(arialMedium);

    drawNewBlock(sf::Vector2f(200, 100), START_BLOCK, arialMedium);
    drawNewBlock(sf::Vector2f(400, 600), STOP_BLOCK, arialMedium);
    drawNewBlock(sf::Vector2f(500, 500), INPUT_BLOCK, arialMedium);
    drawNewBlock(sf::Vector2f(200, 400), ASSIGN_BLOCK, arialMedium);
    drawNewBlock(sf::Vector2f(450, 200), OUTPUT_BLOCK, arialMedium);
    drawNewBlock(sf::Vector2f(250, 230), DECISION_BLOCK, arialMedium);
    //drawNewBlock(sf::Vector2f(150, 630), STOP_BLOCK, arialMedium);

    //cout << code.allBlocks[2]->blockTitle.getLocalBounds().width; //for text centering

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

            case sf::Event::MouseButtonPressed: // Mouse pressed buttons
                switch (event.key.code) {
                case sf::Mouse::Left:
                    code.appProps.mouseIsPressed = true;
                    if(mouseIsOnAddBlock() != -1){
                        addBlockIsPressedHandler(mouseIsOnAddBlock(), arialMedium);
                    }
                    if(mouseIsOnBlockMenuButton() != -1) {
                        blockMenuButtonIsPressedHandler(mouseIsOnBlockMenuButton());
                    }
                    code.appProps.blockMenu.blockMenuIsActive = false;
                    break;
                case sf::Mouse::Right:
                    break;
                }
                break;

            case sf::Event::MouseButtonReleased: // Mouse released buttons
                switch (event.key.code) {
                case sf::Mouse::Left:
                    if(mouseIsOnAppOutputButton()) {
                        appOutputButtonIsPressedHandler(mouseIsOnAppOutputButton());
                    }
                    code.appProps.mouseIsPressed = false;
                    code.appProps.block.blockIsBeingMoved = false;
                    code.appProps.addBlockMenu.blockIsBeingAdded = false;
                    break;
                case sf::Mouse::Right:
                    code.appProps.blockMenu.blockMenuIsActive = false;
                    if(mouseIsOnBlock() != -1) {
                        updateBlockMenu(mouseIsOnBlock(), arialMedium);
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

        if(code.appProps.mouseIsPressed) {
            if(code.appProps.block.blockIsBeingMoved) {
                moveBlock(code.appProps.block.blockIsBeingMoved);
            }
            else if(mouseIsOnBlock() != -1) {
                moveBlock(mouseIsOnBlock());
                //rearrangeBlocks(code.appProps.block.blockIsBeingMoved);
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

        /// END OF DRAWING ZONE ///

        window.display();
    }

}
