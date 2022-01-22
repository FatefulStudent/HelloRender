#include "Excercise.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application application;
    std::shared_ptr<BaseExcercise> test = make();
    test->Initialize(application.GetWindow());

    while (!application.ShouldCloseWindow()) {
        test->PreTick();
        test->Tick();
        test->PostTick();
        application.Tick();
    }

    test->Finalize();
    return 0;
}
