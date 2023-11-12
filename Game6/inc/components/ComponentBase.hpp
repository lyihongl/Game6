#pragma once

class Component2D {
    public:
    //Component2D() = delete;
    //Component2D(Component2D&) = delete;
    //Component2D(Component2D&&) = delete;
    //Component2D& operator=(Component2D&) = delete;
    //~Component2D() = delete;
    virtual void reset() = 0;
};
