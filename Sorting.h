

#ifndef TAREAARREGLOSPAGINADOS_QUICKSORT_H
#define TAREAARREGLOSPAGINADOS_QUICKSORT_H


#include "PagedArray.h"

class Sorting {
public:


    static void quickSort(PagedArray *arr, int left, int right);

    static void insertionSort(PagedArray *arr, int length);

    static void selectionSort(PagedArray *arr, int n);
};


#endif //TAREAARREGLOSPAGINADOS_QUICKSORT_H
