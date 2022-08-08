//Дано N кубиков.Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
//Каждый вышележащий слой пирамиды должен быть не больше нижележащего.

// Ответ на задачу:
// P(n, m) = кол-во способов разложить число n в сумму, где каждое слагаемое не превышает k.

#include <iostream>
#include <vector>

long long find_quantity_of_pyramids(int n) //P(n, m) = P(n – m, m) + P(n, m – 1) n - раскладываемое число, m - ограничение на величину слагаемого
{                                          //используем long long, так как способов разложения числа намного больше чем само число => можем выйти за пределы инта
    std::vector<std::vector<long long>> array_of_summands(n + 1, std::vector<long long>(n + 1, 0)); 
    for (int i = 0; i <= n; i++)
    {
        array_of_summands[0][i] = 1;
    }
    for (int i = 1; i <= n; i++) // i - раскладываемое число
    {
        for (int j = 1; j <= n; j++) // j - ограничение на величину слагаемого
        {
            if (j <= i)
            {
                array_of_summands[i][j] = array_of_summands[i][j - 1] + array_of_summands[i - j][j];
            }
            else
            {
                array_of_summands[i][j] = array_of_summands[i][j - 1];
            }
        }
    }
    return array_of_summands[n][n];
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::cout << find_quantity_of_pyramids(n);
    return 0;
}