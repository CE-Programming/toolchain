#include <fileioc.h>
#include <stdio.h>
#include <tice.h>


int main(void)
{
    static const char *name0 = "file0";
    static const char *name1 = "file1";
    static const char *name2 = "file2";
    ti_var_t file0;
    ti_var_t file1;
    ti_var_t file2;
    bool error;
    int test;

    os_ClrHome();

    error = true;
    test = 0;
    do
    {
        file0 = ti_Open(name0, "w");
        if (++test, !file0) break;

        file1 = ti_Open(name1, "w");
        if (++test, !file1) break;

        file2 = ti_Open(name2, "w");
        if (++test, !file2) break;

        if (++test, ti_Resize(1, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 1) break;
        if (++test, ti_Resize(512, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 512) break;
        if (++test, ti_Resize(1024, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 1024) break;
        if (++test, ti_Resize(32768, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 32768) break;
        if (++test, ti_Resize(1024, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 1024) break;
        if (++test, ti_Resize(512, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 512) break;
        if (++test, ti_Resize(1, file0) < 0) break;
        if (++test, ti_GetSize(file0) != 1) break;

        if (!ti_Close(file0)) break;

        if (++test, ti_Resize(1, file1) < 0) break;
        if (++test, ti_GetSize(file1) != 1) break;
        if (++test, ti_Resize(0, file1) < 0) break;
        if (++test, ti_GetSize(file1) != 0) break;
        if (++test, ti_Resize(1, file1) < 0) break;
        if (++test, ti_GetSize(file1) != 1) break;

        if (!ti_Close(file1)) break;

        file1 = ti_Open(name1, "r");
        if (++test, !file1) break;

        if (++test, ti_Resize(32768, file2) < 0) break;
        if (++test, ti_GetSize(file2) != 32768) break;

        if (!ti_Close(file2)) break;

        if (++test, ti_GetSize(file1) != 1) break;

        if (!ti_Close(file1)) break;

        error = false;
    } while (0);

    ti_Delete(name0);
    ti_Delete(name1);
    ti_Delete(name2);

    if (!error)
    {
        puts("All tests passed");
    }
    else
    {
        printf("Test %d failed\n", test);
    }

    while (!os_GetCSC());

    return 0;
}
