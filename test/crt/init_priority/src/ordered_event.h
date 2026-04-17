#ifndef ORDERED_EVENT_H
#define ORDERED_EVENT_H

#include <ti/screen.h>
#include <ti/getcsc.h>

class OrderedEvent {
public:
    OrderedEvent(
        const char *ctor_label, const char *dtor_label
    ) : ctor_label_(ctor_label), dtor_label_(dtor_label) {
        if (ctor_label_) {
            os_ClrHome();
            os_PutStrFull(ctor_label_);
            while (!os_GetCSC());
        }
    }

    ~OrderedEvent() {
        if (dtor_label_) {
            os_ClrHome();
            os_PutStrFull(dtor_label_);
            while (!os_GetCSC());
        }
    }

private:
    const char *ctor_label_;
    const char *dtor_label_;
};

#endif /* ORDERED_EVENT_H */
