

#include <iostream>
#include<string>
#include<list>
#include<queue>
#include<string.h>
#include <time.h>


#define SIZE 100 
int path = 0;
using namespace std;

typedef struct Node_string
{
	string state;
	struct Node_string* parent; // tree search

	int path_cost;
	int depth;
	int g;  //giá trị heuristic
	struct Node_string* nextNode; // list


} Node;


list<Node*> conAB(Node* cha)
{
	list<Node*> child;
	size_t found = cha->state.find("AB");
	int lenght = cha->state.length();
	while (found < lenght)
	{
		Node* con = new Node();
		con->depth = cha->depth + 1;
		con->parent = cha;
		string str = cha->state;
		if (found != string::npos && str[found] == 'A' && str[found + 1] == 'B')
			str.replace(found, 2, "BC");
		found += 2;
		if (found > lenght)
			break;
		con->state = str;
		child.push_back(con);
	}
	return child;
}
list<Node*> conAC(Node* cha)
{
	list<Node*> child;
	size_t found = cha->state.find("AC");;
	int lenght = cha->state.length();
	while (found < lenght)
	{
		Node* con = new Node();
		con->depth = cha->depth + 1;
		con->parent = cha;
		string str = cha->state;
		if (found != string::npos && str[found] == 'A' && str[found + 1] == 'C')
			str.replace(found, 2, "E");
		found += 2;
		if (found > lenght)
			break;
		con->state = str;
		child.push_back(con);

	}
	return child;
}
list<Node*> conBB(Node* cha)
{
	list<Node*> child;
	size_t found = cha->state.find("BB");;
	int lenght = cha->state.length();
	while (found < lenght)
	{
		Node* con = new Node();
		con->depth = cha->depth + 1;
		con->parent = cha;
		string str = cha->state;
		if (found != string::npos && str[found] == 'B' && str[found + 1] == 'B')
			str.replace(found, 2, "E");
		found += 2;
		if (found > lenght)
			break;
		con->state = str;
		child.push_back(con);

	}
	return child;
}
list<Node*> conEx(Node* cha)
{
	list<Node*> child;
	size_t found = cha->state.find("E");
	int lenght = cha->state.length();
	while (found < lenght)
	{
		Node* con = new Node();
		con->depth = cha->depth + 1;
		con->parent = cha;
		string str = cha->state;
		if (found != string::npos && str[found] == 'E')
			str.replace(found, 1, "");
		found += 2;
		if (found > lenght)
			break;
		con->state = str;
		child.push_back(con);

	}
	return child;
}
typedef struct NodeList {
	unsigned int nodeCount;    //the number of nodes in the list
	Node* head;            //pointer to the first node in the list
	Node* tail;            //pointer to the last node in the list
};


NodeList* FIFO_initial() {
	//
	NodeList* list = new NodeList();
	list->head = list->tail = NULL;
	list->nodeCount = 0;
	return list;
}

void FIFO_add(NodeList* list, Node* node) {
	if (list->head != NULL)
	{
		list->tail->nextNode = node;
		list->tail = node;
		list->tail->nextNode = NULL;
		list->nodeCount += 1;
	}
	else
	{
		node->nextNode = NULL;
		list->head = list->tail = node;
		list->nodeCount += 1;
	}
}

void FIFO_addHead(NodeList* list, Node* node) {
	if (list->head != NULL)
	{
		node->nextNode = list->head;
		list->head = node;
		list->nodeCount += 1;
	}
	else
	{
		node->nextNode = NULL;
		list->head = list->tail = node;
		list->nodeCount += 1;
	}
}

Node* FIFO_pop(NodeList* list) {
	//
	if (list->nodeCount != 0)
	{
		Node* n = list->head;
		list->head = n->nextNode;
		list->nodeCount -= 1;
		if (list->nodeCount == 0)
		{
			list->head = list->tail = NULL;
		}
		return n;
	}
	return NULL;
}

bool inList(list<Node*> close, Node* n)
{
	list<Node*> temp = close;
	while (!temp.empty())
	{
		Node* t = temp.front();
		temp.pop_front();
		if (n->state == t->state)
			return true;
	}
	return false;
}


void Solution(Node* node) {
	//
	Node* current = node;
	NodeList* path = FIFO_initial();
	//list<Node*> path;
	while (current != NULL)
	{
		FIFO_addHead(path, current);
		//path.push_front(current);
		current = current->parent;
	}
	current = path->head;
	//current = path.front;
	while (current != NULL)
		//for(Node* n :path(current))
	{
		cout << current->state << endl;
		current = current->nextNode;
	}
}

void breadthFirstSearch(Node* root, Node* goal) {
	list<Node*>open;
	list<Node*>close;
	Node* current = new Node();
	//openq.push(root);
	open.push_back(root);
	while (!open.empty())
	{
		//current = openq.front();
		current = open.front();
		if (current->state == goal->state)
		{
			Solution(current);
			cout << "\nCo Goal" << endl;
			return;
		}
		//successor ở đây!!
		for (Node* n : conAC(current))
			if (!inList(close, n) && !inList(open, n))
				//openq.push(n);
				open.push_back(n);

		for (Node* n : conAB(current))
			if (!inList(close, n) && !inList(open, n))
				//openq.push(n);
				open.push_back(n);

		for (Node* n : conBB(current))
			if (!inList(close, n) && !inList(open, n))
				//openq.push(n);
				open.push_back(n);

		for (Node* n : conEx(current))
			//openq.push(n);
			if (!inList(close, n) && !inList(open, n))
				open.push_back(n);
		//tới đây
		//openq.pop();
		open.pop_front();
		close.push_back(current);
		//closeq.push(current);
	//	FIFO_add(close, current);
	}
}


//So sanh de them node vao priority queue
struct NodeCmp
{
	bool operator()(const Node* ln, const Node* rn) const
	{
		return ln->state.length() > rn->state.length();
	}
};

bool inQueue(priority_queue<Node*, vector<Node*>, NodeCmp> pq, Node* n)
{
	list<Node*> temp;
	while (!pq.empty())
	{
		Node* t = pq.top();
		pq.pop();
		temp.push_back(t);
		if (t->state == n->state)
			return true;
	}
	while (!temp.empty())
	{
		pq.push(temp.back());
		temp.pop_back();
	}
	return false;
}

void bestFirstSearch(Node* root, Node* goal)
{
	priority_queue<Node*, vector<Node*>, NodeCmp> openq;
	priority_queue<Node*, vector<Node*>, NodeCmp> closeq;
	openq.push(root);
	while (!openq.empty())
	{
		Node* current = openq.top();
		openq.pop();
		if (current->state == goal->state)
		{
			Solution(current);
			cout << "\nCo Goal " << endl;
			return;
		}
		for (Node* n : conAC(current))
			//node khong o trong open thi them vao open
			if (!inQueue(openq, n) && !inQueue(closeq, n))
				openq.push(n);

		for (Node* n : conAB(current))
			if (!inQueue(openq, n) && !inQueue(closeq, n))
				openq.push(n);

		for (Node* n : conBB(current))
			if (!inQueue(openq, n) && !inQueue(closeq, n))
				openq.push(n);

		for (Node* n : conEx(current))
			if (!inQueue(openq, n) && !inQueue(closeq, n))
				openq.push(n);
		//
		closeq.push(current);

	}

}

int h( Node* Child)
{
	int d = 0;
	for (int i = 0; i < Child->state.length() - 1; i++)
		if (Child->state[i] == 'E' || (Child->state[i] == 'A' && Child->state[i+1] == 'C'))
			d++;

	return d;
}
int Heuristic( Node* Child)
{
	int g = 0;
	g += path + Child->state.length() - h(Child);
	return g;
}

struct NodeCp
{
	bool operator()(const Node* ln, const Node* rn) const
	{
		//return Heuristic(ln) > Heuristic(rn);
		return ln->state.length() > rn->state.length(); 
	}
};

bool inQueue2(priority_queue<Node*, vector<Node*>, NodeCp> pq, Node* n)
{
	list<Node*> temp;
	while (!pq.empty())
	{
		Node* t = pq.top();
		pq.pop();
		temp.push_back(t);
		if (t->state == n->state)
			return true;
	}
	while (!temp.empty())
	{
		pq.push(temp.back());
		temp.pop_back();
	}
	return false;
}

void bestFS2(Node* root, Node* goal)
{
	priority_queue<Node*, vector<Node*>, NodeCp> openq;
	priority_queue<Node*, vector<Node*>, NodeCp> closeq;
	Node* f;
	openq.push(root);
	while (!openq.empty())
	{
		Node* current = openq.top();
		openq.pop();
		if (current->state == goal->state)
		{
			Solution(current);
			cout << "\nCo Goal " << endl;
			return;
		}
		for (Node* n : conAC(current))
			//node khong o trong open thi them vao open
			if (!inQueue2(openq, n) && !inQueue2(closeq, n))
			{
				path++;
				n->path_cost += path + n->state.length() - Heuristic(n);
				openq.push(n);
				//	n->path_cost++;
			}
		for (Node* n : conAB(current))
			if (!inQueue2(openq, n) && !inQueue2(closeq, n))
			{
				path++;
				n->path_cost += path + n->state.length() - Heuristic(n);
				openq.push(n);
				//	n->path_cost++;
			}

		for (Node* n : conBB(current))
			if (!inQueue2(openq, n) && !inQueue2(closeq, n))
			{
				path++;
				n->path_cost += path + n->state.length() - Heuristic(n);
				openq.push(n);
				//n->path_cost++;
			}

		for (Node* n : conEx(current))
			if (!inQueue2(openq, n) && !inQueue2(closeq, n))
			{
				path++;
				n->path_cost += path + n->state.length() - Heuristic(n);
				openq.push(n);
				//n->path_cost++;
			}
		//
		closeq.push(current);

	}
}

int main()
{
	Node* Start = new Node();
	Node* Goal = new Node();

	Goal->state = "E";
	cout << "Goal string: " << Goal->state << "\nInput start string: ";
	cin >> Start->state;

	Start->depth = 0;
	Start->path_cost = 0;
	//
	clock_t start, end;
	double cpu_time_used;


	start = clock();
	//BFS
	cout << "bestFS: " << endl;
	bestFirstSearch(Start, Goal);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << cpu_time_used;

	start = clock();
	cout << "BFS: " << endl;
	breadthFirstSearch(Start, Goal);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << cpu_time_used;

	start = clock();
	cout << "aStar" << endl;
	bestFS2(Start, Goal);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << cpu_time_used;

	return 0;

	//test ABABAEECBBACAC
}

