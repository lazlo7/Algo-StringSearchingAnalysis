#pragma once

class Nameable {
public:
    virtual ~Nameable() = default;
    virtual const char* name() const = 0;
};
