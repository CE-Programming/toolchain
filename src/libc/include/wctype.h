#ifndef _WCTYPE_H
#define _WCTYPE_H

#include <__wchar_def.h>

typedef int wctrans_t;

typedef int wctype_t;

__BEGIN_DECLS

int iswalnum(wint_t wc);

int iswalpha(wint_t wc);

int iswblank(wint_t wc);

int iswcntrl(wint_t wc);

int iswdigit(wint_t wc);

int iswgraph(wint_t wc);

int iswlower(wint_t wc);

int iswprint(wint_t wc);

int iswpunct(wint_t wc);

int iswspace(wint_t wc);

int iswupper(wint_t wc);

int iswxdigit(wint_t wc);

wint_t towlower(wint_t wc);

wint_t towupper(wint_t wc);

wint_t towctrans(wint_t wc, wctrans_t desc);

wctrans_t wctrans(const char *str);

int iswctype(wint_t wc, wctype_t desc);

wctype_t wctype(const char *property);

__END_DECLS

#endif /* _WCTYPE_H */
