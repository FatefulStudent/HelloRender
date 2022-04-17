#ifndef EX_ARKANOID_H
#define EX_ARKANOID_H

#include "../../examples/BaseExcercise.h"
#include "Excercise.h"

#include <memory>
#include <vector>
#include <string>

class Camera3d;

class Arkanoid : public BaseExcercise {
public:
    Arkanoid(){};
    virtual ~Arkanoid(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick(float deltaTime) override;
    virtual void Finalize() override;

private:
    std::shared_ptr<Camera3d> m_camera;
};


std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Arkanoid>();
}

#endif
