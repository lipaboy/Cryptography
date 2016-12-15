cmake_minimum_required(VERSION 3.5)
project(CryptographyMain)

set(SOURCE_FILES
        numberPropertiesAlgorithms/propertiesOfNumbers.cpp
        numberPropertiesAlgorithms/jacobySymbol.cpp
        crypto.h
        vector_extra/iovector.h
        polynom/polynom.h
        complexNumbers/complex_numbers.h
        finiteField/finite_field.h
        main_crypto.cpp
        numberPropertiesAlgorithms/number_properties_algorithms.h
        finiteField/field_element.h vector_extra/vector_arithmetics.h)

add_executable(runCryptographyMain ${SOURCE_FILES})


