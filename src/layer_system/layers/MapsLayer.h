//
// Created by Daniel Laplana Gimeno on 18/4/25.
//

#ifndef MAPSLAYER_H
#define MAPSLAYER_H

#include <iostream>
#include "layer_system/Layer.h"
#include "render/Texture.h"
#include "render/Camera.h"

class MapsLayer : public Layer{

private:
    Texture* _texture = nullptr;
    Texture* _normalMap = nullptr;
    Texture* _diffuseMap = nullptr;

    Camera _camera;

public:
    MapsLayer();
    ~MapsLayer();

public:
    void Init() override;
    void Update() override;
    void Close() override;

    void HandleEvent(Event& event) override;
};



#endif //MAPSLAYER_H
