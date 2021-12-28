#include "../Lessons/Textures/Ex_Textures.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application application;
    Ex_Textures test;
    test.Initialize();

    while (!application.ShouldCloseWindow()) {
        test.PreTick();
        test.Tick();
        test.PostTick();
        application.Tick();
    }

    test.Finalize();
    return 0;
}
