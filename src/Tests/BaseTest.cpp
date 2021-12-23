#include "BaseTest.h"

#include <GL/glew.h>

void BaseTest::Initialize() {
    glClearColor(0.f, 0.f, 0.0f, 1.0f);
}

void BaseTest::PreTick() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT);
}

void BaseTest::PostTick() {
    glBindVertexArray(0);
}
