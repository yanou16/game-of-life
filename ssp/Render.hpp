#pragma once
#include "Grid.hpp"

class Render {
public:
    virtual ~Render() = default;
    virtual void render(const Grid& grid) = 0;
    virtual bool isOpen() const = 0;
    virtual void handleEvents() = 0;
};