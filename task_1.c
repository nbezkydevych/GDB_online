#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ULL;

// Task: Get number of operation ("-1" or "/2") after value (represent in binary form in string) will be zero.

ULL calc_number_of_operations(char *S) {
    ULL N = 0, size = 0, operations = 0;
    char start = 0;

    while (S[N] != '\0')
    {
        if (start)
            size++;
        else if(S[N] == '1')
        {
            start = 1;
            size++;
        }
        N++;
    }

    do {
        if (S[N-1] == '1' && size != 1)
            operations += 2;
        else
            operations++;

        N--;
        size--;
    } while (size);

    return operations;
}

int calc_number_of_operations_by_value(char *S) {
    int operations = 0, value = 0, size = strlen(S);

    for (int i = 0; i < size; ++i)
        value = value * 2 + (S[i] - '0');

    while (value > 0)
    {
        if (value % 2 == 0)
            value /= 2;
        else
            value -= 1;
        operations++;
    }

    return operations;
}

int main() {

    printf("For \"011100\" numb of operation is %d\n", 
            calc_number_of_operations_by_value("011100")); // Output: 7
    printf("For \"011100\" numb of operation is %llu\n",
            calc_number_of_operations("011100")); // Output: 7
    printf("For \"111\" numb of operation is %d\n",
            calc_number_of_operations_by_value("111")); // Output: 5
    printf("For \"111\" numb of operation is %llu\n",
            calc_number_of_operations("111")); // Output: 5
    printf("For \"1111010101111\" numb of operation is %d\n",
            calc_number_of_operations_by_value("1111010101111")); // Output: 22
    printf("For \"1111010101111\" numb of operation is %llu\n",
            calc_number_of_operations("1111010101111")); // Output: 22

    const int size = 1000000000;
    char *big_input = (char *)malloc(sizeof(char) * (size + 1));
    memset(big_input, '1', size);
    big_input[size+1] = '\0';

    printf("For \'1\' repeated %d numb of operation is %d\n",
            size,
            calc_number_of_operations_by_value(big_input));
    printf("For \'1\' repeated %d numb of operation is %llu\n",
            size,
            calc_number_of_operations(big_input)); // Output: 1999999999

    free(big_input);
    return 0;
}