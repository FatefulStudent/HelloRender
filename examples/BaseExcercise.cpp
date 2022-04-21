#include "BaseExcercise.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void BaseExcercise::Initialize(GLFWwindow* InWindow) {
    Window = InWindow;
    glClearColor(0.f, 0.f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void BaseExcercise::PreTick(float DeltaTime) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BaseExcercise::PostTick(float DeltaTime) {
    glBindVertexArray(0);
}
