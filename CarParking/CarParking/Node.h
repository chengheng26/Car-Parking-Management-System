#ifndef Node_type
#define Node_type

#include	"Car.h"

typedef Car type;

struct Node {
	type item;
	Node *next;
	Node(type);
};


#endif