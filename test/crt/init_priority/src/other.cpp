#include "ordered_event.h"

/* Ensure init_priority ordering works across translation units. */

OrderedEvent init_120 __attribute__((init_priority(120)))("init_ctor_120", "init_dtor_120");
OrderedEvent init_109 __attribute__((init_priority(109)))("init_ctor_109", "init_dtor_109");
