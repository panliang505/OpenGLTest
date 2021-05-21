/**********************************
*  @description :
*  @author ：divels@qq.com
*  @date : 2021.05.20
***********************************/

#include "algorithms.h"
#include <iostream>

void Algorithms::printArray(int num[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << num[i] << ",";
    }
    std::cout << std::endl;
}

// 比较相邻的两个数据，如果第二个数小，就交换位置。
// 从后向前两两比较，一直到比较最前两个数据。
void Algorithms::bubbleSort(int num[], int size)
{
    int i, j;
    bool isChange = false;
    for (i = 0; i < size; ++i)
    {
        isChange = false;
        for (j = size - 1; j > 0; --j)
        {
            if (num[j] < num[j - 1])
            {
                num[j] = num[j] + num[j - 1];
                num[j - 1] = num[j] - num[j - 1];
                num[j] = num[j] - num[j - 1];
                isChange = true;
            }
        }
        if (!isChange)
            break;
    }

}

void Algorithms::insertSort(int num[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        int key = num[i];
        int j = i - 1;
        for (; j >= 0; --j)
        {
            if (key < num[j])
                num[j + 1] = num[j];
            else
                break;
        }
        num[j + 1] = key;
    }
}

// 第一次遍历n-1个数，找到最小的数值与第一个元素交换
// 第二次遍历n-2个数，找到最小的数值与第二个元素交换
// 以此类推
// 第n-1次遍历，找到最小的数值与第n-1个元素交换，排序完成。
void Algorithms::selectSort(int num[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int temp = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (num[temp] > num[j])
                temp = j;
        }
        if (temp != i)
        {
            num[i] = num[i] + num[temp];
            num[temp] = num[i] - num[temp];
            num[i] = num[i] - num[temp];
        }
    }
}

// 1、从起始中找到中间数，然后将小于它的放左边，大于它的放右边；
// 2、递归重复1
void Algorithms::quickSort(int num[], int start, int end)
{
    int ref, low, high;
    if (start < end)
    {
        low = start;
        high = end;
        ref = num[(low + high) / 2];
        do
        {
            while (num[low] < ref) ++low;
            while (num[high] > ref) --high;
            if (low <= high)
            {
                num[low] = num[low] + num[high];
                num[high] = num[low] - num[high];
                num[low] = num[low] - num[high];
                ++low;
                --high;
            }
        } while (low < high);
        if (low < end) quickSort(num, low, end);
        if (high > start) quickSort(num, start, high);
    }
}

void Algorithms::shellSort(int num[], int size)
{
    int h = 1;
    while (h < size)
        h = 3 * h + 1;

    while (h > 0)
    {
        for (int i = h; i < size; ++i)
        {
            int key = num[i];
            int j = i - h;
            while (j >= 0 && num[j] > key)
            {
                num[j + h] = num[j];
                j = j - h;
            }
            num[j + h] = key;
        }
        h = h / 3;
    }
}

#include <ctype.h>
#include <map>
#include <functional>
int Algorithms::getMaxArray()
{
    // 控制输入
    char data[10] = { 0 };
    int length = 10;
    bool isReinput = false;
    do
    {
        isReinput = false;
        memset(data, 0, 10);
        std::cin >> data;
        for (int i = 0; i < 10; ++i)
        {
            if ((data[i] <= 90 && data[i] >= 63) ||
                (data[i] <= 122 && data[i] >= 97))
            {
                data[i] = toupper(data[i]);
            }
            else if (0 == data[i])
            {
                length = i;
                break;
            }
            else
            {
                isReinput = true;
                break;
            }
        }
    } while (isReinput);
    // 统计有多少不同的字母
    std::map<char, int> dataMap;
    for (int i = 0; i < length; ++i)
    {
        auto iter = dataMap.find(data[i]);
        if (iter == dataMap.end())
        {
            dataMap.insert(std::make_pair(data[i], 1));
        }
        else
        {
            ++dataMap[data[i]];
        }
    }

    std::function<long(int)> getJieChen = [&](int _num) -> long
    {
        long result = 1;
        for (int i = 0; i < _num; ++i)
        {
            result = result * (_num - i);
        }
        return result;
    };
    
    long max = getJieChen(length);
    for (auto i : dataMap)
    {
        max = max / getJieChen(i.second);
    }

    std::cout << max << std::endl;
    return max;
}

#include <vector>
#include <algorithm>
int Algorithms::getAlone(int num[], int size)
{
    if (size <= 0) return 0;
    if (1 == size) return num[0];
    int result;
    std::map<int, int> datas;
    for (int i = 0; i < size; ++i)
    {
        if (datas.find(num[i]) == datas.end())
        {
            datas.insert(std::make_pair(num[i], 1));
        }
        else
        {
            ++datas[num[i]];
        }
    }
    for (auto iter : datas)
    {
        if (1 == iter.second)
        {
            result = iter.first;
            break;
        }
    }
    std::cout << result << std::endl;
    return result;
}
