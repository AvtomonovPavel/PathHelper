#include "PathHelper.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <windows.h>
#include <cmath>


PathHelper::PathHelper(const XPSHelper& xpsHelper) : 
	xpsHelper_(xpsHelper) 
{}

const int number_of_x_sections = 72;  // !!!!!!!!!!!!Достать из XPS_Helper
const int number_of_y_sections = 74; // !!!!!!!!!!!!Достать из XPS_Helper
const int k = 40;
const int number_of_vert_rect = 3;
const int number_of_hor_rect = 1;
const int number_of_rect = number_of_vert_rect * number_of_hor_rect;
double a[number_of_rect][6];
int ind = 1;
int par_of_rect; // ?????????????????????????????? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! номер в котором сейчас
int day = 0;
int par = 0;
std::vector<std::vector<int>> matrix(number_of_y_sections, std::vector <int>(number_of_x_sections));

// ??? ?? ? ? ?? ? ? ?? ? ? 
std::vector<std::vector<int>> create_field() {
	std::vector<std::vector<int>> vector_of_pairs_new(number_of_y_sections * number_of_x_sections, std::vector <int>(3));
	std::ofstream out("field.txt", std::ios::out);
	std::vector<std::vector<int>> vector_of_pairs(number_of_y_sections * number_of_x_sections, std::vector <int>(2));
	std::ifstream in("true_field.txt", std::ios::in);
	if (not in.is_open())
		throw std::invalid_argument("\n"
			"input file is not open\n"
		);
	int i = 0; //!!!!!!!!!!!!!!!!!!!!!!!!
	while (!in.eof()) {
		//std::string line = ""; ? 
		std::string new_line_1 = "";
		std::string new_line_2 = "";
		//getline(in, line); ?? ?????????????????????????????????????????????????????????
		in >> new_line_1 >> new_line_2;
		vector_of_pairs[i][0] = std::stoi(new_line_1); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		vector_of_pairs[i][1] = std::stoi(new_line_2); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		i += 1;
	}
	in.close();
	int param = 0; // !!!!!!!!!!!!!!!
	for (int i = 0; i < number_of_x_sections; i++) {
		for (int j = 0; j < number_of_y_sections; j++) {
			if (not out.is_open())
				throw std::invalid_argument("\n"
					"Output file at output stream is not open\n"
				);
			bool k = false; //!!!!!!!!!!!!!!!!
			for (int m = 0; m < vector_of_pairs.size(); m++) { // !!!!!!!!!!!!!!!!!!
				if (i == vector_of_pairs[m][0] && j == vector_of_pairs[m][1])
					k = true;
			}

			// !!!!!!!!!!!!!
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

	out.close(); // ?????????

	return vector_of_pairs_new;
}

void create_walls(int p, int direction) {
	int m = number_of_y_sections / (p + 1) + 1; // колво вершин в блок ???????????????????? 
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
			std::cout << a[ma][0] << " " << a[ma][1] << " " << a[ma][2] << " " << a[ma][3] << " " << a[ma][4] << " " << a[ma][5] << std::endl;
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
			std::cout << a[ma][0] << " " << a[ma][1] << " " << a[ma][2] << " " << a[ma][3] << " " << a[ma][4] << " " << a[ma][5] << std::endl;
			ma += 1;
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

	std::cout << a[rect][1] + 0.5 << " " << a[rect][2] - 0.5 << " " << a[rect][4] + 0.5 << " " << a[rect][3] - 0.5 << std::endl;
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
	int m = 0;
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
	int m = 73;
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
	int m = 73;
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

std::pair <int, int> find_the_neighbor(std::pair <int,int> end) {
	int min_x = number_of_x_sections - 1;
	int min_y = number_of_y_sections - 1;
	double min_w = pow((pow(min_x, 2) + pow(min_y, 2)), 0.5);
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
	return std::make_pair(min_x, min_y);
}





void PathHelper::WriteXPSPath() {
//	double m = number_of_y_sections / (2. + 1.);
//	std::cout << m << std::endl << std::endl;
	std::cout << "Part_1_start" << "\n";
	std::vector<std::vector<int> > vector_of_pairs_new = create_field(); //28 :/
	std::cout << "Part_1_finish" << "\n";

	int size_of_direction = 2;
	int direction = 0; // ????

	std::cout << "Part_3_start" << "\n";
	std::pair<int, int> start; // (., .)
	int rect = 0; //???
	a[rect][5] = 1;
	int way = 0;
	std::cout << "way " << way << std::endl;
	std::cout << "Part_3_finish" << "\n";

	std::pair <int, int> end; // (., .)
	for (int p = 0; p <= 2; p++) { // p - колво упоры
		for (int i = 0; i < size_of_direction; i++) { // i - ориентация упоров
			for (int j = 0; j < 4; j++) { // j - номер угла
				day = 0; //номер дня в который раскладка
				par = 0; //????
				int sum = 0; //???
				if (j == 0) {
					start = std::make_pair(0, 0);
					par_of_rect = 0; // !!!!!!!!!!!!!!!!!!!!!!! 22
				}
				if (j == 1 && i == 0) {
					start = std::make_pair(71, 0); // правый нижний угол
					par_of_rect = 0; // !!!!!!!!!!!!!!!!!!!!!!! 22
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

				create_walls(p, i); // ??? 85
				a[par_of_rect][5] = 1;
				std::cout << start.first << " " << start.second << std::endl;
				std::vector <int> snake_way;
				while (sum != p + 1) {
					int sum_new = 0;
					for (int q = 0; q <= p; q++) {
						std::cout << "q" << q << " " << a[q][5] << std::endl;
						sum_new += a[q][5];
					}
					sum = sum_new;
					std::cout << "start " << start.first << " " << start.second << " par_of_rect " << par_of_rect << std::endl;
					way = find_the_wall(start, par_of_rect);
					std::cout << sum << " " << way << " " << i << std::endl;
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
					std::cout << " a_par" << a[par_of_rect][5] << std::endl;
					end = std::make_pair(snake_way[snake_way.size() - 3], snake_way[snake_way.size() - 2]);
					start = find_the_neighbor(end);

					std::cout << "end " << end.first << " " << end.second << std::endl;
					std::cout << "start " << start.first << " " << start.second << std::endl;
					std::cout << " a_par_start" << par_of_rect << std::endl;

				}
				std::cout << "file_walls_" << p << "_direction_" << i << "_start_" << j << std::endl << std::endl;
				std::ofstream out;
				std::string filename; // âðåìåííûé áóôåð; // ñàì ôàéë
				std::string path; // ñþäà ìû áóäåì ëîæèòü íîâûå èìåíà
				filename = "walls_" + std::to_string(p) + "_start_" + std::to_string(j) + "_direction_" + std::to_string(i) + ".txt";
				path = ".\\"; // ÷àñòü èìåíè ôàéëà (îíî áóäåò ïîñòîÿííûì)
				path += filename; // ñîáèðàåì ïóòü è èìÿ äëÿ íîâîãî ôàéëà
				out.open(path.c_str()); // ñîçäàòü íîâûé ôàéë ñ íîâûì èìåíåì
				for (int i = 0; i < snake_way.size(); i++) {
					//std::cout << snake_way[i] << "\n";
					if (i % 3 == 0)
						//out << snake_way[i] << " " << snake_way[i + 1] << " ";
					out << xpsHelper_.GetOldCoords(xpsHelper_.GetWellNum(std::make_pair(snake_way[i], snake_way[i + 1]))).first << " "
					<< xpsHelper_.GetOldCoords(xpsHelper_.GetWellNum(std::make_pair(snake_way[i], snake_way[i + 1]))).second << " ";
					if ((i % 3 == 2))
						out << snake_way[i] << std::endl;
				}
				out.close(); // îáÿçàòåëüíî çàêðûâàåì
			}
		}
	}

}