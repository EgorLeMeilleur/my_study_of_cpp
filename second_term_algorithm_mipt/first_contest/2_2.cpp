//В большой IT - фирме есть только одна переговорная комната.
//Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
//Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
//Число заявок ≤ 100000.

#include <iostream>
#include <vector>
#include <algorithm>

bool comp(std::pair<int, int>& x, std::pair<int, int>& y) //оператор сравнения, возрвращающий сравнение по второй координате
{
    return (x.second < y.second);
}

int find_max_quantity_of_applications(std::vector<std::pair<int, int>>& array_of_time)
{
    std::sort(array_of_time.begin(), array_of_time.end(), comp);
    int meetings = 1;
    int cur_time = array_of_time[0].second;
    for (int i = 0; i < array_of_time.size();)
    {
        if (array_of_time[i].first < cur_time)
        {
            ++i;
        }
        else
        {
            meetings++;
            cur_time = array_of_time[i].second;
        }
    }
    return meetings;
}

int main()
{
    std::vector<std::pair<int, int>> array_of_time;
    int start = 0, end = 0;
    while (std::cin >> start >> end)
    {
        array_of_time.push_back(std::make_pair(start, end));
    }
    std::cout << find_max_quantity_of_applications(array_of_time);
    return 0;
}
