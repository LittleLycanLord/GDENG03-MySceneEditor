#include "Core/Input System/MyInputSystem.hpp"
#include "Core/MyLogger.hpp"

DX3D::MyInputSystem* DX3D::MyInputSystem::instance = nullptr;

using namespace DX3D;

MyInputSystem::MyInputSystem() {}
MyInputSystem::~MyInputSystem() {
    MyInputSystem::instance = nullptr;
}

void MyInputSystem::Create() {
    if (MyInputSystem::instance) {
        std::cerr << "[ERROR]: MyInputSystem already created" << std::endl;
        throw std::exception("MyInputSystem already created");
    }
    MyInputSystem::instance = new MyInputSystem();
}
void MyInputSystem::Release() {
    if (MyInputSystem::instance) {
        delete MyInputSystem::instance;
        MyInputSystem::instance = nullptr;
        if (LOG_INFO_INPUT_SYSTEM_MOUSE || LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: MyInputSystem released" << std::endl;
    }
    else {
        throw std::exception("MyGraphicsEngine is already null in MyGraphicsEngine::Release");
    }
}
void MyInputSystem::Update() {
    POINT currentMousePosition = {};
    GetCursorPos(&currentMousePosition);
    ScreenToClient(this->windowHandle, &currentMousePosition);

    if (this->firstFrame) {
        this->oldMousePosition.x = currentMousePosition.x;
        this->oldMousePosition.y = currentMousePosition.y;
        this->firstFrame = false;
    }

    this->newMousePosition.x = currentMousePosition.x;
    this->newMousePosition.y = currentMousePosition.y;

    this->deltaMousePosition = this->rawMouseDelta;

    if (this->rawMouseDelta.x != 0.0f || this->rawMouseDelta.y != 0.0f) {
        for (auto& listenerPair : this->inputListeners) {
            MyInputListener* listener = listenerPair.first;
            if (listener != nullptr) {
                listener->OnMouseMove(this->deltaMousePosition);
            }
        }
        this->rawMouseDelta = MyVector2(0.0f);
    }

    if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: MyInputSystem::Update called" << std::endl;
    if (GetKeyboardState(this->newKeyStates)) {
        for (int key = 0; key < 256; key++) {
            if (this->newKeyStates[key] & 0x80) {
                if (!(this->oldKeyStates[key] & 0x80)) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            if (key == VK_LBUTTON)
                                listener->OnLMBDown(this->newMousePosition);
                            if (key == VK_RBUTTON)
                                listener->OnRMBDown(this->newMousePosition);
                            listener->OnKeyDown(key);
                            if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Key " << key << " pressed in MyInputSystem::Update" << std::endl;
                        }
                    }
                }
                for (auto& listenerPair : this->inputListeners) {
                    MyInputListener* listener = listenerPair.first;
                    if (listener != nullptr) {
                        if (key == VK_LBUTTON)
                            listener->OnLMBHold(this->deltaMousePosition);
                        if (key == VK_RBUTTON)
                            listener->OnRMBHold(this->deltaMousePosition);
                        listener->OnKeyHold(key);
                        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Key " << key << " being held in MyInputSystem::Update" << std::endl;
                    }
                }
            }
            else {
                if (this->oldKeyStates[key] & 0x80) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            if (key == VK_LBUTTON)
                                listener->OnLMBUp(this->newMousePosition);
                            if (key == VK_RBUTTON)
                                listener->OnRMBUp(this->newMousePosition);
                            listener->OnKeyUp(key);
                            if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Key " << key << " released in MyInputSystem::Update" << std::endl;
                        }
                    }
                }
            }
        }
        memcpy(this->oldKeyStates, this->newKeyStates, sizeof(this->newKeyStates));
    }
    else {
        std::cerr << "[ERROR]: Failed to get keyboard state in MyInputSystem::Update" << std::endl;
        throw std::exception("Failed to get keyboard state in MyInputSystem::Update");
        return;
    }

    this->oldMousePosition = this->newMousePosition;

    if (this->lockMouse) {
        int centerX = static_cast<int>(this->windowWidth / 2);
        int centerY = static_cast<int>(this->windowHeight / 2);
        if (this->newMousePosition.x != centerX || this->newMousePosition.y != centerY)
            MyInputSystem::GetInstance()->SetCursorPosition(MyScreenPoint(centerX, centerY));
    }
}
void MyInputSystem::AddListener(MyInputListener* inputListener) {
    if (inputListener == nullptr) {
        std::cerr << "[ERROR]: inputListener is null in MyInputSystem::AddListener" << std::endl;
        throw std::exception("inputListener is null in MyInputSystem::AddListener");
        return;
    }
    auto iterator = this->inputListeners.find(inputListener);
    if (iterator != this->inputListeners.end()) {
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[WARNING] : Listener already exists in MyInputSystem::AddListener" << std::endl;
    }
    else {
        this->inputListeners.insert(std::make_pair<MyInputListener*, MyInputListener*>(std::forward<MyInputListener*>(inputListener), std::forward<MyInputListener*>(inputListener)));
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Listener added successfully in MyInputSystem::AddListener" << std::endl;
    }
}
void MyInputSystem::RemoveListener(MyInputListener* inputListener) {
    if (inputListener == nullptr) {
        std::cerr << "[ERROR]: inputListener is null in MyInputSystem::RemoveListener" << std::endl;
        throw std::exception("inputListener is null in MyInputSystem::RemoveListener");
        return;
    }
    auto iterator = this->inputListeners.find(inputListener);
    if (iterator != this->inputListeners.end()) {
        this->inputListeners.erase(iterator);
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Listener removed successfully in MyInputSystem::RemoveListener" << std::endl;
    }
    else {
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[WARNING] : Listener not found in MyInputSystem::RemoveListener" << std::endl;
    }
}
void MyInputSystem::AddRawMouseDelta(float deltaX, float deltaY) {
    rawMouseDelta += MyVector2(deltaX, deltaY);
}
void MyInputSystem::SetCursorPosition(const MyScreenPoint& position) {
    POINT point = { position.x, position.y };
    ClientToScreen(this->windowHandle, &point);
    SetCursorPos(point.x, point.y);
}
void MyInputSystem::SetCursorVisibility(bool showCursor) {
    ShowCursor(showCursor);
}

