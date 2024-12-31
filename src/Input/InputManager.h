#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "KeyCombination.h"
#include "./commands/Command.h"
#include "../CameraManager.h"
#include "../TextEditor.h"

class InputManager
{
private:
    TextEditor    &textEditor;
    CameraManager &cameraManager;

    std::unordered_map<KeyCombination, Command*, KeyCombinationHash> keyBindings;

public:
    InputManager(TextEditor &, CameraManager &);
    ~InputManager();

    void BindKeyToCommand(sf::Keyboard::Key, Command *);
    void BindKeyToCommand(KeyCombination, Command *);

    void ProcessKeyboardInput(sf::Keyboard::Key);
    void ProcessMouseInput();

private:
    bool IsKeyValid(sf::Keyboard::Key);
};