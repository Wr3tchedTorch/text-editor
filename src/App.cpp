#include "App.h"

void App::SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager)
{
    textEditor.SetText(toText);
    cameraManager.SetLimits(sf::FloatRect({0, 0}, {textEditor.GetTextWidth(), textEditor.GetTextHeight()}));
}

void App::HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode)
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

    App::HandleKeyCombinations(textEditor, keyCode);
}

void App::HandleKeyCombinations(TextEditor &textEditor, sf::Keyboard::Key keyCode)
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