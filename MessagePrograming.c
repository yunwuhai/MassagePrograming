#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 60  // ��������

int Back[MAX_LEN];  // �洢����ֵ

typedef struct BACK_STR // ���Ʒ���ֵ
{
    bool isBackWrite[MAX_LEN];   // ��¼��δ洢��0��ʾ���洢��1��ʾ�洢
    unsigned int pBackWrite[MAX_LEN];     // ��¼����λ�ã�˳����룬ֻ����isBackWriteΪ1ʱ�ſ��Ե��ã����Դ���Back��ָ��λ��
}backStr;

typedef struct PARA_STR // ���Ʋ���ֵ
{
    bool isParaReadBack[MAX_LEN * 3];   // ��¼�ò����ӷ���ֵ����1��ȡ���ǴӲ�����ȡ��0��
    unsigned int Para[MAX_LEN * 3]; // ��¼�˲���λ�ã�����isParaReadBackΪ0ʱ�ſ��Ե��ã�˳�����
    unsigned int pBackRead[MAX_LEN * 3]; // ��¼ȡ��λ�ã�˳��ȡ����ֻ����isParaReadBackΪ1ʱ�ſ��Ե��ã�˳����ã�����ȡ��ָ��λ�õ�Backֵ
}paraStr;

/*
 * ȫ�ֱ�������
 */
int static flag = 0;

/*
 * ��̺���
 */
void SayHello() // ��ӡһ��Hello World!
{
    printf("Hello World!\n");
}

int NowFlag()   // ��flagֵ����һȻ���ӡ����������
{
    flag++;
    printf("flag = %d\n", flag);
    return flag;
}

void ShowSum(int a, int b)  // ��ӡ��������֮��
{
    printf("%d + %d = %d\n", a, b, a+b);
}

int GetSum(int a, int b, int c) // ��ӡ������������֮��
{
    int sum = a + b + c;
    printf("%d + %d + %d = %d\n",a, b, c, sum);
    return sum;
}

/*
** ��������
*/
// ���÷���ֵ����һ�������������������ڶ������������Ƿ������������У����������뵱ǰ�Ѿ�Ĭ�ϱ���ռ�õĿռ���ָ�룬���ĸ��������������Ϊ1������Ӧ�Ĵ洢�ռ�
void InitBack(backStr * B, int *p_isBackWrite, int *p_Back, int *p_pBackWrite)
{
    // ѡ���Ƿ���������ѡ������¼�ڷ���ֵ����������
    printf("�����Ƿ�������ֵ,1������0������:");
    int isTemp;
    scanf("%d", &isTemp);
    // ��¼�˴��Ƿ�����������޸��Ƿ������飬��������ָ������һ
    B->isBackWrite[*p_isBackWrite] = isTemp;
    (*p_isBackWrite)++;
    // ��������Ƿ�����Ϊ���������������ʱ���Բ������κβ�������Ϊ����ֵ����������û���κ�Ӱ��
    if(isTemp)   // ���Ҫ����
    {
        printf("�Ƿ���Ҫ�Զ�������1�ֶ���0�Զ�:");
        scanf("%d", &isTemp);
        // �����Ƿ��Զ��������Զ�������Ĭ���ڵ�ǰ˳���µ���һλ���б����������Ҫ����֮ǰ��ֵ����Ҫ�ֶ�ѡ�񱣴�λ�ã�����һ���ֲ��ܽ����ζ���ʹ�洢�ռ������ָ���¼�洢λ�ò�����һ
        if(isTemp)  // ָ��λ�ñ���,���������ֶ����뵱ǰָ��صĴ洢�ռ䣬�����޸�Ĭ�ϱ���ռ�õĿռ���ָ��
        {
            printf("������ָ��λ��,��0��ʼС��60,���ʹ���˳���%d��λ�ÿ����ں��淵��ֵ����:", *p_Back-1);
            int stateTemp;
            scanf("%d", &stateTemp);    // ѡ��λ�ã��������������ü�һ���ж�
            // ��Ϊ��Ҫ�������˴���¼������λ�ã��������ʼ�����Ƿ�����1������ͬ
            B->pBackWrite[*p_pBackWrite] = stateTemp;    // ��¼�洢��ַ
            printf("����%d��λ�ô洢�˵�ǰ�����ķ���ֵ", stateTemp);
            (*p_pBackWrite)++;
        }
        else    // �Զ�˳�򱣴棬�����˳����ռ�ÿռ����һλ�������ô洢ռ�ÿռ�ָ������һ
        {
            B->pBackWrite[*p_pBackWrite] = *p_Back; // �����Ѿ�ռ�õ���������ȷ��Ĭ�ϱ���ĵ�ַ
            printf("����%d��λ�ô洢�˵�ǰ�����ķ���ֵ", *p_Back);
            (*p_pBackWrite)++;
            (*p_Back)++;
        }
    }// ��������ִ���κβ���
}

void InitPara(int paraAll, paraStr * P, int *p_isParaReadBack, int *p_pBackRead, int *p_Para, int p_Back)
{
    int paraNum;    // ��¼��������
    for(paraNum = 0; paraNum < paraAll; paraNum++)
    {
        printf("���ʲ��������ڳ������Ƿ���ֵ��1���أ�0����");
        int isTemp;
        scanf("%d", &isTemp);
        P->isParaReadBack[*p_isParaReadBack] = isTemp;
        (*p_isParaReadBack)++;
        if(isTemp) // ���Է���ֵ
        {
            int stateTemp;
            printf("�����������Է���ֵ��ţ���ǰ����ʹ�ñ�����Ϊ%d:", p_Back-1);
            scanf("%d", &stateTemp);
            P->pBackRead[*p_pBackRead] = stateTemp;  // ָ����
            (*p_pBackRead)++;
        }
        else    // ���Գ���
        {
            printf("���������%d:", paraNum + 1);
            int stateTemp;
            scanf("%d", &stateTemp);
            P->Para[*p_Para] = stateTemp;
            (*p_Para)++;
        }
    }
}

void Coding(unsigned char codeStr[], backStr * B, paraStr * P)    // ��λ�����
{
    printf("�밴˳����������ţ�1|SayHello, 2|NowFlag, 3|ShowSum, 4|GetSum, 5|����\n");
    int line;  // ��¼ָ���
    int p_isBackWrite = 0;  // �Ƿ��з���ֵ����ָ��
    int p_pBackWrite = 0;  // ָ�򷵻�ֵ�洢��ַ��ָ�������ָ��
    int p_isParaReadBack = 0;  // �Ƿ��ȡ����ֵ��Ϊ��������ָ��
    int p_Back = 0; // ��¼����ֵָ��
    int p_Para = 0;  // ��¼����ָ��
    int p_pBackRead = 0;    // ָ�򷵻�ֵ��ȡ��ַ��ָ�������ָ��
    int inst;   // ������
    for(line = 0; line <= MAX_LEN; line++)   // �����ܳ�����󳤶�
    {
        printf("%d|  ", line + 1); // ��ʽռ��
        scanf("%d", &inst); // ��ȡָ��
        switch(inst)
        {
        case 1: // �޲����޷���ֵ
            {
                codeStr[line] = inst * 0x01;
                break;
            }
        case 2: // �޲����з���ֵ
            {
                codeStr[line] = inst * 0x01;
                InitBack(B, &p_isBackWrite, &p_Back, &p_pBackWrite);
                break;
            }
        case 3: // �в����޷���ֵ
            {
                codeStr[line] = inst * 0x01;
                InitPara(2, P, &p_isParaReadBack, &p_pBackRead, &p_Para, p_Back);
                break;
            }
        case 4: // �в����з���ֵ
            {
                codeStr[line] = inst * 0x01;
                InitPara(3, P, &p_isParaReadBack, &p_pBackRead, &p_Para, p_Back);
                InitBack(B, &p_isBackWrite, &p_Back, &p_pBackWrite);
                break;
            }
        case 5:
            {
                printf("����ɹ���\n");
                codeStr[line] = 0xff;	// ������Խ�����λ��switch������
                return;
            }
        default:
            {
                printf("�޵�ǰָ����������룡");
                line--;
                break;
            }
        }
        printf("\n");
    }
}

int main()
{
    unsigned char instruction[MAX_LEN];// ָ��洢��
    backStr B;
    paraStr P;
    Coding(instruction, &B, &P);    // ��ȡָ��
    int p_isParaReadBack = 0;   // ȷ�����������ڳ������Ƿ���ֵָ��
    int p_pBackRead = 0;   // ȷ������
    int p_pBackWrite = 0;
    int p_Para = 0;  // ȷ��ָ�򷵻�ֵ��ַ
    for(int i = 0; i < MAX_LEN; i++)
    {
        switch(instruction[i]) // �ж�ָ��
        {
        case 0x01:
            {
                SayHello();
                break;
            }
        case 0x02:
            {
                if(B.isBackWrite)   // ��������ֵ
                {
                    Back[B.pBackWrite[p_pBackWrite]] = NowFlag();
                    p_pBackWrite++;
                }
                else
                {
                    NowFlag();
                }
                break;
            }
        case 0x03:
            {
                int a, b;
                if(P.isParaReadBack[p_isParaReadBack])  // ���Է���ֵ
                {
                    a = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // ���Է���ֵ
                {
                    a = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // ���Է���ֵ
                {
                    b = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // ���Է���ֵ
                {
                    b = P.Para[p_Para];
                    p_Para++;
                }
                ShowSum(a, b);
                break;
            }
        case 0x04:
            {
                int a, b, c;
                if(P.isParaReadBack[p_isParaReadBack])  // ���Է���ֵ
                {
                    a = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // ���Է���ֵ
                {
                    a = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // ���Է���ֵ
                {
                    b = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // ���Է���ֵ
                {
                    b = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // ���Է���ֵ
                {
                    c = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // ���Է���ֵ
                {
                    c = P.Para[p_Para];
                    p_Para++;
                }
                if(B.isBackWrite)   // ��������ֵ
                {
                    Back[B.pBackWrite[p_pBackWrite]] = GetSum(a, b, c);
                    p_pBackWrite++;
                }
                else
                {
                    GetSum(a, b, c);
                }
                break;
            }
        default:
            {
                return 0;
            }
        }
    }
}
