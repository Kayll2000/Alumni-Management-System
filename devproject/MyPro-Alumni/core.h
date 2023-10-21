#ifndef CORE_H
#define CORE_H

extern void GCU_Core(void);//核心实现函数
extern void GCU_Init(void);//初始化输出文字
extern void GCU_Quit(void);//退出问候语
extern void GCU_PrintWord(void);//随机打印字符串
extern bool GCU_IsNumeric(string str);//输入数字合法检测
extern void GCU_PrintCharByChar(string s, int delay);//逐字输出文字
// extern void GCU_Core(AlumniManager _alumni_manager,AdminManager _admin_manager,Admin _admin);

#endif