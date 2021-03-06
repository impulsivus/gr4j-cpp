#include "FileReader.h"

FileReader::FileReader(char *filename)
{
    this->filename = filename;
}
FILE *FileReader::openFile()
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return NULL;
    }
    return file;
}
void FileReader::closeFile(FILE *file)
{
    fclose(file);
}
std::vector<long double> FileReader::readFile()
{
    std::vector<long double> data;
    long double q;
    FILE *file = openFile();
    long double i;
    while ((i = fscanf(file, "%Lf", &q)) != EOF)
    {
        data.emplace_back(q);
    }
    closeFile(file);
    return data;
}