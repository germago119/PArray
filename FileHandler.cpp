
#include "FileHandler.h"
#include <iostream>
#include <fstream>

using namespace std;



/**
 * Checks if a file exists
 * @param fileName The filename to look for
 * @return boolean If file exists
 */
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

/**
 * Creates a temporary binary file
 * @return The temporary file pointer
 */
std::FILE* FileHandler::createTempFile() {
   std::FILE* tmpf = std::tmpfile();
    return tmpf;
}

/**
 * Opens a file by filename
 * @param filename The file to be opened
 * @param mode The mode for fopen
 * @return The file pointer
 */
std::FILE* FileHandler::openByFilename(string filename, string mode) {

    std::FILE *pFile;
    // It checks if the file exists first and THEN tries to open the file. The other way around would create the file.

    if (!is_file_exist(filename.c_str()) || (pFile = std::fopen(filename.c_str(), mode.c_str())) == NULL)  {
        cout << "Couldn't open file: " + filename << endl;
        exit(101);
    };


    return pFile;
}

/**
 * Converts a comma-separated list of integers on a text file to a binary file
 * @param file The input file pointer
 * @return The output file pointer
 */
std::FILE* FileHandler::txtToBinary(std::FILE* file) {

    int charCode;
    std::fseek(file, 0, SEEK_SET);

    string tmpNum;

    std::FILE *binFile = FileHandler::createTempFile();

    while ((charCode = std::fgetc(file)) != EOF) {

        char charData = (char) charCode;

        if (charCode == 44 || charCode == 32) { // Check if it's a comma (ascii code 44) or space (code 32)

            try {

                FileHandler::writeNumtoBin(binFile, std::stoi(tmpNum));

            } catch(std::invalid_argument&) {
                std::cout << "The input file contains invalid data" << std::endl;
                exit(102);
            }


            tmpNum = "";
            continue;
        }

        tmpNum += charData;

    }

    if (tmpNum != "") {
        FileHandler::writeNumtoBin(binFile, std::stoi(tmpNum));
    }


    return binFile;

}

/**
 * Writes a number to the binary file
 * @param file The binary file to write to
 * @param num The number to write
 */
void FileHandler::writeNumtoBin(std::FILE* file, int num) {

    std::fseek(file, 0, SEEK_END);

    std::fwrite(&num, sizeof(int), 1, file);
}

/**
 * Writes an array of numbers to the binary file
 * @param file The binary file to write to
 * @param arr The pointer of the integer array
 * @param page The number of the page to be written
 */
void FileHandler::writeNumbers(std::FILE* file, int* arr, int page) {

    if (page == -1)
        return;

    int arrSize = 256;

    //printf("Will save page %d\n", page);
    //printf("The arrsize is %d\n", arrSize);


    std::fseek(file, sizeof(int) * page * arrSize, SEEK_SET);


    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == -1)
            continue;

        //cout << arr[i] << endl;
        std::fwrite(&arr[i], sizeof(int), 1, file);
    }


}

/**
 * Prepares to exit the software by creating the final text file
 * @param binFile The final binary file to be used as input
 * @param filename The final text file as output
 */
void FileHandler::createFinalFile(std::FILE* binFile, std::string filename) {
    std::FILE* pFile = std::fopen(filename.c_str(), "wb");
    std::fclose(pFile);

    std::ofstream out(filename.c_str());


    std::fseek(binFile, 0L, SEEK_END);
    long size = ftell(binFile);

    std::fseek(binFile, 0, SEEK_SET);

    int length = size / sizeof(int);

    for (int i = 0; i < length; i++){
        int result;

        std::fread(&result, sizeof(int), 1, binFile);
        out << result;

        if (i+1 < length)
            out << ",";
    }




}


/**
 * Reads an array of numbers from the binary file
 * @param pFile The binary file pointer
 * @param start Position to start reading data from
 * @param length The length of data to be read
 * @return The array of integers read from the file
 */
int *FileHandler::readNumbers(std::FILE *pFile, int start, int length) {

    // Must be in heap because of the non-constant array size.
    static int* result;
    result = (int*) malloc(length * sizeof(int));
    std::fill_n(result, length, -1);



    std::fseek(pFile, sizeof(int) * start, SEEK_SET);



    for (int i = 0; i < length; i++){
        std::fread(&result[i], sizeof(int), 1, pFile);
    }


    return result;
}

/**
 * Gets the size of a file
 * @param binFile The file pointer
 * @return long The file size
 */
long FileHandler::getSize(FILE *binFile) {
    std::fseek(binFile, 0L, SEEK_END);
    long size = ftell(binFile);

    std::fseek(binFile, 0, SEEK_SET);

    return size;
}
