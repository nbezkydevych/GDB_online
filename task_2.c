#include <stdio.h>
#include <stdbool.h>

// get find next max or min value from start index in integer array, which initialize values in range[MIN, MAX]

void init_arr(int* arr, int min, int max, size_t size)
{
    int temp = max/2;
    bool up = true;
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = temp;
        if (up)
        {
            temp++;
            if (temp >= max)
            {
                up = false;
                i++;
                arr[i] = temp;
            }
        }
        else
        {
            temp--;
            if (temp <= min)
            {
                up = true;
                i++;
                arr[i] = temp;
            }
        }
    }
}

int find_index_of_max_after_pos(int* arr, size_t size, size_t start_index)
{
    int curr = 0;
    int next = 0;
    int res = -1;
    size_t i = start_index;
    
    do {
        curr = arr[i];
        next = arr[i+1];
        
        if (curr > next)
        {
            res = i;
            break;
        }
        i++;
    } while (i < size);
    
    return res;
}

int find_index_of_min_after_pos(int* arr, size_t size, size_t start_index)
{
    int curr = 0;
    int next = 0;
    int res = -1;
    size_t i = start_index;
    
    do {
        curr = arr[i];
        next = arr[i+1];
        
        if (curr < next)
        {
            res = i;
            break;
        }
        i++;
    } while (i < size);
    
    return res;
}

void print_arr(int* arr, size_t size)
{
    
    for (size_t i = 0; i < size; i++)
    {
        printf ("%2ld ",i);
    }
    printf ("\n");
    for (size_t i = 0; i < size; i++)
    {
        printf ("%2d ", arr[i]);
    }
    printf ("\n");
}

#define ARR_SIZE 60
#define MIN_INIT_VALUE -2
#define MAX_INIT_VALUE 8

int main()
{
    int max_value_index = 0, min_value_index = 0;
    int i_arr[ARR_SIZE];

    init_arr(i_arr, MIN_INIT_VALUE, MAX_INIT_VALUE, ARR_SIZE);
    print_arr(i_arr, ARR_SIZE);

    do
    {
        max_value_index = find_index_of_max_after_pos(i_arr, ARR_SIZE, min_value_index);       
        min_value_index = find_index_of_min_after_pos(i_arr, ARR_SIZE, max_value_index);
        if (max_value_index >= 0)
            printf ("Max value: %3d, at position: %2d\n",i_arr[max_value_index], max_value_index);
        if (min_value_index >= 0)
            printf ("Min value: %3d, at position: %2d\n",i_arr[min_value_index], min_value_index);
    } while (max_value_index != -1 || min_value_index != -1);
    
    return 0;
}