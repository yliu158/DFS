#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

const int MAX_E_PER_V = 4;
vector<list<int> > graph; // graph
vector<int> color; // visited 1 fully visited 2
vector<int> parent; // parent index starting from 0

//declaration of functions
void execute(); // all executable lines
int getInput(); // get size of vertices from user
void prepareGraph(); // prepare the graph
void DFS(int v); // Depth First Search
void printGraph(); // print graph using list
void printStatus();

int main(int argc, char const *argv[]) {
  execute();
  return 0;
}

// implementation of functions

void execute() {
  srand(time(NULL));
  string input = "";
  bool sign = true;
  while (sign) {

    prepareGraph();
    int start_v = rand()%graph.size();
    DFS(start_v);
    printStatus();

    cout << "Press any other button to continue." << endl;
    cout << "Press e to Exit." << endl;
    cin >> input;
    if (input[0] == 'e' || input[0] == 'E') {
      sign = false;
    }

    while (cin.fail()) {
      cin.clear();
      cin.ignore();
      cin >> input;
      if (input[0] == 'e' || input[0] == 'E') {
         sign = false;
      }
    }
  }
  cout << "Successfully Exited" << endl;
}

// get the size of matrix from user
int getInput() {
  cout << "Please input number of vertices: ";
  int n = 0;
  cin >> n;
  while (cin.fail()) {
    cin.clear();
    cin.ignore();
    cout << "\nPlease input number of vertices: ";
    cin >> n;
  }

  while (n < 5 || n >10) {
    cout << "Please input number of vertices.\n";
    cout << "Please input a value between 5 and 10(inclusive): ";
    cin >> n;
    while (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout << "\nPlease input number of vertices.";
      cout << "Please input a value between 5 and 10(inclusive): ";
      cin >> n;
    }
  }
  return n;
}


// get graph prepared
void prepareGraph(){
  int max_vertices = getInput();
  graph = vector<list<int> >(max_vertices, list<int>());
  color = vector<int>(max_vertices, 0);
  parent = vector<int> (max_vertices, -1);
  set<int> s = set<int>();

  for (int i = 0; i < max_vertices; i++) {
    int size = rand()%max_vertices;
    s.clear();
    for (int j = 0; j < size && j < MAX_E_PER_V; j++) {
      int v = rand()%max_vertices;
      if (v != i) {
        set<int>::iterator it = s.find(v);
        if (it == s.end()){
          graph.at(i).push_back(v);
          s.insert(v);
        }
      }
    }
  }
  printGraph();
}

void DFS(int v) {
  if (color[v] == 0) {
    color[v] = 1;
    for (list<int>::iterator it = graph.at(v).begin(); it != graph.at(v).end(); ++it) {
      if (color[*it] == 0) {
        cout << "visited: " << *it << endl;
        parent[*it] = v;
      }
      DFS(*it);
    }
    color[v] = 2;
  }
}


// print the graph
void printGraph() {
  for (int i = 0; i < graph.size(); i++){
    list<int> vertices = graph.at(i);
    cout << "V:[" << i << "]->{";
    for (list<int>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      cout << *it << " ";
    }
    cout << "}" << endl;
  }
}

// print status of visiting
void printStatus() {
  for (int i = 0; i < color.size(); i++) {
    if (color[i] == 0) {
      cout << "vertices " << i << " not visited.";
    } else if (color[i] == 1) {
      cout << "vertices " << i << " visited but not explored.";
    } else {
      cout << "vertices " << i << " finished exploring.";
    }
    cout << " parent: " << parent[i] << endl;
  }
}
