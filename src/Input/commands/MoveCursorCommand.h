#include <SFML/Graphics.hpp>
#include "../TextEditor.h"
#include "Command.h"

class MoveCursorCommand : public Command 
{
    private:
        TextEditor   &textEditor;
        sf::Vector2i direction;

    public:
        MoveCursorCommand(TextEditor &textEditor, sf::Vector2i direction) 
            : textEditor(textEditor), direction(direction) 
        {
        }

        void Execute() override 
        {
            textEditor.MoveCursor(direction);
        }

};