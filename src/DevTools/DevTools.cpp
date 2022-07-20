#include "DevTools.h"
#include "LogWindow.h"
#include "Logger/Logger.h"

bool DevTools::showDevTools = false;
bool DevTools::showDemoWindow = false;
bool DevTools::showLogWindow = false;
bool DevTools::renderHitboxes = false;
ExampleAppLog DevTools::log;

bool DevTools::logToStdCout = true;
bool DevTools::logToImGuiWindow = true;
bool DevTools::logToFile = false;

void DevTools::Render()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ShowDevTools();

    if (showDemoWindow)
    {
        ImGui::ShowDemoWindow();
    }

    if (showLogWindow)
    {
        ShowLogWindow();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

    // Create a vector with both Sprite and Transform component of all entities
}

void DevTools::ToggleShowDevTools(const KeyPressedEvent &event)
{
    if (event.keycode == 167) // Tilde
    {
        showDevTools = !showDevTools;
    }
}

void DevTools::ShowDevTools()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (ImGui::Begin("Dev Tools", NULL, window_flags))
    {
        ImGui::Checkbox("Show ImGui Demo Window", &showDemoWindow);
        ImGui::Checkbox("Render Hitboxes", &renderHitboxes);

        if (ImGui::CollapsingHeader("Logger Settings"))
        {
            ImGui::Checkbox("Show log window", &showLogWindow);
            ImGui::Checkbox("Log to std::cout", &logToStdCout);
            ImGui::Checkbox("Log to ImGui Log Window", &logToImGuiWindow);
            ImGui::Checkbox("Log to file", &logToFile);
        }

        ImGui::End();
    }
}

void DevTools::ShowLogWindow()
{
    log.Draw("Log Window");
}
