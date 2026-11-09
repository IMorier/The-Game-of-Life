#include "functions.h"
#include <string>
#include <fstream>
#include <iostream>








int main() {

	std::string fileName{};
	std::cout << "Write file name with input data for the game: ";
	std::getline(std::cin >> std::ws, fileName);
	std::ifstream fout{fileName};
	static int count{0};
	

	while (fout.is_open()) {

		readFile(fout, count);




		fout.close();
		fout.clear();
		count = 0;
		std::cout << "Write file name with input data for the next game: ";
		std::getline(std::cin >> std::ws, fileName);
		fout.open(fileName);
	}


	std::cout << "Thanks for the game!\n\n\n";




	return 0;
}






