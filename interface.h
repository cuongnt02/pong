#ifndef INTERFACE_H
#define INTERFACE_H

class IMovable {
    public:
        virtual ~IMovable() {};
        virtual void move(int x, int y) = 0;
};

#endif

