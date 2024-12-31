#include "../../TextEditor.h"
#include "Command.h"

class SelectCellCommand : public Command 
{
    private:
        TextEditor &textEditor;
    
    public:
        SelectCellCommand(TextEditor &textEditor)
            : textEditor(textEditor)
        {}

        void Execute() override 
        {
            textEditor.MarkCurrentCursorPositionAsSelected();
        }
};