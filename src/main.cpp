// !FIX: refactor TextEditor code;
// *ADD: Add variables to track cursor position (cursorX and cursorY);
// *ADD: Draw a visual cursor using sf::RectangleShape;
// *ADD: Capture arrow key inputs to move the cursor horizontally and vertically;
// *ADD: Use Text::findCharacterPos() and Text::getCharacterSize() to do text wrap and limit the displayed lines within the visible area of the window;
// *ADD: Clamp cursor movement to prevent moving out of bounds;
// *ADD: Scroll the viewport down when the cursor moves out of the visible area;
// *ADD: Implement cursor blinking effect using sf::Clock;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextEditor.h"
#include "CameraManager.h"

const sf::Color BG_COLOR = sf::Color(27.0f, 24.0f, 51.0f, 1.0f);
const sf::Color CURSOR_COLOR = sf::Color(242.0f, 159.0f, 88.0f, 120.0f);

void HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode);

std::vector<std::string> text = {
    "import java.util.HashMap;",
    "import java.util.Map;",
    " ",
    "public class Fibonacci {",
    "    private static Map<Integer, Integer> memo = new HashMap<>();",
    " ",
    "    public static int fibonacci(int n) {",
    "        if (n <= 1)",
    "            return n;",
    "        if (memo.containsKey(n))",
    "            return memo.get(n);",
    "        int result = fibonacci(n - 1) + fibonacci(n - 2);",
    "        memo.put(n, result);",
    "        return result;",
    "    }",
    " ",
    "    public static void main(String[] args) {",
    "        int n = 10;",
    "        for (int i = 0; i < n; i++) {",
    "            System.out.print(fibonacci(i) + \" \");",
    "        }",
    "    }",
    "}"};

int main()
{
    sf::RenderWindow window({1080u, 720u}, "Text Editor");
    window.setFramerateLimit(144);

    CameraManager camera(sf::Vector2f(1080u, 720u), sf::FloatRect(0, 0, 1080u, 720u));

    TextEditor textEditor(text, CURSOR_COLOR);

    sf::Font monacoFont;
    monacoFont.loadFromFile("./fonts/Monaco.ttf");

    const float LINE_HEIGHT = 50.0f;
    const unsigned int CHAR_SIZE = 30u;

    textEditor.SetLineHeight(LINE_HEIGHT);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseWheelMoved:
            {
                int direction = event.mouseWheel.delta * -1;
                camera.Scroll(direction);
                break;
            }
            case sf::Event::KeyPressed:
                HandleKeyboardInput(textEditor, event.key.code);
                break;
            }

            window.clear(BG_COLOR);

            camera.SetLimits(sf::FloatRect(0, 0, 1300, textEditor.GetTextHeight()));
            camera.Render(window);

            textEditor.Draw(window, monacoFont, CHAR_SIZE, sf::Color::White);

            window.display();
        }
    }
}

void HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
    case sf::Keyboard::Key::Right:
        textEditor.MoveCursor(1, 0);
        break;
    case sf::Keyboard::Key::Left:
        textEditor.MoveCursor(-1, 0);
        break;
    case sf::Keyboard::Key::Down:
        textEditor.MoveCursor(0, 1);
        break;
    case sf::Keyboard::Key::Up:
        textEditor.MoveCursor(0, -1);
        break;
    case sf::Keyboard::Key::End:
        std::cout << "\nend";
        textEditor.MoveCursor(999, 0);
        break;
    case sf::Keyboard::Key::Home:
        std::cout << "\nhome";
        textEditor.MoveCursor(-999, 0);
        break;
    default:
        break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if (keyCode == sf::Keyboard::Key::End)
        {
            std::cout << "\nctrl + " << " end";
            textEditor.MoveCursor(0, 999);
        }
        else if (keyCode == sf::Keyboard::Key::Home)
        {
            std::cout << "\nctrl + " << " home";
            textEditor.MoveCursor(0, -999);
        }
    }
}
