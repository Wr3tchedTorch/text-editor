#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "KeyCombination.h"
#include "CameraManager.h"
#include "TextEditor.h"

class InputManager
{
private:
    TextEditor    * textEditor;
    CameraManager * cameraManager;

    // std::unordered_map<KeyCombination, Command *, KeyCombinationHash> keyBindings;

public:
    InputManager(TextEditor & textEditor, CameraManager & cameraManager);
    ~InputManager();

    void ProcessKeyboardInput(sf::Keyboard::Key keyCode);
    void ProcessKeyCombination(sf::Keyboard::Key keyCode);
};