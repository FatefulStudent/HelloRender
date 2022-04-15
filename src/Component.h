#ifndef COMPONENT_H
#define COMPONENT_H

class UComponent {

public:
    UComponent();
    UComponent(long&& NewID);

    virtual void Destroy(){};

    virtual ~UComponent();

private:
    long ID;
};

#endif