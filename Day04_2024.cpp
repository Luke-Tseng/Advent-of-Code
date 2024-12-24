#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int check_X(std::vector<std::vector<char>> letters, int row, int col)
{
    int total = 0;
    int rows = letters.size();
    int cols = letters[0].size();
    // rows
    if (rows - row > 3)
    {
        if (letters[row + 1][col] == 'M' && letters[row + 2][col] == 'A' && letters[row + 3][col] == 'S')
            total++;
    }
    if (row >= 3)
    {
        if (letters[row - 1][col] == 'M' && letters[row - 2][col] == 'A' && letters[row - 3][col] == 'S')
            total++;
    }

    // cols
    if (cols - col > 3)
    {
        if (letters[row][col + 1] == 'M' && letters[row][col + 2] == 'A' && letters[row][col + 3] == 'S')
            total++;
    }
    if (col >= 3)
    {
        if (letters[row][col - 1] == 'M' && letters[row][col - 2] == 'A' && letters[row][col - 3] == 'S')
            total++;
    }

    // diag
    if (rows - row > 3 && cols - col > 3)
    {
        if (letters[row + 1][col + 1] == 'M' && letters[row + 2][col + 2] == 'A' && letters[row + 3][col + 3] == 'S')
            total++;
    }
    if (row >= 3 && col >= 3)
    {
        if (letters[row - 1][col - 1] == 'M' && letters[row - 2][col - 2] == 'A' && letters[row - 3][col - 3] == 'S')
            total++;
    }
    if (rows - row > 3 && col >= 3)
    {
        if (letters[row + 1][col - 1] == 'M' && letters[row + 2][col - 2] == 'A' && letters[row + 3][col - 3] == 'S')
            total++;
    }
    if (cols - col > 3 && row >= 3)
    {
        if (letters[row - 1][col + 1] == 'M' && letters[row - 2][col + 2] == 'A' && letters[row - 3][col + 3] == 'S')
            total++;
    }
    return total;
}

int check_MAS(std::vector<std::vector<char>> letters, int row, int col)
{
    int total = 0;
    int rows = letters.size();
    int cols = letters[0].size();

    if (rows - row > 2 && cols - col > 2)
    {
        if (letters[row][col + 2] == 'S' && letters[row + 1][col + 1] == 'A' && letters[row + 2][col] == 'M' && letters[row + 2][col + 2] == 'S')
            total++;

        if (letters[row][col + 2] == 'M' && letters[row + 1][col + 1] == 'A' && letters[row + 2][col] == 'S' && letters[row + 2][col + 2] == 'S')
            total++;
    }

    if (row >= 2 && col >= 2)
    {
        if (letters[row][col - 2] == 'M' && letters[row - 1][col - 1] == 'A' && letters[row - 2][col] == 'S' && letters[row - 2][col - 2] == 'S')
            total++;

        if (letters[row][col - 2] == 'S' && letters[row - 1][col - 1] == 'A' && letters[row - 2][col] == 'M' && letters[row - 2][col - 2] == 'S')
            total++;
    }
    return total;
}

int main()
{
    std::vector<std::vector<char>> letters;

    std::ifstream file("Day04_2024_input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<char> row;
        char c;
        while (iss >> c)
        {
            row.push_back(c);
        }
        letters.push_back(row);
    }
    file.close();
    int rows = letters.size();
    int cols = letters[0].size();
    int total_xmas = 0;
    int total_x_mas = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (letters[i][j] == 'X')
                total_xmas += check_X(letters, i, j);
            if (letters[i][j] == 'M')
                total_x_mas += check_MAS(letters, i, j);
        }
    }
    std::cout << total_xmas << std::endl;
    std::cout << total_x_mas << std::endl;
    return 0;
}