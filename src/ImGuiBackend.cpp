#include "ImGuiBackend.h"
#include "core/Window.h"
#include "core/Log.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Surpass::Tools {
	RendererBackend ImGuiBackend::s_Backend = RendererBackend::None;

	void ImGuiBackend::init(Window& window, const ImGuiBackendConfig& config)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = config.initPath;

		ImGui_ImplGlfw_InitForOpenGL(window.getNativeHanble(), config.installCallback);

		s_Backend = config.backend;
		switch (s_Backend)
		{
		case RendererBackend::OpenGL:
			ImGui_ImplOpenGL3_Init("#version 330");
			break;
		default:
			Log::error("Unsupported ImGui renderer backend");
			break;
		}
	}

	void ImGuiBackend::shutdown()
	{
		if (s_Backend == RendererBackend::OpenGL)
			ImGui_ImplOpenGL3_Shutdown();

		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		s_Backend = RendererBackend::None;
	}

	void ImGuiBackend::beginFrame()
	{
		switch (s_Backend)
		{
		case RendererBackend::OpenGL:
			ImGui_ImplOpenGL3_NewFrame();
			break;
		default:
			Log::error("Unsupported ImGui renderer backend");
			break;
		}

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiBackend::endFrame(Window& window)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Render();

		switch (s_Backend)
		{
		case RendererBackend::OpenGL:
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			break;
		default:
			Log::error("Unsupported ImGui renderer backend");
			break;
		}
	}
}