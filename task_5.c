#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SILENT_TEST

// Maximum value for generated random integers
#define MAX_GENERATED_VALUE 1000

// Macro to compute the number of elements in an array
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// Function pointer type for sorting functions
typedef void (*sort_fn)(int *, int);

// Forward declarations for test harness
void run_all_sort_tests(void);

// Get current time in seconds as a double
double now_seconds() {
    return (double)clock() / CLOCKS_PER_SEC;
}

/**
 * generate_array - Fill an integer array with pseudo-random values.
 * @arr: Pointer to the first element of the array (must be non-NULL).
 * @size: Number of elements to generate (must be >= 0).
 *
 * Values are in the range [0, MAX_GENERATED_VALUE - 1].
 * Time complexity: O(n). Space complexity: O(1). 
 */
void generate_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (rand() % MAX_GENERATED_VALUE); 
    }
}

/**
 * print_array - Print up to the first 20 elements of an integer array.
 * @arr: Pointer to the first element of the array.
 * @size: Number of elements in the array.
 *
 * If size > 20, only the first 20 elements are printed to keep output concise.
 * Elements are printed in a comma-separated list enclosed in brackets.
 * Time complexity: O(min(n, 20)). Space complexity: O(1).
 */
void print_array(int *arr, int size) {
    if (size > 20) {
        size = 20;
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == size-1) {
            printf("%3d", arr[i]);
        } else {
            printf("%3d, ", arr[i]);
        }
    }
    printf("]\n");
}

/**
 * find_min - Return the minimum value in an integer array.
 * @arr: Pointer to the first element of the array (assumed non-empty).
 * @size: Number of elements in the array (must be >= 1).
 *
 * Returns the smallest element.
 * Time complexity: O(n). Space complexity: O(1).
 */
int find_min(int arr[], int size) {
    int min = arr[0]; 
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

/**
 * find_max - Return the maximum value in an integer array.
 * @arr: Pointer to the first element of the array (assumed non-empty).
 * @size: Number of elements in the array (must be >= 1).
 *
 * Returns the largest element.
 * Time complexity: O(n). Space complexity: O(1).
 */
int find_max(int arr[], int size) {
    int max = arr[0]; 
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * swap_element - Swap two integer values in-place.
 * @a: Pointer to the first integer.
 * @b: Pointer to the second integer.
 *
 * Performs a simple three-value swap. Both pointers must be valid.
 */
void swap_element(int *a, int *b)
{
    int tmp = *a; *a = *b; *b = tmp;
}

/**
 * bubble_sort - Sort an array of integers in ascending order.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Sorts the array in-place by comparing each element with all previous elements
 * and swapping when a smaller element is found. Runs in O(n^2) time (quadratic)
 * in the average and worst cases and uses O(1) additional space. No operation is
 * performed for size <= 1. Stability: preserves the relative order of equal
 * elements because swaps occur only when arr[i] < arr[j].
 *
 * Note: Requires a compatible swap_element(int *a, int *b) helper function.
 * Stability: stable (equal elements maintain their relative order because the inner loop only swaps when arr[i] < arr[j]).
 * Time complexity: O(n^2). 
 * Space complexity: O(1).
 */
void bubble_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] < arr[j]) {
                swap_element(&arr[i], &arr[j]);
            }
        }
    }
}

/**
 * selection_sort - Sort an integer array in ascending order using selection sort.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Performs in-place selection sort: for each position i finds the minimum element
 * in arr[i..size-1] and swaps it into position i.
 * Stability: not stable (may change relative order of equal elements).
 * Time complexity: O(n^2) in all cases.
 * Space complexity: O(1).
 */
void selection_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    for (int i = 0; i < size; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        
        if (arr[min_index] < arr[i]) {
            swap_element(&arr[min_index], &arr[i]);
        }
    }
}

/**
 * insertion_sort - Insert elements one by one into the sorted left side.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Sorts the array in-place by iterating from the second element to the end,
 * treating the left portion as sorted. For each element, it is compared with
 * elements in the sorted portion and shifted left until it is in the correct position.
 * Stability: stable (equal elements maintain their relative order
 * because the inner loop only shifts elements greater than the key).
 * Time complexity: O(n^2) in the worst case (reverse sorted), O(n) in the best case (already sorted). 
 * Space complexity: O(1). 
 */
void insertion_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        /* Shift elements of the sorted segment that are greater than key */
        for (; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        /* Place key in its correct position */
        arr[j + 1] = key;
    }
}

/**
 * quick_sort_partition - Partition subarray arr[first..last] around pivot.
 * @arr: array containing the subarray.
 * @first: starting index of subarray.
 * @last: ending index of subarray (pivot chosen as arr[last]).
 *
 * Places all elements <= pivot to the left and > pivot to the right.
 * Returns final index of the pivot.
 */
int quick_sort_partition(int *arr, int first, int last) {
    int pivot = arr[last];
    int i = first - 1;

    for (int j = first; j < last; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap_element(&arr[i], &arr[j]);
        }
    }
    swap_element(&arr[i + 1], &arr[last]);
    return i + 1;
} 

/**
 * r_quick_sort - Recursive quicksort implementation.
 * @arr: array to sort.
 * @first: starting index of current subarray.
 * @last: ending index of current subarray.
 * 
 * Sorts arr[first..last] in-place using quicksort. Base case is when first >= last.
 */
void r_quick_sort(int *arr, int first, int last) {
    if (first < last) {
        int pivot_index = quick_sort_partition(arr, first, last);
        r_quick_sort(arr, first, pivot_index - 1);
        r_quick_sort(arr, pivot_index + 1, last);
    }
}

/**
 * recursive_quick_sort - Public recursive quicksort wrapper.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Calls the recursive quicksort on the full array.
 * Stability: not stable (may change relative order of equal elements).
 * Average time complexity: O(n log n). Worst-case: O(n^2).
 * Space complexity: O(log n) on average due to recursion stack, O(n) in worst case.
 */
void recursive_quick_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    r_quick_sort(arr, 0, size - 1);
}

/**
 * iterative_quick_sort - Iterative quicksort using an explicit stack.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 * 
 * Calls the iterative quicksort on the full array.
 * Uses an explicit stack to avoid recursion.
 * Stability: not stable (may change relative order of equal elements).
 * Average time complexity: O(n log n). Worst-case: O(n^2).
 * Space complexity: O(n) in worst case due to stack.
 */
void iterative_quick_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    /* Create an auxiliary stack */
    int *stack = (int *)malloc(sizeof(int) * size);
    int top = -1;
    /* Push initial values of first and last indices */
    stack[++top] = 0;
    stack[++top] = size - 1;
    /* Keep popping from stack while it's not empty */
    while (top >= 0) {
        int last = stack[top--];
        int first = stack[top--];
        int pivot_index = quick_sort_partition(arr, first, last);
        /* If there are elements on left side of pivot, push left side to stack */
        if (pivot_index - 1 > first) {
            stack[++top] = first;
            stack[++top] = pivot_index - 1;
        }
        /* If there are elements on right side of pivot, push right side to stack */
        if (pivot_index + 1 < last) {
            stack[++top] = pivot_index + 1;
            stack[++top] = last;
        }
    }
    free(stack);
}

/**
 * counting_sort - Stable counting sort for non-negative integers.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Uses auxiliary count array of size max_value+1 to count occurrences of each integer, then writes back sorted output. 
 * Assumes all integers are in the range [0, max_value]. 
 * Stable and in-place with O(k) extra space where k = max_value. Modifies array in-place.
 * Time complexity: O(n + k).
 * Space complexity: O(k) where k = max_value in array.
 */
void counting_sort(int *arr, int size) {
    if (!arr || size <= 1) return;
    int max_value = find_max(arr, size);
    /* allocate and zero count array of size max_value+1 */
    int *count_array = (int *)malloc(sizeof(int) * (max_value + 1));
    memset(count_array, 0, (max_value + 1) * sizeof(int));
    
    /* count occurrences and clear original array for output writing */
    for (int i = 0; i < size; i++) {
        count_array[arr[i]]++;
        arr[i] = 0;
    }
    
    /* write back values in sorted order using counts */
    for (int i = 0, k = 0; i <= max_value; i++) {
        for (int j = count_array[i]; j > 0; j--) {
            arr[k++] = i;
        }
    }

    free(count_array);
}

/**
 * radix_counting_sort - Stable counting sort by single digit (base 10).
 * @arr: input array.
 * @n: length of array.
 * @e: exponent (1, 10, 100, ...) indicating digit place.
 *
 * Uses an output buffer and count[10] for digits 0..9. Stable per-digit sort.
 */
void radix_counting_sort(int arr[], int n, int e) {
    /* output buffer sized n (n+1 earlier was unnecessary but preserved) */
    int *output = (int *)malloc(sizeof(int) * (n + 1));
    memset(output, 0, (n + 1) * sizeof(output[0]));
    int count[10] = {0};

    /* count occurrences of current digit */
    for (int i = 0; i < n; i++)
        count[(arr[i] / e) % 10]++;

    /* accumulate counts to get positions */
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* build output array in reverse to maintain stability */
    for (int i = n - 1; i >= 0; i--) {
        int d = (arr[i] / e) % 10;
        output[count[d] - 1] = arr[i];
        count[d]--;
    }

    /* copy sorted-by-digit output back to original array using memcpy */
    memcpy(arr, output, n * sizeof(int));

    free(output);
}

/**
 * radix_sort - LSD radix sort for non-negative integers (base 10).
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Calls radix_counting_sort for every digit from least significant to most.
 * Stability: stable (each counting sort is stable, so overall order of equal elements is preserved).
 * Time complexity: O(d*(n+k)), where d = number of digits.
 * Space complexity: O(n + k) where k = base (10). In-place with O(n) extra space for output buffer.
 */
void radix_sort(int arr[], int size) {
    if (!arr || size <= 1) return;
    int m = find_max(arr, size);
    /* process digits 10^0, 10^1, ... until all digits processed */
    for (int e = 1; m / e > 0; e *= 10) {
        radix_counting_sort(arr, size, e);
    }
}

/**
 * merge - Merge two sorted subarrays arr[left..middle] and arr[middle+1..right].
 * @arr: array containing subarrays.
 * @left: starting index of left subarray.
 * @middle: ending index of left subarray.
 * @right: ending index of right subarray.
 *
 * Allocates temporary arrays for merging. 
 */
void merge(int arr[], int left, int middle, int right) {
    // sizes of left and right subarrays
    int left_arr_size = middle - left + 1;
    int right_arr_size = right - middle;

    /* allocate temporary left and right arrays */
    int *left_arr = (int *)malloc(sizeof(int) * left_arr_size);
    int *right_arr = (int *)malloc(sizeof(int) * right_arr_size);
    memset(left_arr, 0, left_arr_size * sizeof(int));
    memset(right_arr, 0, right_arr_size * sizeof(int));

    /* copy data into temporaries using memcpy */
    memcpy(left_arr, arr + left, left_arr_size * sizeof(int));
    memcpy(right_arr, arr + middle + 1, right_arr_size * sizeof(int));

    /* merge back into array */
    int i = 0, j = 0, k = left;
    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    /* copy any remaining elements */
    while (i < left_arr_size) {   
        arr[k++] = left_arr[i++];
    }
    while (j < right_arr_size) {
        arr[k++] = right_arr[j++];
    }

    free(left_arr);
    free(right_arr);
}

/**
 * r_merge_sort - Recursive merge sort helper sorting arr[left..right].
 * @arr: array to sort.
 * @left: left index of subarray.
 * @right: right index of subarray.
 *
 * Divides array, sorts halves, then merges.
 */
void r_merge_sort(int arr[], int left, int right) {
    if (left < right) {
        // Avoids overflow for large left and right
        int middle = left + (right - left) / 2;
        // Recursively sort first and second halves
        r_merge_sort(arr, left, middle);
        // Recursively sort second half
        r_merge_sort(arr, middle + 1, right);
        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

/**
 * recursive_merge_sort - Public recursive merge sort wrapper.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Calls recursive merge sort on the full array.
 * Time complexity: O(n log n).
 * Space complexity: O(n) due to temporary arrays used in merging. Modifies arr in-place with sorted output.
 */
void recursive_merge_sort(int arr[], int size) {
    if (!arr || size <= 1) return;
    r_merge_sort(arr, 0, size - 1);
}

/**
 * iterative_merge_sort - Bottom-up (iterative) merge sort.
 * @arr: pointer to the first element of the integer array.
 * @size: number of elements in the array.
 *
 * Merges subarrays of increasing size: 1, 2, 4, ...
 * For each size, merges adjacent pairs of subarrays.
 * Stability: stable (merge function is stable, so overall order of equal elements is preserved).
 * Time complexity: O(n log n).
 * Space complexity: O(n) due to temporary arrays used in merging. Modifies arr in-place with sorted output.
 */
void iterative_merge_sort(int arr[], int size) {
    if (!arr || size <= 1) return;
    int curr_size;  /* size of subarrays to merge */
    int left_start; /* starting index of left subarray */

    for (curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < size - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            /* compute right end and clamp to array bounds */
            int right_end = (left_start + 2 * curr_size - 1 < size - 1) ?
                             left_start + 2 * curr_size - 1 : size - 1;
            if (mid >= size) mid = size - 1;
            // merge subarrays arr[left_start..mid] and arr[mid+1..right_end]
            merge(arr, left_start, mid, right_end);
        }
    }
}

int main()
{
    run_all_sort_tests();

    // const int size = 20;
    // const int size = 100000;
    // srand(time(NULL));
    // int *arr = (int *)malloc(sizeof(int) * size); if (!arr) return 1;
    // generate_array(arr, size);

    // int arr[] = {7, 5, 2, 2};
    // int arr[] = {7, 12, 9, 4};
    int arr[] = {9, 3, 3, 0, 0, 0, 4, 6, 3, 5};
    const int size = ARRAY_SIZE(arr);
    
    printf("Input array:\n");
    print_array(arr, size);
    double t0 = now_seconds();
    
    // bubble_sort(arr, size);
    // selection_sort(arr, size);
    // insertion_sort(arr, size);
    // recursive_quick_sort(arr, size);
    // iterative_quick_sort(arr, size);
    // counting_sort(arr, size);
    // radix_sort(arr, size);
    // recursive_merge_sort(arr, size);
    iterative_merge_sort(arr, size);
    
    double t1 = now_seconds();
    printf("Output array:\n");
    print_array(arr, size);
    printf("It toook %.6f seconds to execute\n",  t1 - t0);

    return 0;
}

/* Test harness: generate test arrays and run each sort, comparing to qsort result. */
int int_cmp_qsort(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int *copy_array_alloc(const int *src, int n) {
    int *dst = (int *)malloc(sizeof(int) * (n > 0 ? n : 1));
    if (!dst) return NULL;
    if (n > 0) memcpy(dst, src, n * sizeof(int));
    return dst;
}

int arrays_equal(const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++) if (a[i] != b[i]) return 0;
    return 1;
}

void run_single_test(const char *sort_name, sort_fn fn, const int *input, int n, int *golden_expected, int *fail_counter) {
    int *work = copy_array_alloc(input, n);
    if (!work) {
        #ifndef SILENT_TEST
        printf("%s: malloc failed\n", sort_name);
        #endif
        return;
    }

    /* run algorithm */
    fn(work, n);

    /* compare to golden_expected */
    int ok = arrays_equal(work, golden_expected, n);

#ifdef SILENT_TEST
    if (!ok) {
        printf("%-20s : FAIL\n", sort_name);
        printf("  input   : ");
        print_array((int *)input, n);
        printf("  output  : ");
        print_array(work, n);
        printf("  expected: ");
        print_array(golden_expected, n);
        if (fail_counter) { (*fail_counter)++; }
    }
#else
    printf("%-20s : %s\n", sort_name, ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("  input   : ");
        print_array((int *)input, n);
        printf("  output  : ");
        print_array(work, n);
        printf("  expected: ");
        print_array(golden_expected, n);
        if (fail_counter) { (*fail_counter)++; }
     }
#endif

    free(work);
}

void run_tests_for_all_sorts(const int *input, int n, int *fail_counter) {
    
    /* prepare golden expected using qsort */
    int *golden = copy_array_alloc(input, n);
    if (!golden) {
        printf("golden malloc failed\n");
        return;
    }
    if (n > 0) qsort(golden, n, sizeof(int), int_cmp_qsort);

    struct {
        const char *name;
        sort_fn fn;
    } sorts[] = {
        {"bubble_sort", bubble_sort},
        {"selection_sort", selection_sort},
        {"insertion_sort", insertion_sort},
        {"recursive_quick_sort", recursive_quick_sort},
        {"iterative_quick_sort", iterative_quick_sort},
        {"counting_sort", counting_sort},
        {"radix_sort", radix_sort},
        {"recursive_merge_sort", recursive_merge_sort},
        {"iterative_merge_sort", iterative_merge_sort},
    };

    int n_sorts = sizeof(sorts) / sizeof(sorts[0]);
    for (int i = 0; i < n_sorts; i++) {
        run_single_test(sorts[i].name, sorts[i].fn, input, n, golden, fail_counter);
    }

    free(golden);
}

/* A small set of deterministic test cases (non-negative values only). */
void run_all_sort_tests(void) {
    int fail_counter = 0;
#ifndef SILENT_TEST
    printf("=== Running sorting algorithm correctness tests ===\n");
#endif

    /* deterministic edge and special cases */
    const int t0[] = { }; /* empty */
    const int t1[] = { 1 }; /* single */
    const int t2[] = { 1, 2, 3, 4, 5 }; /* already sorted */
    const int t3[] = { 5, 4, 3, 2, 1 }; /* reverse */
    const int t4[] = { 3, 1, 2, 1, 3, 0 }; /* duplicates & zero */
    const int t5[] = { 7, 7, 7, 7 }; /* all equal */
    const int t6[] = { 9, 3, 3, 0, 0, 0, 4, 6, 3, 5 }; /* mixed duplicates */
    const int t7[] = { 313, 973, 720, 721, 965, 111, 222, 30, 968, 690, 397, 290, 210, 380, 181, 439, 621, 200, 169, 949 };

    run_tests_for_all_sorts(t0, 0, &fail_counter);
    run_tests_for_all_sorts(t1, ARRAY_SIZE(t1), &fail_counter);
    run_tests_for_all_sorts(t2, ARRAY_SIZE(t2), &fail_counter);
    run_tests_for_all_sorts(t3, ARRAY_SIZE(t3), &fail_counter);
    run_tests_for_all_sorts(t4, ARRAY_SIZE(t4), &fail_counter);
    run_tests_for_all_sorts(t5, ARRAY_SIZE(t5), &fail_counter);
    run_tests_for_all_sorts(t6, ARRAY_SIZE(t6), &fail_counter);
    run_tests_for_all_sorts(t7, ARRAY_SIZE(t7), &fail_counter);

    if (0 != fail_counter) {
#ifdef SILENT_TEST
        printf("FAIL %d\n", fail_counter);
#else
        printf("%d sorting algorithms failed the test.\n", fail_counter);
#endif
    } else {
#ifdef SILENT_TEST
        printf("OK\n");
#else
        printf("%d sorting algorithms failed the test.\n", fail_counter);
#endif
}

#ifndef SILENT_TEST
    printf("=== Tests completed ===\n\n");
#endif
}

