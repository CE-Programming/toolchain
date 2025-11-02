#ifndef _LOCALE_H
#define _LOCALE_H

#include <cdefs.h>

struct lconv {
    char* decimal_point;        /* "."      */
    char* thousands_sep;        /* ""       */
    char* grouping;             /* ""       */
    char* mon_decimal_point;    /* ""       */
    char* mon_thousands_sep;    /* ""       */
    char* mon_grouping;         /* ""       */
    char* positive_sign;        /* ""       */
    char* negative_sign;        /* ""       */
    char* currency_symbol;      /* ""       */
    char  frac_digits;          /* CHAR_MAX */
    char  p_cs_precedes;        /* CHAR_MAX */
    char  n_cs_precedes;        /* CHAR_MAX */
    char  p_sep_by_space;       /* CHAR_MAX */
    char  n_sep_by_space;       /* CHAR_MAX */
    char  p_sign_posn;          /* CHAR_MAX */
    char  n_sign_posn;          /* CHAR_MAX */
    char* int_curr_symbol;      /* ""       */
    char  int_frac_digits;      /* CHAR_MAX */
    char  int_p_cs_precedes;    /* CHAR_MAX */
    char  int_n_cs_precedes;    /* CHAR_MAX */
    char  int_p_sep_by_space;   /* CHAR_MAX */
    char  int_n_sep_by_space;   /* CHAR_MAX */
    char  int_p_sign_posn;      /* CHAR_MAX */
    char  int_n_sign_posn;      /* CHAR_MAX */
};

#define LC_COLLATE  (0x010)
#define LC_CTYPE    (0x020)
#define LC_MONETARY (0x040)
#define LC_NUMERIC  (0x080)
#define LC_TIME     (0x100)
#define LC_MESSAGES (0x200)
#define LC_ALL      (LC_COLLATE | LC_CTYPE | LC_MONETARY | LC_NUMERIC | LC_TIME | LC_MESSAGES)

#ifdef __cplusplus
extern "C" {
#endif

char* setlocale(int category, const char* locale);

struct lconv* localeconv(void);

#ifdef __cplusplus
}
#endif

#endif /* _LOCALE_H */
