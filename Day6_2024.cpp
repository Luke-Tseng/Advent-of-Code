#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

enum Direction
{
    up,
    right,
    down,
    left
};

std::pair<int, int> move(std::pair<int, int> position, Direction dir)
{
    std::pair<int, int> newPosition = position;
    switch (dir)
    {
    case up:
        newPosition.first -= 1;
        break;
    case right:
        newPosition.second += 1;
        break;
    case down:
        newPosition.first += 1;
        break;
    case left:
        newPosition.second -= 1;
        break;
    default:
        break;
    }
    return newPosition;
}

bool check_edge(Direction dir, std::pair<int, int> pos, int row, int col)
{
    switch (dir)
    {
    case up:
        if (pos.first == 0)
            return true;
    case right:
        if (pos.second == col - 1)
            return true;
    case down:
        if (pos.first == row - 1)
            return true;
    case left:
        if (pos.second == 0)
            return true;
    default:
        break;
    }
    return false;
}

int test_obstruction(std::pair<int, int> obstuction, std::vector<std::vector<char>> map, std::pair<int, int> position, Direction dir)
{
    int row = map.size();
    int col = map[0].size();
    std::map<std::pair<int, int>, std::vector<int>> visited;

    while (!check_edge(dir, position, row, col))
    {
        std::pair<int, int> newPosition = move(position, dir);
        if (map[newPosition.first][newPosition.second] == '#' || newPosition == obstuction)
        {
            dir = static_cast<Direction>((dir + 1) % 4);
        }
        else if (std::find(visited[newPosition].begin(), visited[newPosition].end(), dir) != visited[newPosition].end())
        {
            return 1;
        }
        else
        {
            visited[newPosition].push_back(dir);
            position = newPosition;
        }
    }
    return 0;
}

std::vector<std::vector<char>> read_input(std::string filename, std::pair<int, int> &position)
{
    std::vector<std::vector<char>> map;
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<char> row;
        for (int j = 0; j < line.length(); j++)
        {
            char c = line[j];
            if (c == '^')
                position = {i, j};
            row.push_back(c);
        }
        map.push_back(row);
        i++;
    }
    file.close();
    return map;
}

int main()
{
    std::pair<int, int> startingPosition;
    std::vector<std::vector<char>> map = read_input("Day6_2024_input.txt", startingPosition);
    std::set<std::pair<int, int>> visited;
    std::pair<int, int> position = startingPosition;
    visited.insert(position);

    Direction dir = up;
    int row = map.size();
    int col = map[0].size();

    while (!check_edge(dir, position, row, col))
    {
        std::pair<int, int> newPosition = move(position, dir);
        if (map[newPosition.first][newPosition.second] == '#')
        {
            dir = static_cast<Direction>((dir + 1) % 4);
        }
        else
        {
            visited.insert(newPosition);
            position = newPosition;
        }
    }
    std::cout << visited.size() << std::endl;

    int total = 0;
    for (auto &obstuction : visited)
    {
        if (obstuction == startingPosition)
            continue;
        dir = up;
        total += test_obstruction(obstuction, map, startingPosition, dir);
    }
    std::cout << total << std::endl;
    return 0;
}