#pragma once
#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct Node
{
public:
	Node(int X, int Y, string Name);
	void Connect(Node* ChildNode);

	double x, y; // The node coordinates
	double f, g, h; // The A* properties
	std::string name;
	std::vector<Node*> PointTo;

};
