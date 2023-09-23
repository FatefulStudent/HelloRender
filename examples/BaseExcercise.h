#ifndef BASE_EXCERCISE_H
#define BASE_EXCERCISE_H

#include <memory>

class GLFWwindow;

class BaseExcercise {
public:
    BaseExcercise() {}
    virtual void Initialize(GLFWwindow* InWindow);

    virtual void ProcessInput(double DeltaTime){}
    virtual void PreTick(double DeltaTime);
    virtual void Tick(double DeltaTime) {}
    virtual void PostTick(double DeltaTime);

    virtual void Finalize() {}

    virtual ~BaseExcercise() {}

protected:
    GLFWwindow* Window = nullptr;
};
#endif
