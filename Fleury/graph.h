#pragma once
#include <iostream>
#include<queue>
#include <vector>
using namespace std;

struct Node {
	Node* nodes[10] = {};
	int conns = 0;
	string label;
	bool statusDFS = false;
	bool statusBFS = false;

	void connect(Node* node) {
		if (isConnected(node) == true)
			return;
		nodes[conns] = node;
		conns++;
		node->connect(this);
	}

	bool isConnected(Node* node) {
		for (int i = 0; i < conns; i++) {
			if (node == nodes[i])
				return true;
		}
		return false;
	}
	void unconnect(Node* node)
	{
		if (isConnected(node) == false) return;
		for (int i = 0; i < conns; i++) {
			if (nodes[i] == node) {
				// Tìm thấy đối tượng cần ngắt kết nối
				// Di chuyển tất cả các phần tử sau phần tử này lên
				for (int j = i; j < conns - 1; j++) {
					nodes[j] = nodes[j + 1];
				}
				// Đặt phần tử cuối cùng về nullptr và giảm conns đi 1
				nodes[conns - 1] = nullptr;
				conns--;
				// Ngắt kết nối đối tượng kia
				node->unconnect(this);
				return;
			}
		}
	}
};
struct Graph {
	Node* nodes[100] = {};
	int gSize = 0;
	void resetStatusBFS() {
		for (int i = 0; i < gSize; i++)
		{
			nodes[i]->statusBFS = false;
		}
	}
	int countConnectedNodes()
	{
		int d = 0;
		for (int i = 0; i < gSize; i++)
		{
			if (nodes[i]->conns > 0) d++;
		}
		return d;
	}
	void addNodes(int n, Node* newNodes[]) {
		for (int i = 0; i < n; i++) {
			nodes[i] = newNodes[i];
		}
		gSize += n;
	}

	void print() {
		for (int i = 0; i < gSize; i++) {
			cout << nodes[i]->label << ", ";
		}
		cout << endl;
	}
	int BFS(Node* root) {
		queue<Node*> q;
		int nodesVisited = 0; // Số nút đã duyệt qua
		q.push(root);
		while (!q.empty()) {
			Node* current = q.front();
			current->statusBFS = true;
			q.pop();
			nodesVisited++;
			for (int i = 0; i < current->conns; i++) {
				if (!current->nodes[i]->statusBFS) {
					current->nodes[i]->statusBFS = true;
					q.push(current->nodes[i]);
				}
			}
		}
		return nodesVisited;
	}
	Node* checkDegree()
	{
		int countOdd = 0;
		Node* temp = new Node();
		for (int i = 0; i < gSize; i++)
		{
			if (nodes[i]->conns % 2 != 0)
			{
				countOdd++;
				/*if(nodes[i]->conns!=1)*/temp = nodes[i];
			}
		}
		if (countOdd > 0 and countOdd != 2)
		{
			temp = NULL;
			return temp;
		}
		else
			if (countOdd == 2) return temp;
			else return nodes[0];
	}
	bool Fleury(Node* current, vector<Node*>& path, Node* root)
	{
		//if (checkDegree() == false) return false;
		if (current == nullptr) return false;
		if (current->conns > 0)
		{
			path.push_back(current);
			for (int i = 0; i < current->conns; i++)
			{
				Node* nextNode = current->nodes[i];
				if (nextNode != nullptr)
				{
					current->unconnect(nextNode);
					int d1 = BFS(nextNode);
					int d2 = countConnectedNodes();
					if (d1 == d2)
					{
						resetStatusBFS();
						if (Fleury(nextNode, path, root))
							return true;
					}
					else if (d1 == 1 and d2 == 0) { current->connect(nextNode); path.push_back(current->nodes[0]); return true; }
					else {


						current->connect(nextNode);
						resetStatusBFS();
						i = 0;
						//Fleury(current, path, root);
					}
				}
			}
		}
		return (path.size() == gSize);
	}

	void printFleury(/*Node* root*/)
	{
		vector<Node*> path;
		if (checkDegree() != NULL)
		{
			Node* root = checkDegree();
			if (Fleury(root, path, root) == true)
			{
				cout << "Path from root: " << root->label << endl;
				for (size_t i = 0; i < path.size(); i++) {
					cout << path[i]->label;
					if (i < path.size() - 1) cout << " -> ";
				}
				cout << endl;
			}
		}
		else {
			cout << " Can not print Euler path in the graph." << endl;
		}
	}


};