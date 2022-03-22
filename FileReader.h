#include <vector>

class FileReader
{
    char *filename;

public:
    FileReader(char *filename);
    FILE *openFile();
    void closeFile(FILE *file);
    std::vector<long double> readFile();
};