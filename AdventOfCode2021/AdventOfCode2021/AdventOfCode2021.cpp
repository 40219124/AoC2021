// AdventOfCode2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

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

void D1P2() {
	int total = 0;
	queue<int> values;
	int queueLength = 3;

	ifstream file(FileFolder + "D1P1.txt");
	if (file.is_open()) {
		string line;
		int last = 0;

		for (int i = 0; i < queueLength; ++i) {
			if (getline(file, line)) {
				int val = stoi(line);
				values.push(val);
				last += val;
			}
			else {
				return;
			}
		}

		while (getline(file, line)) {
			int val = stoi(line);

			int curr = last - values.front() + val;

			values.push(val);
			values.pop();

			if (curr > last) {
				total++;
			}
			last = curr;
		}

		cout << total << endl;
	}
}

function<void(void)> Problems[25][2] = { {D1P1, D1P2 } };

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