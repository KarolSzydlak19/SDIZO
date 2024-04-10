#include"Amatrix.h"
#include<string>
#include<iostream>
#include<fstream>
#include<string.h>
#include<Windows.h>
#include <conio.h>
#include<queue>
#include<vector>
#include<list>
#include<algorithm>
#include<climits>
#include<queue>
#include <random>
using namespace std;

Amatrix::Amatrix() {

}
Amatrix::~Amatrix() {

}

int Amatrix::loadFromFileMST(string FileName) {		//wczytanie z pliku dla shortpath
	if (matrix != nullptr) {
		for (int i = 0; i < nodeCnt; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "nofile" << endl;
		return 1;
	}
	iFile >> edgeCnt;
	iFile >> nodeCnt;
	iFile >> param;
	int startNode;
	int endNode;
	int val;
	matrix = new int* [nodeCnt];
		for (int i = 0; i < nodeCnt; i++) {
			matrix[i] = new int[nodeCnt];
		}
		for (int i = 0; i < nodeCnt; i++) {
			for (int j = 0; j < nodeCnt; j++) {
				matrix[i][j] = 0;
			}
		}
		for (int i = 0; i < edgeCnt; i++) {
			iFile >> startNode;
			iFile >> endNode;
			iFile >> val;
			matrix[startNode][endNode] = val;
		}	
}
int Amatrix::loadFromFileForMST(string FileName) {
	if (matrix != nullptr) {
		for (int i = 0; i < nodeCnt; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
	ifstream iFile;
	iFile.open(FileName);
	if (!iFile.is_open()) {
		cout << "nofile" << endl;
		return 1;
	}
	iFile >> edgeCnt;
	iFile >> nodeCnt;
	//iFile >> param;
	param = 0;
	int startNode;
	int endNode;
	int val;
	matrix = new int* [nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		matrix[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < edgeCnt; i++) {
		iFile >> startNode;
		iFile >> endNode;
		iFile >> val;
		matrix[startNode][endNode] = val;
		matrix[endNode][startNode] = val;
	}
}
void Amatrix::printMatrix() {
	cout << "Macierz sasiedztwa:" << endl;
	cout << "  ";
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
	}
	/*cout << endl;
	for (int i = 0; i < nodeCnt+4; i++) {
		cout << "--";
	}*/
	cout << endl;
	for (int i = 0; i < nodeCnt; i++) {
		//cout << "| "<< i<<"|";
		cout << i << " ";
		for (int j = 0; j < nodeCnt; j++) {
			cout << matrix[i][j] << " ";
		}
		//cout << " |";
		cout << endl;
	}
}
float Amatrix::PrimAlgorithm() {
	/*if (matrix == nullptr) {
		return 0;
	}
	int** mst;
	mst = new int* [nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		mst[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			mst[i][j] = 0;
		}
	}

	int* key = new int[nodeCnt];
	int* p = new int[nodeCnt];
	bool* rozp = new bool[nodeCnt];  // Indicates if the node is included in the MST
	for (int i = 0; i < nodeCnt; i++) {
		key[i] = INT_MAX;
		p[i] = -1;
		rozp[i] = false;
	}

	key[0] = 0;
	p[0] = 0;

	for (int count = 0; count < nodeCnt - 1; count++) {
		int u = MinKey(key, rozp);

		rozp[u] = true;

		for (int v = 0; v < nodeCnt; v++) {
			if (matrix[u][v] != 0 && !rozp[v] && matrix[u][v] < key[v]) {
				p[v] = u;
				key[v] = matrix[u][v];
			}
		}
	}

	int sum = 0;
	for (int j = 0; j < nodeCnt; j++) {
		sum += key[j];
		mst[p[j]][j] = key[j];
		mst[j][p[j]] = key[j];
	}

	// Print 
	cout << "  ";
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
		for (int j = 0; j < nodeCnt; j++) {
			cout << mst[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Wartosc sumaryczna: " << sum << endl;

	return **mst;
}

int Amatrix::MinKey(int* key, bool* rozp) {
	int minKey = INT_MAX;
	int minIndex = -1;

	for (int v = 0; v < nodeCnt; v++) {
		if (!rozp[v] && key[v] < minKey) {
			minKey = key[v];
			minIndex = v;
		}
	}

	return minIndex;*/
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	if (matrix == nullptr) {
		return 0;
	}
	int** mst;
	mst = new  int*[nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		mst[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			mst[i][j] = 0;
		}
	}
	int *key = new int[nodeCnt];
	int* p = new int[nodeCnt];
	int* rozp = new int[nodeCnt];
	int* nierozp = new int[nodeCnt];
	int nodesAdded = nodeCnt;
	for (int i = 0; i < nodeCnt; i++) {
		key[i] = INT_MAX;
		p[i] = -1;
		rozp[i] = 0;
		nierozp[i] = 1;
	}
	key[0] = 0;
	p[0] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	for (int i = 0; i < nodeCnt; i++) {
		Q.push(make_pair(key[i], i));
	}
	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if (rozp[u] == 0) {
			for (int i = 0; i < nodeCnt; i++) {
				int v = matrix[u][i];
				if (matrix[u][i] < key[i]&&rozp[i]==0&&v>0) {
					key[i] = matrix[u][i];
					p[i] = u;
					Q.push(make_pair(key[i], i));
				}
			}
		}
		rozp[u] = 1;
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	cout << endl;
	int sum = 0;
	for (int j = 0; j < nodeCnt; j++) {
		sum = sum + key[j];
		cout << p[j] << " ";
	}
	cout << endl;
	for (int i = 0; i < nodeCnt; i++) {
		if (p[i] == -1) {
			p[i] = i;
		}
	}
	for (int j = 0; j < nodeCnt; j++) {
		mst[p[j]][j] = key[j];
		mst[j][p[j]] = key[j];
	}
	cout << "  ";
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
		for (int j = 0; j < nodeCnt; j++) {
			cout << mst[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Wartosc sumaryczna: " << sum << endl;
	return time;
}
float Amatrix::Djikstra() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	if (matrix == nullptr) {
		return 1;
	}
	int* MB = new int[nodeCnt];
	int mbcnt = 0;
	int* d = new int[nodeCnt];
	int* p = new int[nodeCnt];
	int* rozp = new int[nodeCnt];
	int* visited = new int[nodeCnt];
	int visCnt = 0;		//tworzenie listy s¹siadów
	for (int i = 0; i < nodeCnt; i++) {
		d[i] = INT_MAX;
		p[i] = -1;
		rozp[i] = 0;
	}
	d[param] = 0;
	visited[visCnt] = param;
	visCnt++;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	//priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> D;
	for (int i = 0; i < nodeCnt; i++) {
		Q.push(make_pair(d[i], i));		//dodanie numeru wierzcho³ka powi¹zaniego z przebyt¹ drog¹ do kolejki priorytetowej
	}
	while (!Q.empty()) {
		int u = Q.top().second;
		//MB[mbcnt] = u;
		mbcnt++;
		Q.pop();
		if (rozp[u] == 0) {								//sprawdzenie czy wierzcho³ek by³ ju¿ rozpatrzony
			for (int i = 0; i < nodeCnt; i++) {
				int v = matrix[u][i];
				if (d[i] > d[u] + matrix[u][i]&&v>0) {
					d[i] = d[u] + matrix[u][i];			
					p[i] = u;
					Q.push(make_pair(d[i], i));
				}
			}
			rozp[u] = 1;
		}
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	int cost = 0;
	for (int i = 0; i < nodeCnt; i++) {
		cost = cost + d[i];
	}
	p[param] = 0;
	vector<vector<int>> path;
	vector<int> nodePath;
	for (int i = 0; i < nodeCnt; i++) {
		nodePath.push_back(i);
		int j = i;
		int weigh = 0;
		int prevW = 0;
		//cout << i << ": ";
		weigh = d[i];
		while (1) {
			nodePath.push_back(p[j]);
			if (p[j] == 0) {
				break;
			}
			j = p[j];
		}
		//cout << weigh << endl;
		nodePath.push_back(weigh);
		path.push_back(nodePath);
		nodePath.clear();
		cout << endl;
	}
	for (int i = 0; i < nodeCnt; i++) {
		nodePath = path[i];
		int weigh = nodePath[nodePath.size() - 1];
		cout << i << ": ";
		int k = nodePath.size() - 2;
		while (k > 0) {
			cout << nodePath[k] << " ";
			k--;
			if (k < 0) {
				break;
			}
		}
		cout << i << "      |" << weigh << endl;
		//cout << endl;
	}
	return time;

}

float Amatrix::Kruskal() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	if (matrix == nullptr) {
		return 0 ;
	}
	int sum = 0;
	int** mst;
	mst = new  int* [nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		mst[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			mst[i][j] = 0;
		}
	}
	struct Kedge {
		int start;
		int end;
		int weigh;
		Kedge() {};
	};

	struct Compare {
		bool operator()(const Kedge& a, const Kedge& b) const {
			return a.weigh > b.weigh;  
		}
	};
	priority_queue < Kedge, vector<Kedge>, Compare> sE;			//kolejka priorytetowa zawieraj¹ca krawêdzie

	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			if (matrix[i][j] != 0) {
				Kedge edge;
				edge.start = i;
				edge.end = j;
				edge.weigh = matrix[i][j];
				sE.push(edge);
			}
		}
	}
	//makeset:
	int* parent = new int[nodeCnt];
	int* rank = new int[nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
	while (!sE.empty()) {
		Kedge edge;
		edge = sE.top();
		sE.pop();
		if (FindSet(parent,edge.start) != FindSet(parent,edge.end)) {	//jesli krawedzie nie tworza cyklu i naleza do roznych poddrzew sa dodawane
			mst[edge.start][edge.end] = edge.weigh;
			mst[edge.end][edge.start] = edge.weigh;
			sum = sum + edge.weigh;
			Union(edge.start, edge.end, parent, rank);
		}
	}
	QueryPerformanceCounter(&endTime);
	diffTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	float time = ((float)diffTime.QuadPart * 1000) / frequency.QuadPart;
	cout << "Wartosc sumaryczna: " << sum << endl;
	cout << "  ";
	for (int j = 0; j < nodeCnt; j++) {
		cout << j << " ";
	}
	cout << endl;
	for (int i = 0; i < nodeCnt; i++) {
		cout << i << " ";
		for (int j = 0; j < nodeCnt; j++) {
			cout << mst[i][j] << " ";
		}
		cout << endl;
	}
	return time;

}
int Amatrix::FindSet(int *parent, int x) {
	if (parent[x] != x) {
		parent[x] = FindSet(parent,parent[x]);
	}
	
	return parent[x];
}
void Amatrix::Union(int x, int y, int* parent, int *rank) {
	int a = FindSet(parent,x);
	int b = FindSet(parent,y);
	if (rank[a] < rank[b]) {
		parent[a] = b;
	}
	else {
		parent[b] = parent[a];
	}
	if (rank[a] = rank[b]) {
		rank[a] = rank[a] + 1;
	}
}
int Amatrix::generateUndirected(int v, int p) {
	int maxV = (v * (v - 1)) / 2;
	float perc = p / 100.0;
	if (perc < (1.0 / (v - 1))) {
		perc = float((1.0 / (v - 1)));
	}
	int edges = maxV * perc;
	if (matrix != nullptr) {
		for (int i = 0; i < nodeCnt; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
	nodeCnt = v;
	edgeCnt = edges;
	param = 0;
	matrix = new int* [nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		matrix[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			matrix[i][j] = 0;
		}
	}
	int* rozp = new int[nodeCnt];
	int* nierozp = new int[nodeCnt];
	int* av = new int[nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		rozp[i] = 0;
		nierozp[i] = 1;
		av[i] = i;
	}
	int count = 0;
	bool mst = false;
	while (!mst) {
		int u, v, w;
		u = rand() % (nodeCnt);
		v = rand() % (nodeCnt);
		w = rand() % 9+1;
		if ((rozp[u] == 0 || rozp[v] == 0)&&u!=v) {
			rozp[u] = 1;
			rozp[v] = 1;
			matrix[u][v] = w;
			matrix[v][u] = w;
			count++;
		}
		mst = true;
		for (int j = 0; j < nodeCnt; j++) {
			if (rozp[j] == 0) {
				mst = false;
			}
		}

	}
	if (count > edges) {
		edgeCnt = count;
	}
	int u, w;
	while (count < edgeCnt) {
		u = rand() % (nodeCnt);
		v = rand() % (nodeCnt);
		if (matrix[u][v] == 0&&u!=v) {
			w = rand() % 9+1;
			matrix[u][v] = w;
			matrix[v][u] = w;
			count++;
		}
	}

	return nodeCnt;
}

int Amatrix::generateDirected(int v, int p) {
	int maxV = v*(v-1);
	float perc = p / 100.0;
	if (perc < (1.0 / (v - 1))) {
		perc = float((1.0 / (v - 1)));
	}
	int edges = maxV * perc;
	if (matrix != nullptr) {
		for (int i = 0; i < nodeCnt; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
	}
	nodeCnt = v;
	edgeCnt = edges;
	param = rand() %nodeCnt;
	matrix = new int* [nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		matrix[i] = new int[nodeCnt];
	}
	for (int i = 0; i < nodeCnt; i++) {
		for (int j = 0; j < nodeCnt; j++) {
			matrix[i][j] = 0;
		}
	}
	int* rozp = new int[nodeCnt];
	int* dojsc = new int[nodeCnt];
	int* hasEdge = new int[nodeCnt];
	for (int i = 0; i < nodeCnt; i++) {
		rozp[i] = 0;
		dojsc[i] = 0;
		hasEdge[i] = 0;
	}
	int count = 0;
	bool mst = false;
	int first = 0;
	int last = 0;
	int u, w;
	int currStart;
	u = rand() % (nodeCnt);
	v = rand() % (nodeCnt);
	w = rand() % 9 + 1;
	dojsc[u] = 1;
	rozp[u] = 1;
	dojsc[v] = 1;
	matrix[u][v] = w;
	hasEdge[u] = 1;
	count++;
	currStart = v;
	bool loop = false;
	first = u;
	while (!loop) {
		u = currStart;
		v = rand() % (nodeCnt);
		w = rand() % 9 + 1;
		if ((dojsc[v] == 0) && u != v) {
			matrix[u][v] = w;
			hasEdge[u] = 1;
			rozp[u] = 1;
			dojsc[v] = 1;
			last = v;
			currStart = v;
			count++;
		}
		loop = true;
		for (int i = 0; i < nodeCnt; i++) {
			if (dojsc[i] == 0) {
				loop = false;
			}
		}
		for (int j = 0; j < nodeCnt; j++) {
			if (hasEdge[j] == 0) {
				last = j;
			}
		}
	}
	int we = rand() % 9 + 1;
	matrix[last][first] = we;
	count++;
	//petla:
	/*int u, w;
	u = rand() % (nodeCnt);
	v = rand() % (nodeCnt);
	w = rand() % 9+1;
	dojsc[u] = 1;
	rozp[u] = 1;
	dojsc[v] = 1;
	matrix[u][v] = w;
	hasEdge[u] = 1;
	count++;
	bool loop = false;
    first = u;
	while (!loop) {
		u = rand() % (nodeCnt);
		v = rand() % (nodeCnt);
		w = rand() % 9+1;
		for (int i = 0; i < nodeCnt; i++) {
			cout << dojsc[i] << " ";
		}
		cout << endl << "---------------" << endl;
		for (int i = 0; i < nodeCnt; i++) {
			cout << rozp[i] << " ";
		}
		cout <<endl<< "---------------" << endl;
		if ((rozp[u] == 0 && dojsc[v] == 0)&&u!=v) {
			matrix[u][v] = w;
			hasEdge[u] = 1;
			rozp[u] = 1;
			dojsc[v] = 1;
			last = v;
			count++;
		}
		loop = true;
		for (int i = 0; i < nodeCnt; i++) {
			if (dojsc[i] == 0) {
				loop = false;
			}
		}
		for (int j = 0; j < nodeCnt; j++) {
			if (hasEdge[j] == 0) {
				last = j;
			}
		}

	}
	for (int i = 0; i < nodeCnt; i++) {
		cout << dojsc[i]<<" ";
	}
	cout << endl;
	int we = rand() % 9+1;
	matrix[last][first] = we;
	count++;*/
	if (count > edges) {
		edgeCnt = count;
	}
	while (count < edgeCnt) {
		u = rand() % (nodeCnt);
		v = rand() % (nodeCnt);
		if (matrix[u][v] == 0 && u != v) {
			w = rand() % 9+1;
			matrix[u][v] = w;
			count++;
		}
	}
	return nodeCnt;
}

void Amatrix::SPmeasure() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	char opt;
	int mesCount = 0;
	int size = 0;
	int min, max = 0;
	int index = 0;
	int value;
	bool result = false;
	int* nodes = new int[7];
	int* p = new int[3];
	p[0] = 20;
	p[1] = 60;
	p[2] = 99;
	nodes[0] = 10;
	nodes[1] = 20;
	nodes[2] = 30;
	nodes[3] = 40;
	nodes[4] = 50;
	nodes[5] = 60;
	nodes[6] = 70;
	ofstream aFile, lFile;
	aFile.open("Pomiary/AM_Djikstra");
	if (aFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				generateDirected(nodes[j],p[i]);
				float time = Djikstra();
				if (aFile.is_open()) {
					aFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	if (aFile.is_open()) {
		aFile.close();
	}
}

void Amatrix::MSTmeasure() {
	LARGE_INTEGER startTime, endTime, diffTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	char opt;
	int mesCount = 0;
	int size = 0;
	int min, max = 0;
	int index = 0;
	int value;
	bool result = false;
	int* nodes = new int[7];
	int* p = new int[3];
	p[0] = 20;
	p[1] = 60;
	p[2] = 99;
	nodes[0] = 10;
	nodes[1] = 20;
	nodes[2] = 30;
	nodes[3] = 40;
	nodes[4] = 50;
	nodes[5] = 60;
	nodes[6] = 70;
	ofstream aFile, bFile;
	aFile.open("Pomiary/AM_Prim");
	bFile.open("Pomiary/AM_Kruskal");
	if (aFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	if (bFile.is_open()) {
		aFile << "";
		aFile << "Czas operacji[ms]\tV\tGestosc" << endl;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				generateUndirected(nodes[j], p[i]);
				float time = PrimAlgorithm();
				if (aFile.is_open()) {
					aFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int n = 0; n < 50; n++) {
				generateUndirected(nodes[j], p[i]);
				float time = Kruskal();
				if (bFile.is_open()) {
					bFile << time << "\t\t\t" << nodes[j] << "\t\t\t" << p[i] << endl;
				}
			}
		}
	}
	if (aFile.is_open()) {
		aFile.close();
	}
	if (bFile.is_open()) {
		bFile.close();
	}
}
