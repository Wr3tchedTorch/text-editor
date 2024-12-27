#include "InputManager.h"

InputManager::InputManager(TextEditor &textEditor, CameraManager &cameraManager)
{
    this->textEditor    = & textEditor;
    this->cameraManager = & cameraManager;
}

InputManager::~InputManager()
{

}
