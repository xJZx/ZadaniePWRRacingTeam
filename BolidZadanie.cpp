#include <iostream>
#include <vector>

#define INT_MAX 10000000

using namespace std;

void DijkstrasMain();

int main() {
  DijkstrasMain();
  return 0;
}

class Node;
class Edge;

void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
float Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);

vector<Node*> nodes;
vector<Edge*> edges;

class Node {
   public:
  Node(char id)
    : id(id), previous(NULL), distanceFromStart(INT_MAX) {
    nodes.push_back(this);
  }

   public:
  char id;
  Node* previous;
  float distanceFromStart;
};

class Edge {
   public:
  Edge(Node* node1, Node* node2, float distance)
    : node1(node1), node2(node2), distance(distance) {
    edges.push_back(this);
  }
  bool Connects(Node* node1, Node* node2) {
    return (
      (node1 == this->node1 &&
       node2 == this->node2) ||
      (node1 == this->node2 &&
       node2 == this->node1));
  }

   public:
  Node* node1;
  Node* node2;
  float distance;
};

///////////////////
void DijkstrasMain() {
	float red, green, blue;
	int x,y;
	char id;
	cout<<"Podaj ceny drog (czerwona->zielona->niebieska): "<<endl;
	cin>>red;
	cin>>green;
	cin>>blue;
	cout<<"Podaj liczbe przystankow: ";
	cin>>x;
	cout<<"Podaj przystanek poczatkowy: ";
  	cin>>id;								// set start node
	
  Node* a = new Node('A');
  Node* b = new Node('B');
  Node* c = new Node('C');
  Node* d = new Node('D');
  Node* p1 = new Node('p1');
  Node* p2 = new Node('p2');
  Node* p3 = new Node('p3');
  Node* p4 = new Node('p4');
  Node* p5 = new Node('p5');
  Node* p6 = new Node('p6');
  Node* p7 = new Node('p7');
  Node* p8 = new Node('p8');
  Node* p9 = new Node('p9');
  Node* p10 = new Node('p10');
  Node* p11 = new Node('p11');

  Edge* e1 = new Edge(a, p1, blue);
  Edge* e2 = new Edge(a, p4, green);
  Edge* e3 = new Edge(b, p5, blue);
  Edge* e4 = new Edge(p1, p2, red);
  Edge* e5 = new Edge(p2, c, red);
  Edge* e6 = new Edge(p2, p3, blue);
  Edge* e7 = new Edge(p3, p4, green);
  Edge* e8 = new Edge(p4, p5, red);
  Edge* e9 = new Edge(p5, p8, green);
  Edge* e10 = new Edge(c, p9, green);
  Edge* e11 = new Edge(p9, p6, green);
  Edge* e12 = new Edge(p6, p3, green);
  Edge* e13 = new Edge(p6, p4, blue);
  Edge* e14 = new Edge(p6, p10, red);
  Edge* e15 = new Edge(p9, p10, blue);
  Edge* e16 = new Edge(p10, p11, red);
  Edge* e17 = new Edge(p11, d, red);
  Edge* e18 = new Edge(p11, p7, blue);
  Edge* e19 = new Edge(p7, p6, green);
  Edge* e20 = new Edge(p7, p5, blue);
  Edge* e21 = new Edge(d, p8, red);

  for(x<=y; y=1; y++){
		if(id=='A'){					 
		  a->distanceFromStart = 0;
	  	  Dijkstras();
	  	  cout<<"Najtansze drogi z hangaru A do hangarow: B, C, D: "<<endl;
		  PrintShortestRouteTo(b);
		  PrintShortestRouteTo(c);
		  PrintShortestRouteTo(d);
		  a->distanceFromStart = 0;
 	  		 break;
		  }
		else if(id=='B'){
		  b->distanceFromStart = 0;	
		  Dijkstras();  
		  cout<<"Najtansze drogi z hangaru B do hangarow: A, C, D: "<<endl;
		  PrintShortestRouteTo(a);
		  PrintShortestRouteTo(c);
		  PrintShortestRouteTo(d);
		  b->distanceFromStart = 0;	
		  	  break;
		  }
		else if(id=='C'){
		  c->distanceFromStart = 0;	
		  Dijkstras();  
		  cout<<"Najtansze drogi z hangaru C do hangarow: A, B, D: "<<endl;
		  PrintShortestRouteTo(a);
		  PrintShortestRouteTo(b);
		  PrintShortestRouteTo(d);
		  c->distanceFromStart = 0;	
		  	  break;
		  }
		else if(id=='D'){
		  d->distanceFromStart = 0;	
		  Dijkstras();  
		  cout<<"Najtansze drogi z hangaru D do hangarow: A, B, C: "<<endl;
		  PrintShortestRouteTo(a);
		  PrintShortestRouteTo(b);
		  PrintShortestRouteTo(c);
		  d->distanceFromStart = 0;	
	  		  break;
		  }
}

}

///////////////////

void Dijkstras() {
  while (nodes.size() > 0) {
    Node* smallest = ExtractSmallest(nodes);
    vector<Node*>* adjacentNodes =
      AdjacentRemainingNodes(smallest);

    const float size = adjacentNodes->size();
    for (float i = 0; i < size; ++i) {
      Node* adjacent = adjacentNodes->at(i);
      float distance = Distance(smallest, adjacent) +
               smallest->distanceFromStart;

      if (distance < adjacent->distanceFromStart) {
        adjacent->distanceFromStart = distance;
        adjacent->previous = smallest;
      }
    }
    delete adjacentNodes;
  }
}

// Find the node with the smallest distance,
// remove it, and return it.
Node* ExtractSmallest(vector<Node*>& nodes) {
  float size = nodes.size();
  if (size == 0) return NULL;
  float smallestPosition = 0;
  Node* smallest = nodes.at(0);
  for (float i = 1; i < size; ++i) {
    Node* current = nodes.at(i);
    if (current->distanceFromStart <
      smallest->distanceFromStart) {
      smallest = current;
      smallestPosition = i;
    }
  }
  nodes.erase(nodes.begin() + smallestPosition);
  return smallest;
}

// Return all nodes adjacent to 'node' which are still
// in the 'nodes' collection.
vector<Node*>* AdjacentRemainingNodes(Node* node) {
  vector<Node*>* adjacentNodes = new vector<Node*>();
  const float size = edges.size();
  for (float i = 0; i < size; ++i) {
    Edge* edge = edges.at(i);
    Node* adjacent = NULL;
    if (edge->node1 == node) {
      adjacent = edge->node2;
    } else if (edge->node2 == node) {
      adjacent = edge->node1;
    }
    if (adjacent && Contains(nodes, adjacent)) {
      adjacentNodes->push_back(adjacent);
    }
  }
  return adjacentNodes;
}

// Return distance between two connected nodes
float Distance(Node* node1, Node* node2) {
  const float size = edges.size();
  for (float i = 0; i < size; ++i) {
    Edge* edge = edges.at(i);
    if (edge->Connects(node1, node2)) {
      return edge->distance;
    }
  }
  return -1;  // should never happen
}

// Does the 'nodes' vector contain 'node'
bool Contains(vector<Node*>& nodes, Node* node) {
  const float size = nodes.size();
  for (float i = 0; i < size; ++i) {
    if (node == nodes.at(i)) {
      return true;
    }
  }
  return false;
}

///////////////////

void PrintShortestRouteTo(Node* destination) {
  Node* previous = destination;
  cout << "Oplata za przejazd: "
     << destination->distanceFromStart <<endl;
}

