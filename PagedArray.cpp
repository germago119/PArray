

#include <cmath>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "PagedArray.h"
#include "FileHandler.h"
#include <string>


const int PAGESIZE = 256;
const int NUMPAGES = 6;

int *pageContainer[NUMPAGES];

int lastAccessed = -1;

int loadedPages[NUMPAGES] = {-1, -1, -1, -1, -1, -1};

int accessNumbers[NUMPAGES] = {0, 0, 0, 0, 0, 0};

std::FILE *file;

/**
 * Constructor for the class
 * @param binFile The binary file pointer to be used in the PagedArray
 */
PagedArray::PagedArray(std::FILE *binFile) {
    file = binFile;

    int i;
    for (i = 0; i < NUMPAGES; i++) {
        pageContainer[i] = (int *) malloc(PAGESIZE * sizeof(int));
        std::fill_n(pageContainer[i], PAGESIZE, -1);
    }

}

/**
 * Gets a page, lods from disk if necesssary
 * @param page Int number of page
 * @return The page array pointer
 */
int *PagedArray::getPage(int page) {

    int i;
    for (i = 0; i < NUMPAGES; i++) {
        if (loadedPages[i] == page) {
            //printf ("Page %d is already on slot %d\n", page, i);
            //printf("LoadedPages: %d %d %d %d %d %d\n", loadedPages[0], loadedPages[1], loadedPages[2], loadedPages[3], loadedPages[4], loadedPages[5]);
            //printf("AccessedPages: %d %d %d %d %d %d\n", accessNumbers[0], accessNumbers[1], accessNumbers[2], accessNumbers[3], accessNumbers[4], accessNumbers[5]);

            lastAccessed = page;
            accessNumbers[i] += 1;
            return pageContainer[i];
        }
    }

    int whereToLoad = freePage();
    accessNumbers[whereToLoad] = 0;
    return loadPage(whereToLoad, page);
}


/**
 * Overloads the [] operator
 * @param index The index to be used for the [] operator
 * @return The value on the requested index
 */
int &PagedArray::operator[](int index) {
    int pageToGet = (int) floor(index / PAGESIZE);
    int position = index % PAGESIZE;

    int *page = getPage(pageToGet);

    return page[position];
}


/**
 * Loads a page from disk into memory
 * @param where In which slot to load the page
 * @param which Which page to load
 * @return The loaded page array pointer
 */
int *PagedArray::loadPage(int where, int which) {
    int *loadedPage = FileHandler::readNumbers(file, which * PAGESIZE, PAGESIZE);
    pageContainer[where] = loadedPage;
    loadedPages[where] = which;

    //printf ("Loaded page %d on slot %d\n", which, where);

    return loadedPage;

}

/**
 * Replacement algorithm, decides which page to free
 * @return The page array of the newly allocated page in memory
 */
int PagedArray::freePage() {

    int toReplace = 0;
    int maxValue = -1;

    //printf("Last accessed is: %i\n", lastAccessed);
    //printf("LoadedPages: %d %d %d %d %d %d\n", loadedPages[0], loadedPages[1], loadedPages[2], loadedPages[3], loadedPages[4], loadedPages[5]);
    //printf("AccessedPages: %d %d %d %d %d %d\n", accessNumbers[0], accessNumbers[1], accessNumbers[2], accessNumbers[3], accessNumbers[4], accessNumbers[5]);


    int i;
    for (i = 0; i < NUMPAGES; i++) {

        if (loadedPages[i] == -1) {
            toReplace = i;
            break;
        }
        if (loadedPages[i] == lastAccessed)
            continue;

        if (accessNumbers[i] >= maxValue) {
            toReplace = i;
            maxValue = accessNumbers[i];
        }
    }

    FileHandler::writeNumbers(file, pageContainer[toReplace], loadedPages[toReplace]);
    delete (pageContainer[toReplace]);
    loadedPages[toReplace] = -1;

    //printf ("Will free slot: %d\n", toReplace);

    return toReplace;

}

/**
 * Prepares to exit the program by writing all pages to disk
 * @param filename The final output filename
 */
void PagedArray::cleanup(std::string filename) {
    int i;
    for (i = 0; i < NUMPAGES; i++) {
        if (loadedPages[i] != -1)
            FileHandler::writeNumbers(file, pageContainer[i], loadedPages[i]);
    }

    FileHandler::createFinalFile(file, filename);
}