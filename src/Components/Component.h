#ifndef COMPONENT_H
#define COMPONENT_H

class UComponent {

public:
    UComponent();

    virtual void Destroy(){};

    virtual ~UComponent();

private:
    long ID;
};

#endif