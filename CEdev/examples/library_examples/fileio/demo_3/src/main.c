/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
 
/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Shared library headers - depends on which ones you wish to use */
#include <lib/ce/fileioc.h>

/* Main Function */
void main(void) {
	/* Declare some variables */
	equ_t    *my_equ;
	list_t   *my_list;
	matrix_t *my_matrix;
	real_t    my_real;
	cplx_t    my_cplx;
	real_t	  real_1_5 = os_FloatToReal(1.5);
	real_t	  real_2_5 = os_FloatToReal(2.5);
	real_t	  real_3_5 = os_FloatToReal(3.5);
	
	/* Store the value '1.5+2.5i' into the varaible B */
	my_cplx.real = real_1_5;
	my_cplx.imag = real_2_5;
	ti_SetVar(TI_CPLX_TYPE, ti_B, &my_cplx);
	
	/* Store the value '1.5' into the varaible A */
	my_real = real_1_5;
	ti_SetVar(TI_REAL_TYPE, ti_A, &my_real);
	
	/* Store the equation "2+2" into the Y1 variable */
	my_equ = ti_AllocEqu(3);
	my_equ->data[0] = '2';
	my_equ->data[1] = tAdd;
	my_equ->data[2] = '2';
	ti_SetVar(TI_EQU_TYPE, ti_EquY1, my_equ);
	free(my_equ);
	
	/* Store the list {1.5,2.5,3.5} to L1 */
	my_list = ti_AllocList(3);
	my_list->items[0] = real_1_5;
	my_list->items[1] = real_2_5;
	my_list->items[2] = real_3_5;
	ti_SetVar(TI_REAL_LIST_TYPE, ti_L1, my_list);
	free(my_list);
	
	/* Store the matrix [2.5,2.5] to Ans */
	my_matrix = ti_AllocMatrix(1,2);
	matrix_element(my_matrix, 0, 0) = real_2_5;
	matrix_element(my_matrix, 0, 1) = real_2_5;
	ti_SetVar(TI_MATRIX_TYPE, ti_Ans, my_matrix);
	free(my_matrix);

	/* Clean up everything */
	prgm_CleanUp();
}
