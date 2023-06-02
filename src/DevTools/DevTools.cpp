#include "DevTools.h"
#include "LogWindow.h"
#include "Logger/Logger.h"

#include "Events/EventDispatcher.h"
#include "Events/SceneSwitchEvent.h"

bool DevTools::showEntityExplorer = true;
bool DevTools::showDevTools = false;
bool DevTools::showDemoWindow = false;
bool DevTools::showLogWindow = false;
bool DevTools::renderHitboxes = false;

ExampleAppLog DevTools::log;

bool DevTools::logToStdCout = true;
bool DevTools::logToImGuiWindow = true;
bool DevTools::logToFile = false;

void DevTools::Render(double elapsedTime)
{

    static unsigned int fps = 0;
    static double updateFpsTimer = 0.5;
    updateFpsTimer += elapsedTime;
    if (updateFpsTimer > 0.5)
    {
        fps = static_cast<int>(1.0 / elapsedTime);
        updateFpsTimer = 0.0;
    }

    ShowDevTools(fps);

    if (showDemoWindow)
    {
        ImGui::ShowDemoWindow();
    }

    if (showLogWindow)
    {
        ShowLogWindow();
    }
}

void DevTools::ToggleShowDevTools(const KeyPressedEvent &event)
{
    if (event.keycode == 167) // Tilde
    {
        showDevTools = !showDevTools;
    }
}

void DevTools::ShowDevTools(unsigned int fps)
{
    ImGui::SetNextWindowPos(ImVec2(0, 200), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (ImGui::Begin("Dev Tools", NULL, window_flags))
    {
        ImGui::Text(("Fps: " + std::to_string(fps)).c_str());

        if (ImGui::Button("Open Map Editor"))
        {
            Event::dispatcher.trigger(SceneSwitchEvent{"Game", "MapEditor"});
        }

        if (!DevTools::showEntityExplorer)
        {
            if (ImGui::Button("Open Entity Explorer"))
            {
                DevTools::showEntityExplorer = true;
            }
        }
        else
        {
            if (ImGui::Button("Close Entity Explorer"))
            {
                DevTools::showEntityExplorer = false;
            }
        }

        ImGui::Checkbox("Show ImGui Demo Window", &showDemoWindow);
        ImGui::Checkbox("Render Hitboxes", &renderHitboxes);

        if (ImGui::CollapsingHeader("Logger Settings"))
        {
            ImGui::Checkbox("Show log window", &showLogWindow);
            ImGui::Checkbox("Log to std::cout", &logToStdCout);
            ImGui::Checkbox("Log to ImGui Log Window", &logToImGuiWindow);
            ImGui::Checkbox("Log to file", &logToFile);
        }
    }
    ImGui::End();
}

void DevTools::ShowLogWindow()
{
    log.Draw("Log Window");
}
