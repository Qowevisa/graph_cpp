#include <iostream>
#include <limits>
#include "GC.h"

using namespace std;

// Reading user input of Adjacency matrix and transfer to this->get_arcs()
void GC::read_adj_matrix() {
	int vers = this->get_nov();
	
	cout << "   ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	cout << string(3+2*vers, '-') << endl;
	
	for (int index = 0; index < vers; index++) {
		cout << index+1 << " | ";
		int* row = (int*)malloc(vers*sizeof(int));
		for (int i = 0; i < vers; i++) {
			cin >> row[i];
			if (row[i] != 0)
				// Desided to increse by one so it would be easier to calculate
				g::add_arc(index + 1, i + 1);
		}
	}
	
	// It has to be here. If user have written conflicting pares of this->get_arcs().
	g::conflict_finder();
	this->get_arcs()_weight();
}

// Print this->get_arcs() to Adjacency matrix 
void GC::show_adj_matrix() {
	int vers = this->get_nov();
	
	cout << "   ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	cout << string(3+2*vers, '-') << endl;
	
	for (int index = 0; index < vers; index++) {
		int* ends = (int*)calloc(vers, sizeof(int));
		for (int i = 0; i < this->get_noa(); i++)
			if (this->get_arcs()[i].start_point == index+1)
				ends[this->get_arcs()[i].end_point - 1] = 1;
		
		cout << index+1 << " | ";
		for (int i =0; i < vers; i++)
			cout << ends[i] << ' ';
		cout << endl;
	}
}

// Reading user input of Incidence matrix and transfer to this->get_arcs()
void GC::read_inc_matrix() {
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
	
	int vers = this->get_nov();
	
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
			g::add_arc(str, end);
			index++;
		}
		else {
			cout << "You have to enter at least once enter -1 AND 1 to create arc.\n";
		}
	}
	g::conflict_finder();
	this->get_arcs()_weight();
}

// Print this->get_arcs() to Incidence matrix
void GC::show_inc_matrix() {
	int vers = this->get_nov();
	
	cout << "    ";
	for (int j = 0; j < vers; j++) cout << ' ' << j+1;
	cout << endl;
	cout << string(4+2*vers, '-') << endl;
	
	int count;
	int index = 0;
	for (int i = 0; i < this->get_noa(); i++) {
		cout << "e" << i+1 << " | ";
		
		for (int j = 0; j < vers; j++)
			if (this->get_arcs()[i].start_point == this->get_arcs()[i].end_point && 
				this->get_arcs()[i].start_point == j+1)
				cout << "2 ";
			else if (this->get_arcs()[i].start_point == j+1)
				cout << "-1 ";
			else if (this->get_arcs()[i].end_point == j+1)
				cout << "1 ";
			else cout << "0 ";
		cout << "\n";
	}
}

// Reading user input of Adjaacency list and transfer to this->get_arcs()
void GC::read_adj_list() {
	cout << "Invalid numbers will be skipped! Don't forget to put 0 in the end!\n";
	int vers = this->get_nov();
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
					g.add_arc(i+1, tmp);
			}
		i++;
	}
	g::conflict_finder();
	this->get_arcs()_weight();
}

// Print arcs to Adjacency list 
void GC::show_adj_list() {
	for (int i = 0; i < this->get_nov(); i++) {
		cout << i+1 << " - ";
		for (int j = 0; j < this->get_noa(); j++)
			if (this->get_arcs()[j].start_point == i+1)
				cout << this->get_arcs()[j].end_point << ", ";
			cout << "0\n";
	}
}

// Whole interface for user
int GC::loop() {
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
}

