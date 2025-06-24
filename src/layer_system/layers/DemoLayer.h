
#ifndef COMETA_DEMO_LAYER_H
#define COMETA_DEMO_LAYER_H

#include <iostream>
#include <render/Material.h>

#include "layer_system/Layer.h"
#include "render/Texture.h"
#include "render/Camera.h"

class DemoLayer : public Layer{

private:
    Camera _camera;
    // Material _mat;

public:
    DemoLayer();
    ~DemoLayer() override;

public:
    void Init() override;
    void Update() override;
    void Close() override;

    void HandleEvent(Event& event) override;
};

#endif //COMETA_DEMO_LAYER_H
