#include "Excercise.h"
#include "Helper/Application.h"

int main(void) {
    Application application;
    std::shared_ptr<BaseExcercise> test = make();
    test->Initialize(application.GetWindow());

    float deltaTime = 0.0f;  // Time between current frame and last frame
    float lastFrame = 0.0f;  // Time of last frame

    while (!application.ShouldCloseWindow()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        std::cout << 1.0f / deltaTime << std::endl;
        lastFrame = currentFrame;

        test->ProcessInput(deltaTime);
        test->PreTick(deltaTime);
        test->Tick(deltaTime);
        test->PostTick(deltaTime);
        application.Tick(deltaTime);
    }

    test->Finalize();
    return 0;
}
