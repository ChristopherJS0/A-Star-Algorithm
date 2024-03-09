#include <iostream>
#include "Node.h"
#include <vector>
#include <queue>
using namespace std;

double h(Node* n, Node* Goal)
{
	double H = (abs(sqrt
		(Goal->x - n->x) * (Goal->x - n->x)
		+ (Goal->y - n->y) * (Goal->y - n->y)));
	cout << H << " is H" << endl;
	return H;
}

double g(Node* Current, Node* n)
{
	//	Moving by 2 directional movements, not diagnally.
	return abs(n->x - Current->x) + abs(n->y - Current->y);
}

double f(double& PreCost,Node* Current, Node* n, Node* Goal) 
{
	// Add Precost + PreNode x to y + heuristic! f(n) = g(n) + h(n)
	return (PreCost + g(Current, n) + h(n, Goal)); //Getting to Node n from Current!
}

bool NodeSort(Node* A, Node* B) {
	return A->f < B->f;
}

/* Returns bool to know if more child nodes were added to new parent.*/
bool Expand(vector<Node*>& ChildNodes, vector<Node*>& ClosedNodes,
	Node* Parent,
	Node* G, double& SumCost, double& Threshold){
	
	bool MoreAdded = false;

	for (Node* node : Parent->PointTo) {
		if (node->f == -1) { node->f = f(SumCost, Parent, node, G); } // Avoid using bad f value.
		if (node->f < Threshold) { //	Adding low f nodess to open list.
			ChildNodes.push_back(node); MoreAdded = true;
		}
		else if (node->f < Threshold) { //	Pruning odes past threshold.
			ClosedNodes.push_back(node);
		}
	}

	sort(ChildNodes.begin(), ChildNodes.end(), NodeSort);
	sort(ClosedNodes.begin(), ClosedNodes.end(), NodeSort);
	cout << "Print child nodes of " << Parent->name << endl;
	for (int i = 0; i < ChildNodes.size(); i++) {
		cout << ChildNodes[i]->name << " ";
	}
	cout << "Print closed nodes of " << Parent->name << endl;
	for (int i = 0; i < ClosedNodes.size(); i++) {
		cout << ClosedNodes[i]->name << " ";
	}

	return MoreAdded;
}

vector<Node*> BestSearchAlgo(Node* S, Node* G) 
{
	vector<Node*> OpenList;	//Put the lowest node first.
	vector<Node*> ClosedList; //Put the lowest node first.
	vector<Node*> OptimalPath; OptimalPath.push_back(S);

	Node* IterNode = S;
	double Threshold = h(S, G); // Create the first f(n) for the first threshold.
	double SumCost = 0;

	IterNode->f = h(S, G); cout << "Start f is: " << IterNode->f << endl;
	ClosedList.push_back(IterNode);

	while (IterNode != G || !ClosedList.empty()){
		
		cout << "inside while loop" << endl;
		int Depth = 0; bool MoreKidNodes;
		Threshold = ClosedList[0]->f; ClosedList.erase(ClosedList.begin());
		
		//Adding admissable child nodes to OpenList.
		MoreKidNodes = Expand(OpenList, ClosedList, IterNode, G, SumCost, Threshold);

		while (!OpenList.empty()) {
			if (IterNode == G) { cout << "G is found" << endl; break; }

			SumCost += g(IterNode, OpenList[0]);
			IterNode = OpenList[0];
			OpenList.erase(OpenList.begin());

			if (MoreKidNodes){OptimalPath.push_back(IterNode);}

			MoreKidNodes = Expand(OpenList, ClosedList,
				IterNode, G, SumCost, Threshold);
			cout << "IterNode is now: " << IterNode->name << endl;
		}

		if (IterNode == G) {
			cout << "The Sum Cost from Start to Goal is: " << SumCost << endl;
			break;
		}
		Threshold = ClosedList[0]->f;	
	}
	return OptimalPath;
}

int main()
{
	//1. 
	// Will be  y, x
	Node* Grid[10][10] = {};
	
	// Initialize nodes
	Node* A = new Node(5, 0, "A"); Node* B = new Node(1, 2, "B");
	Node* C = new Node(3, 4, "C"); Node* D = new Node(7, 2, "D");
	Node* E = new Node(7, 5, "E"); Node* F = new Node(7, 5, "F");
	Node* G = new Node(9, 9, "G");

	//	Connecting the nodes
	A->Connect(B); A->Connect(D);
	B->Connect(C);
	C->Connect(F); C->Connect(G);
	D->Connect(C); D->Connect(E);
	E->Connect(G);
	F->Connect(G);

	// Insert nodes into appropriate y, x.
	Grid[0][5] = A;	Grid[2][1] = B;
	Grid[4][3] = C; Grid[2][7] = D;
	Grid[5][7] = E; Grid[7][5] = F;
	Grid[9][9] = G;
	
	//	Creating Blank spaces to replace nulls.
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (Grid[i][j] == NULL) {
				Node* Space = new Node(j, i, "|");
				Grid[i][j] = Space;
			}
		}
	}

	//	Printing the Node Grid
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << Grid[i][j]->name << " ";
		}
		cout << endl;
	}

	// Algorithm at work.
	vector<Node*> BestPath = BestSearchAlgo(A, G);
	cout << BestPath.size() << endl;
	for (int i = 0; i < BestPath.size(); i++) {
		cout << BestPath[i]->name << " -> ";
	}

	// Final: Free up memory!
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			delete Grid[i][j];
		}
	}

	return 0;
}
