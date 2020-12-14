#include <vector>
#include <fstream>
#include <string>
#include <iostream>

//Day9 Part1
//Given a set of numbers, with a preamble length of twenty five, each number after 25 must be a sum of two numbers in the preamble. If a number is the list
//shifts by one so instead of numbers 1 to 25 being the preamble the numbers 2 to 26 are the preamble. We need to find the first number that is not a sum of
//2 numbers in the preamble.

//For this we can use a nested for loop to check the sum of each number pair until we don't find a pair that sums to our target value.

//Part 2
//Using the answer from part 1 find a contiguous set of numbers who sum to the same value as the answer, then get the highest and lowest values from that
//set and add them together for the answer

//for this we can also use a nested loop, we can get our first number then add following numbers until we either reach our target which then we can
//return a pair of indexes or if we go over the target we can break the loop.

std::vector<int64_t> getPuzzleInput()
{
	std::vector<int64_t> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	while (std::getline(file, line))
	{
		int64_t x = std::stoll(line);
		input.push_back(x);
	}

	return input;
}

bool check(int start, int end, int64_t target, std::vector<int64_t> input)
{
	for (int i = start; i <= end; i++)
	{
		for (int j = start + 1; j <= end; j++)
		{
			if (input[i] + input[j] == target)
			{
				return false; //if it finds a match
			}
				
		}
	}
	
	return true; //if it doesn't find a match
}

int64_t findAnswerPart1(std::vector<int64_t> input)
{
	int start = 0;
	int end = 24;

	while (true)
	{
		bool result = check(start, end, input[end + 1], input);

		if (result)
			return input[end + 1];
		else
		{
			start++;
			end++;
		}
	}
}

std::pair<int, int> findContiguous(std::vector<int64_t> input, int64_t target)
{
	for (int i = 0; i <= input.size(); i++)
	{
		int64_t sum = input[i];

		for (int j = i+1; j < input.size(); j++)
		{
			sum += input[j];
			
			if (sum == target)
				return std::make_pair(i, j);
			else if (sum > target)
				break;
		}
	}
}

int64_t findAnswerPart2(std::vector<int64_t> input)
{
	std::pair<int, int> result = findContiguous(input, 258585477);

	int64_t max = -1;
	int64_t min = LONG_MAX;

	int start = result.first;
	int end = result.second;

	for (int i = start; i <= end; i++)
	{
		if (input[i] > max)
			max = input[i];
		if (input[i] < min)
			min = input[i];
	}

	std::cout << "max:" << max << " min:" << min << '\n';
	return max + min;
}

int main()
{
	std::vector<int64_t> input = getPuzzleInput();

	/*for (int i = 0; i < input.size(); i++)
	{
		std::cout << "#" << i << ":" << input[i] << '\n';
	}*/

	std::cout << findAnswerPart1(input) << '\n';

	std::cout << findAnswerPart2(input) << '\n';

	return 0;
}