#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <sstream>

class SimpleCPU1 {

	//Registers
	int regA;
	int programCounter;

public:

	//Memory space
	std::string* cpuMemory;



	//Constructors
	SimpleCPU1() {

		cpuMemory = new std::string[16];
		programCounter = 0;

		for (int i = 0; i < 16; i++) {
			cpuMemory[i] = "";
		}


	}

	SimpleCPU1(int totalMemory) {

		cpuMemory = new std::string[totalMemory];
		programCounter = 0;

		for (int i = 0; i < totalMemory; i++) {
			cpuMemory[i] = "";
		}

	}


	//Functions



	bool BRK() {

		return true;

	}

	void LDA(int numberInMemory, bool literalValue, bool hexValue) {
		
		if (literalValue == true)
			regA = numberInMemory;

		else
			regA = std::stoi(cpuMemory[numberInMemory]);

		programCounter++;
	}



	void ADA(int numberInMemory, bool literalValue, bool hexValue) {
		
		if (literalValue == true)
		regA += numberInMemory;

			
		else
			regA =+ std::stoi(cpuMemory[numberInMemory]);

			programCounter += 2;
	}



	void STA(int numberInMemory, bool literalValue, bool hexValue) {

		cpuMemory[numberInMemory] = std::to_string(regA);
		

		programCounter += 2;

	}



	void alterAddresses(int n, std::string string) {

		cpuMemory[n] = string;

	}

	void printAddresses() {

		for (int i = 0; i < 16; i++) {
			
			if (cpuMemory[i] == "")
			std:: cout << "NULL\n";
			
			else
				std::cout << cpuMemory[i] << "\n";

		}

	}

	void checkLiteralsAndHexes(std::string memoryContent, bool& literalValue, bool&hexValue, int &pointWhereNumbersBegin) {
		
		
		std::string stringPlaceholder = "";
		//literal value
		if (memoryContent.substr(4, 1) == "#")
			literalValue = true;

		//Hex values
		if ((memoryContent.substr(4, 1) == "$") || (memoryContent.substr(5, 1) == "$"))
			hexValue = true;

			
		if (literalValue == true && hexValue == true)
			stringPlaceholder = memoryContent.substr(6);
		
		else if ((literalValue == true && hexValue == false) || (literalValue == false && hexValue == true))
			stringPlaceholder =  memoryContent.substr(5);
		
		else if (literalValue == false && hexValue == false)
			stringPlaceholder =  memoryContent.substr(4);
			
			pointWhereNumbersBegin = std::stoi(stringPlaceholder);
			
	}

	void callOperations() {
		
		
		bool endProgram = false;
		bool literalValue;
		bool hexValue;
		int pointWhereNumbersBegin = 0;
		std::string memoryContent;
		
		for (int i = 0; endProgram == !true; i++){
			
			memoryContent = cpuMemory[i];
			literalValue = false;
			hexValue = false;
			
		std::string opCode = memoryContent.substr(0, 3);
				
		if (opCode == "LDA") {
			
			checkLiteralsAndHexes(memoryContent, literalValue, hexValue, pointWhereNumbersBegin);
			LDA(pointWhereNumbersBegin, literalValue, hexValue);
			
		}

		else if (opCode == "ADA") {

			checkLiteralsAndHexes(memoryContent, literalValue, hexValue, pointWhereNumbersBegin);
			ADA(pointWhereNumbersBegin, literalValue, hexValue);

		}

		else if (opCode == "STA") {

			checkLiteralsAndHexes(memoryContent, literalValue, hexValue, pointWhereNumbersBegin);
			STA(pointWhereNumbersBegin, literalValue, hexValue);

		}

		else if (opCode == "BRK") {
			endProgram = BRK();
		}

	}
	
	}

};




int main(int argc, char **argv)
{

	SimpleCPU1 firstCPU;

	firstCPU.alterAddresses(0, "LDA #100");
	firstCPU.alterAddresses(1, "ADA #7");
	firstCPU.alterAddresses(2, "STA 15");
	firstCPU.alterAddresses(3, "BRK");

	firstCPU.printAddresses();

	firstCPU.callOperations();

	firstCPU.printAddresses();

	return 0;
}

