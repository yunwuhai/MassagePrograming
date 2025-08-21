/******************************************************************
* @File name: UserProgram.c
* @Author: Yun
* @Date: 2020-11-24
* @Description: 本文件用于存储用户操作函数的定义
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UserProgram.h"


/* 无参无返回begin */

/*********************************************************
* Function name ：P_SayHello
* Description   ：打印一行Hello World
* Parameter     ：None
* Return        ：None
**********************************************************/
void P_SayHello()
{
    printf("Hello World!\n");
}

/* 无参无返回end */

/* 无参有返回begin */

/*********************************************************
* Function name ：P_NowFlag
* Description   ：内置一静态变量flag，每次调用会让flag自增一，然后输出值并返回
* Parameter     ：None
* Return        ：int, flag当前的值
**********************************************************/
int P_NowFlag()
{
    int static flag = 0;
    flag++;
    printf("flag = %d\n", flag);
    return flag;
}

/* 无参有返回end */

/* 有参无返回begin */


/*********************************************************
* Function name ：P_ShowSum
* Description   ：将两数相加并打印
* Parameter     ：
*       @a          作为加数的第一个整数
*       @b          作为加数的第二个整数
* Return        ：None
**********************************************************/
void P_ShowSum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a+b);
}

/* 有参无返回end */

/* 有参有返回begin */

/*********************************************************
* Function name ：P_GetSum
* Description   ：将三数相加并打印，返回结果
* Parameter     ：
*       @a          作为加数的第一个整数
*       @b          作为加数的第二个整数
*       @c          作为加数的第三个整数
* Return        ：int, 三个参数之和
**********************************************************/
int P_GetSum(int a, int b, int c)
{
    int sum = a + b + c;
    printf("%d + %d + %d = %d\n",a, b, c, sum);
    return sum;
}

/* 有参有返回end */
