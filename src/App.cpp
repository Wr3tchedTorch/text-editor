#include "App.h"

void App::SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager)
{
    textEditor.SetText(toText);
    cameraManager.SetLimits(sf::FloatRect({0, 0}, {textEditor.GetTextWidth(), textEditor.GetTextHeight()}));
}

void App::CameraFollow(sf::Vector2f position, CameraManager &camera)
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
    
    if (position.x > camera.GetRightPosition())
    {
        camera.Move({camera.GetMovementSpeed(), 0});
    }
    if (position.x < camera.GetLeftPosition())
    {
        camera.Move({-camera.GetMovementSpeed(), 0});
    }
}