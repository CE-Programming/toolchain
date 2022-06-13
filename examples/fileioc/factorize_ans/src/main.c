#include <ti/screen.h>
#include <ti/real.h>
#include <math.h>
#include <fileioc.h>

void prime_factors(unsigned int n);

int primes[512];
unsigned int total_primes = 0;

int main(void)
{
    real_t *real_in;
    list_t *list_out;
    unsigned i;
    int in;

    /* Clear the homescreen */
    os_ClrHome();

    /* Get the answer variable */
    if (ti_RclVar(OS_TYPE_REAL, OS_VAR_ANS, (void**)&real_in)) return 1;
    if ((in = os_RealToInt24(real_in)) < 1) return 1;

    /* Get the prime factors of the input */
    prime_factors((unsigned int)in);

    /* Create a list to store the primes */
    if (!total_primes)
    {
        return 1;
    }

    /* Allocate list to store output */
    /* Same as ti_AllocList(total_primes, malloc) */
    list_out = ti_MallocList(total_primes);

    /* Write out the list of primes */
    for (i = 0; i < total_primes; ++i)
    {
        list_out->items[i] = os_Int24ToReal(primes[i]);
    }

    /* Set the new answer */
    ti_SetVar(OS_TYPE_REAL_LIST, OS_VAR_ANS, list_out);

    /* Free the allocated list */
    free(list_out);

    return 0;
}

/* Store to an array all the prime numbers */
void prime_factors(unsigned int n)
{
    unsigned int div, end;

    while (!(n % 2))
    {
        primes[total_primes++] = 2;
        n /= 2;
    }

    if (n == 1)
    {
        return;
    }

    div = 3;
    end = sqrt(n);

    while (div <= end)
    {
        if (!(n % div))
        {
            do
            {
                primes[total_primes++] = div;
                n /= div;
            } while (!(n % div));

            if (n == 1)
            {
                return;
            }

            end = sqrt(n);
        }
        div += 2;
    }

    primes[total_primes++] = n;
}
