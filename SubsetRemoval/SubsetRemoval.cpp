// SubsetRemoval.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> subSetSum(std::vector<int> vec, int target_index) {
	if (vec.size() <= 2) { return std::vector<int> { };}
	int target_element = vec[target_index];
	vec.erase(vec.begin() + target_index);
	std::vector<std::vector<bool>> subSetSumVec(vec.size(), std::vector<bool>(target_element + 1));

	for (int i = 0; i < (int) subSetSumVec[0].size(); i++) {
		if (i == vec[0] || i == 0) { subSetSumVec[0][i] = true; }
		else { subSetSumVec[0][i] = false; }
	}


	int row, col;

	for (row = 1; row < (int) vec.size(); ++row) {
		int cur_num = vec[row];
		
		for (col = 0; col < (int) subSetSumVec[row].size(); ++col) {
			if (col < cur_num) {
				subSetSumVec[row][col] = subSetSumVec[row - 1][col];
			}
			else {
				subSetSumVec[row][col] = subSetSumVec[row - 1][col - cur_num];
			}
		}
	}

	row--;
	col--;

	if (subSetSumVec[row][col] == false) { return std::vector<int> { };}

	std::vector<int> backTrackVec;

	while (row >= 0 && col > 0) {
		if (row == 0) { 
			backTrackVec.push_back(vec[row]); 
			break;
		}
		else if (subSetSumVec[row - 1][col]) {
			--row;
		}
		else {
			backTrackVec.push_back(vec[row]);
			col -= vec[row];
			--row;
		}
	}


	if (backTrackVec.size() == vec.size()) { return std::vector<int> {}; }

	for (int ele : backTrackVec) {
		vec.erase(std::find(vec.begin(), vec.end(), ele));
	}

	return vec;
}



void subSetSumRemoval(std::vector<int> vec, std::vector<int> & min_vec) {

	for (int i = 2; i < (int) vec.size(); i++) {
		std::vector<int> new_vec = subSetSum(vec, i);
		if (new_vec.size() != 0) { 
			if (new_vec.size() < min_vec.size()) { min_vec = new_vec; }
			subSetSumRemoval(new_vec, min_vec); 
		}
	}

}

int main(int argc, char *argv[])
{
	
	std::vector<int> test_1 = {1,3,5,6};
	std::vector<int> ret_1 = test_1;
 	std::sort(test_1.begin(), test_1.end());

	subSetSumRemoval(test_1, ret_1);

	for (auto r : ret_1) {
		std::cout << r << std::endl;
	}
	std::cout << std::endl;
	

	std::vector<int> test_2 = {48,20,1,3,4,6,9,24};
	std::vector<int> ret_2 = test_2;
	std::sort(test_2.begin(), test_2.end());

	subSetSumRemoval(test_2, ret_2);

	for (auto r : ret_2) {
		std::cout << r << " ";
	}
	std::cout << std::endl;

    return 0;
}

