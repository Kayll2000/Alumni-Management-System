/****************************************************************************************************************************
* @function:校友管理系统主函数
* @version:v1.5
* @author:chenjunlong
* @description:By calling other modules, the main functions are achieved.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
* @compile:Compile the environment is Dev-C++(Embarcadero Dev-C++)
*           FUCTION:
                    1、校友登录
                        	1.1 修改个人信息
	                        1.2 查看其他校友信息
	                        1.3 填写问卷
	                        1.4 查看新闻
	                        1.5 退出登录
                    2、管理员登录
                    	    2.1 查看校友列表
	                        2.2 添加校友信息
	                        2.3 修改校友信息
	                        2.4 删除校友信息
	                        2.5 新闻功能
	                        2.6 问卷功能
	                        2.7 退出登录
            BUGFIX:
            MODIFY:[2023.04.24]增加主函数登录界面输入的容错性，优化主界面，优化UI。
                   [2023.05.08]简化主函数体，避免冗余。
				   [2023.05.09]优化代码，规范化，所有函数以GCU开头，遵循驼峰式命名。
				   [2023.05.10]修改core函数名，符合整体规范。
				   [2023.05.12]增加在系统开启和关闭时“逐字”语句输出功能。
				   [2023.05.12]增加多线程。
				   [2023.05.15]去除多线程功能。

*
****************************************************************************************************************************/
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <io.h>
#include<direct.h> 
#include <list>
#include "login.h"
#include "core.h"

using namespace std;
//int main(int argc, char** argv)
int main() 
{
	/* code */
	#if SYS_PRINT
	GCU_Init();
	#endif
	//GCU_PrintWord();
	GCU_Core();

	// HANDLE h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GCU_PrintWord, NULL, 0, NULL);
    // HANDLE h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GCU_Core, NULL, 0, NULL);
    // WaitForSingleObject(h1, INFINITE);
    // WaitForSingleObject(h2, INFINITE);
    // CloseHandle(h1);
    // CloseHandle(h2);
	
    return 0;
}