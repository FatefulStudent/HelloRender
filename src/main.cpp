#include "Helper/ApplicationHelper.h"
#include "Lessons/Shaders/Ex_2ShaderPrograms.h"

int main(void) {
    Application* application = new Application();

    BaseExcercise* test = new Ex_2ShaderPrograms();
    test->Initialize();

    while (!application->ShouldCloseWindow()) {
        test->PreTick();
        test->Tick();
        test->PostTick();
        application->Tick();
    }

    test->Finalize();

    delete application;

    return 0;
}
