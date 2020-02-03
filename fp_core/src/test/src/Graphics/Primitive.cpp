#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <fruitpunch/Graphics/Primitive.h>

using namespace fp_core;

class PrimitiveTest: public FpCoreTest {
public:
	Primitive p;

protected:

	virtual void SetUp() {
		initEnvironment();

		point p1, p2, p3, p4;

		p1.x = 0.0;
		p1.y = 0.0;

		p2.x = 10.0;
		p2.y = 0.0;

		p3.x = 0.0;
		p3.y = 10.0;

		p4.x = 10.0;
		p4.y = 10.0;

		Vertex v1(p1), v2(p2), v3(p3), v4(p4);

		p.addVertex(v1);
		p.addVertex(v2);
		p.addVertex(v3);
		p.addVertex(v4);
	}

};

TEST_F(PrimitiveTest, Initialization) {
	Primitive p;
	ASSERT_EQ(p.getAlpha(), 1);
	ASSERT_EQ(p.getRotation(), 0);
	ASSERT_EQ(p.getCenter().x, 0);
	ASSERT_EQ(p.getCenter().y, 0);
	ASSERT_EQ(p.getScale().x, 1);
	ASSERT_EQ(p.getScale().y, 1);
	ASSERT_EQ(p.getPosition().x, 0);
	ASSERT_EQ(p.getPosition().y, 0);
}

TEST_F(PrimitiveTest, pointerDetection) {
	for (float x = 0.0; x <= 10; x++) {
		for (float y = 0.0; y <= 10; y++) {
			point pointer;
			pointer.x = x;
			pointer.y = y;
			//printf("(%f, %f)", x, y);
			ASSERT_TRUE(p.contains(pointer));
		}
	}
}

TEST_F(PrimitiveTest, pointerDetectionMoveX) {

	for (int position = 0; position < 10; position++) {
		for (float x = 0.0 + position; x <= 10 + position; x++) {
			for (float y = 0.0; y <= 10; y++) {
				point pointer;
				pointer.x = x;
				pointer.y = y;
				//printf("(%f, %f)", x, y);
				ASSERT_TRUE(p.contains(pointer));
			}
		}
		p.move(1, 0);
	}
}

TEST_F(PrimitiveTest, pointerDetectionMoveY) {

	for (int position = 0; position < 10; position++) {
		for (float x = 0.0; x <= 10; x++) {
			for (float y = 0.0 + position; y <= 10 + position; y++) {
				point pointer;
				pointer.x = x;
				pointer.y = y;
				//printf("(%f, %f)", x, y);
				ASSERT_TRUE(p.contains(pointer));
			}
		}
		p.move(0, 1);
	}
}

TEST_F(PrimitiveTest, pointerDetectionMoveDiagonal) {

	for (int position = 0; position < 10; position++) {
		for (float x = 0.0 + position; x <= 10 + position; x++) {
			for (float y = 0.0 + position; y <= 10 + position; y++) {
				point pointer;
				pointer.x = x;
				pointer.y = y;
				//printf("(%f, %f)", x, y);
				ASSERT_TRUE(p.contains(pointer));
			}
		}
		p.move(1, 1);
	}
}
