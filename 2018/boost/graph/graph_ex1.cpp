#include <iostream>
#include <utility>
#include <algorithm>
#include <thread>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;
using namespace std::literals::chrono_literals;

template <class Graph> struct exercise_vertex
{
	exercise_vertex(Graph& g_) : g(g_) {}

	typedef typename graph_traits<Graph>::vertex_descriptor Vertex;

	void operator()(const Vertex& v) const
	{
		//=====================================================================
		typedef graph_traits<Graph> GraphTraits;
		typename property_map<Graph, vertex_index_t>::type
			index = get(vertex_index, g);
		
		std::cout << "out-edges: ";
		typename GraphTraits::out_edge_iterator out_i, out_end;
		typename GraphTraits::edge_descriptor e;

		for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i)
		{
			e = *out_i;
			Vertex src = source(e, g), targ = target(e, g);
			std::cout << "(" << index[src] << ","
				<< index[targ] << ")";
		}
		std::cout << std::endl;
		//=====================================================================
		std::cout << "in-edges: ";
		typename GraphTraits::in_edge_iterator in_i, in_end;
		for (boost::tie(in_i, in_end) = in_edges(v, g);
			in_i != in_end; ++in_i)
		{
			e = *in_i;
			Vertex src = source(e, g), targ = target(e, g);
			std::cout << "(" << index[src] << "," << index[targ] << ")";
		}
		std::cout << std::endl;
		//=====================================================================
		std::cout << "adjacent vertices: ";
		typename graph_traits<Graph>::adjacency_iterator ai, ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
			ai != ai_end; ++ai)
		{
			std::cout << index[*ai] << " ";
		}
		std::cout << std::endl;
	}

	Graph& g;
};

int main(int, char*[])
{
	//=========================================================================
	// create a typedef for the Graph type
	typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

	// Make convenient labels for the vertices
	enum { A, B, C, D, E, N };
	const int num_vertices = N;
	const char* name = "ABCDE";

	// writing out the edges in the graph
	typedef std::pair<int, int> Edge;
	Edge edge_array[] =
	{ Edge(A, B), Edge(A, D), Edge(C, A), Edge(D, C),
	  Edge(C, E), Edge(B, D), Edge(D, E)
	};
	const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

	// declare a graph object
	Graph g(num_vertices);

	// add the edges to the graph object
	for (int i = 0; i < num_edges; ++i)
	{
		add_edge(edge_array[i].first, edge_array[i].second, g);
	}
	//=========================================================================
	typedef graph_traits<Graph>::vertex_descriptor Vertex;
	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);

	std::cout << "vertices(g) = ";
	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(g); vp.first != vp.second; ++vp.first)
	{
		Vertex v = *vp.first;
		std::cout << index[v] << " ";
	}
	std::cout << std::endl;
	//=========================================================================
	std::cout << "edges(g) = ";
	graph_traits<Graph>::edge_iterator ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	{
		std::cout << "(" << index[source(*ei, g)]
			<< "," << index[target(*ei, g)] << ")";
	}
	std::cout << std::endl;
	//=========================================================================
	std::for_each(vertices(g).first, vertices(g).second,
		exercise_vertex<Graph>(g));

	std::this_thread::sleep_for(1000s);
	return 0;
}