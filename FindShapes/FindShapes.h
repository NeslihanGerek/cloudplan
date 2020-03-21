#pragma once

void checkNeighbors(std::vector<std::vector<unsigned short>>& grid, int i, int j, std::vector<std::pair<int, int>>& shape);
std::vector<std::pair<int, int>> biggestShape(std::vector<std::vector<unsigned short>>& grid);
bool checkDigitAndPush(char item, std::vector<unsigned short> &row);
void exitProgram();