cmake_minimum_required(VERSION 3.5)
project(CryptographyMain)

set(SOURCE_FILES
        numberPropertiesAlgorithms/PropertiesOfNumbers.cpp
        numberPropertiesAlgorithms/JacobySymbol.cpp
        CryptographyMath.h
        vectorExtraFuncs/OutputVector.h
        monicPolynomial/Polynom.h
        complexNumbers/Complex.h
        finiteField/FiniteField.h
        main_crypto.cpp
        numberPropertiesAlgorithms/PropertiesOfNumbers.h
        finiteField/FieldElement.h vectorExtraFuncs/VectorArithmetics.h algebraInterfaces/IAlgebra.h polymorphicTypeCasting/SharedPolymPtr.h)

add_executable(runCryptographyMain ${SOURCE_FILES})

