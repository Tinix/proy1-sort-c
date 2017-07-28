#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "sort.h"

struct minp_data {
    unsigned long int comps;
    unsigned int minp;
};

struct piv_data {
    unsigned long int comps;
    unsigned long int swaps;
    unsigned int piv;
};

bool array_is_sorted(int *a, unsigned int length) {
    bool result = true;
    unsigned int i = 0;

    while (result && i + 1 < length) {
        result = a[i] <= a[i + 1];
        i += 1;
    }

    return (result);
}

bool odd_even_order(int n, int m) {
    bool result = false;

    if (n % 2 == 1 || (-n) % 2 == 1) {
        result = (m % 2 == 0) || n <= m;
    } else if (n % 2 == 0 || (-n) % 2 == 0) {
        result = (m % 2 == 0) && n <= m;
    }

    return (result);
}

bool array_is_odd_even_sorted(int *a, unsigned int length) {
    bool result = true;
    unsigned int i = 0;

    while (result && i + 1 < length) {
        result = odd_even_order(a[i], a[i + 1]);
        i += 1;
    }

    return (result);
}

void swap(int *a, unsigned int i, unsigned int j) {
/*
    Swap the value at position 'i' with the value at position 'j' in the
    array 'a'. The values 'i' and 'j' must be valid positions in the array.

*/
    int temp = 0;

    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

struct minp_data min_pos_from(int *a, unsigned int length, unsigned int i) {
/*
    Return the position of the minimum value in the array 'a' starting
    at position 'i'. The array 'a' must have exactly 'length' elements,
    and 'i' must be a valid position in the array.

*/
    struct minp_data result;
    result.comps = 0;
    result.minp = 0;

    result.minp = i;
    for (unsigned int j = i + 1; j < length; j++) {
        if (a[j] < a[result.minp]) {
            result.minp = j;
        }
        result.comps += 1;
    }

    return (result);
}

struct sorting_stats selection_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    struct sorting_stats result;
    result.comps = 0;
    result.swaps = 0;
    struct minp_data count;
    count.comps = 0;
    count.minp = 0;

    for (unsigned int i = 0; i + 1 < length; i++) {
        count = min_pos_from(a, length, i);
        result.comps += count.comps;
        swap(a, i, count.minp);
        result.swaps += 1;
    }

    /* Check postconditions */
    assert(array_is_sorted(a, length));

    return (result);
}

struct sorting_stats insertion_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    unsigned int j = 0;
    struct sorting_stats result;
    result.comps = 0;
    result.swaps = 0;

    for (unsigned int i = 1; i < length; i++) {
        j = i;
        while (j > 0 && a[j] < a[j - 1]) {
            result.comps += 1;
            swap(a, j - 1, j);
            result.swaps += 1;
            j -= 1;
        }
        if (j > 0) {
            result.comps += 1;
        }
    }

    /* Check postconditions */
    assert(array_is_sorted(a, length));

    return (result);
}

struct piv_data pivot(int *a, int left, int right, bool random) {
    unsigned int i = 0, j = 0;
    struct piv_data result;
    result.comps = 0;
    result.swaps = 0;
    result.piv = 0;

    if (random) {
        /* entre M y N  -->  rand() % (N-M+1) + M
           entre left y right ... */
        result.piv = (rand() % (right - left + 1)) + left;
        swap(a, left, result.piv);
        result.swaps += 1;
    }
    result.piv = left;
    i = left + 1;
    j = right;
    while (i <= j) {
        if (a[i] < a[result.piv]) {
            result.comps += 1;
            i += 1;
        } else if (a[j] > a[result.piv]) {
            result.comps += 2;
            j -= 1;
        } else {
            result.comps += 2;
            swap(a, i, j);
            result.swaps += 1;
            i += 1;
            j -= 1;
        }
    }
    swap(a, result.piv, j);
    result.swaps += 1;
    result.piv = j;

    return (result);
}

struct piv_data recursive_quick_sort(int *a, unsigned int length, int left,
                                     int right, bool random) {
    struct piv_data result;
    result.comps = 0;
    result.swaps = 0;
    result.piv = 0;
    struct piv_data rec1;
    rec1.comps = 0;
    rec1.swaps = 0;
    rec1.piv = 0;
    struct piv_data rec2;
    rec2.comps = 0;
    rec2.swaps = 0;
    rec2.piv = 0;

    if (right > left) {
        result = pivot(a, left, right, random);
        rec1 = recursive_quick_sort(a, length, left, result.piv - 1, random);
        rec2 = recursive_quick_sort(a, length, result.piv + 1, right, random);
        result.comps += rec1.comps + rec2.comps;
        result.swaps += rec1.swaps + rec2.swaps;
    }

    return (result);
}

struct sorting_stats quick_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    struct sorting_stats result;
    struct piv_data count;

    count = recursive_quick_sort(a, length, 0, (int)length - 1, false);
    result.comps = count.comps;
    result.swaps = count.swaps;

    /* Check postconditions */
    assert(array_is_sorted(a, length));

    return (result);
}

struct sorting_stats rand_quick_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    struct sorting_stats result;
    struct piv_data count;

    srand(time(NULL));
    count = recursive_quick_sort(a, length, 0, (int)length - 1, true);
    result.comps = count.comps;
    result.swaps = count.swaps;

    /* Check postconditions */
    assert(array_is_sorted(a, length));

    return (result);
}

struct sorting_stats bubble_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    unsigned int i = 0;
    bool swapped = true;
    struct sorting_stats result;
    result.comps = 0;
    result.swaps = 0;

    while (swapped && i + 1 < length) {
        swapped = false;
        for (unsigned int j = length - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                swap(a, j - 1, j);
                result.swaps += 1;
                swapped = true;
            }
            result.comps += 1;
        }
        i += 1;
    }

    /* Check postconditions */
    assert(array_is_sorted(a, length));

    return (result);
}

struct sorting_stats odd_even_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    unsigned int j = 0;
    struct sorting_stats result;
    result.comps = 0;
    result.swaps = 0;

    for (unsigned int i = 1; i < length; i++) {
        j = i;
        while (j > 0 && !odd_even_order(a[j - 1], a[j])) {
            result.comps += 1;
            swap(a, j - 1, j);
            result.swaps += 1;
            j -= 1;
        }
        if (j > 0) {
            result.comps += 1;
        }
    }

    /* Check postconditions */
    assert(array_is_odd_even_sorted(a, length));

    return (result);
}
