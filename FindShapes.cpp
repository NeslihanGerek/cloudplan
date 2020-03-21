// FindShapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include "FindShapes.h"

// checkNeighbors checks all surrounding cells if they are 1 or 0
void checkNeighbors(std::vector<std::vector<unsigned short>>& grid, int i, int j, std::vector<std::pair<int, int>>& shape)
{
	if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0)
	{
		return;
	}
	grid[i][j] = 0;
	shape.push_back(std::make_pair(i, j));

	checkNeighbors(grid, i, j - 1, shape);
	checkNeighbors(grid, i, j + 1, shape);
	checkNeighbors(grid, i + 1, j - 1, shape);
	checkNeighbors(grid, i + 1, j, shape);
	checkNeighbors(grid, i + 1, j + 1, shape);
	checkNeighbors(grid, i - 1, j + 1, shape);
	checkNeighbors(grid, i - 1, j, shape);
	checkNeighbors(grid, i - 1, j - 1, shape);
}

// biggestShape returns the elements of the biggest shape
std::vector<std::pair<int, int>> biggestShape(std::vector<std::vector<unsigned short>>& grid)
{
	std::vector<std::pair<int, int>> maxSizeShape;
	if (grid.empty())
	{
		return maxSizeShape;
	}
	auto n = grid.size();
	auto m = grid[0].size();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (grid[i][j] == 1)
			{
				std::vector<std::pair<int, int>> tempShape;
				checkNeighbors(grid, i, j, tempShape);
				if (tempShape.size() > maxSizeShape.size())
				{
					maxSizeShape = tempShape;
				}
			}
		}
	}
	return maxSizeShape;
}

// checkDigitAndPush is used to update input grid. If the input is 0 or 1; data is pushed into the grid
bool checkDigitAndPush(char item, std::vector<unsigned short> &row)
{
	if (!isdigit(item))
	{
		return false;
	}
	unsigned short temp = atoi(&item);
	if (temp == 0 || temp == 1)
	{
		row.push_back(temp);
		return true;
	}

	return false;
}

// exitProgram informs the user and exists
void exitProgram()
{
	std::cout << "Please enter a valid matrix next time... Press Enter to exit.\n";
	std::cin.ignore();
}

int main()
{
	std::cout << "Please enter the matrix in the following format : [0 1] [1 0]\n";
	std::string input;
	getline(std::cin, input);
	std::stringstream ss(input);

	std::vector<std::string> items;
	while (getline(ss, input, ' ')) {
		items.push_back(input);
	}

	if (items.size() == 0)
	{
		exitProgram();
	}
	else
	{
		std::vector<std::vector<unsigned short>> grid;
		std::vector<unsigned short> row;
		bool errorExists = false;
		for (auto item : items) {
			if (item.size() == 0)
			{
				errorExists = true;
				break;
			}
			if (item.size() == 2) {
				if (item[0] == '[') // new row
				{
					if (!checkDigitAndPush(item[1], row))
					{
						errorExists = true;
						break;
					}
				}
				else if (item[1] == ']') // last element of the row
				{
					if (!checkDigitAndPush(item[0], row))
					{
						errorExists = true;
						break;
					}
					if (grid.size() == 0 || grid.back().size() == row.size())
						grid.push_back(row);
					else
					{
						errorExists = true;
						break;
					}
					row.clear();
				}
				else
				{
					errorExists = true;
					break;
				}
			}
			else if (item.size() == 1)
			{
				if (!checkDigitAndPush(item[0], row))
				{
					errorExists = true;
					break;
				}
			}
			else
			{
				errorExists = true;
				break;
			}
		}
		if (errorExists)
		{
			exitProgram();
		}
		else
		{
			auto shape = biggestShape(grid);
			std::cout << "the biggest shape in your matrix contains following points:\n ";
			for (auto el : shape)
			{
				std::cout << "point(" << el.first << ", " << el.second << ")\n";
			}
			std::cout << "Press Enter to exit.\n";
			std::cin.ignore();
		}
	}
}
