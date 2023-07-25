#include <algorithm>
#include <climits>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>


// Checks if sort is valid
bool check(std::vector<int> nums)
{
    int prev = INT_MIN;
    for(int num:nums)
    {
        if(num < prev)
        {
            return true;
        }
        prev = num;
    }
    return false;
}

// Prints ordered array + sort number
void printNums(std::vector<int> nums, int* count)
{
    
    *count = *count + 1;
    std::cout << std::endl << "Sort number " << *count << ":  " << std::endl;

    for(int num: nums)
    {
        std::cout << num << ", ";
    }
    std::cout << std::endl;
}

// sorts and gets time to sort
double getTime(std::vector<int> nums, int* count)
{
    bool unsorted = true;
    auto start = std::chrono::system_clock::now(); // get start time
    int sorts = 0;

    while(unsorted)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(nums.begin(), nums.end(), std::default_random_engine(seed)); // randomize with this seed
        unsorted = check(nums); // check to see if sorted
        sorts++;
    }

    auto end = std::chrono::system_clock::now();
    printNums(nums, count);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Total time " << elapsed_seconds.count() << std::endl << "Sorts required: " << sorts << std::endl;
    return elapsed_seconds.count();  
}


int main(int argc, char** argv)
{
    if(argc < 2 || std::stoi(argv[1]) > 100)
    {
        std::cout << "INCORRECT USAGE " << std::endl;
        std::cout << "./<executable> <numz to sort>" << std::endl;
        std::cout << "Must be less than 9" << std::endl;
        return -1;
    }

    srand(time(NULL)); // seed for random numbers  
    int numToSort = std::stoi(argv[1]);
    int timesToRun = 5; // times to run simulation (for metrics)
    int num = 0;
    int count = 0;
    double sum = 0;
    std::vector<int> nums;
    std::vector<double> resultTimes;
    std::unordered_map<int, int> map;

    // generate random array of given length
    for(int i = 0; i < numToSort+1; i++)
    {
        num = rand() % 1000;
        if(map[num] != -62)
        {
            nums.push_back(num);
        }
        map[num] = -62;
        std::cout << "added " << num << std::endl;
    }

    std::cout << std::endl << "Started sort ..." << std::endl<< std::endl;
    
    for(int i = 0; i < timesToRun; i++)
    {
        resultTimes.push_back(getTime(nums, &count));
    }

    for(double num:resultTimes)
    {
        sum += num;
    }

    float result = float(sum) / float(timesToRun);
    std::cout << std::endl << "Average time is: " << result << std::endl;
    std::cout << "Total time to run " << timesToRun << " Tests: " << sum << std::endl;
}