#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/** @note assumes that the following strings are used: */
#if 0
static char const * const errno_str[] = {
	"no error",
	"permission error",
	"invalid argument",
	"io error",
	"math domain error",
	"math range error",
};

static char * const unknown_errno_string = "unknown error -8388608";
#endif

int main(void)
{
	os_ClrHome();

	errno = 0; perror(NULL);
	errno = 1; perror("");
	errno = 2; perror("\0");
	errno = 3; perror(" ");
	errno = 4; perror("%d");
	errno = 5; perror("perror");

	while (!os_GetCSC());

	os_ClrHome();

	errno = 6; perror(NULL);
	errno = -1; perror("");
	errno = -123456; perror("%d");
	errno = 123456; perror("???");
	errno = INT_MIN; perror(" ");
	errno = INT_MAX; perror("#");
	
	while (!os_GetCSC());

	return 0;
}
