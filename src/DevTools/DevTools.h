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

    static bool showDevTools;
    static bool showDemoWindow;
    static bool showLogWindow;
    static bool renderHitboxes;

    static bool logToStdCout;
    static bool logToImGuiWindow;
    static bool logToFile;

    static void Render();
    static void ToggleShowDevTools(const KeyPressedEvent &event);
    static void ShowDevTools();
    static void ShowLogWindow();
};

#endif