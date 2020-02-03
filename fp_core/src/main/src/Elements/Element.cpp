/*
 * Element.cpp
 *
 *  Created on: 2012-05-21
 *      Author: leo
 */

#include <fruitpunch/Elements/Element.h>
#include <fruitpunch/Common/Event.h>
#include <fruitpunch/Common/Events.h>
#include <fruitpunch/Elements/Scene.h>
#include <fruitpunch/Common/Collection.h>
#include <boost/make_shared.hpp>

using namespace std;
using namespace fp_core::common;

namespace fp_core {

Element::Element() :
		Observable() {
	mChildren = boost::shared_ptr<Vector>(new Vector());
}

Element::~Element() {
	onRemove();
}

// ____________________________________________________________________________

Element::ref Element::add(Element::ref element) {
	if (element->getParent()) {
		element->getParent()->remove(element);
	}
	element->setParent(getThis<Element>());
	boost::shared_ptr<Scene> scene = this->getScene();
	element->setScene(this->getScene());
	addOrphan(element);

	return element;
}

// ____________________________________________________________________________

Element::ref Element::addOrphan(Element::ref element) {
	mChildren->append(element);
	element->notify(boost::shared_ptr<Event>(new Event(EV_ADD)));
	element->onAdd();

	return element;
}

// ____________________________________________________________________________

Element::ref Element::remove(Element::ref element) {
	element->setParent(boost::shared_ptr<Element>());

	boost::shared_ptr<Iterator> it = mChildren->getIterator();

	bool found = false;
	while (it->next()) {
		if (it->get() == element) {
			found = true;
			break;
		}
	}

	if (found) {
		it->remove();
		mChildChanged = true;
		element->notify(boost::shared_ptr<Event>(new Event(EV_REMOVE)));
		element->onRemove();
		return element;
	}

	return boost::shared_ptr<Element>();
}

// ----------------------------------------------------------------------------
// Getters and setters
// ----------------------------------------------------------------------------

void Element::onAdd() {
}

void Element::onRemove() {
}

// ____________________________________________________________________________

void Element::renderFrame() {
	notify(boost::make_shared<Event>(EV_PRE_RENDER));
	onRender();

	// We use a while and not a for loop here because the
	// size of the children array might change during
	// renderFrame()
	int i = 0;
	while (true) {
		if (i >= mChildren->getSize()) {
			break;
		}

		mChildren->getAndCast<Element>(i)->renderFrame();
		i++;
	}

	notify(boost::make_shared<Event>(EV_POST_RENDER));
}

// ____________________________________________________________________________

void Element::tick() {
	notify(boost::make_shared<Event>(EV_TICK));

	int i = 0;
	while (true) {
		if (i >= mChildren->getSize()) {
			break;
		}

		mChildren->getAndCast<Element>(i)->tick();
		i++;
	}
}

// ____________________________________________________________________________

void Element::onRender() {
}

// ____________________________________________________________________________

void Element::setParent(Element::ref parent) {
	mParent = parent;
}

// ____________________________________________________________________________

void Element::setScene(boost::shared_ptr<Scene> scene) {
	mScene = scene;
}

// ____________________________________________________________________________

boost::shared_ptr<Scene> Element::getScene() const {
	return mScene;
}

// ____________________________________________________________________________

boost::shared_ptr<fp_core::common::Collection> Element::getChildren() const {
	return mChildren;
}

// ____________________________________________________________________________

Element::ref Element::getParent() const {
	return mParent;
}

// ____________________________________________________________________________

void Element::destroy() {
	this->notify(Event::ref(new Event(EV_DESTROY)));

	// Remove from parent and tell all the children to commit suicide
	if (this->getParent()) {
		getParent()->remove(getThis<Element>());
	}

	while (mChildren->getSize()) {
		mChildren->getAndCast<Element>(0)->destroy();
	}

}

}

/* namespace fp_core */


