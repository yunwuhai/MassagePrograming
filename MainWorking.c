/******************************************************************
* @File name: MainWorking.c
* @Author: Yun
* @Date: 2020-11-24
* @Description: ���ļ�Ϊc������
******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UserProgram.h"
#include "AppProgram.h"

int main()
{
    unsigned char instruction[MAX_LEN];// ָ��洢��
    CtrlOut O;
    CtrlIn I;
    unsigned int OutStr[MAX_LEN];
    Coding(instruction, &O, &I);
    MCUCtrl(instruction, OutStr, &O, &I);
}
