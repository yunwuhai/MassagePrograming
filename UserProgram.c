/******************************************************************
* @File name: UserProgram.c
* @Author: Yun
* @Date: 2020-11-24
* @Description: ���ļ����ڴ洢�û����������Ķ���
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UserProgram.h"


/* �޲��޷���begin */

/*********************************************************
* Function name ��P_SayHello
* Description   ����ӡһ��Hello World
* Parameter     ��None
* Return        ��None
**********************************************************/
void P_SayHello()
{
    printf("Hello World!\n");
}

/* �޲��޷���end */

/* �޲��з���begin */

/*********************************************************
* Function name ��P_NowFlag
* Description   ������һ��̬����flag��ÿ�ε��û���flag����һ��Ȼ�����ֵ������
* Parameter     ��None
* Return        ��int, flag��ǰ��ֵ
**********************************************************/
int P_NowFlag()
{
    int static flag = 0;
    flag++;
    printf("flag = %d\n", flag);
    return flag;
}

/* �޲��з���end */

/* �в��޷���begin */


/*********************************************************
* Function name ��P_ShowSum
* Description   ����������Ӳ���ӡ
* Parameter     ��
*       @a          ��Ϊ�����ĵ�һ������
*       @b          ��Ϊ�����ĵڶ�������
* Return        ��None
**********************************************************/
void P_ShowSum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a+b);
}

/* �в��޷���end */

/* �в��з���begin */

/*********************************************************
* Function name ��P_GetSum
* Description   ����������Ӳ���ӡ�����ؽ��
* Parameter     ��
*       @a          ��Ϊ�����ĵ�һ������
*       @b          ��Ϊ�����ĵڶ�������
*       @c          ��Ϊ�����ĵ���������
* Return        ��int, ��������֮��
**********************************************************/
int P_GetSum(int a, int b, int c)
{
    int sum = a + b + c;
    printf("%d + %d + %d = %d\n",a, b, c, sum);
    return sum;
}

/* �в��з���end */
