/******************************************************************
* @File name: AppProgram.c
* @Author: Yun
* @Date: 2020-11-23
* @Description: ���ļ����ڴ洢��λ�����ƺ�������λ�����ƺ����Ķ���
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AppProgram.h"
#include "UserProgram.h"

/******************************************* ��λ�����ֵ���� ********************************************************/

/*********************************************************
* Function name ��OutSavingCtrl
* Description   �����ڿ��Ʊ����������������з���ֵ�ĺ��������ʹ��
*                 ��
* Parameter     ��
*       @O          �ṹ��ָ�룬�ýṹ���ڰ����п�������������ֵ
* Return        ��None
**********************************************************/
void OutSavingCtrl(CtrlOut *O)
{
    int check;
    printf("�����Ƿ񱣴���������(1|��||��|0):");
    scanf("%d", &check);
    if(check == 0)  // ������
    {
        O->O_isSaving[O->pO_isSaving] = 0;  // ��¼�˴�������������
        O->pO_isSaving++;   // ���±�ָ����һλ
        printf("������˲��������...\n");
    }
    else if(check == 1) // ����
    {
        O->O_isSaving[O->pO_isSaving] = 1;  // ��¼�˴�����������
        O->pO_isSaving++;   // ���±�ָ����һλ
        IsAutoSaving(O);    // �ж��Ƿ��Զ�����
    }
    else    // ����
    {
        printf("����������������룡\n");
        OutSavingCtrl(O);
    }
}

/*********************************************************
* Function name ��IsAutoSaving
* Description   �����ڿ����Զ����棬������OutSavingCtrl�����У������鵥��ʹ��
* Parameter     ��
*       @O          �ṹ��ָ�룬�ýṹ���ڰ����п�������������ֵ
* Return        ��None
**********************************************************/
void IsAutoSaving(CtrlOut *O)
{
    int check;  // �ж��Ƿ��Զ�����
    unsigned int addr;  // �����ַ�±�
    printf("�����Ƿ��Զ����棿(1|�Զ�||�ֶ�|0):");
    scanf("%d", &check);
    if(check == 0)  // �ֶ�����
    {
        printf("���ֶ����뱣���ַ�±꣺");
        scanf("%d", &addr);
        printf("�˲��������ַ�±�Ϊ��%d\n", addr);
        O->O_SavingAddr[O->pO_SavingAddr] = addr;   // ��¼��ǰ�����ַ�±�
        O->pO_SavingAddr++; // ���±�ָ����һλ
    }
    else if(check == 1) // �Զ�����
    {
        printf("�Զ�����˲������ֵ...\n");
        O->O_SavingAddr[O->pO_SavingAddr] = O->O_AutoSavingAddr;   // ��¼�Զ������±�
        printf("�˲��������ַ�±�Ϊ��%d\n", O->O_AutoSavingAddr);
        O->O_AutoSavingAddr++;  // �Զ����������һ
        O->pO_SavingAddr++; // ���±�ָ����һλ
    }
    else
    {
        printf("����������������룡\n");
        IsAutoSaving(O);
    }
}


/******************************************* ��λ������ֵ���� ********************************************************/

/*********************************************************
* Function name ��InReadCtrl
* Description   �����ڿ��Ʋ������в����Ĳ�������Ҫʹ�ô˺���
* Parameter     ��
*       @I          �ṹ��ָ�룬�ýṹ���ڰ����п�������������ֵ
*       @paraNum     �����Ĳ�������
* Return        ��None
**********************************************************/
void InReadCtrl(CtrlIn *I, int paraNum)
{
    int check;  // �����ж�������Դ�Ƿ�Ϊ����ֵ���ֶ�����
    int tempVal;    // ������ʱ�洢����
    unsigned int tempAddr;   // ������ʱ�洢�±�
    for(int i = 0; i < paraNum; i++)
    {
        printf("����%d|���ʸò���Ϊ����������������ֶ�����ֵ?(1|���||�ֶ�|0):", i);
        scanf("%d", &check);
        if(check == 0)  // �ֶ�����
        {
            I->I_isRead[I->pI_isRead] = 0;  // ��¼���������ֶ�����
            I->pI_isRead++; // ���±�ָ����һλ
            printf("���ֶ�����ò�����");
            scanf("%d", &tempVal);
            I->I_ReadVal[I->pI_ReadVal] = tempVal;  // ��¼����
            I->pI_ReadVal++;    // ���±�ָ����һλ
        }
        else if(check == 1) // �Զ�����
        {
            I->I_isRead[I->pI_isRead] = 1;  // ��¼�����������ֵ
            I->pI_isRead++; // ���±�ָ����һλ
            printf("��������������±꣺");
            scanf("%d", &tempAddr);
            I->I_ReadVal[I->pI_ReadVal] = tempAddr;  // ��ʱ��¼�±�ֵ
            I->pI_ReadVal++;    // ���±�ָ����һλ
        }
        else
        {
            printf("����������������룡\n");
            i--;
        }
    }
}

/*********************************************** ��λ����� **********************************************************/

/*********************************************************
* Function name ��Coding
* Description   ��������λ����̣���Ϊ��λ��������ͨ���ó�����Ա��CtrlOut�ṹ���CtrlIn�ṹ�壬�Լ�һ������ָ�����飬����Ϊ�������λ���Ĵ���
* Parameter     ��
*       @codeStr[]          ����ָ�����
*       @O                 �ṹ��ָ�룬������ƽṹ��
*       @I                 �ṹ��ָ�룬������ƽṹ��
* Return        ��None
**********************************************************/
void Coding(unsigned char codeStr[], CtrlOut *O, CtrlIn *I)    // ��λ�����
{
    InitIO(I, O);
    printf("�밴˳����������ţ�1|SayHello, 2|NowFlag, 3|ShowSum, 4|GetSum, 5|����\n");
    int line;  // ��¼ָ���
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
                OutSavingCtrl(O);
                break;
            }
        case 3: // �в����޷���ֵ
            {
                codeStr[line] = inst * 0x01;
                InReadCtrl(I, 2);
                break;
            }
        case 4: // �в����з���ֵ
            {
                codeStr[line] = inst * 0x01;
                InReadCtrl(I, 3);
                OutSavingCtrl(O);
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
    printf("��ǰ�Ѵﵽ�ɱ����󳤶ȣ�");
}

/*********************************************************
* Function name ��InitIO
* Description   �����ڳ�ʼ���ṹ�壬����������IO�ṹ��ָ��ָ��ͷ���ú����ѱ�����Coding��MCUCtrl�����������鵥��ʹ��
* Parameter     ��
*       @I          �ṹ��ָ�룬����ṹ��
*       @O          �ṹ��ָ�룬����ṹ��
* Return        ��None
**********************************************************/
void InitIO(CtrlIn *I, CtrlOut *O)
{
    I->pI_isRead = 0;
    I->pI_ReadVal = 0;
    O->O_AutoSavingAddr = 0;
    O->pO_isSaving = 0;
    O->pO_SavingAddr = 0;
}

/******************************************* ��λ�����ֵ���� ********************************************************/

/*********************************************************
* Function name ��MCUOutCtrl
* Description   ��������λ��������ƣ�ÿ���з���ֵ�ĺ�������Ҫ�����ֵͨ���˺������в���
* Parameter     ��
*       @OutStr[]           ����ֵ��������
*       @O                 �ṹ��ָ�룬������ƽṹ��
*       @OutVal             ��������ֵ
* Return        ��None
**********************************************************/
void MCUOutCtrl(int OutStr[], CtrlOut *O, int OutVal)
{
    if(!(O->O_isSaving[O->pO_isSaving]))  // ������
    {
        O->pO_isSaving++;   // �±�ָ����һλ
        return; // �����������
    }
    else    // ����
    {
        O->pO_isSaving++;   // �±�ָ����һλ
        OutStr[O->O_SavingAddr[O->pO_SavingAddr]] = OutVal; // ��ǰ������Ӧ�ı����ַ��¼���ֵ
        O->pO_SavingAddr++; // �±�ָ����һλ
    }
}

/******************************************* ��λ�����ֵ���� ********************************************************/

/*********************************************************
* Function name ��MCUInCtrl
* Description   ��������λ��������ƣ�ÿ���в����ĺ�������Ҫ������ͨ���˺������в�������ÿ��������Ҫ����
* Parameter     ��
*       @OutStr[]           ����ֵ��������
*       @I                 �ṹ��ָ�룬������ƽṹ��
*       @InVal              ����ָ�룬������ƽṹ�壬��������ָ�봫��
* Return        ��None
**********************************************************/
void MCUInCtrl(int OutStr[], CtrlIn *I, int *InVal)
{
    if(!(I->I_isRead[I->pI_isRead]))    // �ֶ�����
    {
        I->pI_isRead++;
        *InVal = I->I_ReadVal[I->pI_ReadVal];
        I->pI_ReadVal++;
    }
    else    // �Զ�����
    {
        I->pI_isRead++;
        *InVal = OutStr[I->I_ReadVal[I->pI_ReadVal]];
        I->pI_ReadVal++;
    }
}

/*********************************************** ��λ������ **********************************************************/

/*********************************************************
* Function name ��MCUCtrl
* Description   ��������λ�����ƣ���λ��ͨ��IOָ���ж�ִ�ж�Ӧ�Ĳ���
* Parameter     ��
*       @instruction[]       ����ָ�����
*       @OutStr[]           ����ֵ��������
*       @O                 �ṹ��ָ�룬������ƽṹ��
*       @I                 �ṹ��ָ�룬������ƽṹ��
* Return        ��None
**********************************************************/
void MCUCtrl(unsigned char instruction[], int OutStr[], CtrlOut *O, CtrlIn *I)
{
    InitIO(I, O);
    for(int i = 0; i < MAX_LEN; i++)
    {
        switch(instruction[i]) // �ж�ָ��
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
