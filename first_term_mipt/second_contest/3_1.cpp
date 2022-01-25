//���� ��������������� ����� ����� n, k � ������ ����� ����� ��[0..10 ^ 9] ������� n.
//��������� ����� k - � ���������� ����������.�.�.���������� �����, ������� �� ������ �� ������� � �������� k(0..n - 1) � ��������������� �������.
//�������� ������������� ��������.
//���������� � �������������� ������ : O(n).��������� ������� ����� ������ : O(n).
//���������� ��������� ������ �������� �������� �������� ����.������� Partition ���������� ������� ������� ����� ����������� �� ������ ������� � �����.

#include <iostream> 
#include <vector>
int find_pivot_index(const std::vector<int>& array, int left, int right, int middle)
{
    if (array[left] <= array[right] && array[middle] <= array[left] ||
        array[left] <= array[middle] && array[right] <= array[left]) return left;
    if (array[middle] <= array[left] && array[right] <= array[middle] ||
        array[middle] <= array[right] && array[left] <= array[middle]) return middle;
    if (array[right] <= array[middle] && array[left] <= array[right] ||
        array[right] <= array[left] && array[middle] <= array[right]) return right - 1;
}
int partition(std::vector<int>& array, int left, int right)
{
    if (right - left <= 1)
    {
        return left;
    }
    int middle = (right + left) / 2;
    int pivot_index = find_pivot_index(array, left, right - 1, middle);
    const int pivot = array[pivot_index];
    std::swap(array[pivot_index], array[right - 1]);
    int i = 0, j = 0;
    while (j < right - 1)
    {
        if (array[j] <= array[right - 1])
        {
            std::swap(array[i], array[j]);
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }
    std::swap(array[i], array[right - 1]);
    return i;
}
int find_k_order_statistics(std::vector<int>& array, int k)
{
    int left = 0;
    int right = array.size();
    while (true) 
    {
        int partition_index = partition(array, left, right);
        if (partition_index == k) 
        {
            return array[partition_index];
        }
        else if (partition_index > k)
        {
            right = partition_index;
        }
        else 
        {
            left = partition_index + 1;
        }
    }
}
int main()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> array(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> array[i];
    }
    std::cout << find_k_order_statistics(array, k);
    return 0;
}
