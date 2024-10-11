#include <ctype.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "cwalk.h"
#include "whereami.h"

#ifdef FILENAME_MAX
#define FILENAME_MAX_LENGTH FILENAME_MAX
#else
#define FILENAME_MAX_LENGTH 65536
#endif

#define TIME_MAX_LENGTH 42

static int help(const char *prgm)
{
    fprintf(stdout, "usage: %s <option>\n", prgm);
    fprintf(stdout, "\n");
    fprintf(stdout, "Get various configuration information needed to compile programs\n");
    fprintf(stdout, "using the CE C/C++ Toolchain.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "  --version         Print CE C/C++ Toolchain version.\n");
    fprintf(stdout, "  --prefix          Print the installation prefix.\n");
    fprintf(stdout, "  --makefile        Core toolchain makefile path.\n");
    fprintf(stdout, "  --help            Show this page.\n");

    return 0;
}

static const char *executable_path(void)
{
    static char path[FILENAME_MAX_LENGTH];
    int length, dirname_length;

    length = wai_getExecutablePath(NULL, 0, &dirname_length);
    if (length > 0)
    {
        wai_getExecutablePath(path, length, &dirname_length);
        path[length] = '\0';
    }
    else
    {
        fprintf(stderr, "Could not find CEdev installation.\n");
        exit(1);
    }

    return path;
}

static bool is_valid_make_path(const char *str, size_t max)
{
    size_t i = 0;

    for (; i < max; ++i)
    {
        char c = str[i];
        if (!c)
        {
            return true;
        }
        if (isspace(c))
        {
            return false;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    static char cedev[FILENAME_MAX_LENGTH];
    static char buffer[FILENAME_MAX_LENGTH];
    static char timebuffer[TIME_MAX_LENGTH];
    time_t rawtime;
    struct tm * timeinfo;

    if (argc != 2)
    {
        help(argv[0]);
        return 1;
    }

    cwk_path_get_absolute(executable_path(), "../..", cedev, sizeof cedev);

    for (;;)
    {
        int c;
        static struct option long_options[] =
        {
            {"help",         no_argument, 0, 'h'},
            {"version",      no_argument, 0, 'v'},
            {"prefix",       no_argument, 0, 'p'},
            {"makefile",     no_argument, 0, 'm'},
            {"comment",      no_argument, 0, 'c'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "hvpmc", long_options, NULL);
        if (c < 0)
        {
            break;
        }

        switch (c)
        {
            case 'v':
                fprintf(stdout, CEDEV_VERSION "\n");
                break;

            case 'p':
                fprintf(stdout, "%s\n", cedev);
                break;

            case 'm':
                cwk_path_get_absolute(cedev, "./meta/makefile.mk", buffer, sizeof buffer);
                if (!is_valid_make_path(buffer, sizeof buffer))
                {
                    fprintf(stderr, "The CE C Toolchain is installed in a directory containing\n");
                    fprintf(stderr, "spaces. This does not work properly with the \'make\' command.\n");
                    fprintf(stderr, "Please move the install directory to a path that does not\n");
                    fprintf(stderr, "contain any spaces.\n");
                    return 1;
                }
                fprintf(stdout, "%s\n", buffer);
                break;

            case 'c':
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(timebuffer, TIME_MAX_LENGTH, "%FT%T%z", timeinfo);
                fprintf(stdout, "%s " CEDEV_VERSION "\n", timebuffer);
                break;

            case 'h':
            default:
                return help(argv[0]);
        }
    }

    return 0;
}
