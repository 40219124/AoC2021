// AdventOfCode2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string FileFolder = "D:\\Repos\\AoC2021\\Inputs\\";

void D1P1() {
	int total = 0;
	ifstream file(FileFolder + "D1P1.txt");
	if (file.is_open()) {
		string line;
		getline(file, line);
		int last = stoi(line);

		while (getline(file, line)) {
			int curr = stoi(line);
			if (curr > last) {
				total++;
			}
			last = curr;
		}

		cout << total << endl;
	}
}

function<void(void)> Problems[25][2] = { {D1P1, } };

int main(int argc, char** argv)
{
	vector<string> args;
	for (int i = 1; i < argc; ++i) {
		string arg = "";
		char c = argv[i][0];
		for (int j = 1; c != '\0'; ++j) {
			arg += c;
			c = (argv[i][j]);
		}
		args.push_back(arg);
	}

	Problems[stoi(args[0]) - 1][stoi(args[1]) - 1]();
}