/*
 * FpCoreTest.h
 *
 *  Created on: Sep 8, 2012
 *      Author: steven
 */
#ifndef FPCORETEST_H_
#define FPCORETEST_H_

#include <gtest/gtest.h>
#include <MockEnvironment.h>
#include <boost/shared_ptr.hpp>

class FpCoreTest : public testing::Test {
public:
	void initEnvironment();
	boost::shared_ptr<MockEnvironment> mEnvironment;

};

#endif /* FPCORETEST_H_ */
