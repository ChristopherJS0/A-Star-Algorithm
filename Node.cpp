#include "Node.h"
using namespace std;

//Methods of struct Node

Node::Node(int X, int Y, string Name){
	// These values will never be negative,
	// this is only to make sure these values aren't used
	// with the A* Algorithm.
	f = -1; g = -1; h = -1;
	x = X; y = Y;
	name = Name;
}

void Node::Connect(Node* ChildNode)
{
	// We add the child node to the vector of connecting nodes, and also add parent to child
	// so that it can point back to parent if necessary!
	PointTo.push_back(ChildNode);
}



