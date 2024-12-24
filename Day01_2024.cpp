#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

int main()
{
    std::vector<int> list1;
    std::vector<int> list2;

    // Putting input into 2 lists
    std::ifstream file("Day01_2024_input.txt");
    int num;
    bool toggle = true;
    while (file >> num)
    {
        if (toggle)
        {
            list1.push_back(num);
        }
        else
        {
            list2.push_back(num);
        }
        toggle = !toggle;
    }
    file.close();

    // Part 1
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int n = list1.size();
    int distance = 0;
    // Getting total distance between the two lists
    for (int i = 0; i < n; i++)
    {
        distance += abs(list1[i] - list2[i]);
    }

    std::cout << distance << std::endl;

    // Part 2
    std::unordered_map<int, int> map;

    // Put list2 into a map
    for (int i : list2)
    {
        map[i]++;
    }

    long long similarity = 0;
    for (int i : list1)
    {
        similarity += i * map[i];
    }

    std::cout << similarity << std::endl;

    return 0;
}