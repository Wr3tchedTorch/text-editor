// ?REFACTOR: CameraManager.cpp and App.cpp codes
// ? continue the creation of the InputManager class using maps and KeyCombinations
// ? create abstract Command class with an Execute() function for general command execution


// *ADD: Use Text::findCharacterPos() and Text::getCharacterSize() to do text wrap and limit the displayed lines within the visible area of the window;
// *ADD: Implement cursor blinking effect using sf::Clock;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextEditor.h"
#include "CameraManager.h"
#include "./input/InputManager.h"
#include "App.h"

const sf::Vector2f WINDOW_RESOLUTION = {1080u, 720u};
const std::string WINDOW_TITLE = "Eric Code";

const sf::Color CURSOR_COLOR = sf::Color(242.0f, 159.0f, 88.0f, 120.0f);
const sf::Color BG_COLOR = sf::Color(27.0f, 24.0f, 51.0f);
const sf::Color FONT_COLOR = sf::Color(255.0f, 240.0f, 220.0f);

float clampValue(float value, float max, float min)
{
    if (value > max)
    {
        value = max;
    }
    if (value < min)
    {
        value = min;
    }
}

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

    InputManager inputManager(textEditor, camera);

    App::SetEditorText(text, textEditor, camera);

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
            {
                inputManager.ProcessKeyboardInput(event.key.code);

                App::CameraFollow(textEditor.GetCursorPosition(), camera);
                break;
            }
            case sf::Event::TextEntered:
                if (event.text.unicode >= 32 && event.text.unicode <= 126)
                    textEditor.AddCharacterAtCursorPosition(static_cast<char>(event.text.unicode));
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                mousePosition.x += camera.GetLeftPosition();
                mousePosition.y += camera.GetTopPosition();
                textEditor.SetCursorPosition(mousePosition);
            }

            window.clear(BG_COLOR);

            camera.SetLimits(sf::FloatRect(0, 0, 1300, textEditor.GetTextHeight()));
            camera.Render(window);

            textEditor.Draw(window, CHAR_SIZE, FONT_COLOR);

            window.display();
        }
    }
}