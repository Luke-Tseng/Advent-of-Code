#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

void blink(std::vector<long long int> &stones)
{
    for (long long i = 0; i < stones.size(); i++)
    {
        long long int stone = stones[i];
        if (stone == 0)
        {
            stones[i] = 1;
        }
        else if (std::to_string(stone).length() % 2 == 0)
        {
            std::string s = std::to_string(stone);
            long long int left = std::stoll(s.substr(0, s.length() / 2));
            long long int right = std::stoll(s.substr(s.length() / 2));
            stones[i] = left;
            stones.insert(stones.begin() + (++i), right);
        }
        else
        {
            stones[i] = stone * 2024;
        }
    }
}

std::unordered_map<std::string, long long int> cache;

long long int count(long long int stone, int blink)
{
    std::string key = std::to_string(stone) + "," + std::to_string(blink);

    // Check if the result is already in the cache
    if (cache.find(key) != cache.end())
    {
        return cache[key];
    }
    long long int result;
    if (blink == 0)
        result = 1;
    else if (stone == 0)
        result = count(1, blink - 1);
    else
    {
        std::string s = std::to_string(stone);
        if (s.length() % 2 == 0)
        {
            long long int left = std::stoll(s.substr(0, s.length() / 2));
            long long int right = std::stoll(s.substr(s.length() / 2));
            result = count(left, blink - 1) + count(right, blink - 1);
        }
        else
        {
            result = count(stone * 2024, blink - 1);
        }
    }
    cache[key] = result;
    return result;
}

int main()
{
    std::vector<long long int> stones;
    std::ifstream file("Day11_2024_input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int n;

        while (iss >> n)
        {
            stones.push_back(n);
        }
    }
    file.close();

    std::vector<long long int> stones_part_2 = stones;

    for (int i = 0; i < 25; i++)
    {
        blink(stones);
    }

    std::cout << stones.size() << std::endl;

    long long int total = 0;
    for (long long int stone : stones_part_2)
    {
        total += count(stone, 75);
    }
    std::cout << total << std::endl;

    return 0;
}