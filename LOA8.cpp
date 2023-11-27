#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <fstream>  

#define X 3
#define Y 1
#define Z 1

using namespace std; // ��������� ��� ������������� ������������ ���� std

struct Node {
	int data;
	Node* next;
};


// ��������� ��� ������������� �������� �������
struct QueueNode {
	int data;
	QueueNode* next;
};

// ��������� ��� ������������� �������
struct Queue {
	QueueNode* front;
	QueueNode* rear;
};

// ������������� ������ �������
Queue* createQueue() {
	Queue* queue = new Queue;
	queue->front = queue->rear = nullptr;
	return queue;
}

// ��������, ����� �� �������
bool isEmpty(Queue* queue) {
	return queue->front == nullptr;
}

// ������� ������ ������ ���������
void printAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		cout << "������� " << i << " ������ � : ";
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
}

// ������� �������������� ������� ��������� � ������ ��������� � �������� �������� �������� ������
Node** adjacencyMatrixToAdjacencyList(int** matrix, int size) {
	Node** adjacencyList = new Node * [size];

	for (int i = 0; i < size; i++) {
		adjacencyList[i] = nullptr;  // ������������� ������� 

		for (int j = size - 1; j >= 0; j--) { // �������� ���� ��� ���������� ������ � �������� ������� 
			if (matrix[i][j] == 1) {
				Node* newNode = new Node;
				newNode->data = j;
				newNode->next = adjacencyList[i];
				adjacencyList[i] = newNode;
			}
		}
	}

	return adjacencyList;
}


// ������� ����������� ������ ������ ��������� 
void freeAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] adjacencyList;
}

// ������� ��� ��������� ������ ��� ��������� ������
int** createMatrix(int size) {
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	return matrix;
}

// ������� ��� ������������ ������, ���������� ��� �������
void deleteMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// ������� ��� ���������� ������� ���������� ����������
void fillMatrixRandom(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else {
				int randomValue = rand() % 2;
				matrix[i][j] = randomValue;
				matrix[j][i] = randomValue; // ������� �����������
			}
		}
	}
}

// ������� ��� ������ ������� � ����������, ������������ ��������
void printMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j];
			cout << " ";

		}
		cout << endl;
	}
}

int* breadthFirstSearch(int** graph, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // Initially, mark all vertices as not visited
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (graph[currentVertex][i] == 1 && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	return traversalOrder;
}

int* bfsTraversal(Node** adjacencyList, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // ���������� ��� ������� �� ���������� 
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		// ������ �� ������� �������� ������ ��������� 
		Node* current = adjacencyList[currentVertex];
		while (current != nullptr) {
			int neighbor = current->data;
			if (!visited[neighbor]) {
				q.push(neighbor);
				visited[neighbor] = true;
			}
			current = current->next;
		}
	}

	delete[] visited;
	return traversalOrder;
}

// ������� ��� ���������� ������� � ������ ���������
void addEdge(Node** adjacencyList, int vertex, int data) {
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = adjacencyList[vertex];
	adjacencyList[vertex] = newNode;
}

// ���������� �������� � �������
void enqueue(Queue* queue, int data) {
	QueueNode* newNode = new QueueNode;
	newNode->data = data;
	newNode->next = nullptr;

	if (isEmpty(queue)) {
		queue->front = queue->rear = newNode;
		return;
	}

	queue->rear->next = newNode;
	queue->rear = newNode;
}

// ���������� �������� �� �������
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		cerr << "������� �����!" << endl;
		return -1; // ���������� -1, ����� ���������� ������
	}

	int data = queue->front->data;
	QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	delete temp;

	if (queue->front == nullptr) {
		queue->rear = nullptr; // ���� ������� ����� ������
	}

	return data;
}

int* BFScustomList(int** matrix, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // ���������� ��� ������� �� ���������� 
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	Queue* queue = createQueue();
	enqueue(queue, startVertex);
	visited[startVertex] = true;

	while (!isEmpty(queue)) {
		int currentVertex = dequeue(queue);
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (matrix[currentVertex][i] == 1 && !visited[i]) {
				enqueue(queue, i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	delete(queue);

	return traversalOrder;
}

int main() 
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int choice;

	cout << "\t\t\t\t\t\t8 ������������ ������" << endl;

	do {
		// ���������� ����
		cout << "����:" << endl;
		cout << "1) ��������� ������� � ����� � ������" << endl;
		cout << "2) ���� ���������� ������ � ������" << endl;
		cout << "3) �����" << endl;

		// ����������� ����� ������������
		cout << "����������, ������� ����� ���������� ������: ";
		cin >> choice;

		// ��������� ������ ������������
		switch (choice) {
		case 1: {
			cout << "�� ������� ����� �1" << endl;

			// 1 ������� 
			int size;
			cout << "\n������� ������ ������� ���������: ";
			cin >> size;
			int** adjacencyMatrix = createMatrix(size);
			fillMatrixRandom(adjacencyMatrix, size);
			printMatrix(adjacencyMatrix, size);

			// ������� ������� ��������� � ������ ��������� � ��� �����
			cout << "\n������ ���������:\n";
			Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
			printAdjacencyList(adjacencyList, size);

			int startVertex;
			cout << "\n������� ��������� ������� ��� ������: ";
			cin >> startVertex; cout << "\n";

			int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);

			for (int i = 0; i < size; i++) {
				cout << traversalOrder[i] << " ";
			}

			cout << " �breadthFirstSearch\n" << endl;
			delete[] traversalOrder;

			int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);


			for (int i = 0; i < size; i++) {
				cout << traversalOrder1[i] << " ";
			}
			cout << " bfsTraversal\n" << endl;

			delete[] traversalOrder1;

			int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);

			for (int i = 0; i < size; i++) {
				cout << traversalOrder2[i] << " ";
			}

			delete[] traversalOrder2;

			cout << " BFScustomList\n" << endl;

			deleteMatrix(adjacencyMatrix, size);

			break; 
		}

		// 2 �������
		case 2: 
		{
			int num_vertex;
			cout << "\n�� ������� ����� �2" << endl;
			cout << "\n������� ���������� ������ �����: ";
			cin >> num_vertex;
			cout << "\n";
			// ������ ����� ��� ������ 
			int* sizes = new int [X * Y * Z];

			for (int i = 0; i < X; i++)
			{
				for (int j = 0; j < Y; j++)
				{
					for (int k = 0; k < Z; k++) {
						*(sizes + i * Y * Z + j * Z + k) = num_vertex;
					}
				}
			}

			// ��������� ���� ��� ������ 
			ofstream outputFile("Test_time.txt");
			if (!outputFile.is_open()) {
				cerr << "������ ��� ��������� �����." << endl;
				return 1;
			}

			outputFile << "������ �������\t  BFS ������� \t  BFS ������ \t   BFS ����\n";

			for (int i = 0; i < X; i++) {
				int size = sizes[i];
				int** adjacencyMatrix = createMatrix(size);
				fillMatrixRandom(adjacencyMatrix, size);

				Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
				int startVertex = 0;

				clock_t startTime, endTime;

				startTime = clock();
				int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsMatrixTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder;

				startTime = clock();
				int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);
				endTime = clock();
				double bfsListTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder1;


				startTime = clock();
				int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsCustomTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder2;

				outputFile << " \t" << size << "\t\t\t" << bfsMatrixTime << "\t\t\t" << bfsListTime << "\t\t\t" << bfsCustomTime << "\n";

				deleteMatrix(adjacencyMatrix, size);
				freeAdjacencyList(adjacencyList, size);
			}
			delete[] sizes;

			outputFile.close();

			break; }
		case 3:
			cout << "�����." << endl;
			break;
		default:
			cout << "\n������������ �����. ����������, ������� ������ ����� ������." << endl;
			break;
		}

	} while (choice != 3); // ����� �� ���� ��� ������ "�����" (����� 4)

	return 0;
}
