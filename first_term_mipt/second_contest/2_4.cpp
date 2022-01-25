//На числовой прямой окрасили N отрезков.
//Известны координаты левого и правого концов каждого отрезка[Li, Ri].Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
//N ≤ 10000. Li, Ri — целые числа в диапазоне[0, 109].

#include <iostream>
#include <vector>
#include <queue>
struct Event
{
    int time;
    int type;
    bool operator<(const Event& event) const
    {
        return time < event.time || time == event.time && type > event.type;
    }
    bool operator>(const Event& event) const
    {
        return time > event.time || time == event.time && type < event.type;
    }
};
int calc_painted_length(const std::vector<Event>& borders)
{
    int current_overlay = 0;
    int total_overlay = 0;
    int last_border = 0;
    for (int i = 0; i < borders.size(); i++)
    {
        if (current_overlay == 1)
        {
            total_overlay += borders[i].time - last_border;
        }
        current_overlay += borders[i].type;
        last_border = borders[i].time;
    }
    return total_overlay;
}
void heapify(std::vector<Event>& borders, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && borders[left] > borders[largest])
    {
        largest = left;
    }
    if (right < n && borders[right] > borders[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        std::swap(borders[i], borders[largest]);
        heapify(borders, n, largest);
    }
}
void heap_sort(std::vector<Event>& borders)
{
    for (int i = borders.size() / 2 - 1; i >= 0; i--)
    {
        heapify(borders, borders.size(), i);
    }
    for (int i = borders.size() - 1; i >= 0; i--)
    {
        std::swap(borders[0], borders[i]);
        heapify(borders, i, 0);
    }
}
int main()
{
    int number_of_segments = 0;
    std::cin >> number_of_segments;

    std::vector<Event> borders(2 * number_of_segments);
    for (int i = 0; i < number_of_segments; i++)
    {
        std::cin >> borders[2 * i].time >> borders[2 * i + 1].time;
        borders[2 * i].type = 1;
        borders[2 * i + 1].type = -1;
    }
    heap_sort(borders);
    std::cout << calc_painted_length(borders);
    return 0;
}
