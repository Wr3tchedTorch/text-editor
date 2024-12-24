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
        textEditor.MoveCursor({999, 0});
        break;
    case sf::Keyboard::Key::Home:
        textEditor.MoveCursor({-999, 0});
        break;
    case sf::Keyboard::BackSpace:    
        textEditor.DeleteCharacterAtCursorPosition();
        break;
    case sf::Keyboard::Enter:
        textEditor.CreateNewLineAtCursorPosition();
        break;    
    }
}

void App::HandleKeyCombinations(CameraManager &camera, TextEditor &textEditor, sf::Keyboard::Key keyCode)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if (keyCode == sf::Keyboard::Key::End)
        {
            textEditor.MoveCursor({0, 999});
            camera.Scroll(999);
        }
        else if (keyCode == sf::Keyboard::Key::Home)
        {
            textEditor.MoveCursor({0, -999});
            camera.Scroll(-999);
        }
    }
}

void App::CameraVerticalFollow(sf::Vector2f position, CameraManager &camera)
{
    const float BOTTOM_OFFSET = 150.0f;
    if (position.y + BOTTOM_OFFSET > camera.GetBottomPosition())
    {
        camera.Scroll(1);
    }
    if (position.y < camera.GetTopPosition())
    {
        camera.Scroll(-1);
    }
}