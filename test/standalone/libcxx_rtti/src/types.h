#ifndef TYPES_H
#define TYPES_H

struct Base {
    virtual ~Base() = default;
};

struct Single : Base {};

struct Side {
    virtual ~Side() = default;
};

struct Multiple : Single, Side {};

Base& get_object(bool multiple);

#endif
