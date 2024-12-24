#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void file_fragmentation(std::vector<int> &disk)
{
    // two pointers to swap free space with files
    int left = 0;
    int right = disk.size() - 1;
    while (left <= right)
    {
        // get left to a free space position
        while (disk[left] != -1)
        {
            left++;
        }
        // get right to a file position
        while (disk[right] == -1)
        {
            right--;
        }
        if (left > right)
            break;

        disk[left] = disk[right];
        disk[right] = -1;
    }
}

void file_compacting(std::vector<int> &disk)
{
    int left = 0;
    int right = disk.size() - 1;
    while (disk[right] != 0)
    {
        left = 0;
        int last = -1;
        int fileSize = 0;
        int freeSpaceSize = 0;
        // search for next file
        while (disk[right] == -1 || disk[right] == last)
        {
            right--;
        }
        last = disk[right];

        // get size of file
        while (disk[right] == last)
        {
            fileSize++;
            right--;
        }

        // search for free space that can fit file
        while (freeSpaceSize < fileSize && left <= right)
        {
            if (disk[left] == -1)
            {
                freeSpaceSize++;
            }
            else
            {
                freeSpaceSize = 0;
            }
            left++;
        }

        // insert file into free space
        if (freeSpaceSize == fileSize)
        {
            for (int i = 1; i <= fileSize; i++)
            {
                disk[left - i] = last;
                disk[right + i] = -1;
            }
        }
    }
}

int main()
{
    std::vector<int> disk;
    std::ifstream file("Day09_2024_input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char c;
        bool toggle = true; // true for files, false for free space
        int id = 0;

        while (iss >> c)
        {
            int n = std::stoi(std::string(1, c));

            if (toggle)
            {
                for (int i = 0; i < n; i++)
                {
                    disk.push_back(id);
                }
                id++;
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    disk.push_back(-1);
                }
            }
            toggle = !toggle;
        }
    }
    file.close();

    std::vector<int> disk_part_2 = disk;

    file_fragmentation(disk);

    long long int total = 0;
    int i = 0;
    while (disk[i] != -1)
    {
        total += disk[i] * i;
        i++;
    }

    std::cout << total << std::endl;

    file_compacting(disk_part_2);

    long long int total_part_2 = 0;
    for (int i = 0; i < disk_part_2.size(); i++)
    {
        if (disk_part_2[i] == -1)
            continue;

        total_part_2 += disk_part_2[i] * i;
    }

    std::cout << total_part_2 << std::endl;
    return 0;
}