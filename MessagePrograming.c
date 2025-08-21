#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 60  // 程序语句最长

int Back[MAX_LEN];  // 存储返回值

typedef struct BACK_STR // 控制返回值
{
    bool isBackWrite[MAX_LEN];   // 记录如何存储，0表示不存储，1表示存储
    unsigned int pBackWrite[MAX_LEN];     // 记录存入位置，顺序存入，只有在isBackWrite为1时才可以调用，可以存入Back的指定位置
}backStr;

typedef struct PARA_STR // 控制参数值
{
    bool isParaReadBack[MAX_LEN * 3];   // 记录该参数从返回值区（1）取还是从参数区取（0）
    unsigned int Para[MAX_LEN * 3]; // 记录了参数位置，仅当isParaReadBack为0时才可以调用，顺序调用
    unsigned int pBackRead[MAX_LEN * 3]; // 记录取出位置，顺序取出，只有在isParaReadBack为1时才可以调用，顺序调用，可以取出指定位置的Back值
}paraStr;

/*
 * 全局变量声明
 */
int static flag = 0;

/*
 * 编程函数
 */
void SayHello() // 打印一行Hello World!
{
    printf("Hello World!\n");
}

int NowFlag()   // 将flag值自增一然后打印出来并返回
{
    flag++;
    printf("flag = %d\n", flag);
    return flag;
}

void ShowSum(int a, int b)  // 打印两个参数之和
{
    printf("%d + %d = %d\n", a, b, a+b);
}

int GetSum(int a, int b, int c) // 打印并返回三参数之和
{
    int sum = a + b + c;
    printf("%d + %d + %d = %d\n",a, b, c, sum);
    return sum;
}

/*
** 操作函数
*/
// 配置返回值，第一个参数代入数据流，第二个参数代入是否保留控制数组中，第三个代入当前已经默认保留占用的空间数指针，第四个代入控制数组中为1的量对应的存储空间
void InitBack(backStr * B, int *p_isBackWrite, int *p_Back, int *p_pBackWrite)
{
    // 选择是否保留，并把选择结果记录在返回值控制数据中
    printf("请问是否保留返回值,1保留，0不保留:");
    int isTemp;
    scanf("%d", &isTemp);
    // 记录此处是否保留，这里会修改是否保留数组，并将保留指针自增一
    B->isBackWrite[*p_isBackWrite] = isTemp;
    (*p_isBackWrite)++;
    // 这里根据是否保留分为两种情况，不保留时可以不进行任何操作，因为返回值对真正程序没有任何影响
    if(isTemp)   // 如果要保留
    {
        printf("是否需要自动保留，1手动，0自动:");
        scanf("%d", &isTemp);
        // 根据是否自动保留，自动保留会默认在当前顺序下的下一位进行保留，如果需要覆盖之前的值则需要手动选择保存位置，在这一部分不管结果如何都会使存储空间的数组指针记录存储位置并自增一
        if(isTemp)  // 指定位置保留,这里会根据手动输入当前指令返回的存储空间，不会修改默认保留占用的空间数指针
        {
            printf("请输入指定位置,从0开始小于60,如果使用了超过%d的位置可能在后面返回值覆盖:", *p_Back-1);
            int stateTemp;
            scanf("%d", &stateTemp);    // 选择位置，如果不是自用最好加一个判断
            // 因为需要保留，此处记录保留的位置，这个数量始终与是否保留的1个数相同
            B->pBackWrite[*p_pBackWrite] = stateTemp;    // 记录存储地址
            printf("您在%d的位置存储了当前操作的返回值", stateTemp);
            (*p_pBackWrite)++;
        }
        else    // 自动顺序保存，这里会顺序将已占用空间的下一位保留，让存储占用空间指针自增一
        {
            B->pBackWrite[*p_pBackWrite] = *p_Back; // 根据已经占用的数量可以确定默认保存的地址
            printf("您在%d的位置存储了当前操作的返回值", *p_Back);
            (*p_pBackWrite)++;
            (*p_Back)++;
        }
    }// 不保留则不执行任何操作
}

void InitPara(int paraAll, paraStr * P, int *p_isParaReadBack, int *p_pBackRead, int *p_Para, int p_Back)
{
    int paraNum;    // 记录参数个数
    for(paraNum = 0; paraNum < paraAll; paraNum++)
    {
        printf("请问参数来自于常量还是返回值，1返回，0常量");
        int isTemp;
        scanf("%d", &isTemp);
        P->isParaReadBack[*p_isParaReadBack] = isTemp;
        (*p_isParaReadBack)++;
        if(isTemp) // 来自返回值
        {
            int stateTemp;
            printf("请输入其来自返回值编号，当前正常使用编号最大为%d:", p_Back-1);
            scanf("%d", &stateTemp);
            P->pBackRead[*p_pBackRead] = stateTemp;  // 指向编号
            (*p_pBackRead)++;
        }
        else    // 来自常量
        {
            printf("请输入参数%d:", paraNum + 1);
            int stateTemp;
            scanf("%d", &stateTemp);
            P->Para[*p_Para] = stateTemp;
            (*p_Para)++;
        }
    }
}

void Coding(unsigned char codeStr[], backStr * B, paraStr * P)    // 上位机编程
{
    printf("请按顺序输入程序编号：1|SayHello, 2|NowFlag, 3|ShowSum, 4|GetSum, 5|编译\n");
    int line;  // 记录指令号
    int p_isBackWrite = 0;  // 是否有返回值数组指针
    int p_pBackWrite = 0;  // 指向返回值存储地址的指针数组的指针
    int p_isParaReadBack = 0;  // 是否读取返回值作为参数数组指针
    int p_Back = 0; // 记录返回值指针
    int p_Para = 0;  // 记录参数指针
    int p_pBackRead = 0;    // 指向返回值读取地址的指针数组的指针
    int inst;   // 程序编号
    for(line = 0; line <= MAX_LEN; line++)   // 程序不能超过最大长度
    {
        printf("%d|  ", line + 1); // 格式占用
        scanf("%d", &inst); // 获取指令
        switch(inst)
        {
        case 1: // 无参数无返回值
            {
                codeStr[line] = inst * 0x01;
                break;
            }
        case 2: // 无参数有返回值
            {
                codeStr[line] = inst * 0x01;
                InitBack(B, &p_isBackWrite, &p_Back, &p_pBackWrite);
                break;
            }
        case 3: // 有参数无返回值
            {
                codeStr[line] = inst * 0x01;
                InitPara(2, P, &p_isParaReadBack, &p_pBackRead, &p_Para, p_Back);
                break;
            }
        case 4: // 有参数有返回值
            {
                codeStr[line] = inst * 0x01;
                InitPara(3, P, &p_isParaReadBack, &p_pBackRead, &p_Para, p_Back);
                InitBack(B, &p_isBackWrite, &p_Back, &p_pBackWrite);
                break;
            }
        case 5:
            {
                printf("编译成功！\n");
                codeStr[line] = 0xff;	// 任意可以结束下位机switch的命令
                return;
            }
        default:
            {
                printf("无当前指令！请重新输入！");
                line--;
                break;
            }
        }
        printf("\n");
    }
}

int main()
{
    unsigned char instruction[MAX_LEN];// 指令存储器
    backStr B;
    paraStr P;
    Coding(instruction, &B, &P);    // 获取指令
    int p_isParaReadBack = 0;   // 确定参数来自于常数还是返回值指针
    int p_pBackRead = 0;   // 确定参数
    int p_pBackWrite = 0;
    int p_Para = 0;  // 确定指向返回值地址
    for(int i = 0; i < MAX_LEN; i++)
    {
        switch(instruction[i]) // 判断指令
        {
        case 0x01:
            {
                SayHello();
                break;
            }
        case 0x02:
            {
                if(B.isBackWrite)   // 保留返回值
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
                if(P.isParaReadBack[p_isParaReadBack])  // 来自返回值
                {
                    a = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // 来自返回值
                {
                    a = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // 来自返回值
                {
                    b = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // 来自返回值
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
                if(P.isParaReadBack[p_isParaReadBack])  // 来自返回值
                {
                    a = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // 来自返回值
                {
                    a = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // 来自返回值
                {
                    b = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // 来自返回值
                {
                    b = P.Para[p_Para];
                    p_Para++;
                }
                if(P.isParaReadBack[p_isParaReadBack])  // 来自返回值
                {
                    c = Back[P.pBackRead[p_pBackRead]];
                    p_pBackRead++;
                }
                else    // 来自返回值
                {
                    c = P.Para[p_Para];
                    p_Para++;
                }
                if(B.isBackWrite)   // 保留返回值
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
