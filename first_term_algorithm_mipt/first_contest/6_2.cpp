/* Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11 
Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел. 
Требуемое время работы O(n*log(n)). */
#include <iostream>
#include <queue>
#include <vector>
int sum_of_computer(std::priority_queue<int, std::vector<int>, std::greater<int>> heap, int &heap_size)
{
    int sum = 0;
    for (int i = 0; i < heap_size - 1; i++)
    {
        int temporary1, temporary2, temporary_sum;
        temporary1 = heap.top(); //запоминаем первое минимальное значение
        heap.pop();
        temporary2 = heap.top(); // //запоминаем второе минимальное значение
        heap.pop();
        temporary_sum = temporary1 + temporary2; //запоминаем сумму двух минимальных элементов
        sum += temporary_sum; //добавляем ее к общей сумме
        heap.push(temporary_sum);
    }
    return sum;
}
int main()
{
    int heap_size;
    std::cin >> heap_size;
    std::vector<int> array_of_numbers(heap_size, 0);
    for (int i = 0; i < heap_size; i++)
    {
        std::cin >> array_of_numbers[i];
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap; //создаем кучу, в корне которой лежит минимальное число
    for (int i = 0; i < heap_size; i++)
    {
        heap.push(array_of_numbers[i]);
    }
    std::cout << sum_of_computer(heap, heap_size);
}
