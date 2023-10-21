/****************************************************************************************************************************
* @function:保存全局变量及函数
* @version:v1.5
* @author:chenjunlong
* @description:Save global variables and functions for the project.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
*           FUCTION:
                    1、后续将进行优化，这个文件主要存放全局变量以及函数。
            BUGFIX:
            MODIFY:
                    1、[2023.05.09]优化代码，规范化。

****************************************************************************************************************************/
#include <iostream>
#include "global.h"

int newsnum = 0;//记录新闻条数
int questionallnum = 0;// 记录所有问卷的数量
int questionpublishnum = 0;//记录已经发布问卷的数量
int answerflag[MAX_QUESTION_NUM] = {0};//记录已经填写的问卷个数，初始化为0
int answersave[MAX_QUESTION_NUM] = {0};
int stuid = 0;//初始值为0
// bool runningflag = true;