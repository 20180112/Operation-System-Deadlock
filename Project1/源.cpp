#include "stdlib.h"
#include "stdio.h"
#include "time.h"


#define NumofProc 5//�������
#define NumofRres 3//������Դ



int main() {
    //���м��㷨��ʼ�������������ݳ�ʼ��ȫΪ0
    static int Available[NumofRres];
    static int Max[NumofProc][NumofRres];
    static int Allocation[NumofProc][NumofRres];
    static int Need[NumofProc][NumofRres];
    static int Finish[NumofProc];
    static int Work[NumofRres];
    //��Ž�����������
    char proc[NumofProc][10] = { "p0","p1","p2","p3","p4" };
    //���м��㷨�е���������������ֵ
    srand((unsigned)time(NULL));
    for (int i = 0; i < NumofRres; i++)
    {//ÿ�ֿ�����Դ��������ΧΪ[1,15]
        Available[i] = rand() % 9 + 1;
    }
    printf("Available:\n");
    for (int i = 0; i < NumofRres; i++)
    {//��ӡ�����ֵ��Available����
        printf("%d ", Available[i]);
    }
    for (int i = 0; i < NumofProc; i++)
    {//����ÿ�����̵�ÿ����Դ��ʹ�����ֵ
        for (int j = 0; j < NumofRres; j++)
        {//��j����Դʹ�õ����ֵ��ΧΪ[0,Available[j]]
            if (Available[j] == 0)
            {//��������rand���
             //��Ϊrand()%0�ᵼ�³�����������������ֱ��ʹ��if����ж�0ʱ�����
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
    {//��ӡ��ֵ���Max����
        printf("%s: ", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Max[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NumofProc; i++)
    {   //������ĿҪ��Ҫ��50%�ĸ��ʵ�i�������Allocation[j]=0��50%�ĸ���Allocation[j]�ķ�ΧΪ[1,Max[i][j]]
        //��֪���������Allocation�����������Ե���������
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
                }//����ʵ�黹�������Ե���������������ÿ����Դ�ĳ�ʼ�����ܺ��ǲ��ܴ����ܵ���Դ����
                else {
                    if (Max[i][j] == 1)
                    {
                        int sum = 0;
                        for (int k = 0; k < i; k++)
                        {
                            sum = sum + Allocation[k][j];
                        }
                        if ((Available[j] - sum) == 0)
                        {//����Դ�Ŀ�����Դ��֮ǰ�Ѿ���ȫ���������ˣ���ô֮������н��̵õ���������Դ�����Ϊ0
                            Allocation[i][j] = 0;
                        }
                        else
                        {
                            Allocation[i][j] = rand() % 1;
                            //���������AllocationʱҪȥ�ж��Ƿ���ڳ�ʼ�����������Դ�������������������������Allocation
                            //���¼�Ϊ�жϵĹ���
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
                        {//����Դ�Ŀ�����Դ�Ѿ���ȫ����������
                            Allocation[i][j] = 0;
                        }
                        else
                        {
                            //else�е��߼���������ͬ
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
    {//��ӡ��ֵ���Allocation����
        printf("%s:", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Allocation[i][j]);
        }
        printf("\n");
    }
    //��ʼ������Դ���Available����ҲҪ��Ӧ�仯
    for (int i = 0; i < NumofProc; i++)
    {
        for (int j = 0; j < NumofRres; j++)
        {
            Available[j] = Available[j] - Allocation[i][j];
        }

    }
    printf("Need:\n");
    for (int i = 0; i < NumofProc; i++)
    {//����ÿ�����̻���Ҫÿ����Դ��������Need����
        for (int j = 0; j < NumofRres; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    for (int i = 0; i < NumofProc; i++)
    {//��ӡNeed����
        printf("%s: ", proc[i]);
        for (int j = 0; j < NumofRres; j++)
        {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
    //����ֵ�󣬽������м��㷨
    for (int i = 0; i < NumofRres; i++)
    {//�Ƚ�Work��������Availble������ͬ����
        Work[i] = Available[i];
    }
    //��ӡWork��Available����
    printf("Available:\n");
    printf("%d %d %d", Available[0], Available[1], Available[2]);
    printf("\n");
    printf("Work:\n");
    printf("%d %d %d", Work[0], Work[1], Work[2]);
    printf("\n");

    int static a[NumofProc];//��¼��ȫ����
    for (int i = 0; i < NumofProc; i++)
    {   //��ʾ�ӵ�i�����̿�ʼ������
        int count = i;
        int release = 0;//��ʾ�ͷŵ���������
        int complete = 1;
        //ÿ�δ�ͷ��ʼ���������³�ʼ��Work��Finish����
        for (int i = 0; i < NumofRres; i++)
        {
            Work[i] = Available[i];
        }
        for (int i = 0; i < NumofProc; i++)
        {
            Finish[i] = 0;//����finish��ֵ
            a[i] = 0;
        }
        //Ѱ�Ҵ�i���̿�ʼִ���Ƿ���ڰ�ȫ����
        while (Finish[count] == 0 || count < NumofProc)
        {
            int find = 1;//ÿ���ж��½��̶�Ҫ����findֵ
            if (Finish[count] == 0)
            {
                for (int j = 0; j < NumofRres; j++)
                {
                    if (Need[count][j] > Work[j])
                    {
                        //�˽����޷�˳��ִ�У���Ϊ�����������Դ����
                        find = 0;
                        break;
                    }
                }
                if (find == 1)
                {
                    a[release] = count;//��¼�³ɹ���ɵĽ���
                    release++;//�����ͷ���+1
                    Finish[count] = 1;//����Ӧ��Finish�����ֵ��Ϊ1����ʾ�˽����Ѿ����
                    for (int j = 0; j < NumofRres; j++)
                    {//��������ռ�õ���Դ�ͷ�
                        Work[j] = Work[j] + Allocation[count][j];
                    }
                    count = 0;//���н�����ɺ󣬾��ڴӵ�һ�������ٴο�ʼ�жϣ�����һ����Դ״̬��δ��ɵĽ������Ƿ��н��̿��Գɹ�ִ��
                    find = 1;
                }
                else
                {
                    if (Finish[i] == 0)
                    {//��ʾ�Ӵ˽���i��ʼû�а�ȫ����
                        complete = 0;
                        break;
                    }
                    count++;
                }
            }
            else
            {//�˽����Ѿ���ִ�й�
                count++;
            }
        }
        for (int i = 0; i < NumofProc; i++)
        {
            if (Finish[i] == 0)
            {
                complete = 0;//���н���δ����ɣ���û�й��ɰ�ȫ����
                break;
            }
        }
        if (complete == 0)
        {//��i��ͷ�����в����ڰ�ȫ����ʱ��ѭ��i+1��ͷ�Ƿ���ڰ�ȫ����
            continue;
        }
        else
        {
            printf("line:");
            for (int i = 0; i < NumofProc; i++)
            {//�������������Ӧ�Ľ��̰�ȫ����
                printf("%s ", proc[a[i]]);
            }
            printf("\nproc   work\n");
            //������Ӧ�Ľ��̰�ȫ���У�����ԭ����������Դ�ͷŷ������
            for (int i = 0; i < NumofRres; i++)
            {//Work��ֵ��Ϊ�����Available�����е�ֵ
                Work[i] = Available[i];
            }
            int count = 0;
            while (count < NumofProc)
            {//���ÿ��״̬��work��ִ�еĽ���
                printf("%s    %d %d %d\n", proc[a[count]], Work[0], Work[1], Work[2]);
                for (int j = 0; j < NumofRres; j++)
                {//���ݰ�ȫ�������ͷ���Դ
                    Work[j] = Work[j] + Allocation[a[count]][j];
                }
                count++;
            }
            return 1;
        }
    }
    //�����ն�û���ҵ���ȫ�������ж�Ϊ����
    printf("Dead lock!");
    return 1;
}
