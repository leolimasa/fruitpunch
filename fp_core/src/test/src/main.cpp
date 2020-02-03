/*
 * main.cpp
 *
 *  Created on: 2012-05-08
 *      Author: leo
 */
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <MockRenderer.h>
#include <stdio.h>

using namespace fp_core;
using namespace boost;
using namespace std;


int main(int   argc, char *argv[] ) {

  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  cout << "Tests complete.";
 
}
