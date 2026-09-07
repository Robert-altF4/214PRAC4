#include <exception>
using namespace std;

#ifndef __ProjectIterator_h__
#define __ProjectIterator_h__

// #include "ProjectComponent.h"

class ProjectComponent;
class ProjectIterator;

// Abstract Iterator. Concrete iterators OBSERVE a ProjectComponent tree;
// they never own or delete any node they visit. The iterator object itself
// is owned by whoever called ProjectComponent::createIIterator().
class ProjectIterator
{

	public: virtual ~ProjectIterator();

	public: virtual void first() = 0;

	public: virtual void next() = 0;

	public: virtual bool isDone() = 0;

	public: virtual ProjectComponent* currentItem() = 0;
};

#endif
