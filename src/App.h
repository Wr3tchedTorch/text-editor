#pragma once
#include <SFML/Graphics.hpp>
#include "CameraManager.h"
#include "TextEditor.h"

class App
{
public:
    static void SetEditorText(std::vector<std::string> toText, TextEditor &textEditor, CameraManager &cameraManager);

    static void CameraFollow(sf::Vector2f position, CameraManager &camera);
};