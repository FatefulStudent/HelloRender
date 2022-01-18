#include "../Lessons/Transforms/Ex_Transforms.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application application;
    Ex_Transforms test;
    test.Initialize(application.GetWindow());

    while (!application.ShouldCloseWindow()) {
        test.PreTick();
        test.Tick();
        test.PostTick();
        application.Tick();
    }

    test.Finalize();
    return 0;
}
