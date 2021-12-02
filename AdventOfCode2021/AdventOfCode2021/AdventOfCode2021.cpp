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

void D2P1() {
	ifstream file(FileFolder + "D2P1.txt");
	if (file.is_open()) {
		string line;
		int h = 0, v = 0;
		int* axis;
		int dir = 1;

		while (getline(file, line)) {
			dir = 1;
			if (line[0] == 'f') {
				axis = &h;
			}
			else {
				axis = &v;
				if (line[0] == 'u') {
					dir = -1;
				}
			}

			(*axis) += (line[line.length() - 1] - '0') * dir;
		}

		cout << "height: " << h << ", depth: " << v << endl;
		cout << "answer: " << h * v << endl;
	}
}

void D2P2() {
	ifstream file(FileFolder + "D2P1.txt");
	if (file.is_open()) {
		string line;
		int h = 0, v = 0, a = 0;

		while (getline(file, line)) {
			int move = line[line.length() - 1] - '0';
			if (line[0] == 'f') {
				h += move;
				v += move * a;
			}
			else {
				if (line[0] == 'u') {
					move *= -1;
				}
				a += move;
			}
		}

		cout << "height: " << h << ", depth: " << v << endl;
		cout << "answer: " << h * v << endl;
	}
}

function<void(void)> Problems[25][2] = { {D1P1, D1P2 }, {D2P1, D2P2} };

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