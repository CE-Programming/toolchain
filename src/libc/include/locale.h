#ifndef _LOCALE_H
#define _LOCALE_H

#include <cdefs.h>

enum {
    LC_COLLATE,
    #define LC_COLLATE LC_COLLATE
    LC_CTYPE,
    #define LC_CTYPE LC_CTYPE
    LC_MONETARY,
    #define LC_MONETARY LC_MONETARY
    LC_NUMERIC,
    #define LC_NUMERIC LC_NUMERIC
    LC_TIME,
    #define LC_TIME LC_TIME
    LC_MESSAGES,
    #define LC_MESSAGES LC_MESSAGES
    LC_ALL,
    #define LC_ALL LC_ALL
    __LC_LAST = LC_ALL
};

#define LC_CTYPE_MASK    (1 << LC_CTYPE)
#define LC_NUMERIC_MASK  (1 << LC_NUMERIC)
#define LC_TIME_MASK     (1 << LC_TIME)
#define LC_COLLATE_MASK  (1 << LC_COLLATE)
#define LC_MONETARY_MASK (1 << LC_MONETARY)
#define LC_MESSAGES_MASK (1 << LC_MESSAGES)
#define LC_ALL_MASK \
(LC_CTYPE_MASK | LC_NUMERIC_MASK | LC_TIME_MASK | LC_COLLATE_MASK | LC_MONETARY_MASK | LC_MESSAGES_MASK)

#define LC_GLOBAL_LOCALE ((locale_t)-1)

#define LC_C_LOCALE LC_GLOBAL_LOCALE

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

struct __locale_struct {
    char const *__name;
    struct lconv *__data;
};

typedef struct __locale_struct * locale_t;

__BEGIN_DECLS

char *setlocale(int, const char *);

struct lconv *localeconv(void);

locale_t newlocale(int, const char *, locale_t);

void freelocale(locale_t);

locale_t duplocale(locale_t);

locale_t uselocale(locale_t);

__END_DECLS

#endif /* _LOCALE_H */
