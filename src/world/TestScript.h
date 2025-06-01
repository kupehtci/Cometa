#ifndef COMETA_TEST_SCRIPT_H
#define COMETA_TEST_SCRIPT_H

#include <iostream>
#include "world/BaseScript.h"


class TestScript final : public BaseScript {
  private:
    std::string _text = "";

  public:
    TestScript() = default;
    explicit TestScript(const std::string& text) {_text = text;}
    TestScript(const TestScript&) = default;

    ~TestScript() override = default;

    void OnInit() override {
      std::cout << "OnInit" << _text << std::endl;
    }

    void OnUpdate(float deltaTime) override{
      // std::cout << "OnUpdate" << _text << std::endl;
    }
    void OnClose() override{
        std::cout << "OnClose" << _text << std::endl;
    }
    void OnCollisionEnter(Entity* other, Collision* collision) override{
      std::cout << "[TEST SCRIPT] OnCollisionEnter [TEST SCRIPT] [TEST SCRIPT] [TEST SCRIPT] " << std::endl;
    }
    void OnCollisionExit(Entity* other, Collision* collision) override{
      std::cout << " [TEST SCRIPT] OnCollisionExit [TEST SCRIPT] [TEST SCRIPT] [TEST SCRIPT] " << std::endl;
    }
};

#endif //COMETA_TEST_SCRIPT_H
