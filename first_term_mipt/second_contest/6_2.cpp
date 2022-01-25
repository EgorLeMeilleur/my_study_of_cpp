//Решите задачу 6 за минимальное время. Разрешается использовать любую сортировку, написанную самостоятельно.
//Сортировка обязательно должна сортировать все элементы массива.
//lsd-sort
#include "sort.h"
#include <vector>
unsigned int get_digit(unsigned int number, unsigned int rank, const unsigned int rank_size)
{
    return number >> (rank * rank_size) & ((1 << rank_size) - 1);
}
unsigned int get_ranks_count(unsigned int number, unsigned int rank_size)
{
    unsigned int ranks_count = 0;
    while (number > 0)
    {
        number >>= rank_size;
        ranks_count++;
    }
    return ranks_count;
}
unsigned int max_number(unsigned int* arr, const unsigned int size)
{
    unsigned int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}
void counting_sort(unsigned int* arr, const unsigned int size, unsigned int rank, const unsigned int rank_size)
{
    std::vector<unsigned int> buckets(1 << rank_size);
    for (unsigned int i = 0; i < size; i++)
    {
        buckets[get_digit(arr[i], rank, rank_size)]++;
    }
    std::vector<unsigned int> borders(1 << rank_size);
    for (unsigned int i = 1; i < buckets.size(); i++)
    {
        borders[i] = borders[i - 1] + buckets[i - 1];
    }
    std::vector<unsigned int> sorted(size);
    for (unsigned int i = 0; i < size; i++)
    {
        sorted[borders[get_digit(arr[i], rank, rank_size)]++] = arr[i];
    }
    for (unsigned int i = 0; i < size; i++)
    {
        arr[i] = sorted[i];
    }
}
void Sort(unsigned int* arr, const unsigned int n)
{
    const unsigned int rank_size = 4;
    const unsigned int max_element = max_number(arr, n);
    const unsigned int ranks_count = get_ranks_count(max_element, rank_size);
    for (int rank = 0; rank < ranks_count; rank++)
    {
        counting_sort(arr, n, rank, rank_size);
    }
}
