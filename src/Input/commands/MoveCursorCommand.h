#pragma once

#include <SFML/Graphics.hpp>
#include "../../TextEditor.h"
#include "Command.h"

class MoveCursorCommand : public Command 
{
    private:
        TextEditor    &textEditor;
        CameraManager &camera;
        sf::Vector2i  direction;
        
    public:
        MoveCursorCommand(TextEditor &textEditor, CameraManager &camera, sf::Vector2i direction) 
            : textEditor(textEditor), camera(camera), direction(direction)
        {            
        }

        void Execute() override 
        {
            textEditor.MoveCursor(direction);
            if ((direction.x >  1 || direction.y >  1) ||
                (direction.x < -1 || direction.y < -1)
            ) 
            {
                camera.CenterAtPosition(textEditor.GetCursorPosition());
                return;
            }            
            camera.Follow(textEditor.GetCursorPosition());
        }

};