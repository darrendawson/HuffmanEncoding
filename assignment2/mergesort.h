// mergesort.h - mergesort interface

# ifndef _MergeSort
# define _MergeSort

# include <stdint.h>
# include <stdlib.h>


void merge(uint32_t *, uint32_t *, uint32_t *, int, int, int *, int *);

void assignValues(uint32_t *, uint32_t *, int, int, int *);

void mergeSort(uint32_t *, int, int*, int*);

# endif
