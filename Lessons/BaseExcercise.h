#ifndef BASE_EXCERCISE_123H
#define BASE_EXCERCISE_123H

class BaseExcercise {
public:
    BaseExcercise() {}
    virtual void Initialize();

    virtual void PreTick();
    virtual void Tick() {}
    virtual void PostTick();

    virtual void Finalize() {}

    virtual ~BaseExcercise() {}
};
#endif
