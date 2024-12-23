#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

bool check_inside(std::pair<int, int> location, int row, int col)
{
    if (location.first < row && location.second < col && location.first >= 0 && location.second >= 0)
        return true;
    return false;
}

void find_antinode(std::set<std::pair<int, int>> &antinodes, std::vector<std::pair<int, int>> freq, int row, int col)
{
    for (int i = 0; i < freq.size() - 1; i++)
    {
        for (int j = i + 1; j < freq.size(); j++)
        {
            // get distances of first antinodes
            std::pair<int, int> dist = {freq[i].first - freq[j].first, freq[i].second - freq[j].second};
            std::pair<int, int> first = {freq[i].first + dist.first, freq[i].second + dist.second};
            std::pair<int, int> second = {freq[j].first - dist.first, freq[j].second - dist.second};

            // insert if inbounds
            if (check_inside(first, row, col))
            {
                antinodes.insert(first);
            }
            if (check_inside(second, row, col))
            {
                antinodes.insert(second);
            }
        }
    }
}

void find_antinode_part_2(std::set<std::pair<int, int>> &antinodes, std::vector<std::pair<int, int>> freq, int row, int col)
{
    for (int i = 0; i < freq.size() - 1; i++)
    {
        for (int j = i + 1; j < freq.size(); j++)
        {
            // get distances of first antinodes
            std::pair<int, int> dist = {freq[i].first - freq[j].first, freq[i].second - freq[j].second};
            std::pair<int, int> first = {freq[i].first + dist.first, freq[i].second + dist.second};
            std::pair<int, int> second = {freq[j].first - dist.first, freq[j].second - dist.second};

            // insert each antenna as antinode
            antinodes.insert(freq[i]);
            antinodes.insert(freq[j]);

            // keep finding antinodes until out of bounds
            while (check_inside(first, row, col))
            {
                antinodes.insert(first);
                first = {first.first + dist.first, first.second + dist.second};
            }
            while (check_inside(second, row, col))
            {
                antinodes.insert(second);
                second = {second.first - dist.first, second.second - dist.second};
            }
        }
    }
}

int main()
{
    std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies;
    std::set<std::pair<int, int>> antinodes;
    std::ifstream file("Day8_2024_input.txt");
    std::string line;
    int row = 0, col = 0;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char c;
        col = 0;
        while (iss >> c)
        {
            if (c != '.')
                frequencies[c].push_back({row, col});
            col++;
        }
        row++;
    }
    file.close();

    for (const auto &freq : frequencies)
    {
        find_antinode(antinodes, freq.second, row, col);
    }

    std::cout << antinodes.size() << std::endl;

    for (const auto &freq : frequencies)
    {
        find_antinode_part_2(antinodes, freq.second, row, col);
    }

    std::cout << antinodes.size() << std::endl;

    return 0;
}