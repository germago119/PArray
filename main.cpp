#include <iostream>
#include <vector>
#include "Sorting.h"
#include "cmdline.h"
#include "FileHandler.h"

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    cmdline::parser a;

    a.add<std::string>("input", 'i', "input file", true, "");

    a.add<std::string>("algorithm", 'a', "sort algorithm to use", true, "",
                       cmdline::oneof<std::string>("QS", "IS", "SS"));

    a.add<std::string>("output", 'o', "output file", false, "resultado.txt");

    a.parse_check(argc, argv);

    std::FILE *file = FileHandler::openByFilename(a.get<std::string>("input"), "r");

    std::FILE *binFile = FileHandler::txtToBinary(file);

    long length = FileHandler::getSize(binFile) / sizeof(int);

    PagedArray par = PagedArray(binFile);


    std::string algo = a.get<std::string>("algorithm");

    if (algo == "QS") {
        Sorting::quickSort(&par, 0, (int) (length - 1));
    } else if (algo == "SS") {
        Sorting::selectionSort(&par, (int) (length));
    } else if (algo == "IS") {
        Sorting::insertionSort(&par, (int) (length));
    }

    par.cleanup(a.get<std::string>("output"));

    return 0;
}