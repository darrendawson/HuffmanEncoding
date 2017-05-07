// quicksort.h - quicksort interface

# ifndef _QuickSort
# define _QuickSort

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

int partition(uint32_t *, int, int, int *, int *);

void quickSort(uint32_t *, int, int, int *, int *);

# endif
