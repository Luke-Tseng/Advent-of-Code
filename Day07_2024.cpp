#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// recursive function operating from right to left
bool calibration(std::vector<long long int> equation, int pos, long long int value)
{
    if (value < equation[1])
        return false;

    long long int n = equation[pos];
    // base case
    if (pos == 1)
    {
        if (value == n)
        {
            return true;
        }
        return false;
    }

    if (value % n == 0)
    {
        return calibration(equation, pos - 1, value / n) || calibration(equation, pos - 1, value - n);
    }
    return calibration(equation, pos - 1, value - n);
}

// recursive function operating from left to right
bool calibration_part_2(std::vector<long long int> equation, int pos, long long int value)
{
    if (value > equation[0])
        return false;

    long long int n = equation[pos];

    // base case
    if (pos == equation.size())
    {
        if (value == equation[0])
        {
            return true;
        }
        return false;
    }
    long long int concat = std::stoll(std::to_string(value) + std::to_string(n));

    return calibration_part_2(equation, pos + 1, value + n) || calibration_part_2(equation, pos + 1, value * n) || calibration_part_2(equation, pos + 1, concat);
}

std::vector<std::vector<long long int>> read_input(std::string filename)
{
    std::vector<std::vector<long long int>> equations;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<long long int> equation;
        long long int value;
        char sep;
        iss >> value >> sep;
        equation.push_back(value);
        while (iss >> value)
        {
            equation.push_back(value);
        }
        equations.push_back(equation);
    }
    file.close();
    return equations;
}

int main()
{
    std::vector<std::vector<long long int>> equations = read_input("Day07_2024_input.txt");
    long long int total = 0;

    std::vector<std::vector<long long int>> failed_equations;
    for (const auto &equation : equations)
    {
        // check if a valid configuration is possible
        if (calibration(equation, equation.size() - 1, equation[0]))
        {
            total += equation[0];
        }
        else
        {
            failed_equations.push_back(equation);
        }
    }
    std::cout << total << std::endl;

    for (const auto &equation : failed_equations)
    {
        if (calibration_part_2(equation, 2, equation[1]))
        {
            total += equation[0];
        }
    }
    std::cout << total << std::endl;
    return 0;
}