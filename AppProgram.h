/******************************************************************
* @File name: AppProgram.h
* @Author: Yun
* @Date: 2020-11-23
* @Description: 本文件用于存储上位机控制函数和下位机控制函数的声明以及相应参数的存储
******************************************************************/

#ifndef APPPROGRAM_H_INCLUDED
#define APPPROGRAM_H_INCLUDED

#define MAX_LEN 60  // 程序语句最长

/* 结构体 */

/***********************************
* Struct name   ：CtrOut
* Description   ：用于控制输出返回值
*                 在上位机使用的时候：首先判断当前是否需要保存返回值，并依次把结果记录在O_isSaving数组中
*                                    然后如果需要保存，则选择是否需要自动保存，自动保存等效于新建变量，手动保存等于赋值已有变量
*                                    如果是手动保存，则需要手动输入保存变量下标，在下位机中我们把保存的变量都放在一个数组中，参数可以通过下标从这里调用内容
*                                    如果是自动保存，则自动下标会自增1然后记录当前自动下标，比如第一次自动记录时自动下标为0，然后第二次为1
*                                       // 注意，如果在手动保存时选择了比自动下标更大的数可能会导致存储内容被覆盖
*                 在下位机使用的时候：实际应用中下位机需要单独另建空间对这些内容进行保存，在demo中我们会省略这部分内容
*                                    首先下位机在执行有返回值的操作时，会进行判断此次操作是否需要保存返回值，此时需要检测O_isSaving数组
*                                    在确定需要保存后，将会从O_SavingAddr数组中取出当前操作的下标，然后将其保存到自定义的函数返回值保存空间的指定下标位置
* Member        ：
*       @O_isSaving[MAX_LEN]            ：用于记录当前操作是否保存返回值 // 当且仅当有返回值时必须记录，1保存，0不保存
*       @pO_isSaving                    ：数组下标，扫描O_isSaving数组    // 每次读写后必须移动到下一位    // 初始化时需要赋值为0
*       @O_SavingAddr[MAX_LEN]          ：用于记录当前保存值地址 // 当且仅当保存返回值时必须记录，如果为自动保存则自动记录当前O_AutoSavingAddr，如果为手动保存则记录输入下标值
*       @pO_SavingAddr                  ：数组下标，扫描O_SavingAddr数组  // 每次读写后必须移动到下一位    // 初始化时需要赋值为0
*       @O_AutoSavingAddr               ：用于记录当前自动保存的个数   // 当且仅当自动保存时将此大小记录在O_SavingAddr中后自增一，否则不对此值执行任何操作  // 初始化时需要赋值为0
***********************************/
typedef struct CONTROL_OUT
{
    bool O_isSaving[MAX_LEN];
    unsigned int pO_isSaving;
    unsigned int O_SavingAddr[MAX_LEN];
    unsigned int pO_SavingAddr;
    unsigned int O_AutoSavingAddr;
}CtrlOut;


/***********************************
* Struct name   ：CtrIn
* Description   ：用于控制输入参数值
*                 在上位机使用的时候：首先判断当前参数来自手动输入还是来自输出返回值，这里可以把输入值理解为常量，把输出返回值理解为已有值变量，并将此记录在I_isReading数组中，
*                                    然后如果来自于输入值，即常量，则在I_ReadVal数组中记录一个数字
*                                    如果来自于返回值，即变量，则在I_ReadVal数组中记录一个下标，该下标可以在函数返回值保存数组中进行取值
*                                      //事实上这是一种不严谨的做法，因为两种数据类型一个是有符号，一个无符号，但是这里我们的数组比较短，所以可以暂时简便起见如此使用
*                 在下位机使用的时候：实际应用中下位机需要单独另建空间对这些内容进行保存，在demo中我们会省略这部分内容
*                                    首先下位机在执行有参数的操作时，会对每个参数进行判断当前参数来自于一个变量还是常量，
*                                    根据我们在I_isRead数组中的记录，如果为常量，即输入值，则直接将对应位置的I_ReadVal中的值取出作为参数
*                                    否则为变量，即返回值，需要先从I_ReadVal中取出对应位置的值作为下标，在自定义的函数返回值保存将对应下标的值取出作为参数
* Member        ：
*       @I_isRead[MAX_LEN * 3]          ：用于记录当前操作函数是否来自返回值  // 当且仅当有参数时必须记录，每个参数都要记录，1来自返回值，0来自输入值
*       @pI_isRead                      ：数组下标，扫描I_isReading数组   // 每次读写必须移动到下一位 // 初始化时需要赋值为0
*       @I_ReadVal[MAX_LEN * 3]         ：用于记录参数值，顺序表，对应每个参数 // 如果来自返回值则根据输入下标从O_SavingVal数组提取，如果来自输入值则直接记录输入
*       @pI_ReadVal                     ：数组下标，扫描I_ReadVal数组 // 每次读写必须移动到下一位 // 初始化时需要赋值为0
***********************************/
typedef struct CONTROL_IN // 控制参数值
{
    bool I_isRead[MAX_LEN * 3];
    unsigned int pI_isRead;
    int I_ReadVal[MAX_LEN * 3];
    unsigned int pI_ReadVal;
}CtrlIn;


void OutSavingCtrl(CtrlOut *O);
void IsAutoSaving(CtrlOut *O);
void InReadCtrl(CtrlIn *I, int paraNum);
void Coding(unsigned char codeStr[], CtrlOut *O, CtrlIn *I);
void InitIO(CtrlIn *I, CtrlOut *O);
void MCUOutCtrl(int OutStr[], CtrlOut *O, int OutVal);
void MCUInCtrl(int OutStr[], CtrlIn *I, int *InVal);
void MCUCtrl(unsigned char instruction[], int OutStr[], CtrlOut *O, CtrlIn *I);

#endif // APPPROGRAM_H_INCLUDED
