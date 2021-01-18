#include<vector>
#include<unordered_set>
using namespace std;

class Node {
	int f=0, g=0, h=0;
	int x, y;
	vector<Node*> neighbors;
public:
	Node(int x, int y);
	int getf();
	int getg();
	int geth();
	int getx();
	int gety();
	void setf(int f);
	void setg(int g);
	void seth(int h);
	vector<Node*> getNeighbors();
	void addNeighbors(int x, int y, int row, int col);
};

class Generator{
	int row;
	int col;
	vector<vector<Node*>> grid;
	vector<vector<int>> directions = {{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
										{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }};
	int direction;
	unordered_set<Node*> openSet;
	unordered_set<Node*> closedSet;
public:
	Generator(int row, int col);
	void setDiagonalMovement(bool enable_);
	void createGrid();
	void findPath(vector<int> start, vector<int> end);
	int heuristic(Node* from, Node* to);
};

