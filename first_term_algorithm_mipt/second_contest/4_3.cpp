//Дана последовательность целых чисел из диапазона(-1000000000 .. 1000000000).Длина последовательности не больше 1000000. Числа записаны по одному в строке.
//Количество чисел не указано.Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из[0..n - 1].
//Требуется напечатать количество таких пар индексов(i, j) из[0..n - 1], что(i < j и a[i] > a[j]).
//Указание : количество инверсий может быть больше 4 * 1000000000 - используйте int64_t.

#include <iostream>
#include <stdint.h>
#include <vector>
int64_t merge_sort_private(std::vector<int>& array, int left, int right)
{
    if (right - left <= 1)
    {
        return 0;
    }
    const int mid = (left + right) / 2;
    int64_t inversions_count = merge_sort_private(array, left, mid);
    inversions_count += merge_sort_private(array, mid, right);
    int merge_left = left;
    int merge_right = mid;
    std::vector<int> buffer(right - left);
    int merge_index = 0;
    while (merge_left < mid || merge_right < right)
    {
        if (merge_left < mid && merge_right < right)
        {
            if (array[merge_left] <= array[merge_right])
            {
                inversions_count += merge_right - mid;
                buffer[merge_index++] = array[merge_left++];
            }
            else
            {
                buffer[merge_index++] = array[merge_right++];
            }
        }
        else if (merge_left < mid)
        {
            inversions_count += right - mid;
            buffer[merge_index++] = array[merge_left++];
        }
        else
        {
            buffer[merge_index++] = array[merge_right++];
        }
    }
    for (int i = 0; i < buffer.size(); i++) 
    {
        array[left + i] = buffer[i];
    }
    return inversions_count;
}
int main()
{
    std::vector<int> array;
    int number;
    for (int i = 0; std::cin >> number; i++)
    {
        array.push_back(number);
    }
    int64_t inversions_count = merge_sort_private(array, 0, array.size());
    printf("%ld", inversions_count);
    return 0;
}

 
