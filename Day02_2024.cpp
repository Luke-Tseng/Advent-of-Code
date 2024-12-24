#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

bool check_dampener(std::vector<int> report, int index, bool increasing)
{
    int n = report.size();
    int last = report[0];
    bool failed = false;
    for (int i = 1; i < n; i++)
    {
        int curr = report[i];
        if (increasing)
        {
            if (i == index)
                continue;
            if (last >= curr || curr - last > 3)
            {
                failed = true;
                break;
            }
        }
        else
        {
            if (i == index)
            {
                continue;
            }
            if (last <= curr || last - curr > 3)
            {
                failed = true;
                break;
            }
        }
        last = curr;
    }
    if (!failed)
        return true;

    index--;
    int start = index == 0 ? 1 : 0;
    last = report[0 + start];

    for (int i = 1 + start; i < n; i++)
    {
        int curr = report[i];
        if (increasing)
        {
            if (i == index)
                continue;
            if (last >= curr || curr - last > 3)
                return false;
        }
        else
        {
            if (i == index)
                continue;
            if (last <= curr || last - curr > 3)
                return false;
        }
        last = curr;
    }
    return true;
}

int main()
{
    std::vector<std::vector<int>> reports;

    // Put input into a vector of vectors for each report
    std::ifstream file("Day2_2024_input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> report;
        int num;
        while (iss >> num)
        {
            report.push_back(num);
        }
        reports.push_back(report);
    }
    file.close();

    int safe = reports.size();
    for (std::vector<int> report : reports)
    {
        int size = report.size();
        bool increasing = report[0] - report[size - 1] < 0 ? true : false;
        int last = report[0];
        bool removed = false;
        for (int i = 1; i < size; i++)
        {
            int curr = report[i];
            if (increasing)
            {
                if (last >= curr || curr - last > 3)
                {
                    if (!check_dampener(report, i, increasing))
                    {
                        safe--;
                    }
                    break;
                }
            }
            else
            {
                if (last <= curr || last - curr > 3)
                {
                    if (!check_dampener(report, i, increasing))
                    {
                        safe--;
                    }
                    break;
                }
            }
            last = curr;
        }
    }
    std::cout << safe << std::endl;
    return 0;
}