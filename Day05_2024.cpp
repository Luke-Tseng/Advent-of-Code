#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <deque>

struct error
{
    int firstPos;
    int secondValue;
};

void edit_rules(std::vector<error> &rules, int pos1, int pos2)
{
    for (error &e : rules)
    {
        if (e.firstPos == pos1)
        {
            e.firstPos = pos2;
        }
        else if (e.firstPos == pos2)
        {
            e.firstPos = pos1;
        }
    }
}

int check_queue(std::vector<int> queue, std::unordered_map<int, std::vector<int>> m)
{
    bool error_found = false;
    std::vector<error> rules;

    for (int i = 0; i < queue.size(); i++)
    {

        for (int j : m[queue[i]])
        {
            rules.push_back(error{i, j});
        }
    }

    for (int i = queue.size() - 1; i >= 0; i--)
    {
        int num = queue[i];
        for (int j = 0; j < rules.size(); j++)
        {
            error e = rules[j];
            if (e.secondValue == num && i > e.firstPos)
            {
                error_found = true;
                std::swap(queue[i], queue[e.firstPos]);
                num = queue[i];
                edit_rules(rules, e.firstPos, i);
            }
        }
    }

    int n = queue.size() / 2;

    return error_found ? queue[n] : 0;
}

int main()
{
    std::unordered_map<int, std::vector<int>> m;
    std::vector<std::vector<int>> queues;

    std::ifstream file("Day05_2024_input.txt");
    std::string line;
    bool toggle = true;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (toggle)
        {
            if (line == "")
            {
                toggle = false;
            }
            int n1;
            int n2;
            char sep;
            iss >> n1 >> sep >> n2;
            m[n2].push_back(n1);
        }
        else
        {
            std::vector<int> queue;
            int n;
            char sep;
            while (iss >> n)
            {
                queue.push_back(n);
                iss >> sep;
            }
            queues.push_back(queue);
        }
    }
    file.close();

    int total = 0;
    for (std::vector<int> &queue : queues)
    {
        total += check_queue(queue, m);
    }

    std::cout << total << std::endl;

    return 0;
}