#ifndef COMETA_UILAYER_H
#define COMETA_UILAYER_H

#include "layer_system/Layer.h"

#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <unordered_map>

#include <filesystem>

/**
 * Layer in charge or rendering an UI editor
 * Must be inserted first in the Onion to be rendered on top of the scene
 */
class UILayer : public Layer{

private:
    #pragma region PerformanceGraphs
    static const int HISTORY_SIZE = 30;
    float _fpsHistory[HISTORY_SIZE];
    float _deltaTimeHistory[HISTORY_SIZE];
    int _historyIndex;
    float _plotUpdateTimer = 0.0f;
    #pragma endregion

    #pragma region ImGuiConfiguration
    bool _mainWindowOpen = true;
    bool _sceneHierarchyOpen = true;
    ImVec2 _thumbnailSize = ImVec2(128, 128);
    bool _showImGuiDemo = false;
    #pragma endregion


    bool isOnSimulation = false;

public:
    UILayer();
    ~UILayer() override;

    /**
     * Initialize the theme and other configurations for ImGUI
     */
    void Init() override;

    /**
     * Update and build the ImGUI editor
     */
    void Update() override;

    /**
     * Close the ImGUI rendering context
     */
    void Close() override;

    /**
     * Handle events by subscription to the Event Bus and capture events for ImGUI.
     * @param event
     */
    void HandleEvent(Event& event) override;

    /**
     * Generate the main hierarchy panel that shows the entities in the scene and theirs components
     */
    void BuildSceneHierarchyPanel();

};



#endif //UILAYER_H
