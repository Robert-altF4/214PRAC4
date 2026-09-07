#include <exception>
using namespace std;

#include "ProjectIterator.h"
#include "ProjectComponent.h"

// Nothing to release: an iterator borrows the tree, it does not own it.
ProjectIterator::~ProjectIterator() {
}
