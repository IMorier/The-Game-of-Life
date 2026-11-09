#include "functions.h"
#include <string>
#include <fstream>
#include <iostream>


void readFile(std::ifstream& fout, int& count) {
	int rows{}, columns{};
	fout >> rows >> columns;
	int size{ countArrSize(fout) };
	if (size == 0) {
		char** generationsArr{ createGenerationsArr(rows, columns) };
		showGeneration(generationsArr, rows, columns, size, count);
		std::cout << "All cells are dead. Game over.\n";
		deleteGenerationsArr(generationsArr, rows);
		return;
	}

	while (fout.get() != '\n') continue;
	char** generationsArr{ createGenerationsArr(rows, columns) };
	int* lifeArr{ createLifeArr(size) };
	fileFillArr(fout, lifeArr, size);
	fillGenerationsArr(generationsArr, lifeArr, size);
	showGeneration(generationsArr, rows, columns, size, count);
	int* lifeArr1{ copyLifeArr(lifeArr, size) };
	int size1{ size };

	size = newGeneration(generationsArr, lifeArr, size, rows, columns);
	showGeneration(generationsArr, rows, columns, size, count);
	
	while (size != 0 && compareLifeArr(lifeArr, lifeArr1, size, size1)) {

		int* temp{ lifeArr1 };
		lifeArr1 = copyLifeArr(lifeArr, size);
		size1 = size;
		deleteLifeArr(temp);


		size = newGeneration(generationsArr, lifeArr, size, rows, columns);
		showGeneration(generationsArr, rows, columns, size, count);
	}

	if (size == 0) {
		std::cout << "All cells are dead. Game over.\n";
		deleteGenerationsArr(generationsArr, rows);
		deleteLifeArr(lifeArr);
		deleteLifeArr(lifeArr1);
		return;
	}

	std::cout << "The world has stagnated. Game over.\n";
	deleteGenerationsArr(generationsArr, rows);
	deleteLifeArr(lifeArr);
	deleteLifeArr(lifeArr1);
}


int countArrSize(std::ifstream& fout) {
	int size{0};
	std::string dummy{};
	while (std::getline(fout, dummy)) {
		++size;
	}
	fout.clear();
	fout.seekg(0, std::ios::beg);
	return size;
}

void fileFillArr(std::ifstream& fout, int* arr, const int size) {
	for (int i{ 0 }; i < size; ++i) {
		fout >> arr[i * 2 + 0] >> arr[i * 2 + 1];
	}
}





int* createLifeArr(const int size) {
	int* arr{ new int [size * 2] {} };
	return arr;
}

void deleteLifeArr(int* arr) {
	delete[] arr;
}

int* copyLifeArr(const int* lifearr, const int size) {
	int* temp{ createLifeArr(size) };
	for (int i{ 0 }; i < size; ++i) {
		temp[i * 2 + 0] = lifearr[i * 2 + 0];
		temp[i * 2 + 1] = lifearr[i * 2 + 1];
	}
	return temp;
}





char** createGenerationsArr(const int rows, const int columns) {
	char** arr{ new char* [rows] {} };
	for (int i{ 0 }; i < rows; ++i) {
		arr[i] = new char [columns] {};
		for (int j{ 0 }; j < columns; ++j) {
			arr[i][j] = '-';
		}
	}
	return arr;
}

void deleteGenerationsArr(char** arr, const int rows) {
	for (int i{ 0 }; i < rows; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
}

void fillGenerationsArr(char** arr, const int* arr1, const int size) {
	for (int i{ 0 }; i < size; ++i) {
		arr[arr1[i * 2 + 0]][arr1[i * 2 + 1]] = '*';
	}
}



void showGeneration(char** arr, const int rows, const int columns, const int size, int& count) {
	for (int i{ 0 }; i < rows; ++i) {
		for (int j{ 0 }; j < columns; ++j) {
			std::cout << arr[i][j] << (j + 1 < columns ? ' ' : '\n');
		}
	}
	std::cout << "Generation: " << ++count << ". Alive cells: " << size << '\n';
}



int newGeneration(char** generationArr, int*& lifeArr, const int size, const int rows, const int columns) {
	int newSize{ size };
	int count{};
	for (int i{ 0 }; i < size; ++i) {
		count = countLife(generationArr, rows, columns, lifeArr[i * 2 + 0], lifeArr[i * 2 + 1]);
		if (count == 3 || count == 2) {
			lifeArr[i * 2 + 0] = -1;
			lifeArr[i * 2 + 1] = -1;
		}
	}
	int* temp{ createLifeArr(rows * columns) };
	int num{ 0 };
	for (int i{ 0 }; i < rows; ++i) {
		for (int j{ 0 }; j < columns; ++j) {
			if (generationArr[i][j] == '*') continue;
			count = countLife(generationArr, rows, columns, i, j);
			if (count == 3) {
				temp[num * 2 + 0] = i;
				temp[num * 2 + 1] = j;
				++num;
				++newSize;
			}
		}
	}
	for (int i{ 0 }; i < num; ++i) {
		generationArr[temp[i * 2 + 0]][temp[i * 2 + 1]] = '*';
	}
	deleteLifeArr(temp);
	for (int i{ 0 }; i < size; ++i) {
		if (lifeArr[i * 2 + 0] < 0) continue;
		generationArr[lifeArr[i * 2 + 0]][lifeArr[i * 2 + 1]] = '-';
		--newSize;
	}
	newLifeArr(generationArr, rows, columns, lifeArr, newSize);
	return newSize;
}

int countLife(char** generationArr, const int rows, const int columns, const int i, const int j) {
	int count{0};
	for (int a{ i - 1 }; a <= i + 1; ++a) {
		if (a < 0 || a >= rows) continue;
		for (int b{ j - 1 }; b <= j + 1; b++) {
			if (b < 0 || b >= columns) continue;
			if (a == i && b == j) continue;
			if (generationArr[a][b] == '*') ++count;
		}
	}
	return count;
}


void newLifeArr(char** generationArr, const int rows, const int columns, int*& lifeArr, const int size) {
	int* newLifeArr{ createLifeArr(size) };
	int* temp = lifeArr;
	lifeArr = newLifeArr;
	deleteLifeArr(temp);
	int num{ 0 };
	for (int i{ 0 }; i < rows; ++i) {
		for (int j{ 0 }; j < columns; ++j) {
			if (generationArr[i][j] == '*') {
				lifeArr[num * 2 + 0] = i;
				lifeArr[num * 2 + 1] = j;
				++num;
			}
		}
	}
}


bool compareLifeArr(const int* arr1, const int* arr2, const int size1, const int size2) {
	if (size1 != size2) return true;
	for (int i{ 0 }; i < size1; ++i) {
		if (arr1[i * 2 + 0] != arr2[i * 2 + 0] || arr1[i * 2 + 1] != arr2[i * 2 + 1]) return true;
	}
	return false;
}
