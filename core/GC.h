#ifndef GC
#define GC
#include "Graph.h"

using namespace std;

class GC {
	Graph g;
	void read_adj_matrix();
	void show_adj_matrix();
	//
	void read_inc_matrix();
	void show_inc_matrix();
	//
	void read_adj_list();
	void show_adj_list();
public:
	int loop();
};

#endif // GC
