#pragma once

#include "ModAr.h"
#include "MemList.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>

class IR {
	//basic info about the IR
public:
	int matSize;
	MemList memlist;

	//information about the graph
public:
	enum class Function { NOT, AND, XOR };

	struct VertexData {
		Function func;
		int mem_index;

		int num_parents_done, num_children_done, in_degree, out_degree;
	};

	//the graph itself
public:
	typedef boost::adjacency_list<boost::vecS, boost::vecS,
		boost::directedS,
		VertexData,
		boost::no_property
		> dag;
public:
	IR();
	~IR();
	void recursive_exec(Node n) {
		n.num_parents_done++;
		if (n.num_parents_done < n.in_degree)
			return;
		n.mem_alloc();
		if (n.func == Function::NOT)
			NOT(n.mem_index, n.parent1->mem_index);
		else if (n.func == Function::AND)
			AND(n.mem_index, n.parent1->mem_index, n.parent2->mem_index);
		else
			XOR(n.mem_index, n.parent1->mem_index, n.parent2->mem_index);
			for (Node p : n.parents) {
				p.num_children_done++;
				if (p.num_children_done >= p.out_degree)
					p.mem_free();
			}
		pfor(Node c : n.children) {
			recursive_exec(c);
		}
	}

	pfor(Node n : base_row) {
		recursive_exec(n);
	}
};