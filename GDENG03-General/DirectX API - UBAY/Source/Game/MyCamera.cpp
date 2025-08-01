#include "Game/MyCamera.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyCamera::MyCamera() : transform(std::make_shared<MyTransform>()), deltaTime(0) {}
MyCamera::~MyCamera() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyCamera::ClampPitch() {
    float maxPitchInRadians = this->maxPitch * 3.14159265f / 180.0f;
    if (this->transform->rotation.x > maxPitchInRadians)
        this->transform->rotation.x = maxPitchInRadians;
    if (this->transform->rotation.x < -maxPitchInRadians)
        this->transform->rotation.x = -maxPitchInRadians;
}
void MyCamera::Update(float deltaTime) {
    this->deltaTime = deltaTime;
    this->UpdateTransformation();
}
void MyCamera::UpdateTransformation() {
    this->ClampPitch();
    MyMatrix4x4 currentRotation = MyMatrix4x4::GetRotationMatrix(this->transform->rotation);
    this->transform->position +=
        (currentRotation.GetRightVector() * this->moveSpeed * this->deltaTime) * this->movementInput.x +
        (currentRotation.GetUpVector() * this->moveSpeed * this->deltaTime) * this->movementInput.y +
        (currentRotation.GetForwardVector() * this->moveSpeed * this->deltaTime) * this->movementInput.z;
    this->transform->Update(this->deltaTime);
    this->transform->worldMatrix.Invert();
}

void MyCamera::SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
    this->projectionMatrix.SetOrthographicLeftHand(width, height, nearPlane, farPlane);
}

void MyCamera::SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
    this->projectionMatrix.SetPerspectiveLeftHand(fieldOfView, aspectRatio, nearPlane, farPlane);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyCamera::OnKeyDown(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyDown called with keyCode: " << keyCode << std::endl;

    switch (keyCode) {
    case 'W':
    case 'A':
    case 'S':
    case 'D':
    case 'Q':
    case 'E':
    default:
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Unhandled key down: " << keyCode << std::endl;
        break;
    }
}

void MyCamera::OnKeyHold(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyDown called with keyCode: " << keyCode << std::endl;

    switch (keyCode) {
    case 'W':
        this->movementInput.z = 1.0f; // Move camera forward
        break;
    case 'A':
        this->movementInput.x = -1.0f; // Move camera left
        break;
    case 'S':
        this->movementInput.z = -1.0f; // Move camera backward
        break;
    case 'D':
        this->movementInput.x = 1.0f; // Move camera right
        break;
    case 'Q':
        this->movementInput.y = -1.0f; // Move camera down
        break;
    case 'E':
        this->movementInput.y = +1.0f; // Move camera up
        break;
    default:
        break;
    }
}

void MyCamera::OnKeyUp(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyUp called with keyCode: " << keyCode << std::endl;

    switch (keyCode) {
    case 'W':
        this->movementInput.z = 0.0f;
        break;
    case 'A':
        this->movementInput.x = 0.0f;
        break;
    case 'S':
        this->movementInput.z = 0.0f;
        break;
    case 'D':
        this->movementInput.x = 0.0f;
        break;
    case 'Q':
        this->movementInput.y = 0.0f;
        break;
    case 'E':
        this->movementInput.y = 0.0f;
        break;
    default:
        break;
    }
}

void MyCamera::OnMouseMove(const MyVector2& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnMouseMove called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;

    //* Yaw
    this->transform->rotation.x += deltaMousePosition.y * this->sensitivity * this->deltaTime;
    //* Pitch
    this->transform->rotation.y += deltaMousePosition.x * this->sensitivity * this->deltaTime;
}

void MyCamera::OnLMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnLMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnLMBHold(const MyVector2& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnLMBHold called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;
    // //* Yaw
    // this->transform->rotation.x += deltaMousePosition.y * this->sensitivity * this->deltaTime;
}

void MyCamera::OnLMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnLMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnRMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnRMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnRMBHold(const MyVector2& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnRMBHold called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;
    // //* Pitch
    // this->transform->rotation.y += deltaMousePosition.x * this->sensitivity * this->deltaTime;
}

void MyCamera::OnRMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnRMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}
