#include <stdio.h>
#include <math.h>

// #define USE_WINDOWS_TIME

#ifndef USE_WINDOWS_TIME
#include <sys/time.h>
#else
#include <sys\timeb.h>
#endif

typedef unsigned long long ULL;

int isPrime(ULL number)
{
    // 0 and 1 are not prime numbers
    // return 0 for non-prime number
    if (number == 0 || number == 1)
        return 0;
    else
    {
        for (ULL i = 2; i <= number / 2; ++i)
        {
            // if number is divisible by i, then n is not prime
            // return 0 for non-prime number
            if (number % i == 0)
                return 0;
        }
    }
    // return 1 for prime number
    return 1;
}

void largestPalindrome(ULL n, ULL* res, ULL* num1, ULL* num2)
{
    ULL upper_limit = pow(10,n) - 1;
 
    // largest number of n-1 digit.
    // One plus this number is lower
    // limit which is product of two numbers.
    ULL lower_limit = 1 + upper_limit / 10;
    
 
    // Initialize result
    ULL max_product = 0;
    for (ULL i = lower_limit; i <= upper_limit; i++)
    {
        for (ULL j = i; j <= upper_limit; j++)
        {
    // for (ULL i = upper_limit; i >= lower_limit; i--)
    // {
    //     for (ULL j = i; j >= lower_limit; j--)
    //     {
            if (isPrime(i) && isPrime(j))
            {
                // calculating product of
                // two n-digit numbers
                ULL product = i * j;
                if (product < max_product)
                    break;
                ULL number = product;
                ULL reverse = 0;
     
                // calculating reverse of
                // product to check whether
                // it is palindrome or not
                while (number != 0)
                {
                    reverse = reverse * 10 + number % 10;
                    number /= 10;
                }
     
                // update new product if exist
                // and if greater than previous one
                if (product == reverse && product > max_product)
                {
                    max_product = product;
                    *num1 = i;
                    *num2 = j;
                    
                    printf("%llu * %llu = %llu\n", i, j, max_product);
                }
            }
        }
    }
    *res = max_product;
    printf("\n");
}

int main()
{
    ULL res = 0, num1 = 0, num2 = 0;
    ULL ms = 0, s = 0, m = 0, h = 0;
#ifndef USE_WINDOWS_TIME
    struct timeval stop, start;
    gettimeofday(&start, NULL);
#else
    struct timeb start, end;
    ftime(&start);
#endif
    
    largestPalindrome(5, &res, &num1, &num2);

#ifndef USE_WINDOWS_TIME
    gettimeofday(&stop, NULL);
    if (start.tv_usec > stop.tv_usec)
        stop.tv_usec += 1000000;
    ms = (stop.tv_usec - start.tv_usec) / 1000;
    s = (stop.tv_sec - start.tv_sec) % 60;
    m = (s / 60) % 60;
    h = (s / (60*60)) % 60;
#else
    ftime(&end);
    if (start.millitm > end.millitm)
        end.millitm += 1000;
    ms = (ULL)(end.millitm - start.millitm);
    s = (end.time - start.time) % 60;
    m = (s / 60) % 60;
    h = (s / (60*60)) % 60;
#endif

    printf("Execute time %02llu:%02llu:%02llu.%03llu\n", h, m, s, ms);

    return 0;
}