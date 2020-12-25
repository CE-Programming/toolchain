#include <tice.h>
#include <fileioc.h>

/* Some function prototypes. Maybe someday a library */
cplx_t Int24sToCplx(int real, int imag);
cplx_t FloatsToCplx(float real, float imag);
cplx_t RealsToCplx(real_t real, real_t imag);
cplx_t StrsToCplx(char *real, char **real_end, char *imag, char **imag_end);

int main(void)
{
    /* Declare some variables */
    equ_t    *my_equ;
    list_t   *my_list;
    matrix_t *my_matrix;
    real_t    my_real;
    cplx_t    my_cplx;
    real_t    real_1_5 = os_FloatToReal(1.5);
    real_t    real_2_5 = os_FloatToReal(2.5);
    real_t    real_3_5 = os_FloatToReal(3.5);

    /* Store the value '1.5+2.5i' into the variable B */
    my_cplx = FloatsToCplx(1.5, 2.5);
    ti_SetVar(TI_CPLX_TYPE, ti_B, &my_cplx);

    /* Store the value '1.5' into the variable A */
    my_real = real_1_5;
    ti_SetVar(TI_REAL_TYPE, ti_A, &my_real);

    /* Store the equation "2+2" into the Y1 variable */
    my_equ = ti_MallocEqu(3); // Same as ti_AllocEqu(3, malloc)
    my_equ->data[0] = '2';
    my_equ->data[1] = tAdd;
    my_equ->data[2] = '2';
    ti_SetVar(TI_EQU_TYPE, ti_Y1, my_equ);
    free(my_equ);

    /* Store the list {1.5,2.5,3.5} to L1 */
    my_list = ti_MallocList(3); // Same as ti_AllocList(3, malloc)
    my_list->items[0] = real_1_5;
    my_list->items[1] = real_2_5;
    my_list->items[2] = real_3_5;
    ti_SetVar(TI_REAL_LIST_TYPE, ti_L1, my_list);
    free(my_list);

    /* Store the matrix [[2.5,2.5]] to Ans */
    my_matrix = ti_MallocMatrix(1,2); // Same as ti_AllocMatrix(1, 2, malloc)
    matrix_element(my_matrix, 0, 0) = real_2_5;
    matrix_element(my_matrix, 0, 1) = real_2_5;
    ti_SetVar(TI_MATRIX_TYPE, ti_Ans, my_matrix);
    free(my_matrix);

    return 0;
}

/* Stores some ints to a complex variable type */
cplx_t Int24sToCplx(int real, int imag)
{
    cplx_t res;
    res.real = os_Int24ToReal(real);
    res.real.sign |= TI_CPLX_TYPE;
    res.imag = os_Int24ToReal(imag);
    res.imag.sign |= TI_CPLX_TYPE;
    return res;
}

/* Stores some floats to a complex variable type */
cplx_t FloatsToCplx(float real, float imag)
{
    cplx_t res;
    res.real = os_FloatToReal(real);
    res.real.sign |= TI_CPLX_TYPE;
    res.imag = os_FloatToReal(imag);
    res.imag.sign |= TI_CPLX_TYPE;
    return res;
}

/* Converts a pair of reals to a complex number */
cplx_t RealsToCplx(real_t real, real_t imag)
{
    cplx_t res;
    res.real = real;
    res.real.sign |= TI_CPLX_TYPE;
    res.imag = imag;
    res.imag.sign |= TI_CPLX_TYPE;
    return res;
}

/* Converts strings to a complex variable type */
cplx_t StrsToCplx(char *real, char **real_end, char *imag, char **imag_end)
{
    cplx_t res;
    res.real = os_StrToReal(real, real_end);
    res.real.sign |= TI_CPLX_TYPE;
    res.imag = os_StrToReal(imag, imag_end);
    res.imag.sign |= TI_CPLX_TYPE;
    return res;
}
