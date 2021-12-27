#include "../Lessons/Textures/Ex_Textures.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application* application = new Application();

    BaseExcercise* test = new Ex_Textures();
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
