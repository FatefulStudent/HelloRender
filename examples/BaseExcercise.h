#ifndef BASE_EXCERCISE_H
#define BASE_EXCERCISE_H

#include <memory>

class GLFWwindow;

class BaseExcercise {
public:
    BaseExcercise() {}
    virtual void Initialize(GLFWwindow* InWindow);

    virtual void ProcessInput(float DeltaTime){};
    virtual void PreTick(float DeltaTime);
    virtual void Tick(float DeltaTime) {}
    virtual void PostTick(float DeltaTime);

    virtual void Finalize() {}

    virtual ~BaseExcercise() {}

protected:
    GLFWwindow* Window = nullptr;
};
#endif
