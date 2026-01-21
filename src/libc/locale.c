#include <limits.h>
#include <locale.h>

const struct lconv __c_locale = {
    .decimal_point =       ".",
    .thousands_sep =       "",
    .grouping =            "",
    .mon_decimal_point =   "",
    .mon_thousands_sep =   "",
    .mon_grouping =        "",
    .positive_sign =       "",
    .negative_sign =       "",
    .currency_symbol =     "",
    .frac_digits =         CHAR_MAX,
    .p_cs_precedes =       CHAR_MAX,
    .n_cs_precedes =       CHAR_MAX,
    .p_sep_by_space =      CHAR_MAX,
    .n_sep_by_space =      CHAR_MAX,
    .p_sign_posn =         CHAR_MAX,
    .n_sign_posn =         CHAR_MAX,
    .int_curr_symbol =     "",
    .int_frac_digits =     CHAR_MAX,
    .int_p_cs_precedes =   CHAR_MAX,
    .int_n_cs_precedes =   CHAR_MAX,
    .int_p_sep_by_space =  CHAR_MAX,
    .int_n_sep_by_space =  CHAR_MAX,
    .int_p_sign_posn =     CHAR_MAX,
    .int_n_sign_posn =     CHAR_MAX,
};

char *setlocale(__attribute__((__unused__)) int category, const char *locale) {
    // query the locale without modifiying it
    if (locale == NULL) {
        return "C";
    }
    // use preferred locale (the "C" locale)
    if (locale[0] == '\0') {
        return "C";
    }
    // use the "C" locale
    if (locale[0] == 'C' && locale[1] == '\0') {
        return "C";
    }
    // unknown locale
    return NULL;
}

struct lconv *localeconv(void) {
    // it is undefined behavior to modify the returned object
    return (struct lconv*)&__c_locale;
}
