#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace DX3D {
    enum class LogLevel {
        INFO_LOG,
        WARNING_LOG,
        ERROR_LOG,
        DEBUG_LOG,
        PERFORMANCE_LOG
    };

    class MyLogger {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyLogger* instance;
        std::ofstream logFile;
        bool fileLoggingEnabled;
        bool consoleLoggingEnabled;

        //* ╔═══════════════╗
        //* ║ Logging Flags ║
        //* ╚═══════════════╝
        // General
        bool logWarningGeneral = true;
        bool logErrorGeneral = true;

        // Engine systems
        bool logInfoWindow = false;
        bool logInfoWindowUpdate = false;
        bool logInfoCamera = false;
        bool logInfoGraphicsEngine = false;
        bool logInfoRenderSystem = false;
        bool logInfoSwapChain = false;
        bool logInfoDeviceContext = false;
        bool logInfoVertexBuffer = false;
        bool logInfoConstantBuffer = false;
        bool logInfoIndexBuffer = false;

        // Shaders
        bool logInfoHullShader = false;
        bool logInfoDomainShader = false;
        bool logInfoVertexShader = false;
        bool logInfoPixelShader = false;

        // Input system
        bool logInfoInputSystemKeyboard = false;
        bool logInfoInputSystemMouse = false;

        // Resource system
        bool logInfoResourceSystem = false;
        bool logInfoResource = false;
        bool logInfoTextureManager = false;
        bool logInfoTexture = false;
        bool logInfoMeshManager = false;
        bool logInfoMeshRenderingSystem = false;
        bool logInfoMesh = false;

        // Lighting system
        bool logInfoLighting = false;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    private:
        // Private constructor for singleton
        MyLogger();

    public:
        // Destructor
        ~MyLogger();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Singleton management
        static void Create();
        static void Release();
        static MyLogger* GetInstance();

        void Initialize(const std::string& filename = "engine.log", bool enableFile = true, bool enableConsole = true);
        void Shutdown();

        void Log(LogLevel level, const std::string& category, const std::string& message);
        void LogInfo(const std::string& category, const std::string& message);
        void LogWarning(const std::string& category, const std::string& message);
        void LogError(const std::string& category, const std::string& message);
        void LogDebug(const std::string& category, const std::string& message);
        void LogPerformance(const std::string& category, const std::string& message);

        // ImGui logging controls
        void RenderImGuiLoggingControls();

        // Static helper functions for easy access to logging flags
        static bool ShouldLogWarningGeneral() { return GetInstance() ? GetInstance()->logWarningGeneral : true; }
        static bool ShouldLogErrorGeneral() { return GetInstance() ? GetInstance()->logErrorGeneral : true; }
        static bool ShouldLogWindow() { return GetInstance() ? GetInstance()->logInfoWindow : false; }
        static bool ShouldLogWindowUpdate() { return GetInstance() ? GetInstance()->logInfoWindowUpdate : false; }
        static bool ShouldLogCamera() { return GetInstance() ? GetInstance()->logInfoCamera : false; }
        static bool ShouldLogGraphicsEngine() { return GetInstance() ? GetInstance()->logInfoGraphicsEngine : false; }
        static bool ShouldLogRenderSystem() { return GetInstance() ? GetInstance()->logInfoRenderSystem : false; }
        static bool ShouldLogSwapChain() { return GetInstance() ? GetInstance()->logInfoSwapChain : false; }
        static bool ShouldLogDeviceContext() { return GetInstance() ? GetInstance()->logInfoDeviceContext : false; }
        static bool ShouldLogVertexBuffer() { return GetInstance() ? GetInstance()->logInfoVertexBuffer : false; }
        static bool ShouldLogConstantBuffer() { return GetInstance() ? GetInstance()->logInfoConstantBuffer : false; }
        static bool ShouldLogIndexBuffer() { return GetInstance() ? GetInstance()->logInfoIndexBuffer : false; }
        static bool ShouldLogVertexShader() { return GetInstance() ? GetInstance()->logInfoVertexShader : false; }
        static bool ShouldLogPixelShader() { return GetInstance() ? GetInstance()->logInfoPixelShader : false; }
        static bool ShouldLogHullShader() { return GetInstance() ? GetInstance()->logInfoHullShader : false; }
        static bool ShouldLogDomainShader() { return GetInstance() ? GetInstance()->logInfoDomainShader : false; }
        static bool ShouldLogInputKeyboard() { return GetInstance() ? GetInstance()->logInfoInputSystemKeyboard : false; }
        static bool ShouldLogInputMouse() { return GetInstance() ? GetInstance()->logInfoInputSystemMouse : false; }
        static bool ShouldLogResourceSystem() { return GetInstance() ? GetInstance()->logInfoResourceSystem : false; }
        static bool ShouldLogResource() { return GetInstance() ? GetInstance()->logInfoResource : false; }
        static bool ShouldLogTextureManager() { return GetInstance() ? GetInstance()->logInfoTextureManager : false; }
        static bool ShouldLogTexture() { return GetInstance() ? GetInstance()->logInfoTexture : false; }
        static bool ShouldLogMeshManager() { return GetInstance() ? GetInstance()->logInfoMeshManager : false; }
        static bool ShouldLogMesh() { return GetInstance() ? GetInstance()->logInfoMesh : false; }
        static bool ShouldLogMeshRenderingSystem() { return GetInstance() ? GetInstance()->logInfoMeshRenderingSystem : false; }
        static bool ShouldLogLighting() { return GetInstance() ? GetInstance()->logInfoLighting : false; }

    private:
        std::string GetTimestamp();
        std::string LogLevelToString(LogLevel level);
        void WriteLog(const std::string& formattedMessage);

        //* ╔═════════════════╗
        //* ║ Nested Classes  ║
        //* ╚═════════════════╝
    public:
        // Performance timing helper
        class PerformanceTimer {
            //* ╔════════════╗
            //* ║ Attributes ║
            //* ╚════════════╝
        private:
            std::chrono::high_resolution_clock::time_point startTime;
            std::string category;
            std::string operation;

            //* ╔════════════════════════════╗
            //* ║ Constructors & Destructors ║
            //* ╚════════════════════════════╝
        public:
            PerformanceTimer(const std::string& cat, const std::string& op);
            ~PerformanceTimer();
        };
    };

    // Convenience macros using singleton
#define LOG_INFO(category, message) if(DX3D::MyLogger::GetInstance()) DX3D::MyLogger::GetInstance()->LogInfo(category, message)
#define LOG_WARNING(category, message) if(DX3D::MyLogger::GetInstance()) DX3D::MyLogger::GetInstance()->LogWarning(category, message)
#define LOG_ERROR(category, message) if(DX3D::MyLogger::GetInstance()) DX3D::MyLogger::GetInstance()->LogError(category, message)
#define LOG_DEBUG(category, message) if(DX3D::MyLogger::GetInstance()) DX3D::MyLogger::GetInstance()->LogDebug(category, message)
#define LOG_PERFORMANCE(category, message) if(DX3D::MyLogger::GetInstance()) DX3D::MyLogger::GetInstance()->LogPerformance(category, message)
#define PERFORMANCE_TIMER(category, operation) DX3D::MyLogger::PerformanceTimer timer(category, operation)

    // Logging toggle macros
#define LOG_WARNING_GENERAL DX3D::MyLogger::ShouldLogWarningGeneral()
#define LOG_ERROR_GENERAL DX3D::MyLogger::ShouldLogErrorGeneral()
#define LOG_INFO_WINDOW DX3D::MyLogger::ShouldLogWindow()
#define LOG_INFO_WINDOW_UPDATE DX3D::MyLogger::ShouldLogWindowUpdate()
#define LOG_INFO_CAMERA DX3D::MyLogger::ShouldLogCamera()
#define LOG_INFO_GRAPHICS_ENGINE DX3D::MyLogger::ShouldLogGraphicsEngine()
#define LOG_INFO_RENDER_SYSTEM DX3D::MyLogger::ShouldLogRenderSystem()
#define LOG_INFO_SWAP_CHAIN DX3D::MyLogger::ShouldLogSwapChain()
#define LOG_INFO_DEVICE_CONTEXT DX3D::MyLogger::ShouldLogDeviceContext()
#define LOG_INFO_VERTEX_BUFFER DX3D::MyLogger::ShouldLogVertexBuffer()
#define LOG_INFO_CONSTANT_BUFFER DX3D::MyLogger::ShouldLogConstantBuffer()
#define LOG_INFO_INDEX_BUFFER DX3D::MyLogger::ShouldLogIndexBuffer()
#define LOG_INFO_VERTEX_SHADER DX3D::MyLogger::ShouldLogVertexShader()
#define LOG_INFO_PIXEL_SHADER DX3D::MyLogger::ShouldLogPixelShader()
#define LOG_INFO_HULL_SHADER DX3D::MyLogger::ShouldLogHullShader()
#define LOG_INFO_DOMAIN_SHADER DX3D::MyLogger::ShouldLogDomainShader()
#define LOG_INFO_INPUT_SYSTEM_KEYBOARD DX3D::MyLogger::ShouldLogInputKeyboard()
#define LOG_INFO_INPUT_SYSTEM_MOUSE DX3D::MyLogger::ShouldLogInputMouse()
#define LOG_INFO_RESOURCE_SYSTEM DX3D::MyLogger::ShouldLogResourceSystem()
#define LOG_INFO_RESOURCE DX3D::MyLogger::ShouldLogResource()
#define LOG_INFO_TEXTURE_MANAGER DX3D::MyLogger::ShouldLogTextureManager()
#define LOG_INFO_TEXTURE DX3D::MyLogger::ShouldLogTexture()
#define LOG_INFO_MESH_MANAGER DX3D::MyLogger::ShouldLogMeshManager()
#define LOG_INFO_MESH_SYSTEM DX3D::MyLogger::ShouldLogMeshRenderingSystem()
#define LOG_INFO_MESH DX3D::MyLogger::ShouldLogMesh()
#define LOG_INFO_LIGHTING DX3D::MyLogger::ShouldLogLighting()
} // namespace DX3D
