/******************************************************************
* @File name: AppProgram.c
* @Author: Yun
* @Date: 2020-11-23
* @Description: 本文件用于存储上位机控制函数和下位机控制函数的定义
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AppProgram.h"
#include "UserProgram.h"

/******************************************* 上位机输出值控制 ********************************************************/

/*********************************************************
* Function name ：OutSavingCtrl
* Description   ：用于控制保存输出，如果控制有返回值的函数则可以使用
*                 在
* Parameter     ：
*       @O          结构体指针，该结构体内包含有控制所需的数组和值
* Return        ：None
**********************************************************/
void OutSavingCtrl(CtrlOut *O)
{
    int check;
    printf("请问是否保存输出结果？(1|是||否|0):");
    scanf("%d", &check);
    if(check == 0)  // 不保存
    {
        O->O_isSaving[O->pO_isSaving] = 0;  // 记录此处不保存输出结果
        O->pO_isSaving++;   // 让下标指向下一位
        printf("不保存此操作不输出...\n");
    }
    else if(check == 1) // 保存
    {
        O->O_isSaving[O->pO_isSaving] = 1;  // 记录此处保存输出结果
        O->pO_isSaving++;   // 让下标指向下一位
        IsAutoSaving(O);    // 判断是否自动保存
    }
    else    // 错误
    {
        printf("输入错误，请重新输入！\n");
        OutSavingCtrl(O);
    }
}

/*********************************************************
* Function name ：IsAutoSaving
* Description   ：用于控制自动保存，被用于OutSavingCtrl函数中，不建议单独使用
* Parameter     ：
*       @O          结构体指针，该结构体内包含有控制所需的数组和值
* Return        ：None
**********************************************************/
void IsAutoSaving(CtrlOut *O)
{
    int check;  // 判定是否自动保存
    unsigned int addr;  // 保存地址下标
    printf("请问是否自动保存？(1|自动||手动|0):");
    scanf("%d", &check);
    if(check == 0)  // 手动保存
    {
        printf("请手动输入保存地址下标：");
        scanf("%d", &addr);
        printf("此操作保存地址下标为：%d\n", addr);
        O->O_SavingAddr[O->pO_SavingAddr] = addr;   // 记录当前保存地址下标
        O->pO_SavingAddr++; // 让下标指向下一位
    }
    else if(check == 1) // 自动保存
    {
        printf("自动保存此操作输出值...\n");
        O->O_SavingAddr[O->pO_SavingAddr] = O->O_AutoSavingAddr;   // 记录自动保存下标
        printf("此操作保存地址下标为：%d\n", O->O_AutoSavingAddr);
        O->O_AutoSavingAddr++;  // 自动保存个数加一
        O->pO_SavingAddr++; // 让下标指向下一位
    }
    else
    {
        printf("输入错误，请重新输入！\n");
        IsAutoSaving(O);
    }
}


/******************************************* 上位机输入值控制 ********************************************************/

/*********************************************************
* Function name ：InReadCtrl
* Description   ：用于控制参数，有参数的操作都需要使用此函数
* Parameter     ：
*       @I          结构体指针，该结构体内包含有控制所需的数组和值
*       @paraNum     操作的参数个数
* Return        ：None
**********************************************************/
void InReadCtrl(CtrlIn *I, int paraNum)
{
    int check;  // 用于判断输入来源是否为返回值或手动输入
    int tempVal;    // 用于临时存储参数
    unsigned int tempAddr;   // 用于临时存储下标
    for(int i = 0; i < paraNum; i++)
    {
        printf("参数%d|请问该参数为其它函数输出还是手动输入值?(1|输出||手动|0):", i);
        scanf("%d", &check);
        if(check == 0)  // 手动保存
        {
            I->I_isRead[I->pI_isRead] = 0;  // 记录参数来自手动输入
            I->pI_isRead++; // 让下标指向下一位
            printf("请手动输入该参数：");
            scanf("%d", &tempVal);
            I->I_ReadVal[I->pI_ReadVal] = tempVal;  // 记录参数
            I->pI_ReadVal++;    // 让下标指向下一位
        }
        else if(check == 1) // 自动保存
        {
            I->I_isRead[I->pI_isRead] = 1;  // 记录参数来自输出值
            I->pI_isRead++; // 让下标指向下一位
            printf("请输入输出保存下标：");
            scanf("%d", &tempAddr);
            I->I_ReadVal[I->pI_ReadVal] = tempAddr;  // 此时记录下标值
            I->pI_ReadVal++;    // 让下标指向下一位
        }
        else
        {
            printf("输入错误，请重新输入！\n");
            i--;
        }
    }
}

/*********************************************** 上位机编程 **********************************************************/

/*********************************************************
* Function name ：Coding
* Description   ：用于上位机编程，此为上位机主程序，通过该程序可以编程CtrlOut结构体和CtrlIn结构体，以及一个操作指令数组，生成为传输给下位机的代码
* Parameter     ：
*       @codeStr[]          操作指令集数组
*       @O                 结构体指针，输出控制结构体
*       @I                 结构体指针，输入控制结构体
* Return        ：None
**********************************************************/
void Coding(unsigned char codeStr[], CtrlOut *O, CtrlIn *I)    // 上位机编程
{
    InitIO(I, O);
    printf("请按顺序输入程序编号：1|SayHello, 2|NowFlag, 3|ShowSum, 4|GetSum, 5|编译\n");
    int line;  // 记录指令号
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
                OutSavingCtrl(O);
                break;
            }
        case 3: // 有参数无返回值
            {
                codeStr[line] = inst * 0x01;
                InReadCtrl(I, 2);
                break;
            }
        case 4: // 有参数有返回值
            {
                codeStr[line] = inst * 0x01;
                InReadCtrl(I, 3);
                OutSavingCtrl(O);
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
    printf("当前已达到可编程最大长度！");
}

/*********************************************************
* Function name ：InitIO
* Description   ：用于初始化结构体，这样可以让IO结构体指针指向开头，该函数已被用于Coding和MCUCtrl函数，不建议单独使用
* Parameter     ：
*       @I          结构体指针，输入结构体
*       @O          结构体指针，输出结构体
* Return        ：None
**********************************************************/
void InitIO(CtrlIn *I, CtrlOut *O)
{
    I->pI_isRead = 0;
    I->pI_ReadVal = 0;
    O->O_AutoSavingAddr = 0;
    O->pO_isSaving = 0;
    O->pO_SavingAddr = 0;
}

/******************************************* 下位机输出值控制 ********************************************************/

/*********************************************************
* Function name ：MCUOutCtrl
* Description   ：用于下位机输出控制，每次有返回值的函数都需要将输出值通过此函数进行操作
* Parameter     ：
*       @OutStr[]           返回值保存数组
*       @O                 结构体指针，输出控制结构体
*       @OutVal             函数返回值
* Return        ：None
**********************************************************/
void MCUOutCtrl(int OutStr[], CtrlOut *O, int OutVal)
{
    if(!(O->O_isSaving[O->pO_isSaving]))  // 不保存
    {
        O->pO_isSaving++;   // 下标指向下一位
        return; // 结束输出控制
    }
    else    // 保存
    {
        O->pO_isSaving++;   // 下标指向下一位
        OutStr[O->O_SavingAddr[O->pO_SavingAddr]] = OutVal; // 当前操作对应的保存地址记录输出值
        O->pO_SavingAddr++; // 下标指向下一位
    }
}

/******************************************* 下位机输出值控制 ********************************************************/

/*********************************************************
* Function name ：MCUInCtrl
* Description   ：用于下位机输入控制，每次有参数的函数都需要将参数通过此函数进行操作，且每个参数都要操作
* Parameter     ：
*       @OutStr[]           返回值保存数组
*       @I                 结构体指针，输入控制结构体
*       @InVal              整型指针，输入控制结构体，即参数以指针传入
* Return        ：None
**********************************************************/
void MCUInCtrl(int OutStr[], CtrlIn *I, int *InVal)
{
    if(!(I->I_isRead[I->pI_isRead]))    // 手动保存
    {
        I->pI_isRead++;
        *InVal = I->I_ReadVal[I->pI_ReadVal];
        I->pI_ReadVal++;
    }
    else    // 自动保存
    {
        I->pI_isRead++;
        *InVal = OutStr[I->I_ReadVal[I->pI_ReadVal]];
        I->pI_ReadVal++;
    }
}

/*********************************************** 下位机控制 **********************************************************/

/*********************************************************
* Function name ：MCUCtrl
* Description   ：用于下位机控制，下位机通过IO指令判断执行对应的操作
* Parameter     ：
*       @instruction[]       操作指令集数组
*       @OutStr[]           返回值保存数组
*       @O                 结构体指针，输出控制结构体
*       @I                 结构体指针，输入控制结构体
* Return        ：None
**********************************************************/
void MCUCtrl(unsigned char instruction[], int OutStr[], CtrlOut *O, CtrlIn *I)
{
    InitIO(I, O);
    for(int i = 0; i < MAX_LEN; i++)
    {
        switch(instruction[i]) // 判断指令
        {
        case 0x01:
            {
                P_SayHello();
                break;
            }
        case 0x02:
            {
                int a = P_NowFlag();
                MCUOutCtrl(OutStr, O, a);
                break;
            }
        case 0x03:
            {
                int a, b;
                MCUInCtrl(OutStr, I, &a);
                MCUInCtrl(OutStr, I, &b);
                P_ShowSum(a, b);
                break;
            }
        case 0x04:
            {
                int a, b, c;
                MCUInCtrl(OutStr, I, &a);
                MCUInCtrl(OutStr, I, &b);
                MCUInCtrl(OutStr, I, &c);
                int d = P_GetSum(a, b, c);
                MCUOutCtrl(OutStr, O, d);
                break;
            }
        default:
            {
                return;
            }
        }
    }
}
