

#ifndef TAREAARREGLOSPAGINADOS_PAGEDARRAY_H
#define TAREAARREGLOSPAGINADOS_PAGEDARRAY_H

#include <string>


class PagedArray {
public:
    int *getPage(int page);

    int *loadPage(int where, int which);

    int freePage();

    void cleanup(std::string filename);


    int& operator[](int index);

    PagedArray(FILE* binFile);
};


#endif //TAREAARREGLOSPAGINADOS_PAGEDARRAY_H
