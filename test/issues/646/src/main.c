#include <stdio.h>
#include <string.h>
#include <ti/screen.h>
#include <ti/getkey.h>

#define C(expr) if (!(expr)) { return __LINE__; }
static int libc_test(void) {

    char const * str = "abcdef";
    char const * empty = "";

    C(strspn(str, "abc") == 3);
    C(strspn(str, "cba") == 3);
    C(strspn(str, "def") == 0);
    C(strspn(str, "fed") == 0);
    C(strspn(str, "ABCDEF") == 0);
    C(strspn(str, "bbeebe") == 0);
    C(strspn(str, "eebbeb") == 0);
    C(strspn(str, "aaffaf") == 1);
    C(strspn(str, "ffaafa") == 1);
    C(strspn(str, str) == 6);
    C(strspn(str, empty) == 0);
    C(strspn(empty, str) == 0);
    C(strspn(empty, empty) == 0);

    C(strcspn(str, "abc") == 0);
    C(strcspn(str, "cba") == 0);
    C(strcspn(str, "def") == 3);
    C(strcspn(str, "fed") == 3);
    C(strcspn(str, "ABCDEF") == 6);
    C(strcspn(str, "bbeebe") == 1);
    C(strcspn(str, "eebbeb") == 1);
    C(strcspn(str, "aaffaf") == 0);
    C(strcspn(str, "ffaafa") == 0);
    C(strcspn(str, str) == 0);
    C(strcspn(str, empty) == 6);
    C(strcspn(empty, str) == 0);
    C(strcspn(empty, empty) == 0);

    C(strpbrk(str, "abc") == str + 0);
    C(strpbrk(str, "cba") == str + 0);
    C(strpbrk(str, "def") == str + 3);
    C(strpbrk(str, "fed") == str + 3);
    C(strpbrk(str, "ABCDEF") == NULL);
    C(strpbrk(str, "bbeebe") == str + 1);
    C(strpbrk(str, "eebbeb") == str + 1);
    C(strpbrk(str, "aaffaf") == str + 0);
    C(strpbrk(str, "ffaafa") == str + 0);
    C(strpbrk(str, str) == str);
    C(strpbrk(str, empty) == NULL);
    C(strpbrk(empty, str) == NULL);
    C(strpbrk(empty, empty) == NULL);

    return 0;
}
#undef C

int main(void)
{
    os_ClrHome();

    printf("%d\n", libc_test());

    os_GetKey();

    return 0;
}
