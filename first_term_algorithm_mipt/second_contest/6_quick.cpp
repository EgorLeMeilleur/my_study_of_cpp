//Дан массив целых чисел в диапазоне[0..10 ^ 9].Размер массива кратен 10 и ограничен сверху значением 2.5 * 107 элементов.
//Все значения массива являются элементами псевдо - рандомной последовательности.Необходимо написать оптимизированную функцию быстрой сортировки массива.
//Для этого нужно прислать.cpp файл, в котором описать функцию Sort
//void Sort(unsigned int* arr, unsigned int size);
//Необходимо включить в файл header #include "sort.h"
//Минимальный набор оптимизаций, который необходимо реализовать :
//1. Оптимизация выбора опорного элемента
//2. Оптимизация Partition
//3. Написать без рекурсии.
//4. Оптимизация концевой рекурсии.Небольшие массивы на глубине рекурсии сортировать другим способом.Например, вставками.

#include "sort.h"
#include <stack>
int find_pivot_index(unsigned int* array, unsigned int left, unsigned int middle, unsigned int right)
{
    if (array[left] <= array[middle] && array[middle] <= array[right])
    {
        return middle;
    }
    else if (array[left] <= array[right] && array[right] <= array[middle])
    {
        return right;
    }
    else if (array[middle] <= array[left] && array[left] <= array[right])
    {
        return left;
    }
    else if (array[middle] <= array[right] && array[right] <= array[left])
    {
        return right;
    }
    else if (array[right] <= array[left] && array[left] <= array[middle])
    {
        return left;
    }
    else if (array[right] <= array[middle] && array[middle] <= array[left])
    {
        return middle;
    }
}
int partition(unsigned int* array, unsigned int left, unsigned int right)
{
    int middle = (left + right) / 2;
    int pivot = find_pivot_index(array, left, middle, right);
    std::swap(array[pivot], array[left]);
    int i = right, j = right;
    while (left < i)
    {
        if (array[i] < array[left] && left < i || left < i && j <= i)
        {
            i--;
        }
        if (array[j] >= array[left] && left < j)
        {
            j--;
        }
        if (i < j)
        {
            std::swap(array[i], array[j]);
        }
    }
    return j;
}
void insertion_sort(unsigned int* arr, unsigned int size)
{
    for (int i = 1; i < size; i++)
    {
        int temporary = arr[i];
        int j = i - 1;
        while (j >= 0 && temporary < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temporary;
    }
}
void Sort(unsigned int* arr, unsigned int size)
{
    int i = 0, j = 0;
    std::stack<int> stack;
    stack.push(size - 1);
    stack.push(0);
    int left = 0, right = 0;
    do {
        left = stack.top();
        stack.pop();
        right = stack.top();
        stack.pop();
        int index_pivot = 0;
        if ((right - left == 1) && arr[left] > arr[right])
        {
            std::swap(arr[left], arr[right]);
        }
        else
        {
            index_pivot = partition(arr, left, right);
        }
        if (left < index_pivot - 1)
        {
            if (index_pivot - left < 43)
            {
                insertion_sort(arr + left, index_pivot - left);
            }
            else
            {
                stack.push(index_pivot - 1);
                stack.push(left);
            }
        }
        if (index_pivot + 1 < right)
        {
            if (right - index_pivot < 43)
            {
                insertion_sort(arr + index_pivot + 1, right - index_pivot);
            }
            else
            {
                stack.push(right);
                stack.push(index_pivot + 1);
            }
        }
    } while (!stack.empty());
}
