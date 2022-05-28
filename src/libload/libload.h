#ifndef LIBLOAD_H
#define LIBLOAD_H

#define libload_IsLibLoaded(name) __extension__({ \
        extern unsigned char _LibLoad_#name;      \
        _LibLoad_#name;                           \
    })

#endif
