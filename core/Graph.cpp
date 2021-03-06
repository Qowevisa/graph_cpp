#include <iostream>
#include <string>
#include <limits>
#include "Graph.h"

using namespace std;

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
	arc* tmp_arcs = (arc*)malloc(new_len*sizeof(arc));
	// Copying every arc to tmp_arcs with ind != ind_to_del
	int k = 0;
	for (int i = 0; i < len; i++) {
		if (i != ind_to_del)
			tmp_arcs[k++] = arcs[i];
	}
	arcs = (arc*) realloc(arcs, new_len * sizeof(arc));
	for (int i = 0; i < new_len; i++)
		arcs[i] = tmp_arcs[i];
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


