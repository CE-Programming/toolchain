#include "types.h"

#include <typeinfo>

#include <ti/getcsc.h>
#include <ti/screen.h>

int main() {
    Base& both = get_object(true);
    Base& single = get_object(false);
    auto* derived = dynamic_cast<Multiple*>(&both);

    const bool passed = typeid(both) == typeid(Multiple)
        && typeid(single) == typeid(Single)
        && derived != nullptr
        && dynamic_cast<Side*>(&both) == static_cast<Side*>(derived)
        && dynamic_cast<Side*>(&single) == nullptr;

    os_ClrHome();
    os_PutStrFull(passed ? "All tests passed" : "RTTI test failed");
    while (!os_GetCSC())
        ;
    return passed ? 0 : 1;
}
