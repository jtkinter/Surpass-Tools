#pragma once
#include "core/RendererBackend.h"

namespace Surpass {
    class Window;
}

namespace Surpass::Tools {
    struct ImGuiBackendConfig
    {
        RendererBackend backend = RendererBackend::OpenGL;
        void* deviceContext = nullptr;
        const char* initPath = "imgui.ini";
        bool installCallback = true;
    };

    class ImGuiBackend
    {
    public:
        static void init(Window& window, const ImGuiBackendConfig& config);
        static void shutdown();
        static void beginFrame();
        static void endFrame(Window& window);

    private:
        static RendererBackend s_Backend;
    };
}