// *ADD: Render text lines from the std::vector<std::vector<char>>;
// *ADD: Use sf::Text to display each line of text in the window;
// *ADD: Text wrap to limit the displayed lines within the visible area of the window;
// *ADD: a scroll functionality to display the lines below the window;
// *ADD: Add variables to track cursor position (cursorX and cursorY);
// *ADD: Draw a visual cursor using sf::RectangleShape;
// *ADD: Capture arrow key inputs to move the cursor horizontally and vertically;
// *ADD: Clamp cursor movement to prevent moving out of bounds;
// *ADD: Scroll the viewport down when the cursor moves out of the visible area;
// *ADD: Implement cursor blinking effect using sf::Clock;

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
