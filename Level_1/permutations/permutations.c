#include <stdio.h>

int get_next_permutation(char *perm, int n)
{
    int i = n - 1;
    while (i > 0 && perm[i - 1] >= perm[i]) {
        i--;
    }

    if (i <= 0) {
        return (0);
    }

    int j = n;
    while (j > i && perm[j - 1] <= perm[i - 1]) {
        j--;
    }

    char tmp = perm[i - 1];
    perm[i - 1] = perm[j - 1];
    perm[j - 1] = tmp;

    i++;
    j = n;
    while (i < j) {
        tmp = perm[i - 1];
        perm[i - 1] = perm[j - 1];
        perm[j - 1] = tmp;
        i++;
        j--;
    }

    return (1);
}

void sort_char_arr(char *arr, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                char tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(int ac, char *av[])
{
    if (ac == 1)
        return (0);

    char *perm = av[1];
    int n = 0;
    while (perm[n]) {
        n++;
    }

    sort_char_arr(perm, n);

    do {
        printf("%s\n", perm);
    } while (get_next_permutation(perm, n));
}