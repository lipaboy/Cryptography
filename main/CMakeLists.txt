cmake_minimum_required(VERSION 3.5)
project(CryptographyMain)

set(SOURCE_FILES
        numberPropertiesAlgorithms/propertiesOfNumbers.cpp
        numberPropertiesAlgorithms/jacobySymbol.cpp
        finiteField/ConversionToFieldElements.cpp
        crypto.h
        vector_extra/iovector.h
        polynom/polynom.h
        complexNumbers/complex_numbers.h
        finiteField/finite_field.h
        finiteField/polynom_mod_2.h
        main_crypto.cpp
        numberPropertiesAlgorithms/number_properties_algorithms.h
        finiteField/polynom_modulus.h vector_extra/vector_arithmetics.h)

add_executable(runCryptographyMain ${SOURCE_FILES})


