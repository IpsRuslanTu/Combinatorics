#pragma once
#include <set>
#include <stack>
#include <vector>
#include <fstream>

struct Edge
{
	int min;
	int max;
};

void PrintGraph(std::vector<std::vector<int>> graph);

void PrintStack(std::stack<int> stack);

std::vector<std::vector<int>> ReadAdjacencyMatrixFromStream(std::ifstream& input);

std::set<int> SearchCutVertices(std::vector<std::vector<int>> graph);

void DFS(const std::vector<std::vector<int>> graph, int root, std::vector<int>& tin,
	std::vector<int>& tout, std::vector<Edge>& reverseEdges);

std::set<int> GetCutVertices(std::vector<std::vector<int>> graph, int root, std::vector<int> tin,
	std::vector<int> tout, std::vector<Edge> reverseEdges);

bool isEdgeInReverse(int first, int second, std::vector<Edge> reverseEdges);