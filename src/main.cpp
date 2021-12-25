#include "Helper/ApplicationHelper.h"
#include "Tests/Test_2ShaderPrograms.h"

int main(void) {
    Application* application = new Application();

    BaseTest* test = new Test_2ShaderPrograms();
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
