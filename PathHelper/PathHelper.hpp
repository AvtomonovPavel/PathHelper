#pragma once

#include "../XPSHelper/XPSHelper.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <set>

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RANDOM
};

class PathHelper {
public:
	PathHelper(const XPSHelper& xpsHelper, int k);
	
	void FindPath(std::vector<int> st);
	void WritePath(std::ofstream& out);
	void WriteXPSPath();
	std::vector <int>snake_up_right(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_up_left(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_right_up(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_right_down(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_down_right(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_down_left(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_left_up(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	std::vector <int>snake_left_down(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way);
	const std::vector<int>& GetPath();
	//возращает последовательность наборов единичных вершин

	void Optimize();

	int GetK() const;

private:
	int FindVertex(std::vector<int> st);
	void AddField(int num, std::set<int>& toAdd);
	bool IsInters(int num, const std::set<int>& toCheck);
	void GenQue(int num, std::vector<std::vector<int>>& toQue, const std::set<int>& toCheck);

	int SimSum(int lhs, int rhs);
	bool VertexEqu(int lhs, int rhs);
	Direction GetDirection(int lhs, int rhs);
	std::vector<std::pair<int, int>> GetVertexGeometry(int vertex);

	std::vector<std::vector<int>> create_field() const;
	void create_walls(int p, int direction) const;
	std::pair <int, int> find_the_neighbor(std::pair <int,int> end) const;

	std::vector<int> path_;
	
	const XPSHelper& xpsHelper_;
	const int k_;
};