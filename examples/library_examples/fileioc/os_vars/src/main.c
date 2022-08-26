#include <fileioc.h>
#include <ti/real.h>
#include <ti/tokens.h>

/* Stores ints to a complex variable type */
cplx_t Int24sToCplx(int real, int imag)
{
    cplx_t res;
    res.real = os_Int24ToReal(real);
    res.real.sign |= OS_TYPE_CPLX;
    res.imag = os_Int24ToReal(imag);
    res.imag.sign |= OS_TYPE_CPLX;
    return res;
}

/* Stores floats to a complex variable type */
cplx_t FloatsToCplx(float real, float imag)
{
    cplx_t res;
    res.real = os_FloatToReal(real);
    res.real.sign |= OS_TYPE_CPLX;
    res.imag = os_FloatToReal(imag);
    res.imag.sign |= OS_TYPE_CPLX;
    return res;
}

/* Converts a pair of reals to a complex number */
cplx_t RealsToCplx(real_t real, real_t imag)
{
    cplx_t res;
    res.real = real;
    res.real.sign |= OS_TYPE_CPLX;
    res.imag = imag;
    res.imag.sign |= OS_TYPE_CPLX;
    return res;
}

/* Converts strings to a complex variable type */
cplx_t StrsToCplx(char *real, char **real_end, char *imag, char **imag_end)
{
    cplx_t res;
    res.real = os_StrToReal(real, real_end);
    res.real.sign |= OS_TYPE_CPLX;
    res.imag = os_StrToReal(imag, imag_end);
    res.imag.sign |= OS_TYPE_CPLX;
    return res;
}

int main(void)
{
    equ_t *equ;
    list_t *list;
    matrix_t *matrix;
    real_t real;
    cplx_t cplx;

    /* Store the value '1.5+2.5i' into the variable B */
    cplx = FloatsToCplx(1.5, 2.5);
    ti_SetVar(OS_TYPE_CPLX, OS_VAR_B, &cplx);

    /* Store the value '1.5' into the variable A */
    real = os_FloatToReal(1.5);
    ti_SetVar(OS_TYPE_REAL, OS_VAR_A, &real);

    /* Store the equation "2+2" into the Y1 variable */
    equ = ti_MallocEqu(3);
    equ->data[0] = OS_TOK_2;
    equ->data[1] = OS_TOK_ADD;
    equ->data[2] = OS_TOK_2;
    ti_SetVar(OS_TYPE_EQU, OS_VAR_Y1, equ);
    free(equ);

    /* Store the list {1.5, 2.5, 3.5} to L1 */
    list = ti_MallocList(3);
    list->items[0] = os_FloatToReal(1.5);
    list->items[1] = os_FloatToReal(2.5);
    list->items[2] = os_FloatToReal(3.5);
    ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_L1, list);
    free(list);

    /* Store the matrix [[2.5, 2.5]] to Ans */
    matrix = ti_MallocMatrix(1, 2);
    OS_MATRIX_ELEMENT(matrix, 0, 0) = os_FloatToReal(2.5);
    OS_MATRIX_ELEMENT(matrix, 0, 1) = os_FloatToReal(2.5);
    ti_SetVar(OS_TYPE_MATRIX, OS_VAR_ANS, matrix);
    free(matrix);

    return 0;
}
