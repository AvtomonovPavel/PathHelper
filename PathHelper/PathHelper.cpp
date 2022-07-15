#include "PathHelper.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <windows.h>
#include <cmath>


PathHelper::PathHelper(const G3& g3) : 
	g3_(g3) 
{}
const int number_of_x_sections = 72;
const int number_of_y_sections = 74;
const int k = 40;
const int number_of_vert_rect = 3;
const int number_of_hor_rect = 1;
const int number_of_rect = number_of_vert_rect * number_of_hor_rect;
double a[number_of_rect][6];
int ind = 1;
int par_of_rect;
int day = 0;
int par = 0;
std::vector<std::vector<int>> matrix(number_of_y_sections, std::vector <int>(number_of_x_sections));

std::vector<std::vector<int>> create_plan() {
	std::vector<std::vector<int>> vector_plans;

	vector_plans.push_back({ 0, 1, 3, 2 });
	vector_plans.push_back({ 0, 2, 3, 1 });
	vector_plans.push_back({ 1, 3, 2, 0 });
	vector_plans.push_back({ 1, 0, 2, 3 });
	vector_plans.push_back({ 2, 0, 1, 3 });
	vector_plans.push_back({ 2, 3, 1, 0 });
	vector_plans.push_back({ 3, 2, 0, 1 });
	vector_plans.push_back({ 3, 1, 0, 2 });

	vector_plans.push_back({ 0, 1, 2, 5, 4, 3, 6, 7, 8 });
	vector_plans.push_back({ 0, 1, 2, 5, 8, 7, 4, 3, 6 });
	vector_plans.push_back({ 0, 1, 2, 5, 8, 7, 6, 3, 4 });
	vector_plans.push_back({ 0, 1, 4, 3, 6, 7, 8, 5, 2 });
	vector_plans.push_back({ 0, 3, 6, 7, 4, 1, 2, 5, 8 });
	vector_plans.push_back({ 0, 3, 6, 7, 8, 5, 4, 1, 2 });
	vector_plans.push_back({ 0, 3, 6, 7, 8, 5, 2, 1, 4 });
	vector_plans.push_back({ 0, 3, 4, 1, 2, 5, 8, 7, 6 });

	vector_plans.push_back({ 2, 1, 0, 3, 4, 5, 8, 7, 6 });
	vector_plans.push_back({ 2, 1, 0, 3, 6, 7, 4, 5, 8 });
	vector_plans.push_back({ 2, 1, 0, 3, 6, 7, 8, 5, 4 });
	vector_plans.push_back({ 2, 1, 4, 5, 8, 7, 6, 3, 0 });
	vector_plans.push_back({ 2, 5, 8, 7, 6, 3, 0, 1, 4 });
	vector_plans.push_back({ 2, 5, 8, 7, 4, 1, 0, 3, 6 });
	vector_plans.push_back({ 2, 5, 8, 7, 6, 3, 4, 1, 0 });
	vector_plans.push_back({ 2, 5, 4, 1, 0, 3, 6, 7, 8 });

	vector_plans.push_back({ 6, 7, 8, 5, 4, 3, 0, 1, 2 });
	vector_plans.push_back({ 6, 7, 8, 5, 2, 1, 4, 3, 0 });
	vector_plans.push_back({ 6, 7, 8, 5, 2, 1, 0, 3, 4 });
	vector_plans.push_back({ 6, 7, 4, 3, 0, 1, 2, 5, 8 });
	vector_plans.push_back({ 6, 3, 0, 1, 4, 7, 8, 5, 2 });
	vector_plans.push_back({ 6, 3, 0, 1, 2, 5, 4, 7, 8 });
	vector_plans.push_back({ 6, 3, 0, 1, 2, 5, 8, 7, 4 });
	vector_plans.push_back({ 6, 3, 4, 7, 8, 5, 2, 1, 0 });

	vector_plans.push_back({ 8, 5, 2, 1, 4, 7, 6, 3, 0 });
	vector_plans.push_back({ 8, 5, 2, 1, 0, 3, 6, 7, 4 });
	vector_plans.push_back({ 8, 5, 2, 1, 0, 3, 4, 7, 6 });
	vector_plans.push_back({ 8, 5, 4, 7, 6, 3, 0, 1, 2 });
	vector_plans.push_back({ 8, 7, 6, 3, 4, 5, 2, 1, 0 });
	vector_plans.push_back({ 8, 7, 6, 3, 0, 1, 4, 2, 5 });
	vector_plans.push_back({ 8, 7, 6, 3, 0, 1, 2, 5, 4 });
	vector_plans.push_back({ 8, 7, 4, 5, 2, 1, 0, 3, 6 });

	//for (int i = 0; i < vector_plans.size(); i++) {
	//	for (int j = 0; j < vector_plans[i].size(); j++)
	//		std::cout << vector_plans[i][j] << " ";
	//		std::cout << std::endl;
	//}

	return vector_plans;

}


std::vector<std::vector<int>> create_field() {
	std::vector<std::vector<int>> vector_of_pairs_new(number_of_y_sections * number_of_x_sections, std::vector <int>(3));
	std::ofstream out("field.txt", std::ios::out);
	std::vector<std::vector<int>> vector_of_pairs(number_of_y_sections * number_of_x_sections, std::vector <int>(2));
	std::ifstream in("true_field.txt", std::ios::in);
	if (not in.is_open())
		throw std::invalid_argument("\n"
			"input file is not open\n"
		);
	int i = 0;
	while (!in.eof()) {
		std::string line = "";
		std::string new_line_1 = "";
		std::string new_line_2 = "";
		getline(in, line);
		in >> new_line_1 >> new_line_2;
		vector_of_pairs[i][0] = std::stoi(new_line_1);
		vector_of_pairs[i][1] = std::stoi(new_line_2);
		i += 1;
	}
	in.close();
	int param = 0;
	for (int i = 0; i < number_of_x_sections; i++) {
		for (int j = 0; j < number_of_y_sections; j++) {
			if (not out.is_open())
				throw std::invalid_argument("\n"
					"Output file at output stream is not open\n"
				);
			bool k = false;
			for (int m = 0; m < vector_of_pairs.size(); m++) {
				if (i == vector_of_pairs[m][0] && j == vector_of_pairs[m][1])
					k = true;
			}
			if (k) {
				vector_of_pairs_new[param][0] = i;
				vector_of_pairs_new[param][1] = j;
				vector_of_pairs_new[param][2] = 1;
				out << i << " " << j << " " << 1 << '\n';

			}
			else {
				vector_of_pairs_new[param][0] = i;
				vector_of_pairs_new[param][1] = j;
				vector_of_pairs_new[param][2] = 0;
				out << i << " " << j << " " << 0 << '\n';
			}
			param += 1;
		}
	}
	return vector_of_pairs_new;
}

void create_walls(int p, int direction) {
	int m = number_of_y_sections / (p + 1) + 1;
	if (direction == 0) {
		int ma = 0;
		for (int j = 0; j <= p; j++) {
			a[ma][4] = j * m - 0.5;
			a[ma][0] = ma;
			a[ma][1] = -0.5;
			a[ma][5] = 0;
			if ((j + 1) * m <= number_of_y_sections)
				a[ma][3] = (j + 1) * m - 0.5;
			else
				a[ma][3] = number_of_y_sections - 0.5;
			a[ma][2] = number_of_x_sections - 0.5;
			//std::cout << a[ma][0] << " " << a[ma][1] << " " << a[ma][2] << " " << a[ma][3] << " " << a[ma][4] << " " << a[ma][5] << std::endl;
			ma += 1;
		}
	}
	if (direction == 1) {
		int ma = 0;
		for (int i = 0; i <= p; i++) {
			a[ma][3] = number_of_y_sections - 0.5;
			a[ma][4] = -0.5;
			a[ma][0] = ma;
			a[ma][1] = i * m - 0.5;
			a[ma][5] = 0;
			if ((i + 1) * m <= number_of_x_sections)
				a[ma][2] = (i + 1) * m - 0.5;
			else
				a[ma][2] = number_of_x_sections - 0.5;
			//std::cout << a[ma][0] << " " << a[ma][1] << " " << a[ma][2] << " " << a[ma][3] << " " << a[ma][4] << " " << a[ma][5] << std::endl;
			ma += 1;
		}
	}
	if (direction == 2) {
		int ma = 0;
		for (int i = 0; i <= p; i++) {
			for (int j = 0; j <= p; j++) {
				a[ma][0] = ma;
				a[ma][4] = j * m - 0.5;
				a[ma][1] = i * m - 0.5;
				a[ma][5] = 0;
				if ((i + 1) * m <= number_of_x_sections)
					a[ma][2] = (i + 1) * m - 0.5;
				else
					a[ma][2] = number_of_x_sections - 0.5;
				if ((j + 1) * m <= number_of_y_sections)
					a[ma][3] = (j + 1) * m - 0.5;
				else
					a[ma][3] = number_of_y_sections - 0.5;
				//std::cout << a[ma][0] << " " << a[ma][1] << " " << a[ma][2] << " " << a[ma][3] << " " << a[ma][4] << " " << a[ma][5] << std::endl;
				ma += 1;
			}
		}

	}
}

int find_the_wall(std::pair <int,int> start, int rect) {
	//a[0][5] = 1;
	int way = 0;

	if (a[rect][1] <= start.first && a[rect][2] >= start.first && a[rect][4] <= start.second && a[rect][3] >= start.second) {
		if (abs(a[rect][1] - start.first) < abs(a[rect][2] - start.first))
			if (abs(a[rect][3] - start.second) < abs(a[rect][4] - start.second))
				way = 3;
			else
				way = 1;
		else
			if (abs(a[rect][3] - start.second) < abs(a[rect][4] - start.second))
				way = 4;
			else
				way = 2;
	}
	return way;

}


std::vector <int> PathHelper::snake_up_right(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;

	//std::cout << a[rect][1] + 0.5 << " " << a[rect][2] - 0.5 << " " << a[rect][4] + 0.5 << " " << a[rect][3] - 0.5 << std::endl;
	for (int i = a[rect][1] + 0.5; i < a[rect][2] - 0.5; i++) {
		if (i % 2 == int(a[rect][1] + 0.5) % 2) {
			para = i * number_of_y_sections + a[rect][4] + 0.5;
			//std::cout << para << " " << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][2] << std::endl;
			for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para += 1;
			}
		}
		else
		{
			para = para + number_of_y_sections - 1;
			for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para -= 1;
			}

		}

	}
	for (int i = a[rect][2] - 0.5; i <= a[rect][2] - 0.5; i++) {
		//std::cout << "we_in_circle";
		para = i * number_of_y_sections + a[rect][4] + 0.5;
	for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
	{
		//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(i);
			snake_way.push_back(j);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
		para += 1;
	}
	}
	return snake_way;
}

std::vector <int> PathHelper::snake_up_left(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	//std::cout << "rect" << rect << std::endl;
	for (int i = a[rect][2] - 0.5; i > a[rect][1] + 0.5; i--) {
		if (i % 2 == int(a[rect][2] - 0.5) % 2) {
			para = i * number_of_y_sections + a[rect][4] + 0.5;
			for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para += 1;
			}
		}
		else
		{
			para = para - number_of_y_sections - 1;
			for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para -= 1;
			}

		}
	}
	for (int i = a[rect][1] + 0.5; i >= a[rect][1] + 0.5; i--) {
		para = i * number_of_y_sections + a[rect][4] + 0.5;
		for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
		{
			//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
			if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
				snake_way.push_back(i);
				snake_way.push_back(j);
				snake_way.push_back(day);
				par += 1;
				if (par == k) {
					day += 1;
					par = 0;
				}
			}
			para += 1;
		}
	}

	return snake_way;
}

std::vector <int> PathHelper::snake_down_right(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	for (int i = a[rect][1] + 0.5; i < a[rect][2] - 0.5; i++) {
		if (i % 2 == int(a[rect][1] + 0.5) % 2) {
			para = i * number_of_y_sections + a[rect][3] - 0.5;
			//std::cout << para << " " << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][2] << std::endl;
			for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para -= 1;
			}
		}
		else
		{
			para = para + number_of_y_sections + 1;
			for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para += 1;
			}

		}

	}
	for (int i = a[rect][2] - 0.5; i <= a[rect][2] - 0.5; i++) {
		para = i * number_of_y_sections + a[rect][3] - 0.5;
	for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
	{
		//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(i);
			snake_way.push_back(j);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
		para -= 1;
	}
	}
	return snake_way;
}

std::vector <int> PathHelper::snake_down_left(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	//std::cout << "rect" << rect << std::endl;
	for (int i = a[rect][2] - 0.5; i > a[rect][1] + 0.5; i--) {
		if (i % 2 == int(a[rect][2] - 0.5) % 2) {
			para = i * number_of_y_sections + a[rect][3] - 0.5;
			for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para -= 1;
			}
		}
		else
		{
			para = para - number_of_y_sections + 1;
			for (int j = a[rect][4] + 0.5; j <= a[rect][3] - 0.5; j++)
			{
				//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(i);
					snake_way.push_back(j);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
				para += 1;
			}

		}
	}
	for (int i = a[rect][1] + 0.5; i >= a[rect][1] + 0.5; i--) {
		para = i * number_of_y_sections + a[rect][3] - 0.5;
		for (int j = a[rect][3] - 0.5; j >= a[rect][4] + 0.5; j--)
		{
			//std::cout << vector_of_pairs_new[para][0] << " " << i << " " << vector_of_pairs_new[para][1] << " " << j << " " << vector_of_pairs_new[para][2] << std::endl;
			if (vector_of_pairs_new[para][0] == i && vector_of_pairs_new[para][1] == j && vector_of_pairs_new[para][2] == 1) {
				snake_way.push_back(i);
				snake_way.push_back(j);
				snake_way.push_back(day);
				par += 1;
				if (par == k) {
					day += 1;
					par = 0;
				}
			}
			para -= 1;
		}
	}
	
	return snake_way;
}

std::vector <int> PathHelper::snake_right_up(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	int m = a[rect][4] + 0.5;
	for (int i = a[rect][4] + 0.5; i < a[rect][3] - 0.5; i++) {
		if (i % 2 == int(a[rect][4] + 0.5) % 2) {

			//std::cout << para << " " << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][2] << std::endl;
			for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
			{
				para = j * number_of_y_sections + m;
				//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m += 1;
		}
		else
		{
			for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--)
			{
				para = j * number_of_y_sections + m;
				//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m += 1;

		}

	}
	for (int i = a[rect][3] - 0.5; i <= a[rect][3] - 0.5; i++)
	for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
	{
		para = j * number_of_y_sections + m;
		//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(j);
			snake_way.push_back(i);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
	}
	return snake_way;
}

std::vector <int> PathHelper::snake_right_down(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	int m = a[rect][3] - 0.5;
	for (int i = a[rect][3] - 0.5; i > a[rect][4] + 0.5; i--) {
		if (i % 2 == int(a[rect][3] - 0.5) % 2) {

			//std::cout  << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][1] << std::endl;
			for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
			{
				para = j * number_of_y_sections + m;
				//	std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m -= 1;
		}
		else
		{
			for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--)
			{
				para = j * number_of_y_sections + m;
				//	std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m -= 1;

		}

	}
	for (int i = a[rect][4] + 0.5; i >= a[rect][4] + 0.5; i--)
	for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
	{
		para = j * number_of_y_sections + m;
		//	std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(j);
			snake_way.push_back(i);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
	}
	return snake_way;
}

std::vector <int> PathHelper::snake_left_up(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	int m = 0;
	for (int i = a[rect][4] + 0.5; i < a[rect][3] - 0.5; i++) {
		if (i % 2 == int(a[rect][4] + 0.5) % 2) {

			//std::cout << para << " " << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][2] << std::endl;
			for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--)
			{
				para = j * number_of_y_sections + i;
				//	std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m += 1;
		}
		else
		{
			for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
			{
				para = j * number_of_y_sections + i;
				//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m += 1;

		}

	}
	for (int i = a[rect][3] - 0.5; i <= a[rect][3] - 0.5; i++)
	for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--)
	{
		para = j * number_of_y_sections + i;
		//	std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(j);
			snake_way.push_back(i);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
	}
	return snake_way;
}

std::vector <int> PathHelper::snake_left_down(std::pair <int, int> start, int way, int rect, std::vector<std::vector<int>>vector_of_pairs_new, std::vector <int> snake_way) {
	int para = 0;
	int m = a[rect][3] - 0.5;
	for (int i = a[rect][3] - 0.5; i > a[rect][4] + 0.5; i--) {
		if (i % 2 == int(a[rect][3] - 0.5) % 2) {

			//std::cout  << vector_of_pairs_new[para][0] << " " << vector_of_pairs_new[para][1] << std::endl;
			for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--) {
				para = j * number_of_y_sections + i;
				//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m -= 1;
		}
		else
		{
			for (int j = a[rect][1] + 0.5; j <= a[rect][2] - 0.5; j++)
			{
				para = j * number_of_y_sections + i;
				//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
				if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
					snake_way.push_back(j);
					snake_way.push_back(i);
					snake_way.push_back(day);
					par += 1;
					if (par == k) {
						day += 1;
						par = 0;
					}
				}
			}
			m -= 1;

		}

	}
	for (int i = a[rect][4] + 0.5; i >= a[rect][4] + 0.5; i--)
	for (int j = a[rect][2] - 0.5; j >= a[rect][1] + 0.5; j--) {
		para = j * number_of_y_sections + i;
		//std::cout << vector_of_pairs_new[para][0] << " " << j << " " << vector_of_pairs_new[para][1] << " " << i << " " << vector_of_pairs_new[para][2] << std::endl;
		if (vector_of_pairs_new[para][0] == j && vector_of_pairs_new[para][1] == i && vector_of_pairs_new[para][2] == 1) {
			snake_way.push_back(j);
			snake_way.push_back(i);
			snake_way.push_back(day);
			par += 1;
			if (par == k) {
				day += 1;
				par = 0;
			}
		}
	}
	return snake_way;
}

std::pair <int, int> find_the_neighbor(std::pair <int,int> end, int parametr) {
	int min_x = number_of_x_sections - 1;
	int min_y = number_of_y_sections - 1;
	double min_w = pow((pow(min_x, 2) + pow(min_y, 2)), 0.5);
	if (parametr == -1) {
		for (int i = 0; i < number_of_rect; i++) {
			if (a[i][5] - 0 < 0.001) {
				//std::cout << "!" << i << std::endl;
				if (std::pow((std::pow((a[i][1] + 1 - end.first), 2) + std::pow((a[i][4] + 1 - end.second), 2)), 0.5) < min_w) {
					min_x = a[i][1] + 0.5;
					min_y = a[i][4] + 0.5;
					min_w = std::pow((std::pow((a[i][1] + 1 - end.first), 2) + std::pow((a[i][4] + 1 - end.second), 2)), 0.5);
					par_of_rect = i;
					//std::cout << "!1" << std::endl;
				}
				if (std::pow((std::pow((a[i][1] + 1 - end.first), 2) + std::pow((a[i][3] - end.second), 2)), 0.5) < min_w) {
					min_x = a[i][1] + 0.5;
					min_y = a[i][3] - 0.5;
					min_w = std::pow((std::pow((a[i][1] + 1 - end.first), 2) + std::pow((a[i][3] + 1 - end.second), 2)), 0.5);
					par_of_rect = i;
					//std::cout << "!2" << std::endl;
				}
				if (std::pow((std::pow((a[i][2] - end.first), 2) + std::pow((a[i][4] + 1 - end.second), 2)), 0.5) < min_w) {
					min_x = a[i][2] - 0.5;
					min_y = a[i][4] + 0.5;
					min_w = std::pow((std::pow((a[i][2] + 1 - end.first), 2) + std::pow((a[i][4] + 1 - end.second), 2)), 0.5);
					par_of_rect = i;
					//std::cout << "!3" << std::endl;
				}
				if (std::pow((std::pow((a[i][2] - end.first), 2) + std::pow((a[i][3] - end.second), 2)), 0.5) < min_w) {
					min_x = a[i][2] - 0.5;
					min_y = a[i][3] - 0.5;
					min_w = std::pow((std::pow((a[i][2] + 1 - end.first), 2) + std::pow((a[i][3] + 1 - end.second), 2)), 0.5);
					par_of_rect = i;
					//	std::cout << "!4" << std::endl;
				}
			}
		}
		a[par_of_rect][5] = 1;
	}
	if (parametr != -1) {
			//std::cout << "!" << i << std::endl;
			if (std::pow((std::pow((a[parametr][1] + 1 - end.first), 2) + std::pow((a[parametr][4] + 1 - end.second), 2)), 0.5) < min_w) {
				min_x = a[parametr][1] + 0.5;
				min_y = a[parametr][4] + 0.5;
				min_w = std::pow((std::pow((a[parametr][1] + 1 - end.first), 2) + std::pow((a[parametr][4] + 1 - end.second), 2)), 0.5);
				par_of_rect = parametr;
				//std::cout << "!1" << std::endl;
			}
			if (std::pow((std::pow((a[parametr][1] + 1 - end.first), 2) + std::pow((a[parametr][3] - end.second), 2)), 0.5) < min_w) {
				min_x = a[parametr][1] + 0.5;
				min_y = a[parametr][3] - 0.5;
				min_w = std::pow((std::pow((a[parametr][1] + 1 - end.first), 2) + std::pow((a[parametr][3] + 1 - end.second), 2)), 0.5);
				par_of_rect = parametr;
				//std::cout << "!2" << std::endl;
			}
			if (std::pow((std::pow((a[parametr][2] - end.first), 2) + std::pow((a[parametr][4] + 1 - end.second), 2)), 0.5) < min_w) {
				min_x = a[parametr][2] - 0.5;
				min_y = a[parametr][4] + 0.5;
				min_w = std::pow((std::pow((a[parametr][2] + 1 - end.first), 2) + std::pow((a[parametr][4] + 1 - end.second), 2)), 0.5);
				par_of_rect = parametr;
				//std::cout << "!3" << std::endl;
			}
			if (std::pow((std::pow((a[parametr][2] - end.first), 2) + std::pow((a[parametr][3] - end.second), 2)), 0.5) < min_w) {
				min_x = a[parametr][2] - 0.5;
				min_y = a[parametr][3] - 0.5;
				min_w = std::pow((std::pow((a[parametr][2] + 1 - end.first), 2) + std::pow((a[parametr][3] + 1 - end.second), 2)), 0.5);
				par_of_rect = parametr;
				//	std::cout << "!4" << std::endl;
			}
			a[par_of_rect][5] = 1;
	}
	
	return std::make_pair(min_x, min_y);
}





void PathHelper::WriteXPSPath() {

	//std::cout << "Part_1_start" << "\n";
	std::vector<std::vector<int> > vector_of_pairs_new = create_field();
	std::vector<std::vector<int>> plan = create_plan();
	//std::cout << "Part_1_finish" << "\n";

	int size_of_direction = 2;
	int direction = 0;


	std::pair<int, int> start;
	int rect = 0;
	a[rect][5] = 1;
	int way = 0;

	std::pair <int, int> end;
	for (int p = 0; p <= 2; p++) {
		for (int i = 0; i < size_of_direction; i++) {
			for (int j = 0; j < 4; j++) {
				day = 0;
				par = 0;
				int sum = 0;
				if (j == 0) {
					start = std::make_pair(0, 0);
					par_of_rect = 0;

				}
				if (j == 1 && i == 0) {
					start = std::make_pair(71, 0);
					par_of_rect = 0;
				}
				if (j == 1 && i == 1) {
					start = std::make_pair(71, 0);
					par_of_rect = p;
				}
				if (j == 2) {
					start = std::make_pair(71, 73);
					par_of_rect = p;
				}
				if (j == 3 && i == 0) {
					start = std::make_pair(0, 73);
					par_of_rect = p;
				}
				if (j == 3 && i == 1) {
					start = std::make_pair(0, 73);
					par_of_rect = 0;
				}

				create_walls(p, i);
				a[par_of_rect][5] = 1;
				std::vector <int> snake_way;
				while (sum != p + 1) {
					int sum_new = 0;
					for (int q = 0; q <= p; q++) {
						sum_new += a[q][5];
					}
					sum = sum_new;
					way = find_the_wall(start, par_of_rect);
					if (way == 1 && i == 0)
						snake_way = snake_up_right(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 1 && i == 1)
						snake_way = snake_right_up(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 2 && i == 0)
						snake_way = snake_up_left(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 2 && i == 1)
						snake_way = snake_left_up(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 3 && i == 0)
						snake_way = snake_down_right(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 3 && i == 1)
						snake_way = snake_right_down(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 4 && i == 0)
						snake_way = snake_down_left(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					if (way == 4 && i == 1)
						snake_way = snake_left_down(start, way, par_of_rect, vector_of_pairs_new, snake_way);
					end = std::make_pair(snake_way[snake_way.size() - 3], snake_way[snake_way.size() - 2]);
					start = find_the_neighbor(end, -1);


				}
				std::ofstream out;
				std::string filename; // временный буфер; // сам файл
				std::string path; // сюда мы будем ложить новые имена
				filename = "Start_" + std::to_string(j) + "_direction_" + std::to_string(i) + "_walls_" + std::to_string(p) + ".txt";
				path = ".\\"; // часть имени файла (оно будет постоянным)
				path += filename; // собираем путь и имя для нового файла
				out.open(path.c_str()); // создать новый файл с новым именем
				for (int i = 0; i < snake_way.size(); i++) {
					//std::cout << snake_way[i] << "\n";
					if (i % 3 == 0)
						//out << snake_way[i] << " " << snake_way[i + 1] << " ";
						out << g3_.GetXPSHelper().GetOldCoords(g3_.GetXPSHelper().GetWellNum(std::make_pair(snake_way[i], snake_way[i + 1]))).first << " "
						<< g3_.GetXPSHelper().GetOldCoords(g3_.GetXPSHelper().GetWellNum(std::make_pair(snake_way[i], snake_way[i + 1]))).second << " ";
					if ((i % 3 == 2))
						out << snake_way[i] << std::endl;
				}
				out.close(); // обязательно закрываем
			}
		}
	}

	for (int i = 0; i < plan.size(); i++) {

		for (int j = 0; j < 4; j++) {
			day = 0;
			par = 0;
			int sum = 0;
			if (j == 0) {
				start = std::make_pair(a[plan[i][0]][1] + 0.5, a[plan[i][0]][4] + 0.5);
				par_of_rect = plan[i][0];

			}
			if (j == 1) {
				start = std::make_pair(a[plan[i][0]][2] - 0.5, a[plan[i][0]][4] + 0.5);
				par_of_rect = plan[i][0];
			}
			if (j == 2) {
				start = std::make_pair(a[plan[i][0]][2] - 0.5, a[plan[i][0]][3] - 0.5);
				par_of_rect = plan[i][0];
			}
			if (j == 3) {
				start = std::make_pair(a[plan[i][0]][1] + 0.5, a[plan[i][0]][4] + 0.5);
				par_of_rect = plan[i][0];
			}

			create_walls(int(pow(plan[i].size(), 0.5) - 1), 2);
			a[par_of_rect][5] = 1;
			std::vector <int> snake_way;
			

			int q = 0;
			way = find_the_wall(start, plan[i][q]);
			if (way == 1 && (abs(plan[i][q + 1] - plan[i][0]) != 1))
				snake_way = snake_up_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 1 && (abs(plan[i][q + 1] - plan[i][q]) == 1))
				snake_way = snake_right_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 2 && (abs(plan[i][q + 1] - plan[i][q]) != 1))
				snake_way = snake_up_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 2 && (abs(plan[i][q + 1] - plan[i][q]) == 1))
				snake_way = snake_left_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 3 && (abs(plan[i][q + 1] - plan[i][q]) != 1))
				snake_way = snake_down_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 3 && (abs(plan[i][q + 1] - plan[i][q]) == 1))
				snake_way = snake_right_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 4 && (abs(plan[i][q + 1] - plan[i][q]) != 1))
				snake_way = snake_down_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 4 && (abs(plan[i][q + 1] - plan[i][q]) == 1))
				snake_way = snake_left_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			end = std::make_pair(snake_way[snake_way.size() - 3], snake_way[snake_way.size() - 2]);
			start = find_the_neighbor(end, plan[i][q + 1]);


			for (int q = 1; q < plan[i].size() - 1; q++) {
				way = find_the_wall(start, plan[i][q]);
				if (way == 1 && (abs(plan[i][q + 1] - plan[i][q]) != abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_up_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 1 && (abs(plan[i][q + 1] - plan[i][q]) == abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_right_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 2 && (abs(plan[i][q + 1] - plan[i][q]) != abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_up_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 2 && (abs(plan[i][q + 1] - plan[i][q]) == abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_left_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 3 && (abs(plan[i][q + 1] - plan[i][q]) != abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_down_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 3 && (abs(plan[i][q + 1] - plan[i][q]) == abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_right_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 4 && (abs(plan[i][q + 1] - plan[i][q]) != abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_down_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				if (way == 4 && (abs(plan[i][q + 1] - plan[i][q]) == abs(plan[i][q - 1] - plan[i][q])))
					snake_way = snake_left_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
				end = std::make_pair(snake_way[snake_way.size() - 3], snake_way[snake_way.size() - 2]);
				start = find_the_neighbor(end, plan[i][q+1]);
			}
			q = plan[i].size() - 1;
			way = find_the_wall(start, plan[i][q]);
			if (way == 1 && (1 != abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_up_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 1 && (1 == abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_right_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 2 && (1!= abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_up_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 2 && (1 == abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_left_up(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 3 && (1 != abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_down_right(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 3 && (1 == abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_right_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 4 && (1 != abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_down_left(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			if (way == 4 && (1 == abs(plan[i][q - 1] - plan[i][q])))
				snake_way = snake_left_down(start, way, plan[i][q], vector_of_pairs_new, snake_way);
			end = std::make_pair(snake_way[snake_way.size() - 3], snake_way[snake_way.size() - 2]);
				std::ofstream out;
				std::string filename; // временный буфер; // сам файл
				std::string path; // сюда мы будем ложить новые имена
				filename =  "Start_" + std::to_string(j) + "_direction_" + std::to_string(2) + "_num_" + std::to_string(i) + "_walls_" + std::to_string(int(pow(plan[i].size(), 0.5) - 1)) + ".txt";
				path = ".\\"; // часть имени файла (оно будет постоянным)
				path += filename; // собираем путь и имя для нового файла
				out.open(path.c_str()); // создать новый файл с новым именем
				for (int t = 0; t < snake_way.size(); t++) {
					//std::cout << snake_way[i] << "\n";
					if (t % 3 == 0)
						//out << snake_way[i] << " " << snake_way[i + 1] << " ";
						out << g3_.GetXPSHelper().GetOldCoords(g3_.GetXPSHelper().GetWellNum(std::make_pair(snake_way[t], snake_way[t + 1]))).first << " "
						<< g3_.GetXPSHelper().GetOldCoords(g3_.GetXPSHelper().GetWellNum(std::make_pair(snake_way[t], snake_way[t + 1]))).second << " ";
					if ((t % 3 == 2))
						out << snake_way[t] << std::endl;
				}
				out.close(); // обязательно закрываем
		}
	}


}