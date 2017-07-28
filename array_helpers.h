#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>


bool file_exists(const char *filepath);
/* Return whether the file at 'filepath' exists or not. */

bool array_is_valid(int *a, unsigned int length);
/*
    Return whether the array 'a' is correctly represented by the given pointer.

    An array representation is valid either if:
        * the 'length' is 0 and the pointer 'a' is NULL
        * the 'length' is not 0 and the pointer 'a' is not NULL

 */

bool array_is_equal(int *a, int *other, unsigned int length);
/*
    Return whether the array 'a' is equal to array 'other'.

    The arrays 'a' and 'other' must have both the same 'length'.

*/

bool array_has_value(int *a, unsigned int length, int value);
/* Return whether 'value' is in the array 'a'. */

unsigned int array_value_count(int *a, unsigned int length, int value);
/* Return how many ocurrences of 'value' exist in the array 'a'. */

bool array_is_permutation_of(int *a, int *other, unsigned int length);
/*
    Return whether the array 'other' is a permutation of the array 'a'.

    The arrays 'a' and 'other' must have both the same 'length'.

*/

int *array_create(unsigned int length);
/* Return a newly allocated array with 'length' zeroed members. */

int *array_destroy(int *a);
/*
    Destroy the resources used by the array 'a'. The array 'a' must be the
    result of calling 'array_create', 'array_duplicate' or 'array_from_file'.

*/

void array_dump(int *a, unsigned int length);
/*

    Write the content of the array 'a' into stdout. The array 'a' must have
    exactly 'length' elements.

    The format of this dump is the same as the expected format in
    'array_length_from_file' and 'array_from_file'.

*/

int *array_duplicate(int *a, unsigned int length);
/* Return a newly allocated array which is the exact copy of the array 'a'. */

int *array_from_file(const char *filepath, unsigned int *array_length);
/*
    Return a newly created array with 'array_length' integer elements.
    The returned array is owned by the caller, so when the caller has
    finished using it, the array  must be released by calling 'array_destroy'.

    Each element is read from the file located at 'filepath'.
    The file must exist in disk and must have its contents in the following
    format:

    <array_length>
    <array_elem_1> <array_elem_2> <array_elem_3> ... <array_elem_N>

    In other words, the first line must be the array length, and the next line
    must contain 'length' amount of elements separated by one or more
    blank characters.

*/

#endif
