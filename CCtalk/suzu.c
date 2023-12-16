#include <stdio.h>

int main()
{
    int n = 0, num = 0, x = 0, y = 0;
    double price[10];
    scanf("%d", &num);
    double sum[10];
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d %d", &n, &x, &y);
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &price[j]);
        }
        double u;
        for (int m = 0; m < n - 1; m++)
        {
            for (int p = 0; p < n - m - 1; p++)
            {
                if (price[p] > price[p + 1])
                {
                    u = price[p];
                    price[p] = price[p + 1];
                    price[p + 1] = u;
                }
            }
        }
        int sign = 0;
        for (int b = n - 1; b >= 0; b--)
        {
            if (y < price[b])
            {
                sign++;
            }
        }
        if (sign == 0)
        {
            price[n - 1] = 0;
        }
        else
        {
            price[n - 1] = price[n - 1] - y;
        }
        price[n - 2] = price[n - 2] * (0.01 * x);
        for (int z = 0; z < n; z++)
        {
            sum[i] = sum[i] + price[z];
        }
        printf("%lf\n", sum[i]);
    }
}
