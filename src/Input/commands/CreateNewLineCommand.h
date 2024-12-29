#pragma once

#include "../../TextEditor.h"
#include "Command.h"

class CreateNewLineCommand : public Command 
{
    private:
        TextEditor &textEditor;

    public:
        CreateNewLineCommand(TextEditor &textEditor)
            : textEditor(textEditor) 
        {
        }

        void Execute() override 
        {
            textEditor.CreateNewLineAtCursorPosition();
        }
};