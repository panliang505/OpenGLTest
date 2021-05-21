/**********************************
*  @description :
*  @author ：divels@qq.com
*  @date : 2021.05.20
***********************************/

#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

class Algorithms
{
public:

    // 打印数组
    static void printArray(int num[], int size);

    // 冒泡排序
    static void bubbleSort(int num[], int size);
    // 插入排序
    static void insertSort(int num[], int size);
    // 选择排序
    static void selectSort(int num[], int size);
    // 快速排序
    static void quickSort(int num[], int start, int end);
    // 希尔排序
    static void shellSort(int num[], int size);

    /*
    * 给定一个只包含大写英文字母的字符串S,要求你给出对S重新排列的所有不相同的排列数。
    * 如: S为ABA,则不同的排列有ABA、AAB、 BAA 三种。
    * 输入：输入一个长度不超过10的字符串S，我们确保都是大写的。
    * 输出：输出S重新排列的所有不相同的排列数（包含自己本身）
    * 例：
    * 输入1：ABA
    * 输出1：3 
    * 输入2：ABCDEFGHHA
    * 输出2：907200
    */
    static int getMaxArray();

    /*
    * 获取数组中单独出现的元素（其他都是成对出现，只有一个元素是独立出现的）
    */
    static int getAlone(int num[], int size);

};

#endif // !_ALGORITHMS_H_
