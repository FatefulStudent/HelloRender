#ifndef BASE_TEST_H
#define BASE_TEST_H

class BaseTest {
public:
    BaseTest() {}
    virtual void Initialize();

    virtual void PreTick();
    virtual void Tick() {}
    virtual void PostTick();

    virtual void Finalize() {}

    virtual ~BaseTest() {}
};
#endif
