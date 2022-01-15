#ifndef BASE_EXCERCISE_H
#define BASE_EXCERCISE_H

#include <memory>

class GLFWwindow;

class BaseExcercise {
public:
    BaseExcercise() {}
    virtual void Initialize(GLFWwindow* window);

    virtual void PreTick();
    virtual void Tick() {}
    virtual void PostTick();

    virtual void Finalize() {}

    virtual ~BaseExcercise() {}

protected:
    GLFWwindow* m_window;
};
#endif
