#include "Core/MyLogger.hpp"
#include "imgui.h"

using namespace DX3D;

//* ╔════════════╗
//* ║ Attributes ║
//* ╚════════════╝
MyLogger* MyLogger::instance = nullptr;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
// Private constructor
MyLogger::MyLogger() : fileLoggingEnabled(false), consoleLoggingEnabled(true) {
}

MyLogger::~MyLogger() {
    Shutdown();
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyLogger::Create() {
    if (!instance) {
        instance = new MyLogger();
    }
}

void MyLogger::Release() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

MyLogger* MyLogger::GetInstance() {
    return instance;
}

void MyLogger::Initialize(const std::string& filename, bool enableFile, bool enableConsole) {
    fileLoggingEnabled = enableFile;
    consoleLoggingEnabled = enableConsole;

    if (fileLoggingEnabled) {
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "[ERROR]: Failed to open log file: " << filename << std::endl;
            fileLoggingEnabled = false;
        }
    }

    // Log initialization messages after everything is set up
    if (fileLoggingEnabled) {
        LogInfo("LOGGER", "Logging system initialized - File: " + filename);
    }

    if (consoleLoggingEnabled) {
        LogInfo("LOGGER", "Console logging enabled");
    }
}

void MyLogger::Shutdown() {
    if (fileLoggingEnabled && logFile.is_open()) {
        LogInfo("LOGGER", "Shutting down logging system");
        logFile.close();
    }
}

void MyLogger::Log(LogLevel level, const std::string& category, const std::string& message) {
    std::string timestamp = GetTimestamp();
    std::string levelStr = LogLevelToString(level);

    std::stringstream ss;
    ss << "[" << timestamp << "] [" << levelStr << "] [" << category << "] " << message;

    WriteLog(ss.str());
}

void MyLogger::LogInfo(const std::string& category, const std::string& message) {
    Log(LogLevel::INFO_LOG, category, message);
}

void MyLogger::LogWarning(const std::string& category, const std::string& message) {
    Log(LogLevel::WARNING_LOG, category, message);
}

void MyLogger::LogError(const std::string& category, const std::string& message) {
    Log(LogLevel::ERROR_LOG, category, message);
}

void MyLogger::LogDebug(const std::string& category, const std::string& message) {
    Log(LogLevel::DEBUG_LOG, category, message);
}

void MyLogger::LogPerformance(const std::string& category, const std::string& message) {
    Log(LogLevel::PERFORMANCE_LOG, category, message);
}

void MyLogger::RenderImGuiLoggingControls() {
    if (ImGui::CollapsingHeader("Logging Controls")) {
        // General
        if (ImGui::TreeNode("General")) {
            ImGui::Checkbox("Warnings", &this->logWarningGeneral);
            ImGui::Checkbox("Errors", &this->logErrorGeneral);
            ImGui::TreePop();
        }

        // Engine Systems
        if (ImGui::TreeNode("Engine Systems")) {
            ImGui::Checkbox("Window", &this->logInfoWindow);
            ImGui::Checkbox("Window Updates", &this->logInfoWindowUpdate);
            ImGui::Checkbox("Camera", &this->logInfoCamera);
            ImGui::Checkbox("Graphics Engine", &this->logInfoGraphicsEngine);
            ImGui::Checkbox("Render System", &this->logInfoRenderSystem);
            ImGui::Checkbox("Swap Chain", &this->logInfoSwapChain);
            ImGui::Checkbox("Device Context", &this->logInfoDeviceContext);
            ImGui::TreePop();
        }

        // Buffers
        if (ImGui::TreeNode("Buffers")) {
            ImGui::Checkbox("Vertex Buffer", &this->logInfoVertexBuffer);
            ImGui::Checkbox("Constant Buffer", &this->logInfoConstantBuffer);
            ImGui::Checkbox("Index Buffer", &this->logInfoIndexBuffer);
            ImGui::TreePop();
        }

        // Shaders
        if (ImGui::TreeNode("Shaders")) {
            ImGui::Checkbox("Hull Shader", &this->logInfoHullShader);
            ImGui::Checkbox("Domain Shader", &this->logInfoDomainShader);
            ImGui::Checkbox("Vertex Shader", &this->logInfoVertexShader);
            ImGui::Checkbox("Pixel Shader", &this->logInfoPixelShader);
            ImGui::TreePop();
        }

        // Input System
        if (ImGui::TreeNode("Input System")) {
            ImGui::Checkbox("Keyboard", &this->logInfoInputSystemKeyboard);
            ImGui::Checkbox("Mouse", &this->logInfoInputSystemMouse);
            ImGui::TreePop();
        }

        // Resource System
        if (ImGui::TreeNode("Resource System")) {
            ImGui::Checkbox("Resource System", &this->logInfoResourceSystem);
            ImGui::Checkbox("Resource", &this->logInfoResource);
            ImGui::Checkbox("Texture Manager", &this->logInfoTextureManager);
            ImGui::Checkbox("Texture", &this->logInfoTexture);
            ImGui::Checkbox("Mesh Manager", &this->logInfoMeshManager);
            ImGui::Checkbox("Mesh", &this->logInfoMesh);
            ImGui::TreePop();
        }

        // Lighting System
        if (ImGui::TreeNode("Lighting")) {
            ImGui::Checkbox("Lighting System", &this->logInfoLighting);
            ImGui::TreePop();
        }

        // Quick actions
        ImGui::Separator();
        if (ImGui::Button("Enable All")) {
            this->logWarningGeneral = this->logErrorGeneral = true;
            this->logInfoWindow = this->logInfoWindowUpdate = this->logInfoCamera = true;
            this->logInfoGraphicsEngine = this->logInfoRenderSystem = this->logInfoSwapChain = true;
            this->logInfoDeviceContext = this->logInfoVertexBuffer = this->logInfoConstantBuffer = true;
            this->logInfoIndexBuffer = this->logInfoHullShader = this->logInfoDomainShader = true;
            this->logInfoVertexShader = this->logInfoPixelShader = true;
            this->logInfoInputSystemKeyboard = this->logInfoInputSystemMouse = true;
            this->logInfoResourceSystem = this->logInfoResource = this->logInfoTextureManager = true;
            this->logInfoTexture = this->logInfoMeshManager = this->logInfoMesh = true;
            this->logInfoLighting = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Disable All")) {
            this->logWarningGeneral = this->logErrorGeneral = true; // Keep warnings and errors
            this->logInfoWindow = this->logInfoWindowUpdate = this->logInfoCamera = false;
            this->logInfoGraphicsEngine = this->logInfoRenderSystem = this->logInfoSwapChain = false;
            this->logInfoDeviceContext = this->logInfoVertexBuffer = this->logInfoConstantBuffer = false;
            this->logInfoIndexBuffer = this->logInfoHullShader = this->logInfoDomainShader = false;
            this->logInfoVertexShader = this->logInfoPixelShader = false;
            this->logInfoInputSystemKeyboard = this->logInfoInputSystemMouse = false;
            this->logInfoResourceSystem = this->logInfoResource = this->logInfoTextureManager = false;
            this->logInfoTexture = this->logInfoMeshManager = this->logInfoMesh = false;
            this->logInfoLighting = false;
        }
    }
}

//* ╔═════════════════════════════════════╗
//* ║ PerformanceTimer Nested Class Impl ║
//* ╚═════════════════════════════════════╝
MyLogger::PerformanceTimer::PerformanceTimer(const std::string& cat, const std::string& op)
    : category(cat), operation(op) {
    startTime = std::chrono::high_resolution_clock::now();
}

MyLogger::PerformanceTimer::~PerformanceTimer() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    std::stringstream ss;
    ss << operation << " completed in " << duration.count() << " microseconds";

    if (MyLogger::GetInstance()) {
        MyLogger::GetInstance()->LogPerformance(category, ss.str());
    }
}

//* ╔══════════════════════╗
//* ║ Utility / Helpers    ║
//* ╚══════════════════════╝
std::string MyLogger::GetTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    // Use localtime_s for thread safety (Windows-specific)
    std::tm timeinfo = {};
    localtime_s(&timeinfo, &time_t);

    std::stringstream ss;
    ss << std::put_time(&timeinfo, "%H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}

std::string MyLogger::LogLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::INFO_LOG: return "INFO";
    case LogLevel::WARNING_LOG: return "WARN";
    case LogLevel::ERROR_LOG: return "ERROR";
    case LogLevel::DEBUG_LOG: return "DEBUG";
    case LogLevel::PERFORMANCE_LOG: return "PERF";
    default: return "UNKNOWN";
    }
}

void MyLogger::WriteLog(const std::string& formattedMessage) {
    if (consoleLoggingEnabled) {
        std::cout << formattedMessage << std::endl;
    }

    if (fileLoggingEnabled && logFile.is_open()) {
        logFile << formattedMessage << std::endl;
        logFile.flush(); // Ensure immediate write for debugging
    }
}
