#include "Excercise.h"
#include "Helper/Application.h"

int main(void) {
    Application application;
    std::shared_ptr<BaseExcercise> test = make();
    test->Initialize(application.GetWindow());

    double deltaTime = 0.0f;  // Time between current frame and last frame
    double lastFrame = 0.0f;  // Time of last frame

    while (!application.ShouldCloseWindow()) {
        const double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        std::cout << "fps:" << 1.0f / deltaTime << std::endl;
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
