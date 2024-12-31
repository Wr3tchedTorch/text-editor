#include "InputManager.h"
#include "./commands/Command.h"
#include "./commands/MoveCursorCommand.h"
#include "./commands/DeleteCharacterCommand.h"
#include "./commands/CreateNewLineCommand.h"
#include "./commands/SelectCellCommand.h"

InputManager::InputManager(TextEditor &textEditor, CameraManager &cameraManager)
    : textEditor(textEditor), cameraManager(cameraManager)
{
    BindKeyToCommand(sf::Keyboard::Key::Right, new MoveCursorCommand(textEditor, cameraManager, { 1,  0 }));
    BindKeyToCommand(sf::Keyboard::Key::Left,  new MoveCursorCommand(textEditor, cameraManager, {-1,  0 }));
    BindKeyToCommand(sf::Keyboard::Key::Down,  new MoveCursorCommand(textEditor, cameraManager, { 0,  1 }));
    BindKeyToCommand(sf::Keyboard::Key::Up,    new MoveCursorCommand(textEditor, cameraManager, { 0, -1 }));
    
    BindKeyToCommand(sf::Keyboard::Key::End,  new MoveCursorCommand(textEditor, cameraManager, { 999, 0 }));
    BindKeyToCommand(sf::Keyboard::Key::Home, new MoveCursorCommand(textEditor, cameraManager, {-999, 0 }));

    BindKeyToCommand({sf::Keyboard::Key::End,  true},  new MoveCursorCommand(textEditor, cameraManager, { 999, 999 }));
    BindKeyToCommand({sf::Keyboard::Key::Home, true},  new MoveCursorCommand(textEditor, cameraManager, {-999,-999 }));

    BindKeyToCommand({sf::Keyboard::Key::BackSpace}, new DeleteCharacterCommand(textEditor));
    BindKeyToCommand({sf::Keyboard::Key::Enter},     new CreateNewLineCommand(textEditor));
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
    KeyCombination combination = {key};
    BindKeyToCommand(combination, command);
}

void InputManager::BindKeyToCommand(KeyCombination keyCombination, Command *command)
{
    bool error = !command || keyBindings.find(keyCombination) != keyBindings.end();

    if (error) 
    {
        std::cout << "InputManager.cpp: Error. Command must be a valid pointer and the key combination must be unique." << std::endl;
        return;
    }    

    keyBindings[keyCombination] = command;
}

void InputManager::ProcessKeyboardInput(sf::Keyboard::Key key)
{
    if (!IsKeyValid(key)) 
    {
        return;
    }

    bool isCtrlPressed  = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || 
                          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

    bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)   || 
                          sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

    bool isAltPressed   = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)     || 
                          sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

    KeyCombination finalCombination = 
    {
        key,
        isCtrlPressed,
        isShiftPressed,
        isAltPressed
    };


    if (keyBindings.find(finalCombination) == keyBindings.end()) 
    {
        std::cout << "InputManager.cpp: Error. Key combination not found: \n\t" << 
                     finalCombination.toString() <<
                     std::endl;
        return;
    }

    keyBindings[finalCombination]->Execute();
}

void InputManager::ProcessMouseInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
    {
        SelectCellCommand command(textEditor);
        command.Execute();
    }
}

bool InputManager::IsKeyValid(sf::Keyboard::Key key)
{
    return (key != sf::Keyboard::Key::LControl && key != sf::Keyboard::Key::RControl) &&
           (key != sf::Keyboard::Key::LShift   && key != sf::Keyboard::Key::RShift)   &&
           (key != sf::Keyboard::Key::LAlt     && key != sf::Keyboard::Key::RAlt);
}
