cmake_minimum_required(VERSION 3.5)
project(CryptographyMain)

set(SOURCE_FILES
        other_funcs.cpp
        jacobySymbol/propertiesOfNumbers.cpp
        jacobySymbol/jacobySymbol.cpp
        finiteField/ConversionToFieldElements.cpp
        crypto.h
        iovector/iovector.h
        polynom/polynomial.h
        complexNumbers/complex_numbers.h
        finiteField/finite_field.h
        finiteField/polynomial_mod_2.h
        main_crypto.cpp jacobySymbol/jacoby.h finiteField/polynomial_modulus.h)

add_executable(runCryptographyMain ${SOURCE_FILES})


