//
// Created by artem on 8/8/16.
//

#include "PropertiesOfNumbers.h"

namespace JacobySymbol {

	//using namespace PropertiesOfNumbers;

	int jacoby(int squareResidue, int module) {
		int value = 1;

		squareResidue = (module + squareResidue % module) % module;		//get the minimum non-negative residue

		while (squareResidue != 1) {

			if (squareResidue == module - 1) //like == -1
			{
				value *= (0 == (module - 1) / 2 % 2) ? 1 : -1;
				squareResidue = 1;
			}
			else {
				if (squareResidue % 2 == 0) {
					int sign = (0 == (module * module - 1) / 8 % 2) ? 1 : -1;

					do {
						value *= sign;
						squareResidue >>= 1;
					} while (squareResidue % 2 == 0);
				}

				std::swap(squareResidue, module);
				value *= (0 == (module - 1) / 2 * (squareResidue - 1) / 2 % 2) ? 1 : -1;
			}

			squareResidue = (module + squareResidue % module) % module;		//get the minimum non-negative residue
		}

		return value;
	}

	int getValueJacobySymbol(int squareResidue, int module) {
		int jacobySymbol;

		if (module >= 2) {
			squareResidue = (module + squareResidue % module) % module;		//get the minimum residue

			if (module == 2)
				jacobySymbol = (squareResidue == 0) ? 0 : 1;
			else if (PropertiesOfNumbers::gcdByEuclid(squareResidue, module) > 1) {
				std::cout << "Error: numbers must be prime one another" << std::endl;
				jacobySymbol = 0;
			}
			else
				jacobySymbol = jacoby(squareResidue, module);
		}
		else {
			std::cout << "Error: Incorrect module (getValueJacobySymbol)" << std::endl;
			jacobySymbol = -2;
		}

		return jacobySymbol;
	}

}