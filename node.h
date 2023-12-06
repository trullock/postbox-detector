#ifndef Node_h
#define Node_h

struct Node
{
	Node* children;
	unsigned int count;
	unsigned int height;
	bool leaf;
	double x;
	double y;
};

#endif