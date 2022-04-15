#ifndef COMPONENT_H
#define COMPONENT_H

class UComponent {

public:
    UComponent();
    UComponent(long&& NewID);

private:
    long ID;
};

#endif