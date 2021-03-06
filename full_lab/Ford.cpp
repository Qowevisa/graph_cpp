#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct arc {
	int start_point = 0;
	int end_point = 0;
	int weight = 0;
};

class Graph {
	private:
		int num_of_vertices = 0;
		arc* arcs = nullptr;
		int num_of_arc = 0;
	public:
		void init();
		// Sort of debugging.
		void test();
		// real functions
		int add_arc(int ind_f, int ind_s);
		void delete_arc(int ind_to_del);
		arc reverse_arc(arc* scr);
		void conflict_finder();
		void arcs_weight();
		//
		void read_adj_matrix();
		void show_adj_matrix();
		//
		void read_inc_matrix();
		void show_inc_matrix();
		//
		void read_adj_list();
		void show_adj_list();
		//
		void ford_alg();
};

// Yes.
void Graph::init() {
	cout << "Enter the number of vertices:\n";
	// Validation
	while (num_of_vertices == 0 || Graph::num_of_vertices < 0) {
		cin >> num_of_vertices;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong type. Enter the number again:" << endl;
			cin >> num_of_vertices;
		}
		else if (num_of_vertices <= 0)
			cout << "No. You need to enter number which is more than 0:" << endl;
	}
}

// D is of De...
void Graph::test() {
	cout << "NVers = " << num_of_vertices << endl;
	cout << "NArcs = " << num_of_arc << endl;
	int len = num_of_arc;
	cout << "Arcs : ";
	for (int i = 0; i < len; i++) {
		int start = arcs[i].start_point;
		int end = arcs[i].end_point;
		printf("[%d,%d] ", start, end);
	}
	cout << endl;
}

// Arc
int Graph::add_arc(int ind_f, int ind_s) {
	if (arcs == nullptr) {
		arcs = (arc*)malloc(sizeof(arc));
		arcs[0].start_point = ind_f;
		arcs[0].end_point = ind_s;
		num_of_arc++;
	}
	else {
		num_of_arc++;
		int len = num_of_arc;
		arcs = (arc*)realloc(arcs, len * sizeof(arc));
		arcs[len - 1].start_point = ind_f;
		arcs[len - 1].end_point = ind_s;
	}
	return 1;
}

// Delete arc. // Hope it will work
void Graph::delete_arc(int ind_to_del) {
	int len = num_of_arc;
	num_of_arc--;
	int new_len = Graph::num_of_arc;
//	printf("l = %d ; nl = %d; d = %d\n", len, new_len, num_of_arc);
	arc* tmp_arcs = (arc*)malloc(new_len*sizeof(arc));
	// Copying every arc to tmp_arcs with ind != ind_to_del
	int k = 0;
	for (int i = 0; i < len; i++) {
		if (i != ind_to_del)
			tmp_arcs[k++] = arcs[i];
	}
//	cout << "TMPArcs : ";
//	for (int i = 0; i < k; i++) {
//		int start = tmp_arcs[i].start_point;
//		int end = tmp_arcs[i].end_point;
//		printf("[%d,%d] ", start, end);
//	}
//	printf("\n");
//	cout << "Arcs : ";
//	for (int i = 0; i < len; i++) {
//		int start = arcs[i].start_point;
//		int end = arcs[i].end_point;
//		printf("[%d,%d] ", start, end);
//	}
//	printf("\n");
	// Re-assinging
//	test();
	arcs = (arc*) realloc(arcs, new_len * sizeof(arc));
	for (int i = 0; i < new_len; i++)
		arcs[i] = tmp_arcs[i];
//	test();
}

// Reverse arc.
arc Graph::reverse_arc(arc* src) {
	arc dst;
	dst.start_point = (*src).end_point;
	dst.end_point = (*src).start_point;
	return dst;
}

// Find same arcs and repots about it.
void Graph::conflict_finder() {
	int len = num_of_arc;
	int i = 0;
	int j = 0;
	// When arcs are the same (ty user <3 )
	while (i < len - 1) {
		j = i + 1;
		arc cmp_arc = arcs[i];
		while (j < len) {
			if (arcs[j].start_point == cmp_arc.start_point &&
				arcs[j].end_point == cmp_arc.end_point) {
//					Graph::test();
					delete_arc(j);
//					cout << "JDeletion. After::" << endl;
//					Graph::test();
					break;
				}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	len = num_of_arc;
	// Reverse
	while (i < len) {
		j = i + 1;
		arc cmp_arc = reverse_arc(&Graph::arcs[i]);
		while (j < len) {
			if (arcs[j].start_point == cmp_arc.start_point &&
				arcs[j].end_point == cmp_arc.end_point) {
					// Start and end points for arc with i index
					int str = arcs[j].end_point;
					int end = arcs[j].start_point;
					// Giving user the opportunity to choose which one to delete.
					printf("Conflict found! Arc [%d,%d] and Arc [%d,%d] are in conflict!\n", str, end, end, str);
					printf("Which one you want to delete? 1 or 2? ");
					int inp = -1;
					cin >> inp;
					while (inp < 1 || inp > 2) {
						if (cin.fail()) {
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "You have entered wrong type. Enter the number again:" << endl;
							cin >> inp;
						}
						else if (inp < 1 && inp > 2)
							cout << "You shall enter only 1 or 2." << endl;
					}
					if (inp == 1) {
						delete_arc(i);
						i--;
						len--;
					}
					else {
						delete_arc(j);
						break;
					}
				}
			j++;
		}
		i++;
	}
}

//
void Graph::arcs_weight() {
	cout << "Enter the weight of arcs:\n";
	for (int i = 0; i < num_of_arc; i++) {
		printf("e%d | [%d, %d] :: ", i+1, arcs[i].start_point, arcs[i].end_point);
		int input = 0;
		cin >> input;
		while (input == 0 || input < 0) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You have entered wrong type. Enter the number again:" << endl;
				cin >> input;
			}
			else if (input <= 0)
				cout << "No. You need to enter number which is more than 0:" << endl;
		}
		arcs[i].weight = input;
	}
}

// Reading user input of Adjacency matrix and transfer to arcs
void Graph::read_adj_matrix() {
	int vers = num_of_vertices;
	
	cout << "   ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	for (int j = 0; j < 3+2*vers; j++) cout << '-';
	cout << endl;
	
	for (int index = 0; index < vers; index++) {
		cout << index+1 << " | ";
		int* row = (int*)malloc(vers*sizeof(int));
		int first_ind = index;
		int second_ind = 0;
		for (int i = 0; i < vers; i++) {
			cin >> row[i];
			if (row[i] != 0)
				// Desided to increse by one so it would be easier to calculate
				add_arc(index + 1, i + 1);
		}
	}
	
	// It has to be here. If user have written conflicting pares of arcs.
	conflict_finder();
	arcs_weight();
}

// Print arcs to Adjacency matrix 
void Graph::show_adj_matrix() {
	int vers = num_of_vertices;
	
	cout << "   ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	for (int j = 0; j < 3+2*vers; j++) cout << '-';
	cout << endl;
	
	for (int index = 0; index < vers; index++) {
		int* ends = (int*)calloc(vers, sizeof(int));
		for (int i = 0; i < num_of_arc; i++)
			if (arcs[i].start_point == index+1)
				ends[arcs[i].end_point - 1] = 1;
		
		cout << index+1 << " | ";
		for (int i =0; i < vers; i++)
			cout << ends[i] << ' ';
		cout << endl;
	}
}

// Reading user input of Incidence matrix and transfer to arcs
void Graph::read_inc_matrix() {
	cout << "Enter the number of arcs:\n";
	// Validation
	int arc_n = 0;
	while (arc_n == 0 || arc_n < 0) {
		cin >> arc_n;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong type. Enter the number again:" << endl;
			cin >> arc_n;
		}
		else if (arc_n <= 0)
			cout << "No. You need to enter number which is more than 0:" << endl;
	}
	
	int vers = num_of_vertices;
	
	cout << "    ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	for (int j = 0; j < 4+2*vers; j++) cout << '-';
	cout << endl;
	
	int count;
	int index = 0;
	while (index < arc_n) {
		cout << 'e' << index+1 << " | ";
		int str = -1;
		int end = -1;
		count = 0;
		int tmp;
		for (int i = 0; i < vers; i++) {
			cin >> tmp;
			if (tmp == -1 && str == -1) {
				str = i + 1;
				count++;
			}
			else if (tmp == 1 && end == -1) {
				end = i + 1;
				count++;
			}
		}
		if (count == 2) {
			add_arc(str, end);
			index++;
		}
		else {
			cout << "You have to enter at least once enter -1 AND 1 to create arc.\n";
		}
	}
	conflict_finder();
	arcs_weight();
}

// Print arcs to Incidence matrix
void Graph::show_inc_matrix() {
	int vers = num_of_vertices;
	
	cout << "    ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	for (int j = 0; j < 4+2*vers; j++) cout << '-';
	cout << endl;
	
	int count;
	int index = 0;
	for (int i = 0; i < num_of_arc; i++) {
		cout << "e" << i+1 << " | ";
		
		for (int j = 0; j < vers; j++)
			if (arcs[i].start_point == arcs[i].end_point && 
				arcs[i].start_point == j+1)
				cout << "2 ";
			else if (arcs[i].start_point == j+1)
				cout << "-1 ";
			else if (arcs[i].end_point == j+1)
				cout << "1 ";
			else cout << "0 ";
		cout << "\n";
	}
}

// Reading user input of Adjaacency list and transfer to arcs
void Graph::read_adj_list() {
	cout << "Invalid numbers will be skipped! Don't forget to put 0 in the end!\n";
	int vers = num_of_vertices;
	string str;
	cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
	int i = 0;
	int fail;
	while (i < vers) {
		cout << i+1 << " - ";
		getline(cin, str);
		// Empty input
		if (str == "0") {
			i++;
			continue;
		}
		// Find delimiter
		string del = "";
		fail = 0;
		int len = str.length();
		if (str.find(", ") > len) {
			if (str.find(" ") > len) {
				if (str.find(",") > len) {
					i--;
					fail = 1;
					cout << "Invalid string! Please ensure that you used at least some token.\n";
				}
				else
					del = ",";
			}
			else
				del = " ";
		}
		else
			del = ", ";
		
		if (fail == 0)
			while (str.find(del) < len) {
				string token = str.substr(0, str.find(del));
				str = str.substr(str.find(del)+del.length(), len);
				len = str.length();
				
				int tmp = stoi(token);
				if (tmp == 0)
					break;
				if (tmp > 0 && tmp <= vers)
					add_arc(i+1, tmp);
			}
		i++;
	}
	conflict_finder();
	arcs_weight();
}

// Print arcs to Adjacency list 
void Graph::show_adj_list() {
	for (int i = 0; i < num_of_vertices; i++) {
		cout << i+1 << " - ";
		for (int j = 0; j < num_of_arc; j++)
			if (arcs[j].start_point == i+1)
				cout << arcs[j].end_point << ", ";
			cout << "0\n";
	}
}

// Fords Algorithm
void Graph::ford_alg() {
	int vers = num_of_vertices;
	int* min_len = (int*)malloc(vers*sizeof(int));
	min_len[0] = 0;
	for (int i = 1; i < vers; i++) min_len[i] = -1;
	for (int i = 0; i < vers; i++)
		for (int j = i+1; j < vers; j++) {
			for (int arc_i = 0; arc_i < num_of_arc; arc_i++)
				if (arcs[arc_i].start_point == i+1 &&
					arcs[arc_i].end_point == j+1)
					if (min_len[j] == -1)
						min_len[j] = min_len[i] + arcs[arc_i].weight;
					else if (min_len[j] - min_len[i] > arcs[arc_i].weight)
						min_len[j] = min_len[i] + arcs[arc_i].weight;
		}
	cout << "Minimal root to every vertex\n";
	cout << "  ";
	for (int i = 0; i < vers; i++)
		cout << i+1 << " ";
	cout << "\n--";
	for (int i = 0; i < vers; i++) cout << "--";
	cout << "\n  ";
	for (int i = 0; i < vers; i++)
		cout << min_len[i] << " ";
	cout << "\n\n";
}


int main() {
	Graph g;
	int input = 0;
	int sub_input = 0;
	int created = 0;
	while (input != 4) {
		cout << "Menu:\n";
		cout << "1. Create the matrix\n";
		cout << "2. Print the matrix\n";
		cout << "3. Solve with Ford algorithm\n";
		cout << "4. Exit\n";
		cin >> input;
		cout << "\n";
		if (input == 2 && created == 0) {
			cout << "Matrix is not even created! There's nothing to print!\n\n";
			continue;
		}
		if (input == 1) {
			g.init();
			created = 1;
			cout << "\nHow do you want to create the matrix?\n";
			cout << "1. With Adjacency matrix\n";
			cout << "2. With Incidence matrix\n";
			cout << "3. With Adjacency list\n";
			cout << "4. Back\n";
			cin >> sub_input;
			cout << "\n";
			if (sub_input == 4) continue;
			if (sub_input == 1) g.read_adj_matrix();
			else if (sub_input == 2) g.read_inc_matrix();
			else if (sub_input == 3) g.read_adj_list();
			cout << "\n";
		}
		else if (input == 2) {
			cout << "In what way do you want to print the matrix?\n";
			cout << "1. As Adjacency matrix\n";
			cout << "2. As Incidence matrix\n";
			cout << "3. As Adjacency list\n";
			cout << "4. Back\n";
			cin >> sub_input;
			cout << "\n";
			if (sub_input == 4) continue;
			if (sub_input == 1) g.show_adj_matrix();
			else if (sub_input == 2) g.show_inc_matrix();
			else if (sub_input == 3) g.show_adj_list();
			cout << "\n";
		}
		else if (input == 3) {
			g.ford_alg();
		}
	}
	return 0;
}
