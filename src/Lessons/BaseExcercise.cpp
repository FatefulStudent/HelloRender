#include "BaseExcercise.h"

#include <GL/glew.h>

void BaseExcercise::Initialize() {
    glClearColor(0.f, 0.f, 0.0f, 1.0f);
}

void BaseExcercise::PreTick() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT);
}

void BaseExcercise::PostTick() {
    glBindVertexArray(0);
}
