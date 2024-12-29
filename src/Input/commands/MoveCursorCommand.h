#pragma once

#include <SFML/Graphics.hpp>
#include "../../TextEditor.h"
#include "Command.h"

class MoveCursorCommand : public Command 
{
    private:
        TextEditor    &textEditor;
        CameraManager *camera;
        sf::Vector2i  direction;
        
    public:
        MoveCursorCommand(TextEditor &textEditor, CameraManager &camera, sf::Vector2i direction) 
            : textEditor(textEditor), camera(&camera), direction(direction)
        {            
        }

        MoveCursorCommand(TextEditor &textEditor, sf::Vector2i direction) 
            : textEditor(textEditor), camera(nullptr), direction(direction)
        {            
        }

        void Execute() override 
        {
            textEditor.MoveCursor(direction);
            if (camera)
            {
                camera->CenterAtPosition(textEditor.GetCursorPosition());
            }
        }

};