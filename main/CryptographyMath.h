//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_CRYPTO_H
#define CRYPTOGRAPHY_CRYPTO_H

#include <vector>
#include <iostream>
#include "vectorExtraFuncs/OutputVector.h"
#include "complexNumbers/Complex.h"
#include "finiteField/FiniteField.h"
#include "monicPolynomial/Polynom.h"

using namespace FiniteField;
using namespace MonicPolynomial;

namespace CryptographyMath {

	int mainCrypto(int argc, char * argv[]);

}


#endif //CRYPTOGRAPHY_CRYPTO_H
