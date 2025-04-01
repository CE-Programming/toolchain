#include <ti/screen.h>
#include <ti/getcsc.h>
#include <string.h>
#include <stdio.h>

void test(const char *a, const char *b)
{
	int cmp = strcasecmp(a, b);
	cmp = cmp < 0 ? -1 : (cmp > 0);
	printf("%d ", cmp);
}

void testn(const char *a, const char *b, size_t n)
{
	int cmp = strncasecmp(a, b, n);
	cmp = cmp < 0 ? -1 : (cmp > 0);
	printf("%d ", cmp);
}

int main(void)
{
	os_ClrHome();

	test("", "");
	test("a", "");
	test("abc", "ABC");
	test("bad", "Apple");
	test("bRiCk", "Bring");
	test("bad", "Badger");
	printf("\n");

	testn("abc", "ABC", 3);
	testn("bad", "Apple", 0);
	testn("bad", "Apple", 6);
	testn("bRiCk", "Bring", 3);
	testn("bRiCk", "Bring", 4);
	testn("bad", "Badger", 6);
	testn("Hello", "HELLO WORLD!", 5);
	testn("Hello", "HELLO WORLD!", 12);
	printf("\n");

	while (!os_GetCSC());

	return 0;
}
