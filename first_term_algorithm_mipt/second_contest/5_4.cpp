//Дан массив неотрицательных целых 64 - разрядных чисел.Количество чисел не больше 1000000. Отсортировать массив методом MSD по битам(бинарный QuickSort).

#include <iostream>
#include <vector>
#include <algorithm>

static const int rank_size = 1;
int get_digit(long long n, int rank)
{
    return (n >> (rank * rank_size)) & ((1 << rank_size) - 1);
}
int get_ranks_count(long long number)
{
    int ranks_count = 0;
    while (number > 0)
    {
        number >>= rank_size;
        ranks_count++;
    }
    return ranks_count;
}
void counting_sort(std::vector<long long>& array, int left, int right, int rank)
{
    if (right - left < 1)
    {
        return;
    }
    if (rank < 0)
    {
        return;
    }
    std::vector<int> buckets(2, 0);
    for (int j = left; j <= right; j++)
    {
        buckets[get_digit(array[j], rank)]++;
    }
    std::vector<int> borders(2, 0);
    for (int k = 1; k < 2; k++)
    {
        borders[k] = borders[k - 1] + buckets[k - 1];
    }
    int middle = borders[1] - 1;
    std::vector<long long> sorted(right - left + 1);
    for (int j = left; j <= right; j++)
    {
        sorted[borders[get_digit(array[j], rank)]++] = array[j];
    }
    for (int k = 0, j = left; j <= right; j++, k++)
    {
        std::swap(array[j], sorted[k]);
    }
    rank--;
    counting_sort(array, left, left + middle, rank);
    counting_sort(array, left + middle + 1, right, rank);
}
void msd_sort(std::vector<long long>& array)
{
    const long long max_element = *std::max_element(array.begin(), array.end());
    int ranks_count = get_ranks_count(max_element);
    counting_sort(array, 0, array.size() - 1, ranks_count);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n = 0;
    std::cin >> n;
    std::vector<long long> array(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> array[i];
    }
    msd_sort(array);
    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
