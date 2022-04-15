#ifndef BASE_EXCERCISE_H
#define BASE_EXCERCISE_H

#include <memory>

class GLFWwindow;

class BaseExcercise {
public:
    BaseExcercise() {}
    virtual void Initialize(GLFWwindow* window);

    virtual void ProcessInput(float deltaTime){};
    virtual void PreTick(float deltaTime);
    virtual void Tick(float deltaTime) {}
    virtual void PostTick(float deltaTime);

    virtual void Finalize() {}

    virtual ~BaseExcercise() {}

protected:
    GLFWwindow* m_window = nullptr;
};
#endif
