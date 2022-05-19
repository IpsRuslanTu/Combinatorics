#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

std::optional<std::string> ParseArgs(int argc, char* argv[]);
std::optional<std::ifstream> OpenFile(std::string fileIn);
std::vector<std::vector<int>> ReadMatrixFromStream(std::ifstream& input, const int size);
std::vector<std::vector<float>> CreateKirchhoffMatrix(const std::vector<std::vector<int>>& arr,
	int size);
void PrintMatrix(const std::vector<std::vector<float>>& arr, int size);
int GetDeterminant(std::vector<std::vector<float>>& arr, int size);
int CalcDeterminant(std::vector<std::vector<float>>& arr, int size);