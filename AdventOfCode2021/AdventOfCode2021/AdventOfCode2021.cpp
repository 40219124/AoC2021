// AdventOfCode2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <map>

using namespace std;

const string FileFolder = "D:\\Repos\\AoC2021\\Inputs\\";


void D1P1(ifstream& file) {
	int total = 0;
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

void D1P2(ifstream& file) {
	int total = 0;
	queue<int> values;
	int queueLength = 3;

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

void D1(int part) {
	ifstream file(FileFolder + "D1P1.txt");
	if (file.is_open()) {
		if (part == 1) {
			D1P1(file);
		}
		else {
			D1P2(file);
		}
	}
}

void D2P1(ifstream& file) {
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

void D2P2(ifstream& file) {
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

void D2(int part) {
	ifstream file(FileFolder + "D2P1.txt");
	if (file.is_open()) {
		if (part == 1) {
			D2P1(file);
		}
		else {
			D2P2(file);
		}
	}
}

void D3P1(ifstream& file) {
	string line;
	const int bitCount = 12;
	int bitSum[bitCount] = {};
	int lineCount = 0;
	while (getline(file, line)) {
		if (line.size() >= bitCount) {
			lineCount++;
			for (int i = 0; i < bitCount; ++i) {
				bitSum[i] += line[i] - '0';
			}
		}
	}

	int gamma = 0, epsilon = 0, bVal = 1;
	for (int i = bitCount - 1; i >= 0; --i) {

		bool oneCommon = ((bitSum[i] * 2) / lineCount) >= 1;
		gamma += oneCommon * bVal;
		epsilon += (!oneCommon) * bVal;
		bVal *= 2;
	}
	cout << "gamma: " << gamma << ", epsilon: " << epsilon << endl;
	cout << "answer: " << gamma * epsilon << endl;
}

string D3P2FindOneCode(vector<string>* oldList, vector<string>* newList, const int bitCount, int oneDoubleCount, int lineCount, bool focusOne) {
	for (int b = 0; b < bitCount && oldList->size() > 1; ++b) {
		newList->clear();

		char common = focusOne + '0';
		if (oneDoubleCount < lineCount) {
			common = !focusOne + '0';
		}
		oneDoubleCount = lineCount = 0;

		for (size_t i = 0; i < oldList->size(); ++i) {
			if ((*oldList)[i][b] == common) {
				newList->push_back((*oldList)[i]);
				if (b + 1 < bitCount) {
					oneDoubleCount += ((*oldList)[i][b + 1] == '1') * 2;
					lineCount++;
				}
			}
		}
		vector<string>* tempList = oldList;
		oldList = newList;
		newList = tempList;
	}

	return (*oldList)[0];
}

void D3P2(ifstream& file) {
	string line;
	const int bitCount = 12;
	vector<string> oldO2List = {}, newO2List = {}, oldCo2List = {}, newCo2List = {};
	int oneDoubleCount = 0, lineCount = 0;

	while (getline(file, line)) {
		oldO2List.push_back(line);
		oldCo2List.push_back(line);
		oneDoubleCount += (line[0] == '1') * 2;
		lineCount++;
	}

	string o2string = D3P2FindOneCode(&oldO2List, &newO2List, bitCount, oneDoubleCount, lineCount, true);
	string co2string = D3P2FindOneCode(&oldCo2List, &newCo2List, bitCount, oneDoubleCount, lineCount, false);

	int o2 = 0, co2 = 0, bVal = 1;
	for (int i = bitCount - 1; i >= 0; --i) {
		o2 += (o2string[i] - '0') * bVal;
		co2 += (co2string[i] - '0') * bVal;
		bVal *= 2;
	}

	cout << "o2: " << o2 << ", co2: " << co2 << endl;
	cout << "answer: " << o2 * co2 << endl;
}

void D3(int part) {
	ifstream file(FileFolder + "D3P1.txt");
	if (file.is_open()) {
		if (part == 1) {
			D3P1(file);
		}
		else {
			D3P2(file);
		}
	}
}

class BingoCard {
public:
	bool CheckNum(int num);
	bool IsComplete();
	void AddNum(int num, int x, int y);
	int* GetCompleteSet() { return completeSet; }
	int SumOfUnchecked();
	BingoCard() {}
private:
	const static int bingoSize = 5;
	int bingoNums[bingoSize][bingoSize] = {};
	bool bingoState[bingoSize][bingoSize] = {};
	int completeSet[bingoSize] = {};
	bool isComplete = false;
};

bool BingoCard::CheckNum(int num) {
	for (int y = 0; y < bingoSize; ++y) {
		for (int x = 0; x < bingoSize; ++x) {
			if (bingoNums[x][y] == num) {
				bingoState[x][y] = true;
				return true;
			}
		}
	}
	return false;
}

bool BingoCard::IsComplete() {
	if (isComplete) {
		return isComplete;
	}
	// Check rows
	for (int y = 0; y < bingoSize; ++y) {
		bool fullRow = true;
		// Step across rows
		for (int x = 0; x < bingoSize; ++x) {
			fullRow = fullRow && bingoState[x][y];
			// Check columns from bottom row
			if (y == 0 && bingoState[x][y]) {
				bool fullColumn = true;
				for (int y2 = 1; y2 < bingoSize; ++y2) {
					fullColumn = fullColumn && bingoState[x][y2];
					if (!fullColumn) {
						break;
					}
				}
				if (fullColumn) {
					isComplete = true;
					for (int y2 = 0; y2 < bingoSize; ++y2) {
						completeSet[y2] = bingoNums[x][y2];
					}
					return isComplete;
				}
			}
			else if (y != 0 && !fullRow) {
				break;
			}
		}
		if (fullRow) {
			isComplete = true;
			for (int x = 0; x < bingoSize; ++x) {
				completeSet[x] = bingoNums[x][y];
			}
			return isComplete;
		}
	}
	return isComplete;
}

void BingoCard::AddNum(int num, int x, int y) {
	if (x < 0 || y < 0 || x >= bingoSize || y >= bingoSize) {
		cout << "incorrect number coords, x: " << x << ", y: " << y << endl;
		return;
	}
	bingoNums[x][y] = num;
	bingoState[x][y] = false;
}

int BingoCard::SumOfUnchecked() {
	int sum = 0;
	for (int y = 0; y < bingoSize; ++y) {
		for (int x = 0; x < bingoSize; ++x) {
			if (!bingoState[x][y]) {
				sum += bingoNums[x][y];
			}
		}
	}
	return sum;
}

void D4P1(ifstream& file) {
	string line;
	getline(file, line);
	string inputNumsS = line;

	vector<BingoCard*> cardsByNumber[100] = {};
	vector<BingoCard*> cards;
	const int bingoSize = 5;

	// Create bingo cards
	while (getline(file, line)) {
		if (line == "") {
			continue;
		}

		cards.push_back(new BingoCard());
		BingoCard* card = cards[cards.size() - 1];
		int x = 0, y = bingoSize - 1;
		while (line != "" && y >= 0) {
			while (x < bingoSize) {
				int num = atoi(line.substr(x * 3, 2).c_str());
				card->AddNum(num, x, y);
				cardsByNumber[num].push_back(card);
				x++;
			}
			x = 0;
			y--;
			getline(file, line);
		}
	}
	cout << "card creation successful" << endl;

	// Check input
	int numsChecked = 0;
	for (size_t i = 0; i < inputNumsS.size(); ++i) {
		char numS[3];
		for (size_t j = 0; ; ++j) {
			if (inputNumsS[j + i] < '0' || inputNumsS[j + i] > '9' || (j + i) >= inputNumsS.size()) {
				i += j;
				numS[j] = '\0';
				break;
			}
			numS[j] = inputNumsS[j + i];
		}
		int num = atoi(numS);
		numsChecked++;
		for (BingoCard* bc : cardsByNumber[num]) {
			bc->CheckNum(num);
			if (numsChecked >= bingoSize && bc->IsComplete()) {
				int sum = bc->SumOfUnchecked();
				cout << "sum of unchecked: " << sum << ", final num: " << num << endl;
				cout << "answer: " << sum * num << endl;
				return;
			}
		}
	}
	cout << "no winners apparently" << endl;
}

void D4P2(ifstream& file) {
	string line;
	getline(file, line);
	string inputNumsS = line;

	vector<BingoCard*> cardsByNumber[100] = {};
	vector<BingoCard*> cards;
	vector<bool> cardStates;
	int completeCardCount = 0;
	const int bingoSize = 5;

	// Create bingo cards
	while (getline(file, line)) {
		if (line == "") {
			continue;
		}

		cards.push_back(new BingoCard());
		cardStates.push_back(false);
		BingoCard* card = cards[cards.size() - 1];
		int x = 0, y = bingoSize - 1;
		while (line != "" && y >= 0) {
			while (x < bingoSize) {
				int num = atoi(line.substr(x * 3, 2).c_str());
				card->AddNum(num, x, y);
				cardsByNumber[num].push_back(card);
				x++;
			}
			x = 0;
			y--;
			getline(file, line);
		}
	}
	cout << "card creation successful" << endl;

	// Check input
	int numsChecked = 0;
	for (size_t i = 0; i < inputNumsS.size(); ++i) {
		char numS[3];
		for (size_t j = 0; ; ++j) {
			if (inputNumsS[j + i] < '0' || inputNumsS[j + i] > '9' || (j + i) >= inputNumsS.size()) {
				i += j;
				numS[j] = '\0';
				break;
			}
			numS[j] = inputNumsS[j + i];
		}
		int num = atoi(numS);
		numsChecked++;
		for (BingoCard* bc : cardsByNumber[num]) {
			bc->CheckNum(num);
			if (numsChecked >= bingoSize && bc->IsComplete()) {
				for (size_t cardI = 0; cardI < cards.size(); ++cardI) {
					if (cards[cardI] == bc) {
						if (!cardStates[cardI]) {
							cardStates[cardI] = cards[cardI]->IsComplete();
							completeCardCount++;
						}
						if (completeCardCount == cards.size()) {
							int sum = cards[cardI]->SumOfUnchecked();
							cout << "sum of unchecked: " << sum << ", final num: " << num << endl;
							cout << "answer: " << sum * num << endl;
							return;
						}
						break;
					}
				}
			}
		}
	}
	cout << "no winners apparently" << endl;
}

void D4(int part) {
	ifstream file(FileFolder + "D4P1.txt");
	if (file.is_open()) {
		if (part == 1) {
			D4P1(file);
		}
		else {
			D4P2(file);
		}
	}
}

void ParseVentPositions(int* positions, string line) {
	char numString[4] = { '\0','\0','\0','\0' };
	for (size_t i = 0, c = 0, p = 0; i <= line.size(); ++i) {
		if (i != line.size() && line[i] >= '0' && line[i] <= '9') {
			numString[c] = line[i];
			c++;
		}
		else if (numString[0] != '\0') {
			numString[c] = '\0';
			int num = atoi(numString);
			positions[p] = num;
			p++;
			c = 0;
			for (int reset = 0; reset < 4; ++reset) {
				numString[reset] = '\0';
			}
		}
	}
}

int* GetTileVal(int* floor, int x, int y, int floorWidth) {
	return &(floor[y * floorWidth + x]);
}

void D5P1(ifstream& file) {
	string line;

	const int floorWidth = 1000;
	int* floor = new int[floorWidth * floorWidth]{};
	int overlapPoints = 0;

	while (getline(file, line)) {
		int positions[4];
		ParseVentPositions(&(positions[0]), line);
		if (positions[0] == positions[2] || positions[1] == positions[3]) {
			int xChange = positions[0] == positions[2] ? 0 : positions[2] > positions[0] ? 1 : -1;
			int yChange = positions[1] == positions[3] ? 0 : positions[3] > positions[1] ? 1 : -1;
			for (int x = positions[0], y = positions[1]; !(x == (positions[2] + xChange) && y == (positions[3] + yChange)); x += xChange, y += yChange) {
				int* tileVal = GetTileVal(floor, x, y, floorWidth);
				(*tileVal)++;
				if ((*tileVal) == 2) {
					overlapPoints++;
				}
			}
		}
	}

	cout << "overlap points: " << overlapPoints << endl;
	delete[] floor;
}

void D5P2(ifstream& file) {
	string line;

	const int floorWidth = 1000;
	int* floor = new int[floorWidth * floorWidth]{};
	int overlapPoints = 0;

	while (getline(file, line)) {
		int positions[4];
		ParseVentPositions(&(positions[0]), line);
		int xChange = positions[0] == positions[2] ? 0 : positions[2] > positions[0] ? 1 : -1;
		int yChange = positions[1] == positions[3] ? 0 : positions[3] > positions[1] ? 1 : -1;
		for (int x = positions[0], y = positions[1]; !(x == (positions[2] + xChange) && y == (positions[3] + yChange)); x += xChange, y += yChange) {
			int* tileVal = GetTileVal(floor, x, y, floorWidth);
			(*tileVal)++;
			if ((*tileVal) == 2) {
				overlapPoints++;
			}
		}
	}

	cout << "overlap points: " << overlapPoints << endl;
	delete[] floor;
}

void D5(int part) {
	ifstream file(FileFolder + "D5P1.txt");
	if (file.is_open()) {
		if (part == 1) {
			D5P1(file);
		}
		else {
			D5P2(file);
		}
	}
}

void D6(int part) {
	ifstream file(FileFolder + "D6P1.txt");
	if (file.is_open()) {
		string line;
		getline(file, line);

		const int maxGestation = 9, regGestation = 7;
		int daysToRun = part == 1 ? 80 : 256;
		double_t fishPregProg[maxGestation] = {};

		for (size_t i = 0; i < line.size(); i += 2) {
			fishPregProg[line[i] - '0']++;
		}

		for (size_t t = 0; t < daysToRun; ++t) {
			double_t zeroCount = fishPregProg[0];
			for (int i = 1; i < maxGestation; ++i) {
				fishPregProg[i - 1] = fishPregProg[i];
			}
			fishPregProg[regGestation - 1] += zeroCount;
			fishPregProg[maxGestation - 1] = zeroCount;
		}

		double_t fishCount = 0;
		for (size_t i = 0; i < maxGestation; ++i) {
			fishCount += fishPregProg[i];
		}

		cout.precision(0);
		cout << fixed << "fish after " << daysToRun << " days: " << fishCount << endl;
		cout << defaultfloat;
	}
}

int CalculateTotalCrabMovement(map<int, int>& positionCounts, int testPos, bool triangularCost) {
	int displacement = 0;
	for (pair<int, int> pair : positionCounts) {
		int diff = pair.first - testPos;
		if (diff < 0) {
			diff *= -1;
		}
		if (triangularCost) {
			diff = (diff * (diff + 1)) / 2;
		}
		displacement += diff * pair.second;
	}
	return displacement;
}

void D7(int part) {
	ifstream file(FileFolder + "D7P1.txt");
	if (file.is_open()) {
		string line;
		map<int, int> positionCounts = {};
		int maxPos = INT16_MIN, minPos = INT16_MAX;

		while (getline(file, line, ',')) {
			int pos = stoi(line);
			if (positionCounts.find(pos) == positionCounts.end()) {
				positionCounts[pos] = 1;
				if (pos > maxPos) {
					maxPos = pos;
				}
				if (pos < minPos) {
					minPos = pos;
				}
			}
			else {
				positionCounts[pos]++;
			}
		}

		int maxPosCost = CalculateTotalCrabMovement(positionCounts, maxPos, part == 2);
		int minPosCost = CalculateTotalCrabMovement(positionCounts, minPos, part == 2);
		pair<int, int> cheapestPosAndCost = (minPosCost < maxPosCost ?
			pair<int, int>{minPos, minPosCost} : pair<int, int>{ maxPos, maxPosCost });
		bool unfinished = true;
		while (unfinished) {
			if (maxPos - minPos <= 1) {
				pair<int, int> cheapestPosAndCost = (minPosCost < maxPosCost ?
					pair<int, int>{minPos, minPosCost} : pair<int, int>{ maxPos, maxPosCost });
				unfinished = false;
				break;
			}

			int mid = (maxPos + minPos) / 2;
			int midCost = CalculateTotalCrabMovement(positionCounts, mid, part == 2);
			if (midCost < cheapestPosAndCost.second) {
				cheapestPosAndCost = pair<int, int>{ mid, midCost };
			}
			if (maxPosCost > minPosCost) {
				maxPosCost = midCost;
				maxPos = mid;
			}
			else {
				minPosCost = midCost;
				minPos = mid;
			}
		}

		cout << "pos: " << cheapestPosAndCost.first << ", cost: " << cheapestPosAndCost.second << endl;
	}
}

function<void(int)> Problems[25] = { D1,D2,D3,D4,D5,D6,D7, };

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

	chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
	Problems[stoi(args[0]) - 1](stoi(args[1]));
	chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();

	cout << "execution time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0f << " ms" << endl;
}