#include "types.h"

Base& get_object(bool multiple) {
    static Single single;
    static Multiple both;
    if (multiple)
        return both;
    return single;
}
