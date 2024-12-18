#pragma once
#include <SFML/Graphics.hpp>
#include "TextEditor.h"
#include "CameraManager.h"

class App
{
public:
    static void SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager);

    static void HandleKeyboardInput(TextEditor &textEditor, sf::Keyboard::Key keyCode);
    static void HandleKeyCombinations(TextEditor &textEditor, sf::Keyboard::Key keyCode);
};