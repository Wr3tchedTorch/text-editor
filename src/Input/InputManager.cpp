#include "InputManager.h"
#include "./commands/Command.h"
#include "MoveCursorCommand.h"

InputManager::InputManager(TextEditor &textEditor, CameraManager &cameraManager)
{
    this->textEditor    = & textEditor;
    this->cameraManager = & cameraManager;

    BindKeyToCommand(sf::Keyboard::Key::Right, new MoveCursorCommand(textEditor, {1, 0}));
}

InputManager::~InputManager()
{
    for (auto keyBind : keyBindings)
    {
        delete keyBind.second;
    }
}

void InputManager::BindKeyToCommand(sf::Keyboard::Key key, Command *command)
{
    BindKeyToCommand({key}, command);
}

void InputManager::BindKeyToCommand(KeyCombination keyCombination, Command *command)
{
    if (keyBindings.find(keyCombination) != keyBindings.end())
        return;

    keyBindings[keyCombination] = command;
}

void InputManager::ProcessKeyboardInput(sf::Keyboard::Key keyCode)
{
    if (keyBindings.find({keyCode}) == keyBindings.end()) 
    {
        std::cout << "A keybinding for the key: " << keyCode << " does not exist.";
        return;
    }

    bool isCtrlPressed  = sf::Keyboard::Key::LControl ||  sf::Keyboard::Key::RControl;
    bool isShiftPressed = sf::Keyboard::Key::LShift   ||  sf::Keyboard::Key::RShift;
    bool isAltPressed   = sf::Keyboard::Key::LAlt     ||  sf::Keyboard::Key::RAlt;

    KeyCombination finalCombination = 
    {
        keyCode,
        isCtrlPressed,
        isShiftPressed,
        isAltPressed
    };

    if (keyBindings.find(finalCombination) == keyBindings.end()) 
    {
        std::cout << "Key combination not found.";
        return;
    }

    keyBindings[finalCombination]->Execute();
}
