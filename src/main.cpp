#include "../Lessons/Shaders/Ex_Additionals.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application* application = new Application();

    BaseExcercise* test = new Ex_Additionals();
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
