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
#include <libs/fileioc.h>

void prime_factors(unsigned int n);

int primes[512];
int total_primes = 0;

/* Main Function */
void main(void) {
    /* Declare some variables */
    real_t *real_in;
    list_t *list_out;
    unsigned i;
    int in;
    
    /* Get the answer variable */
    if(ti_RclVar(TI_REAL_TYPE, ti_Ans, &real_in)) return;    
    if((in = os_RealToInt24(real_in)) < 1) return;
    
    prime_factors((unsigned)in);
    
    if(!total_primes) return;
    list_out = ti_MallocList(total_primes);
    
    for(i=0; i<total_primes; i++) {
        list_out->items[i] = os_Int24ToReal(primes[i]);
    }
    
    ti_SetVar(TI_REAL_LIST_TYPE, ti_Ans, list_out);
    
    /* Clean up everything */
    prgm_CleanUp();
}

/* Store to an array all the prime numbers */
void prime_factors(unsigned int n) {
    unsigned int div, end;
    
    while (!(n % 2)) {
        primes[total_primes++] = 2;
        n /= 2;
    }
    
    if (n == 1) {
        return;
    }
    
    div = 3;
    end = sqrt(n);
    
    while (div <= end) {
        if (!(n % div)) {
            do {
                primes[total_primes++] = div;
                n /= div;
            } while (!(n % div));
            if (n == 1) {
                return;
            }
            end = sqrt(n);
        }
        div += 2;
    }
    
    primes[total_primes++] = n;
}
