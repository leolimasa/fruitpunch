#include <FpCoreTest.h>
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Window.h>
#include <fruitpunch/Graphics/Sprite.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Common/Observable.h>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Graphics/Renderer.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Common/NativeBridge.h>
#include <fruitpunch/Graphics/OpenGl.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Observer.h>
#include <boost/make_shared.hpp>
#include <string.h>

using namespace fp_core;
using namespace std;
using namespace boost;
using namespace fp_core::common;

class SpriteObserver: public Observer{

	public:
		bool clicked;

		void action(){
			clicked = true;
		}
	};

class SpriteTest : public FpCoreTest {
protected :
	virtual void SetUp() {
		initEnvironment();

	}
};

TEST_F(SpriteTest, SpriteClick) {
	boost::shared_ptr<Sprite> s(new Sprite("pedoBear.png"));
	boost::shared_ptr<SpriteObserver> obs(new SpriteObserver());
	s->attachObserver(EV_POINTER_DOWN, obs);
	Runtime::getCurrent()->getWindow()->addPrimitive(s);

	s->setLeft(1.0f);
	s->setTop(1.0f);

	/*printf("image width: %d, image height: %d \n", s->getImage()->getWidth(), s->getImage()->getHeight());
	printf("primitive width: %f primitive height: %f \n", s->getWidth(), s->getHeight());
	printf("primitive center: x: %f, y: %f \n",s->getCenter().x, s->getCenter().y);
	printf("primitive top: %f left: %f \n", s->getTop(), s->getLeft());*/

	point position;
	position.x = 0.0f;
	position.y = 0.0f;

	point center;
	center.x = 50.0f;
	center.y = 50.0f;

	point pointer;
	pointer.x = 50.0f;
	pointer.y = 50.0f;

	obs->clicked = false;
	Runtime::getCurrent()->getWindow()->setPointer(pointer);
	Runtime::getCurrent()->getWindow()->notify(Event::ref(new Event(EV_POINTER_DOWN)));
	ASSERT_TRUE(obs->clicked);
}

TEST_F(SpriteTest, crop) {
	boost::shared_ptr<Sprite> s = boost::make_shared<Sprite>("pedoBear.png");

	float width = 412;
	float height = 744;

	ASSERT_EQ(width, s->getWidth());
	ASSERT_EQ(height, s->getHeight());

	s->crop(100, 200, 50, 50);

	// 0,0
	ASSERT_FLOAT_EQ(100.0 / width, s->getVertices()[0].getUvmap().x);
	ASSERT_FLOAT_EQ(494.0 / height, s->getVertices()[0].getUvmap().y);

	// 0,1
	ASSERT_FLOAT_EQ(100.0 / width, s->getVertices()[1].getUvmap().x);
	ASSERT_FLOAT_EQ(544.0 / height, s->getVertices()[1].getUvmap().y);

	// 1,0
	ASSERT_FLOAT_EQ(150.0 / width, s->getVertices()[2].getUvmap().x);
	ASSERT_FLOAT_EQ(494.0 / height, s->getVertices()[2].getUvmap().y);

	// 1,1
	ASSERT_FLOAT_EQ(150.0 / width, s->getVertices()[3].getUvmap().x);
	ASSERT_FLOAT_EQ(544.0 / height, s->getVertices()[3].getUvmap().y);

}
