#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

//clears used memory
void deleteNodes(Grid<Node*>& nodes) {
	for (int i = 0; i < nodes.numRows(); i++){
		for (int j = 0; j < nodes.numCols(); j++){
			delete nodes[i][j];
		}
	}
}

// initializes the grid of nodes
void initializeGrid(Grid<Node*>& nodes) {
	for (int i = 0; i < nodes.numRows(); i++) {
		for (int j = 0; j < nodes.numCols(); j++) {
			nodes[i][j] = new Node;
			nodes[i][j]->loc = makeLoc(i, j);
			nodes[i][j]->color = GRAY;
			nodes[i][j]->parent = NULL;
		}
	}
}

//puts the elements of linked list into a vector.
void getPathVector(Node* currNode, Vector<Loc>& result) {
	if (currNode==NULL) return;
	getPathVector(currNode->parent, result);
	result.push_back(currNode->loc);
}

// changes the costs of neighbour nodes
void updateGraph(Node*& currNode, Grid<Node*>& nodes, Grid<double>& world, Node*& last,
				TrailblazerPQueue<Node*>& queue, double costFn(Loc from, Loc to, Grid<double>& world),
				double heuristic(Loc start, Loc end, Grid<double>& world)) {

	for (int i = currNode->loc.row - 1; i <= currNode->loc.row + 1; i++){
		for (int j = currNode->loc.col - 1; j <= currNode->loc.col + 1; j++){
			if (world.inBounds(i, j) && (currNode->loc.row != i || currNode->loc.col != j)){
				
				if (nodes[i][j]->color == YELLOW) {
					double newCost = currNode->cost + costFn(currNode->loc, nodes[i][j]->loc, world);
					if (nodes[i][j]->cost > newCost) {
						nodes[i][j]->cost = newCost;
						queue.decreaseKey(nodes[i][j], newCost + heuristic(nodes[i][j]->loc, last->loc, world));
						nodes[i][j]->parent = currNode;
					}
				} else if(nodes[i][j]->color == GRAY){
					nodes[i][j]->cost = currNode->cost + costFn(currNode->loc, nodes[i][j]->loc, world);
					nodes[i][j]->color = YELLOW;
					queue.enqueue(nodes[i][j], nodes[i][j]->cost + heuristic(nodes[i][j]->loc, last->loc, world));
					nodes[i][j]->parent = currNode;
					colorCell(world, nodes[i][j]->loc, YELLOW);
					
				}
			}
		}
	}
}

//generates the shortest path.
Vector<Loc> getPath(Grid<double>& world,Grid<Node*>& nodes, Node*& last,
				TrailblazerPQueue<Node*>& queue,double heuristic(Loc start, Loc end, Grid<double>& world),
				double costFn(Loc from, Loc to, Grid<double>& world)) {

	Vector<Loc> result;
	while (!queue.isEmpty()) {
		Node* currNode = queue.dequeueMin();
		currNode->color = GREEN;
		colorCell(world, currNode->loc, GREEN);

		if (currNode->loc == last->loc) {
			getPathVector(currNode, result);
			break;
		}
		updateGraph(currNode, nodes, world, last, queue, costFn, heuristic);
	}

	deleteNodes(nodes);
	return result;
}

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, 
			double costFn(Loc from, Loc to, Grid<double>& world),
			double heuristic(Loc start, Loc end, Grid<double>& world)) {

	Grid<Node*> nodes(world.numRows(), world.numCols());
	initializeGrid(nodes);

	Node* first = nodes[start.row][start.col];
	Node* last = nodes[end.row][end.col];

	first->color = YELLOW;
	first->cost = 0;

	TrailblazerPQueue<Node*> queue;
	queue.enqueue(first, heuristic(first->loc, last->loc, world));
	return getPath(world, nodes, last, queue, heuristic, costFn);
}



//generates the queue of edges.
TrailblazerPQueue<Edge> setEdgeQueue( int rows, int cols) {
	TrailblazerPQueue<Edge> queue;
	Loc start;
	Loc end;
	double cost;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++) {
			start = makeLoc(i, j);

			end = makeLoc(i + 1, j);
			cost = randomReal(0, 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) {
				queue.enqueue(makeEdge(start, end), cost);
			}
			
			end = makeLoc(i - 1, j);
			cost = randomReal(0, 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) {
				queue.enqueue(makeEdge(start, end), cost);
			}

			end = makeLoc(i, j + 1);
			cost = randomReal(0, 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) {
				queue.enqueue(makeEdge(start, end), cost);
			}
			
			end = makeLoc(i, j - 1);
			cost = randomReal(0, 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) {
				queue.enqueue(makeEdge(start, end), cost);
			}
		}
	}
	return queue;
}

// generates the clusters, initially, each node forms a different cluster.
Map<Loc, int> setClusters(int rows, int cols) {
	Map<Loc, int> clusters;
	int k = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			clusters[makeLoc(i, j)] = k;
			k++;
		}
	}
	return clusters;
}

void mergeClusters(Map<Loc, int>& clusters, int n1, int n2) {
	foreach(Loc loc in clusters){
		if (clusters[loc] == n1){
			
			clusters[loc] = n2;
		}
	}
}

//generates the minimum spanning tree.
Set<Edge> kruskalMST(TrailblazerPQueue<Edge>& queue, Map<Loc, int>& clusters) {
	int numOfClusters = clusters.size();
	Set<Edge> result;
	while (numOfClusters >= 2) {
		Edge e = queue.dequeueMin();
		if (clusters[e.start] != clusters[e.end]) {
			result.add(e);
			mergeClusters(clusters, clusters[e.start], clusters[e.end]);
			numOfClusters--;
		}
	}
	return result;
}

Set<Edge> createMaze(int numRows, int numCols) {

	Map<Loc, int> clusters = setClusters(numRows, numCols);
	TrailblazerPQueue<Edge> queue = setEdgeQueue(numRows, numCols);
	return kruskalMST(queue, clusters);
}