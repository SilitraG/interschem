#include <SFML/Graphics.hpp>

void appWindow()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interschem");
    window.setFramerateLimit(60);

    drawNewBlock(sf::Vector2f(200, 100), START_BLOCK);
    drawNewBlock(sf::Vector2f(400, 600), STOP_BLOCK);
    drawNewBlock(sf::Vector2f(500, 500), INPUT_BLOCK);
    drawNewBlock(sf::Vector2f(450, 200), OUTPUT_BLOCK);
    drawNewBlock(sf::Vector2f(150, 630), STOP_BLOCK);

    rearrangeBlocks(2);

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
                    break;
                }
                break;

            case sf::Event::MouseButtonReleased: // Mouse released buttons
                switch (event.key.code) {
                case sf::Mouse::Left:
                    code.appProps.mouseIsPressed = false;
                    code.appProps.block.blockIsBeingMoved = false;
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


        //cout << mouseIsOnBlock();
        if(code.appProps.mouseIsPressed) {
            if(code.appProps.block.blockIsBeingMoved) {
                moveBlock(code.appProps.block.blockIsBeingMoved);
            }
            else if(mouseIsOnBlock() != -1) {
                moveBlock(mouseIsOnBlock());
                rearrangeBlocks(code.appProps.block.blockIsBeingMoved);
            }
        }

        code.appProps.mouseIsMoving = false;
        window.clear(sf::Color::WINDOW_COLOR);

        /// DRAWING ZONE ///
        displayAllLogicBlocks(window);

        /// END OF DRAWING ZONE ///

        window.display();
    }

}
