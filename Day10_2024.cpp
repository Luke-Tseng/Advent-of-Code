#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

// function to check if position is inside map
bool check_inside(std::vector<std::vector<int>> map, std::pair<int, int> position)
{
    int row = map.size();
    int col = map[0].size();

    if (position.first >= row || position.second >= col || position.first < 0 || position.second < 0)
    {
        return false;
    }

    return true;
}

// recursive function that keeps going if incrementing in a direction
// adds to set if at 9
void find_trail(std::set<std::pair<int, int>> &trails, int &count, std::vector<std::vector<int>> map, int height, std::pair<int, int> position)
{
    // base case
    if (height == 9)
    {
        count++;
        trails.insert(position);
        return;
    }

    std::pair<int, int> newPosition = position;
    // check down
    newPosition.first += 1;
    if (check_inside(map, newPosition) && map[newPosition.first][newPosition.second] == height + 1)
    {
        find_trail(trails, count, map, height + 1, newPosition);
    }
    // check up
    newPosition = position;
    newPosition.first -= 1;
    if (check_inside(map, newPosition) && map[newPosition.first][newPosition.second] == height + 1)
    {
        find_trail(trails, count, map, height + 1, newPosition);
    }
    // check right
    newPosition = position;
    newPosition.second += 1;
    if (check_inside(map, newPosition) && map[newPosition.first][newPosition.second] == height + 1)
    {
        find_trail(trails, count, map, height + 1, newPosition);
    }
    // check left
    newPosition = position;
    newPosition.second -= 1;
    if (check_inside(map, newPosition) && map[newPosition.first][newPosition.second] == height + 1)
    {
        find_trail(trails, count, map, height + 1, newPosition);
    }
}

int main()
{
    std::vector<std::vector<int>> map;
    std::ifstream file("Day10_2024_input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char c;
        std::vector<int> row;

        while (iss >> c)
        {
            int n = std::stoi(std::string(1, c));
            row.push_back(n);
        }
        map.push_back(row);
    }
    file.close();

    int score = 0;
    int score_part_2 = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 0)
            {
                std::set<std::pair<int, int>> trails;
                int count = 0;
                find_trail(trails, count, map, 0, {i, j});
                score += trails.size();
                score_part_2 += count;
            }
        }
    }

    std::cout << score << std::endl;
    std::cout << score_part_2 << std::endl;
    return 0;
}