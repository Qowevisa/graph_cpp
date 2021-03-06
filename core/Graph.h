#ifndef CORE
#define CORE

using namespace std;

struct arc {
	int start_point = 0;
	int end_point = 0;
	int weight = 0;
};

class Graph {
	int num_of_vertices = 0;
	arc* arcs = nullptr;
	int num_of_arc = 0;
public:
	void init();
	int add_arc(int ind_f, int ind_s);
	void delete_arc(int ind_to_del);
	arc reverse_arc(arc* scr);
	void conflict_finder();
	void arcs_weight();
	//
	void ford_alg();
	// Access to private members
	int get_nov() { return num_of_vertices; }
	arc* get_arcs() { return arcs; }
	int get_noa() { return num_of_arc; }
};

#endif // CORE
