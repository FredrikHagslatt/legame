#ifndef RENDERDEVTOOLSSYSTEM_H
#define RENDERDEVTOOLSSYSTEM_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>

#include "Events/KeyPressedEvent.h"
#include "LogWindow.h"

class DevTools
{
public:
    static ExampleAppLog log;
    static bool renderHitboxes;
    static bool logToStdCout;
    static bool logToImGuiWindow;
    static bool logToFile;

    static bool showDevTools;
    static bool showDemoWindow;
    static bool showLogWindow;

    static void Render(double elapsedTime);
    static void ToggleShowDevTools(const KeyPressedEvent &event);
    static void ShowDevTools(unsigned int fps);
    static void ShowLogWindow();
};

#endif