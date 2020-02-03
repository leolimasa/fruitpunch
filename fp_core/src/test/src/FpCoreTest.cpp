/*
 * FpCoreTest.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: steven
 */

#include <FpCoreTest.h>


void FpCoreTest::initEnvironment() {
	mEnvironment = boost::shared_ptr<MockEnvironment>(new MockEnvironment());
}
