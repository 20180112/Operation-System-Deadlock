#include "stdlib.h"
#include "stdio.h"
#include "time.h"


#define NumofProc 5//五个进程
#define NumofRres 3//三种资源



int main() {
    //银行家算法初始化，数组中数据初始化全为0
    static int Available[NumofRres];
    static int Max[NumofProc][NumofRres];
    static int Allocation[NumofProc][NumofRres];
    static int Need[NumofProc][NumofRres];
    static int Finish[NumofProc];
    static int Work[NumofRres];
    //存放进程名称数组
    char proc[NumofProc][10] = { "p0","p1","p2","p3","p4" };
    //银行家算法中的数组和向量赋随机值
    srand((unsigned)time(NULL));
    for (int i = 0; i < NumofRres; i++)
    {//每种可用资源的数量范围为[1,15]
        Available[i] = rand() % 9 + 1;
    }
    printf("Available:\n");
    for (int i = 0; i < NumofRres; i++)
    {//打印赋完初值的Available数组
        printf("%d ", Available[i]);
    }
    for (int i = 0; i < NumofProc; i++)
    {//生成每个进程的每种资源的使用最大值
        for (int j = 0; j < NumofRres; j++)
        {//第j种资源使用的最大值范围为[0,Available[j]]
            if (Available[j] == 0)
            {//避免错误的rand结果
             //因为rand()%0会导致程序出不来结果，所以直接使用if语句判断0时的情况
                Max[i][j] = 0;
            }
            else {
                if (Available[j] == 1)
                {
                    Max[i][j] = rand() % 1;
                }
                else {
                    Max[i][j] = rand() % (Available[j] - 1) + 1;
                }
            }
        }
    }
    printf("\n");
    printf("Max:\n");
    for (int i = 0; i < NumofProc; i++)
    {//打印赋值完的Max数组
        printf("%s: ", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Max[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NumofProc; i++)
    {   //根据题目要求要有50%的概率第i个数组的Allocation[j]=0，50%的概率Allocation[j]的范围为[1,Max[i][j]]
        //可知这里的生成Allocation的数组有显性的限制条件
        for (int j = 0; j < NumofRres; j++)
        {
            int p = rand() % 9 + 1;
            if (p <= 5)
            {
                Allocation[i][j] = 0;
            }
            else {
                if (Max[i][j] == 0)
                {
                    Allocation[i][j] = 0;
                }//但是实验还存在隐性的限制条件，就是每种资源的初始分配总和是不能大于总的资源数的
                else {
                    if (Max[i][j] == 1)
                    {
                        int sum = 0;
                        for (int k = 0; k < i; k++)
                        {
                            sum = sum + Allocation[k][j];
                        }
                        if ((Available[j] - sum) == 0)
                        {//此资源的可用资源在之前已经被全部分配完了，那么之后的所有进程得到的这种资源分配均为0
                            Allocation[i][j] = 0;
                        }
                        else
                        {
                            Allocation[i][j] = rand() % 1;
                            //因此在生成Allocation时要去判断是否存在初始分配大于总资源数的情况，若存在则重新生成Allocation
                            //以下即为判断的过程
                            int sum = 0;
                            for (int k = 0; k <= i; k++)
                            {
                                sum = sum + Allocation[k][j];
                            }
                            if (sum > Available[j])
                            {
                                Allocation[i][j] = 0;
                            }
                        }

                    }
                    else
                    {
                        int sum = 0;
                        for (int k = 0; k < i; k++)
                        {
                            sum = sum + Allocation[k][j];
                        }
                        if ((Available[j] - sum) == 0)
                        {//此资源的可用资源已经被全部分配完了
                            Allocation[i][j] = 0;
                        }
                        else
                        {
                            //else中的逻辑与上面相同
                            Allocation[i][j] = rand() % (Max[i][j] - 1) + 1;
                            int sum = 0;
                            for (int k = 0; k <= i; k++)
                            {
                                sum = sum + Allocation[k][j];
                            }
                            while (sum > Available[j])
                            {
                                Allocation[i][j] = rand() % (Max[i][j] - 1) + 1;
                                sum = 0;
                                for (int k = 0; k <= i; k++)
                                {
                                    sum = sum + Allocation[k][j];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("Allocation:\n");
    for (int i = 0; i < NumofProc; i++)
    {//打印赋值后的Allocation数组
        printf("%s:", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Allocation[i][j]);
        }
        printf("\n");
    }
    //初始分配资源完后Available数组也要相应变化
    for (int i = 0; i < NumofProc; i++)
    {
        for (int j = 0; j < NumofRres; j++)
        {
            Available[j] = Available[j] - Allocation[i][j];
        }

    }
    printf("Need:\n");
    for (int i = 0; i < NumofProc; i++)
    {//生成每个进程还需要每种资源的数量的Need数组
        for (int j = 0; j < NumofRres; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    for (int i = 0; i < NumofProc; i++)
    {//打印Need数组
        printf("%s: ", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
    //赋初值后，进行银行家算法
    for (int i = 0; i < NumofRres; i++)
    {//先将Work数组置与Availble数组相同的数
        Work[i] = Available[i];
    }
    //打印Work和Available数组
    printf("Available:\n");
    printf("%d %d %d", Available[0], Available[1], Available[2]);
    printf("\n");
    printf("Work:\n");
    printf("%d %d %d", Work[0], Work[1], Work[2]);
    printf("\n");

    int static a[NumofProc];//记录安全序列
    for (int i = 0; i < NumofProc; i++)
    {   //表示从第i个进程开始的序列
        int count = i;
        int release = 0;//表示释放的序列数量
        int complete = 1;
        //每次从头开始遍历都重新初始化Work和Finish函数
        for (int i = 0; i < NumofRres; i++)
        {
            Work[i] = Available[i];
        }
        for (int i = 0; i < NumofProc; i++)
        {
            Finish[i] = 0;//重置finish的值
            a[i] = 0;
        }
        //寻找从i进程开始执行是否存在安全序列
        while (Finish[count] == 0 || count < NumofProc)
        {
            int find = 1;//每次判断新进程都要重置find值
            if (Finish[count] == 0)
            {
                for (int j = 0; j < NumofRres; j++)
                {
                    if (Need[count][j] > Work[j])
                    {
                        //此进程无法顺利执行，因为分配给它的资源不够
                        find = 0;
                        break;
                    }
                }
                if (find == 1)
                {
                    a[release] = count;//记录下成功完成的进程
                    release++;//进程释放数+1
                    Finish[count] = 1;//将相应的Finish数组的值变为1，表示此进程已经完成
                    for (int j = 0; j < NumofRres; j++)
                    {//将进程所占用的资源释放
                        Work[j] = Work[j] + Allocation[count][j];
                    }
                    count = 0;//当有进程完成后，就在从第一个进程再次开始判断，看新一个资源状态下未完成的进程中是否有进程可以成功执行
                    find = 1;
                }
                else
                {
                    if (Finish[i] == 0)
                    {//表示从此进程i开始没有安全序列
                        complete = 0;
                        break;
                    }
                    count++;
                }
            }
            else
            {//此进程已经被执行过
                count++;
            }
        }
        for (int i = 0; i < NumofProc; i++)
        {
            if (Finish[i] == 0)
            {
                complete = 0;//若有进程未被完成，则没有构成安全序列
                break;
            }
        }
        if (complete == 0)
        {//当i开头的序列不存在安全序列时，循环i+1开头是否存在安全序列
            continue;
        }
        else
        {
            printf("line:");
            for (int i = 0; i < NumofProc; i++)
            {//若存在则输出相应的进程安全序列
                printf("%s ", proc[a[i]]);
            }
            printf("\nproc   work\n");
            //根据相应的进程安全序列，来还原整个进程资源释放分配过程
            for (int i = 0; i < NumofRres; i++)
            {//Work的值变为最初的Available数组中的值
                Work[i] = Available[i];
            }
            int count = 0;
            while (count < NumofProc)
            {//输出每个状态的work和执行的进程
                printf("%s    %d %d %d\n", proc[a[count]], Work[0], Work[1], Work[2]);
                for (int j = 0; j < NumofRres; j++)
                {//根据安全序列来释放资源
                    Work[j] = Work[j] + Allocation[a[count]][j];
                }
                count++;
            }
            return 1;
        }
    }
    //若最终都没有找到安全序列则判断为死锁
    printf("Dead lock!");
    return 1;
}
