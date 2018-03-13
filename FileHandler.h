

#ifndef TAREAARREGLOSPAGINADOS_FILEWRITER_H
#define TAREAARREGLOSPAGINADOS_FILEWRITER_H


#include <string>

class FileHandler {

public:


    static void writeNumbers(std::string filename);

    static int *
    readNumbers(std::string filename, int start, int finish);

    static FILE *createTempFile();

    static FILE *openByFilename(std::string filename, std::string mode);

    static FILE * txtToBinary(FILE *file);

    static void writeNumtoBin(FILE *file, int num);

    static int *readNumbers(FILE *pFile, int start, int length);

    static void writeNumbers(FILE *file, int *arr, int page);

    static void createFinalFile(FILE *binFile);

    static long getSize(FILE *pFILE);

    static void createFinalFile(FILE *binFile, std::string filename);
};


#endif //TAREAARREGLOSPAGINADOS_FILEWRITER_H
