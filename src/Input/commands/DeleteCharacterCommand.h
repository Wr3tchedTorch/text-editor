#pragma once

#include "Command.h"
#include "../../TextEditor.h"

class DeleteCharacterCommand : public Command
{
    private:
        TextEditor &textEditor;

    public:
        DeleteCharacterCommand(TextEditor &textEditor) 
            : textEditor(textEditor)
        {
        }

        void Execute() override 
        {
            textEditor.DeleteCharacterAtCursorPosition();
        }

};