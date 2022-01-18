#include "../Lessons/Textures/Ex_TexturesAdditionals.h"
#include "Helper/ApplicationHelper.h"

int main(void) {
    Application application;
    Ex_TexturesAdditionals test;
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
