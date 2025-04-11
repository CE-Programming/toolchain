#ifndef DATA_H
#define DATA_H

#include <stdint.h>

#define C(expr) do { if (!(expr)) { return __LINE__; } } while(0)
#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t  zero_u8;
extern uint16_t zero_u16;
extern uint24_t zero_u24;
extern uint32_t zero_u32;
extern uint48_t zero_u48;
extern uint64_t zero_u64;

extern uint8_t  one_u8;
extern uint16_t one_u16;
extern uint24_t one_u24;
extern uint32_t one_u32;
extern uint48_t one_u48;
extern uint64_t one_u64;

extern uint8_t  umax_u8;
extern uint16_t umax_u16;
extern uint24_t umax_u24;
extern uint32_t umax_u32;
extern uint48_t umax_u48;
extern uint64_t umax_u64;

extern uint8_t  smin_u8;
extern uint16_t smin_u16;
extern uint24_t smin_u24;
extern uint32_t smin_u32;
extern uint48_t smin_u48;
extern uint64_t smin_u64;

extern uint8_t  smax_u8;
extern uint16_t smax_u16;
extern uint24_t smax_u24;
extern uint32_t smax_u32;
extern uint48_t smax_u48;
extern uint64_t smax_u64;

extern uint8_t val_0;
extern uint8_t val_1;
extern uint8_t val_7;
extern uint8_t val_8;
extern uint8_t val_15;
extern uint8_t val_16;
extern uint8_t val_23;
extern uint8_t val_24;
extern uint8_t val_31;
extern uint8_t val_32;
extern uint8_t val_47;
extern uint8_t val_48;
extern uint8_t val_63;
extern uint8_t val_64;

#ifdef __cplusplus
}
#endif

#endif /* DATA_H */
