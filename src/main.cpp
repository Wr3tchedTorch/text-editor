// !FIX: create `App` class to store application related functions, such as keyboard processing functions;

// *ADD: Scroll the viewport down when the cursor moves out of the visible area;
// *ADD: Use Text::findCharacterPos() and Text::getCharacterSize() to do text wrap and limit the displayed lines within the visible area of the window;
// *ADD: Implement cursor blinking effect using sf::Clock;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextEditor.h"
#include "CameraManager.h"

void HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode);
void HandleKeyCombinations(TextEditor &textEditor, sf::Keyboard::Key keyCode);
void SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager);

const sf::Vector2f WINDOW_RESOLUTION = {1080u, 720u};
const std::string WINDOW_TITLE = "Eric Code";

const sf::Color CURSOR_COLOR = sf::Color(242.0f, 159.0f, 88.0f, 120.0f);
const sf::Color BG_COLOR = sf::Color(27.0f, 24.0f, 51.0f);
const sf::Color FONT_COLOR = sf::Color(255.0f, 240.0f, 220.0f);

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
    const float LINE_HEIGHT = 50.0f;
    const unsigned int CHAR_SIZE = 30u;

    sf::RenderWindow window(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), WINDOW_TITLE);
    window.setFramerateLimit(144);

    sf::Font monacoFont;
    monacoFont.loadFromFile("./fonts/Monaco.ttf");

    TextEditor textEditor(CURSOR_COLOR, monacoFont);
    textEditor.SetLineHeight(LINE_HEIGHT);

    CameraManager camera(WINDOW_RESOLUTION);

    SetEditorText(text, textEditor, camera);

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

            textEditor.Draw(window, CHAR_SIZE, FONT_COLOR);

            window.display();
        }
    }
}

void HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
    case sf::Keyboard::Key::Right:
        textEditor.MoveCursor({1, 0});
        break;
    case sf::Keyboard::Key::Left:
        textEditor.MoveCursor({-1, 0});
        break;
    case sf::Keyboard::Key::Down:
        textEditor.MoveCursor({0, 1});
        break;
    case sf::Keyboard::Key::Up:
        textEditor.MoveCursor({0, -1});
        break;
    case sf::Keyboard::Key::End:
        std::cout << "\nend";
        textEditor.MoveCursor({999, 0});
        break;
    case sf::Keyboard::Key::Home:
        std::cout << "\nhome";
        textEditor.MoveCursor({-999, 0});
        break;
    default:
        break;
    }

    HandleKeyCombinations(textEditor, keyCode);
}

void HandleKeyCombinations(TextEditor &textEditor, sf::Keyboard::Key keyCode)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if (keyCode == sf::Keyboard::Key::End)
        {
            std::cout << "\nctrl + " << " end";
            textEditor.MoveCursor({0, 999});
        }
        else if (keyCode == sf::Keyboard::Key::Home)
        {
            std::cout << "\nctrl + " << " home";
            textEditor.MoveCursor({0, -999});
        }
    }
}

void SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager)
{
    textEditor.SetText(toText);

    std::cout << "\nText height: " << textEditor.GetTextHeight() << " | Text width: " << textEditor.GetTextWidth();
    cameraManager.SetLimits(sf::FloatRect({0, 0}, {textEditor.GetTextWidth(), textEditor.GetTextHeight()}));
}
