#include <ctype.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cwalk.h"
#include "whereami.h"

#ifdef FILENAME_MAX
#define FILENAME_MAX_LENGTH FILENAME_MAX
#else
#define FILENAME_MAX_LENGTH 65536
#endif

static int help(const char *prgm)
{
    fprintf(stdout, "usage: %s <OPTION>\n", prgm);
    fprintf(stdout, "\n");
    fprintf(stdout, "Get various configuration information needed to compile programs\n");
    fprintf(stdout, "using the CE C Toolchain.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "  --version         Print CE C Toolchain version.\n");
    fprintf(stdout, "  --prefix          Print the installation prefix.\n");
    fprintf(stdout, "  --bindir          Directory containing toolchain executables.\n");
    fprintf(stdout, "  --includedir      Directory containing toolchain headers.\n");
    fprintf(stdout, "  --libdir          Directory containing toolchain libraries.\n");
    fprintf(stdout, "  --makefile        Core toolchain makefile.\n");
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
        fprintf(stderr, "Could not find application path.\n");
        exit(1);
    }

    return path;
}

int main(int argc, char *argv[])
{
    static char cedev[FILENAME_MAX_LENGTH];
    static char buffer[FILENAME_MAX_LENGTH];

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
            {"bindir",       no_argument, 0, 'b'},
            {"includedir",   no_argument, 0, 'i'},
            {"libdir",       no_argument, 0, 'l'},
            {"makefile",     no_argument, 0, 'm'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "h", long_options, NULL);
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

            case 'b':
                cwk_path_get_absolute(cedev, "./bin", buffer, sizeof buffer);
                fprintf(stdout, "%s\n", buffer);
                break;

            case 'i':
                cwk_path_get_absolute(cedev, "./include", buffer, sizeof buffer);
                fprintf(stdout, "%s\n", buffer);
                break;

            case 'l':
                cwk_path_get_absolute(cedev, "./lib", buffer, sizeof buffer);
                fprintf(stdout, "%s\n", buffer);
                break;

            case 'm':
                cwk_path_get_absolute(cedev, "./meta/makefile.mk", buffer, sizeof buffer);
                fprintf(stdout, "%s\n", buffer);
                break;

            case 'h':
                return help(argv[0]);

            default:
                return help(argv[0]);
        }
    }

    return 0;
}
