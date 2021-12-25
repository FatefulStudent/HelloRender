#include "Helper/ApplicationHelper.h"
#include "Tests/Test_SimpleTriangle.h"

int main(void) {
    Application* application = new Application();

    BaseTest* test = new Test_SimpleTriangle();
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
