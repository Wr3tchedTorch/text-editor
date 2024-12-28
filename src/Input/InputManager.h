#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "CameraManager.h"
#include "TextEditor.h"
#include "KeyCombination.h"
#include "./commands/Command.h"

class InputManager
{
private:
    TextEditor    * textEditor;
    CameraManager * cameraManager;

    std::unordered_map<KeyCombination, Command *, KeyCombinationHash> keyBindings;

public:
    InputManager(TextEditor & textEditor, CameraManager & cameraManager);
    ~InputManager();

    void BindKeyToCommand(sf::Keyboard::Key key, Command *command);
    void BindKeyToCommand(KeyCombination keyCombination, Command *command);
    void ProcessKeyboardInput(sf::Keyboard::Key keyCode);
};