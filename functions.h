#ifndef FUNCTIONS_30102026_H
#define FUNCTIONS_30102026_H

#include <fstream>

void readFile(std::ifstream& fout, int& count);
int countArrSize(std::ifstream& fout);
int* createLifeArr(const int size);
void deleteLifeArr(int* arr);
char** createGenerationsArr(const int rows, const int columns);
void deleteGenerationsArr(char** arr, const int rows);
void showGeneration(char** arr, const int rows, const int columns, const int size, int& count);
void fileFillArr(std::ifstream& fout, int* arr, const int size);
void fillGenerationsArr(char** arr, const int* arr1, const int size);
int countLife(char** generationArr, const int rows, const int columns, const int i, const int j);
void newLifeArr(char** generationArr, const int rows, const int columns, int*& lifeArr, const int size);
int newGeneration(char** generationArr, int*& lifeArr, const int size, const int rows, const int columns);
bool compareLifeArr(const int* arr1, const int* arr2, const int size1, const int size2);
int* copyLifeArr(const int* lifearr, const int size);


#endif