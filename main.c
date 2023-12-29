#include <stdio.h>
#include <stdlib.h>

// Declaring the bigint struct
typedef struct bigint
{
    unsigned int size;
    unsigned int *value;
} bigint;

// Function definitions
int cmp(bigint a, bigint b);
void print_bigint_comparision_result(bigint a, bigint b);
bigint *add(bigint a, bigint b);
bigint *create_bigint(unsigned int size);
void print_bigint(bigint *a);


// Main entry point
int main()
{
    bigint *a = create_bigint(10);
    bigint *b = create_bigint(10);
    a->value[0] = 10;
    b->value[0] = 10;
    b->value[1] = 12;
    a->value[1] = 11;

    print_bigint_comparision_result(*a, *b);
    print_bigint(add(*a, *b));
}


/// @brief Compares two bigints
/// @param a First bigint to compare
/// @param b Second bigint to compare with
/// @return Returns 1 if a > b, -1 if a < b and 0 if a == b
int cmp(bigint a, bigint b) {
    if(a.size > b.size) return 1;
    if(a.size < b.size) return -1;
    else {
        unsigned int size = a.size;
        for(unsigned int iterator = 0; iterator < size; iterator++) {
            if(a.value[iterator] > b.value[iterator]) return 1;
            if(a.value[iterator] < b.value[iterator])  return -1;
            else continue;
        }
        return 0;
    }
}

/// @brief Adds two bigints
/// @param a Value of the first big int to add
/// @param b Value of the second big int
/// @return Retunrs a new bigint pointer where a and b are added
bigint* add(bigint a, bigint b)
{
    bigint bigger_int = a.size > b.size ? a : b;

    unsigned int min_size = a.size < b.size ? a.size : b.size;
    unsigned int max_size = a.size < b.size ? b.size : a.size;

    bigint *result = create_bigint(max_size);

    for(unsigned int min_iterator = 0; min_iterator < min_size; min_iterator++) {
        unsigned int a_value_at_it = a.value[min_iterator];
        unsigned int b_value_at_it = b.value[min_iterator];

        result->value[min_iterator] = a_value_at_it + b_value_at_it;
    }

    for(unsigned int max_iterator = min_size; max_iterator < max_size; max_iterator++) {
        result->value[max_iterator] = bigger_int.value[max_iterator];
    }
    return result;
}

/// @brief Create big int with a given size
/// @param size Size of the big int
/// @return Pointer to the big int created
bigint *create_bigint(unsigned int size)
{
    bigint *new_bigint = (bigint *)malloc(sizeof(bigint));

    if (new_bigint == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_bigint->size = size;
    new_bigint->value = (unsigned int *)malloc(size * sizeof(unsigned int));

    if (new_bigint->value == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_bigint);
        exit(EXIT_FAILURE);
    }

    return new_bigint;
}

/// @brief Prints a bigint
/// @param a Pointer to the bigint to print
void print_bigint(bigint *a) {
    printf("Size: %u, Value: [", a->size);
    for (unsigned int iterator = 0; iterator < a->size; ++iterator) {
        printf("%u", a->value[iterator]);
        if (iterator < a->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void print_bigint_comparision_result(bigint a, bigint b) {
    if(cmp(a, b) > 0) printf("a is bigger than b\n");
    else if(cmp(a, b) < 0) printf("a is smaller than b\n");
    else printf("a and b are equal\n");
}