//Задано N точек на плоскости.Указать N − 1 - звенную несамопересекающуюся незамкнутую ломаную, проходящую через все эти точки.
//Указание: стройте ломаную в порядке возрастания x - координаты.Если имеются две точки с одинаковой x - координатой, то расположите раньше ту точку, у которой y - координата меньше.

#include <iostream>
#include <vector>
struct Point
{
    int x;
    int y;
};
std::ostream& operator<<(std::ostream& out, const std::vector<Point>& points)
{
    for (int i = 0; i < points.size(); i++)
    {
        out << points[i].x << " " << points[i].y << "\n";
    }
    return out;
}
std::istream& operator>>(std::istream& in, std::vector<Point>& points)
{
    for (int i = 0; i < points.size(); i++)
    {
        in >> points[i].x;
        in >> points[i].y;
    }
    return in;
}
bool operator<(const Point& first, const Point& second) 
{
    return first.x < second.x || first.x == second.x && first.y < second.y; //соритурем по возрастающему x, если иксы равны, то по возрастающему y
}
void insertion_sort(std::vector<Point>& points)
{
    for (int i = 1; i < points.size(); i++) 
    {
        Point temporary = points[i];
        int j = i - 1;
        while (j >= 0 && temporary < points[j]) 
        {
            points[j + 1] = points[j];
            j--;
        }
        points[j + 1] = temporary;
    }
}
int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point> points(n);
    std::cin >> points;
    insertion_sort(points);
    std::cout << points;
    return 0;
}