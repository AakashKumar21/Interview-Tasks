/* strstr example */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum
{
    AB,
    BA,
    ABA_BAB,
    AAA_BBB
};

int max_index(int *arr, int size)
{
    int m = arr[0];
    int index = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > m)
        {
            index = i;
        }
    }
    return index;
}

int compare(const void *a, const void *b)
{
    int num1 = *((int *)a);
    int num2 = *((int *)b);
    if (num1 < num2)
        return -1;
    else if (num1 > num2)
        return 1;
    else
        return 0;
}

int sort(int *arr, int size)
{
    qsort(arr, size, sizeof(int), compare); // Sort the array
}

int get_priority(int *arr, int *weights, int size)
{
    char index = 0;
    for (int i = 0; i < size; i++)
    {
        index = max_index(arr, size);
        weights[i] = index;
        arr[index] = -1;
    }
}

void print_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int count_instance(char *str, char *substr)
{
    int counts = 0;
    int size = strlen(str);
    int size_sub = strlen(substr);
    char dummy[4] = "xxxx";
    char copy[size];
    strncpy(copy, str, size);

    char *pos = strstr(copy, substr);
    while (pos)
    {
        strncpy(pos, pos+size_sub, size_sub);
        pos[size_sub] = 0;
        counts++;
        pos = strstr(copy, "ab");
    }
    return counts;
}

void remove_instance(char *str, char *substr)
{
    int size_sub = strlen(substr);
    char dummy[4] = "xxxx";

    char *pos = strstr(str, substr);
    while (pos)
    {
        strncpy(pos, pos+size_sub, size_sub);
        pos[size_sub] = 0;
        // printf("%s\n", str);
        pos = strstr(str, "ab");
    }
}

int get_points(char *str, char *substr, int x){
    int points = 0;
    int count = count_instance(str, substr);
    points += count * x;
    remove_instance(str, substr);
    printf("Removed: %s: %d  ", substr, count);
    printf("Now: %s\n", substr);
    return points;
}

int main()
{
    char str[] = "baaababa";
    int x = 4, y = 2;
    int points[] = {x, y, x + y, x * y};
    int weights[4];
    int total_points = 0;
    get_priority(points, weights, 4);
    print_arr(weights, 4);
    int t;
    for (int i = 0; i < 4; i++)
    {
        // priority of AB and BA is same
        // AB
        if ((i < 2) && (weights[0] == weights[1]))
        {
            if (count_instance(str, "ab") > count_instance(str, "ba"))
            {
                total_points += get_points(str, "ab",x);
                total_points += get_points(str, "ba",y);
            }
            else
            {
                total_points += get_points(str, "ba",y);
                total_points += get_points(str, "ab",x);
            }
        }
        if (weights[i] == 0)
        {
            total_points += get_points(str, "ab",x);
        }
        // BA
        if (weights[i] == 1)
        {
            total_points += get_points(str, "ba",y);
        }
        // ABA or BAB
        if (weights[i] == 2)
        {
            if (count_instance(str, "aba") > count_instance(str, "bab"))
            {
                total_points += get_points(str, "aba",x+y);
                total_points += get_points(str, "bab",x+y);
            }
            else
            {
                total_points += get_points(str, "bab",x+y);
                total_points += get_points(str, "aba",x+y);
            }
            continue;
        }
        // AAA or BBB
        if (weights[i] == 3)
        {
            if (count_instance(str, "aaa") > count_instance(str, "bbb"))
            {
                total_points += get_points(str, "aaa",x*y);
                total_points += get_points(str, "bbb",x*y);
            }
            else
            {
                total_points += get_points(str, "bbb",x*y);
                total_points += get_points(str, "aaa",x*y);
            }
            continue;
        }
    }
    printf("Points: %d", total_points);
    return 0;
}