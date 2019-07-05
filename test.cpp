//
// Created by alejandro on 7/5/19.
//
#include <iostream>
#include "catch.hpp"
#include "busquedaThread.h"

TEST_CASE("Tipo int"){
    vector<int> vectorInt = {2,6,3,5,4,7,66,66,23,99,6,22,45};
    REQUIRE(buscar(vectorInt)==99);
}

TEST_CASE("Tipo float"){
    vector<float> vectorFloat = {1.2,5.3,45.8,8.5,88899,14.9,8,6,1,92.5,106,9999,7};
    REQUIRE(buscar(vectorFloat)==88899.0f);

}

TEST_CASE("Tipo unsigned"){
    vector<unsigned int> vectorFloat = {2,6,3,5,4,7,66,66,23,99,6,22,45,1,1};
    REQUIRE(buscar(vectorFloat)==99);

}
