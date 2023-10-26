#include <iostream>
#include "graph.h"
#include <vector>

using namespace std;

int main()
{
	Node* A = new Node();
	A->label = "1";

	Node* B = new Node();
	B->label = "2";

	Node* C = new Node();
	C->label = "3";

	Node* D = new Node();
	D->label = "4";

	Node* E = new Node();
	E->label = "5";

	Node* F = new Node();
	F->label = "6";

	Node* G = new Node();
	G->label = "7";

	Node* H = new Node();
	H->label = "8";

	Node* I = new Node();
	I->label = "9";

	Node* J = new Node();
	J->label = "10";

	Node* K = new Node();
	K->label = "11";

	A->connect(B);
	A->connect(C);
	A->connect(D);
	A->connect(E);
	B->connect(F);
	C->connect(F);
	D->connect(F);
	E->connect(F);

	/*E->connect(D);
	C->connect(B);
	I->connect(J);*/

	F->connect(G);
	F->connect(H);
	F->connect(I);
	F->connect(J);
	G->connect(K);
	H->connect(K);
	I->connect(K);
	J->connect(K);
	Graph* g = new Graph();
	Node* nodes[] = { A, B, C, D, E, F, G, H, I, J, K };
	g->addNodes(11, nodes);
	g->printFleury();
	//// Dap an: 1, 2, 6, 3, 1, 4, 6, 8, 11, 7, 6, 9, 11, 10, 6, 5, 1
}
