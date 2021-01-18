#include <iostream>
#include <vector>
#include "AStar.h"
using namespace std;

int row = 2;
int col = 2;

int main() {

	Generator generator(row, col);
	generator.createGrid();
	generator.setDiagonalMovement(true);

	cout << "Generate path ... \n";
	vector<int> start{ 0, 0 };
	vector<int> end{ row-1, col-1 };
	generator.findPath(start,end);
	system("pause");
	return 0;
}