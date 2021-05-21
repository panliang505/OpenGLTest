/**********************************
*  @description :
*  @author ��divels@qq.com
*  @date : 2021.05.20
***********************************/

#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

class Algorithms
{
public:

    // ��ӡ����
    static void printArray(int num[], int size);

    // ð������
    static void bubbleSort(int num[], int size);
    // ��������
    static void insertSort(int num[], int size);
    // ѡ������
    static void selectSort(int num[], int size);
    // ��������
    static void quickSort(int num[], int start, int end);
    // ϣ������
    static void shellSort(int num[], int size);

    /*
    * ����һ��ֻ������дӢ����ĸ���ַ���S,Ҫ���������S�������е����в���ͬ����������
    * ��: SΪABA,��ͬ��������ABA��AAB�� BAA ���֡�
    * ���룺����һ�����Ȳ�����10���ַ���S������ȷ�����Ǵ�д�ġ�
    * ��������S�������е����в���ͬ���������������Լ�����
    * ����
    * ����1��ABA
    * ���1��3 
    * ����2��ABCDEFGHHA
    * ���2��907200
    */
    static int getMaxArray();

    /*
    * ��ȡ�����е������ֵ�Ԫ�أ��������ǳɶԳ��֣�ֻ��һ��Ԫ���Ƕ������ֵģ�
    */
    static int getAlone(int num[], int size);

};

#endif // !_ALGORITHMS_H_
