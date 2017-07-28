#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"


bool file_exists(const char *filepath) {
    bool result = false;
    FILE *file = NULL;

    assert(filepath != NULL);

    file = fopen(filepath, "r");

    result = (file != NULL);
    if (result) {
        fclose(file);
    }

    return (result);
}

bool array_is_valid(int *a, unsigned int length) {
    return ((length == 0 && a == NULL) || (length != 0 && a != NULL));
}

bool array_is_equal(int *a, int *other, unsigned int length) {
    bool result = true;
    unsigned int i = 0;

    if (length == 0) {
        result = (a == NULL && other == NULL);
    } else {
        /* if length is not zero, none of the arrays should be NULL */
        result = (a != NULL && other != NULL);
        for (i = 0; result && i < length; i++) {
            result = (a[i] == other[i]);
        }
    }

    return (result);
}

bool array_has_value(int *a, unsigned int length, int value) {
    bool result = false;
    unsigned int i = 0;

    assert(array_is_valid(a, length));

    for (i = 0; i < length; i++) {
        result = result || (a[i] == value);
    }

    return (result);
}

unsigned int array_value_count(int *a, unsigned int length, int value) {
    unsigned int i = 0, result = 0;

    assert(array_is_valid(a, length));

    for (i = 0; i < length; i++) {
        if (a[i] == value) {
            result += 1;
        }
    }

    return (result);
}

bool array_is_permutation_of(int *a, int *other, unsigned int length) {
    bool result = true;
    unsigned int i = 0, a_count = 0, other_count = 0;

    assert(array_is_valid(a, length));
    assert(array_is_valid(other, length));

    for (i = 0; i < length; i++) {
        /* a[i] is also present in 'other' */
        result = result && array_has_value(other, length, a[i]);

        /* courrences of a[i] in 'a' match those in 'other' */
        a_count = array_value_count(a, length, a[i]);
        other_count = array_value_count(other, length, a[i]);
        result = result && (a_count == other_count);
    }

    return (result);
}

int *array_create(unsigned int length) {
    int *result = NULL;

    if (length > 0) {
        result = calloc(length, sizeof(int));
        assert(result != NULL);
    }

    return (result);
}

int *array_destroy(int *a) {
    free(a);
    a = NULL;
    return (a);
}

void array_dump(int *a, unsigned int length) {
    unsigned int i = 0;

    assert(array_is_valid(a, length));

    fprintf(stderr, "%u\n", length);
    for (i = 0; i < length; i++) {
        fprintf(stderr, "%i", a[i]);
        if (i < length - 1) {
            fprintf(stderr, " ");
        } else {
            fprintf(stderr, "\n");
        }
    }
}

int *array_duplicate(int *a, unsigned int length) {
    unsigned int i = 0;
    int *result = NULL;

    assert(array_is_valid(a, length));

    result = array_create(length);
    for (i = 0; i < length; i++) {
        result[i] = a[i];
    }

    assert(array_is_valid(result, length));
    assert(array_is_equal(a, result, length));

    return (result);
}

int *array_from_file(const char *filepath, unsigned int *array_length) {
    int fscanf_result = 0;
    unsigned int i = 0, length = 0;
    int *result = NULL;
    FILE *file = NULL;

    /* Check preconditions */
    assert(file_exists(filepath));

    result = array_create(length);

    file = fopen(filepath, "r");
    assert(file != NULL);

    /* read the array length, first line of the file */
    fscanf_result = fscanf(file, " %u \n", array_length);
    if (fscanf_result != 1) {
        printf("The file does not have the correct format for the array "
               "length.\n");
        exit(EXIT_FAILURE);
    }

    length = *array_length;
    /* create the array for the given length */
    result = array_create(length);

    for (i = 0; i < length; i++) {
        fscanf_result = fscanf(file, " %i ", &(result[i]));
        if (fscanf_result != 1) {
            printf("The file does not have the correct format for"
                   " the array elements.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    assert(array_is_valid(result, length));

    return (result);
}
