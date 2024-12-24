#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>

int parse(std::string line, bool& enabled)
{
    int total = 0;
    std::regex re(R"((mul\((\d+),(\d+)\))|(don't\(\))|(do\(\)))");
    std::smatch match;
    while (std::regex_search(line, match, re)) {
        if (match[1].matched) {
            if (enabled)
                total += std::stoi(match[2]) * std::stoi(match[3]);
        }
        if (match[4].matched)
        {
            enabled = false;
        }
        if (match[5].matched)
        {
            enabled = true;
        }
        line = match.suffix().str();
    }
    return total;
}

int main()
{
    std::fstream file("Day03_2024_input.txt");
    std::string line;
    int total = 0;
    bool enabled = true;
    while(std::getline(file, line))
    {
        total += parse(line, enabled);
    }
    
    std::cout << total << std::endl;
    return 0;
}