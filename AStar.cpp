#include <iostream>
#include "AStar.h"
#include <vector>
using namespace std;

Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
}
int Node::getf() {
	return this->f;
}
int Node::getg() {
	return this->g;
}
int Node::geth() {
	return this->h;
}
int Node::getx() {
	return this->x;
}
int Node::gety() {
	return this->y;
}
void Node::setf(int f) {
	this->f = f;
}
void Node::setg(int g) {
	this->g = g;
}
void Node::seth(int h) {
	this->h = h;
}
vector<Node*> Node::getNeighbors() {
	return this->neighbors;
}
void Node::addNeighbors(int x, int y, int row, int col) {
	if (x < row - 1) {
		this->neighbors.push_back(new Node(x + 1, y));
	}
	if (x > 0) {
		this->neighbors.push_back(new Node(x - 1, y));
	}
	if (y < col - 1) {
		this->neighbors.push_back(new Node(x, y + 1));
	}
	if (y > 0){
		this->neighbors.push_back(new Node(x, y - 1));
	}
}

Generator::Generator(int row, int col) {
	this->row = row;
	this->col = col;
	grid.resize(row, vector<Node*>(col, NULL));
}
void Generator::createGrid() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			grid[i][j] = new Node(i, j);
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			grid[i][j]->addNeighbors(i,j,row,col);
		}
	}
}

void Generator::setDiagonalMovement(bool enable_) {
	direction = (enable_ ? 8 : 4);
}
void Generator::findPath(vector<int> start, vector<int> end) {
	Node* startNode = grid[start[0]][start[1]];
	Node *endNode = grid[end[0]][end[1]];

	openSet.insert(startNode);

	while (!openSet.empty()) {

		auto lowestIndex = openSet.begin(); 
		unordered_set<Node*>::iterator it;
		for (it = openSet.begin(); it != openSet.end(); ++it) {
			if ((*it)->getf() < (*lowestIndex)->getf()) {
				lowestIndex = it;
			}
		}

		Node *current = *lowestIndex;
		if (current == endNode) {
			cout << "PATH FOUND" << endl;
			return;
		}

		closedSet.insert(current);
		openSet.erase(current);

		for (int i = 0; i < current->getNeighbors().size(); i++) {
			Node *neighbor = current->getNeighbors()[i];
			
			if (closedSet.find(neighbor) == closedSet.end()) {
				int tempG = current->getg() + 1;

				if (openSet.find(neighbor) != openSet.end()) {
					if (tempG < neighbor->getg()) {
						neighbor->setg(tempG);
					}
				}
				else {
					neighbor->setg(tempG);
					openSet.insert(neighbor);
				}

				neighbor->seth(heuristic(neighbor, endNode));
				neighbor->setf(neighbor->getg() + neighbor->geth());
			}
		}

	}
	if (openSet.empty()) {
		cout << "NOT FOUND" << endl;
		return;
	}
}

int Generator::heuristic(Node *from, Node *to) {
	return abs(from->getx() - to->getx()) + abs(from->gety() - to->gety());
}