#include "Helper/ApplicationHelper.h"
#include "Tests/Test_2ShaderPrograms.h"

#include <GLFW/glfw3.h>


int main(void) {
    GLFWwindow* window = ApplicationHelper::StartApplication();

    Test_2ShaderPrograms* test = new Test_2ShaderPrograms();
    test->Initialize();
    
    while (!ApplicationHelper::ShouldCloseWindow(window)) {
        test->PreTick();
        test->Tick();
        test->PostTick();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    test->Finalize();
    
    ApplicationHelper::FinalizeApplication();
    return 0;
}
