#include <ti/vars.h>
#include <ti/real.h>
#include <ti/getkey.h>
#include <ti/screen.h>
#include <ti/tokens.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int ret;

    os_ClrHome();

    ret = os_EvalVar(OS_VAR_Y1);

    if (ret == 0)
    {
        uint8_t type;
        void *ans;

        ans = os_GetAnsData(&type);
        if (ans != NULL && type == OS_TYPE_REAL)
        {
            real_t *real = ans;

            printf("result: %f\n", os_RealToFloat(real));
        }
    }

    if (ret == 0)
    {
        real_t real = os_FloatToReal(2.0);

        ret = os_SetRealVar(OS_VAR_A, &real);
    }

    if (ret == 0)
    {
        /* Tokenized representation of "A+A" */
        const uint8_t expression[] =
        {
            OS_TOK_A,
            OS_TOK_ADD,
            OS_TOK_A,
        };

        ret = os_Eval(expression, sizeof expression);
    }

    if (ret == 0)
    {
        uint8_t type;
        void *ans;

        ans = os_GetAnsData(&type);
        if (ans != NULL && type == OS_TYPE_REAL)
        {
            real_t *real = ans;

            printf("result: %f\n", os_RealToFloat(real));
        }
    }

    os_GetKey();

    return ret;
}
