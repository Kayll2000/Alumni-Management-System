/****************************************************************************************************************************
* @function:校友管理系统问卷功能子函数
* @version:v1.5
* @author:chenjunlong
* @description:Implement the system's questionnaire editing, saving, and publishing functions, as well as answer collection.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
*           FUCTION:
                    1、添加问卷
                    2、删除问卷
                    3、修改问卷
                    4、显示所有问卷
                    5、显示已发布问卷
                    6、发布问卷
                    7、清空已发布问卷
                    8、清空所有问卷
                    9、收集用户答案
                    10、问卷保存到指定文件夹，输出文本文件
            BUGFIX:
                    1、[2023.04.11]修复问卷信息保存的文件夹创建错误的bug。
                    2、[2023.04.24]修复查询1号问卷时内容为空，当有2个及以上问卷时，查询1号问卷显示的是后一个问卷内容的bug。
                    3、[2023.04.24]修复当使用新闻后再使用问卷功能时，即创建了Debug文件夹后，新闻功能将不会创建对应的文件夹QuestionData的bug。
                    4、[2023.04.28]修复当发布问卷后，选择显示所有问卷时为空的bug。
                    5、[2023.04.28]修复多人问卷填写时，问卷只能被第一个人填写的bug。
                    6、[2023.05.10]修复多人填写问卷问卷答案被覆盖，问卷收集功能异常的bug。
                    7、[2023.05.11]修复在修改问卷时，输入的选项个数不是整数而导致系统异常的bug。
            MODIFY: 1、[2023.04.06]添加查询指定id问卷功能
                    2、[2023.04.10]修改菜单界面函数
                    3、[2023.04.24]优化UI。
                    4、[2023.05.09]优化代码，规范化。

****************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <io.h>
#include <direct.h>
#include "question.h"
#include "global.h"

using namespace std;

void GCU_ShowQuestion_Menu()
{
    cout << "\t\t*********************************************************" << endl;
    cout << "\t\t******************欢迎使用问卷功能***********************" << endl;
    cout << "\t\t******************[1] 增加问卷***************************" << endl;//ok
    cout << "\t\t******************[2] 删除问卷***************************" << endl;//ok
    cout << "\t\t******************[3] 修改问卷***************************" << endl;//ok
     cout << "\t\t******************[4] 查询问卷***************************" << endl;//ok
    cout << "\t\t******************[5] 显示所有问卷***********************" << endl;//ok
    cout << "\t\t******************[6] 显示已经发布的问卷*****************" << endl;//ok
    cout << "\t\t******************[7] 发布问卷***************************" << endl;//ok
    cout << "\t\t******************[8] 收集问卷答案***********************" << endl;//ok
    #if SYS_1
    cout << "\t\t******************[9] 填写问卷[此项已去除]***************" << endl;//ok
    cout << "\t\t******************[10] 清空已经发布的问卷****************" << endl;//ok
    cout << "\t\t******************[11] 清空所有问卷**********************" << endl;//ok
    cout << "\t\t******************[12] 清屏******************************" << endl;//ok
    cout << "\t\t******************[13] 退出当前问卷菜单******************" << endl;//ok
    #elif SYS_2
    cout << "\t\t******************[9] 退出当前问卷菜单******************" << endl;//ok
    #else
        #error SYS宏未打开
    #endif
    cout << "\t\t*********************************************************" << endl;
}

void GCU_ShowQuestio_ALL(QArray *var)//显示所有问卷及选项
{
    //cout <<"qsize = " <<var->qsize << endl;//debug
    cout << endl;
    if(questionallnum > 0)
    {
        cout << "《所有问卷》" << endl;
        for(int i = 0;i<questionallnum;i++)
        {
            cout << "问卷编号：" << var->qarray[i].id << endl;
            cout << "问卷标题：" << var->qarray[i].title << endl;
            for(int j=0;j<var->qarray[i].items.size();j++)
            {
                cout << "选项"<<j+1<<"："  << var->qarray[i].items[j] << endl;
            }
            cout << endl;
        }
    }else{
        cout << "问卷数量为空！" << endl;
    }
    system("pause");
    system("cls");
}

int IsidExit(QArray *var,int id)//问卷id是否存在  存在返回id  不存在返回-1
{
    for(int i=0;i<questionallnum;i++)
    {
        if(var->qarray[i].id == id)
        {
            //cout << "此问卷编号存在！" << endl;//debug
            return id;
        }else{
            //cout << "此问卷编号不存在！" << endl;
        }
    }
    return -1;
}

int Ispublish(QArray *var,int id)//问卷id是否已经发布  未发布返回id  已经发布返回-1
{
    if(IsidExit(var,id) != -1)//问卷id存在
    {
        for(int i=0;i<questionallnum;i++)
        {
            if(var->parray[i].id == id)
            {
                //cout << "问卷编号为"<< id <<"的问卷已经发布！" << endl;//debug
                return -1;
            }else{
                cout << "编号为"<<id<<"的问卷还未发布！"<< endl;
                return id;
            }
        }
    }else{
        cout << "该问卷编号不存在，请先创建！或者" << endl;
    }
    return -1;
}

void GCU_SaveAnswer_Info(Collect *vac ,QArray *var,int temp,string name)
{
    int t_id = temp;
    string t_name = name;
    cout << "正在保存答案信息···" << endl;
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/AnswerData", 0) == -1)
    {
        _mkdir("Debug/AnswerData");//创建AlumniData文件夹
    }
    ofstream fo;
    fo.open(ANSWERFILE,ios::app);
    fo << "填写人[" << t_name << "]" << endl;
    for(int i=answersave[t_id];i<answerflag[t_id];i++)
    {
        fo << "问卷ID[" << i+1 << "]" << endl
        << "问卷标题{" << var->parray[i].title << "}" << endl;
        for(int j=0;j<var->parray[i].items.size() ;j++)
        {
            fo << "选项[" << j+1 <<"]: " << var->parray[i].items[j] << endl;
        }

        fo << "问卷答案：" << vac->collectarr[t_id].results[i] << endl;
        fo << endl;
    }
    fo.close();
    answersave[t_id]++;
    cout << "保存成功！" << endl;
}

void GCU_SaveQuestion_Info(QArray *var)
{
    cout <<"正在保存信息···"<< endl;
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/QuestionData", 0) == -1)
    {
        _mkdir("Debug/QuestionData");//创建AlumniData文件夹
    }
    ofstream fo;
    fo.open(QUEFILENAME,ios::out);//允许输出(写入操作)到流。
    for(int i = 0;i < questionallnum; ++i)
    {
        fo << "问卷ID[" << var ->qarray[i].id  << "]" << endl
        << "问卷标题{" << var->qarray[i].title << "}" << endl;
            for(int j=0;j<var->qarray[i].items.size();j++)
            {
                fo << "选项[" << j+1 <<"]: " << var->qarray[i].items[j] << endl;
            }
            fo << endl;
    }
    fo.close();
    cout << "保存成功！" << endl;
}

void GCU_ClearQuestion_ALL(QArray *var)//清空所有问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    questionallnum = 0;
    GCU_SaveQuestion_Info(var);
}

void GCU_ClearQuestion_Published(QArray *var)//清空已经发布的问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->parray[i] = var->parray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    questionpublishnum = 0;
}

void GCU_QuestionOp_Publish(QArray *var)//发布问卷
{
    vector<string> batarr;
    string flag;
    int index;//发布的索引
    #if CLC
    cout << "是否重新发布修改的问卷[Y/N]" << endl;
    while(true){
        cin >> flag;
        if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
        {
            break;
        }else{
            cout << "输入指令不存在！" << endl;
            cout << "请重新输入！" << endl;
        }
    }
    if(flag == "Y" ||flag == "y")
    {
        index = 0;//全部重新发布
        GCU_ClearQuestion_Published(var);
    }else{
        index = questionpublishnum;//从全部问卷中发布未发布的问卷
    }
    #endif

    index = questionpublishnum;//从全部问卷中发布未发布的问卷

    for(int i = index;i<questionallnum;i++)
    {
    batarr =  var->qarray[i].items;
    var->parray[questionpublishnum].id = var->qarray[i].id;
    var->parray[questionpublishnum].title = var-> qarray[i].title;
    var->parray[questionpublishnum].items.swap(batarr);
    
    #if DEBUG
    cout << "id:" << var->parray[questionpublishnum].id << endl;
    cout << "title: " << var-> parray[questionpublishnum].title << endl;
    #endif

    questionpublishnum++;
    }
    cout << "问卷发布成功！" << endl;
    system("pause");
    system("cls");
}

void GCU_QuestionOp_ADD(QArray *var)
{
    string _Title,flag;
    string _items[MAXITEM];//最多容纳的选项 ——> MAXITEM 个  10个
    int _nums;//_id;
    char ch;
    while(true)
    {
        cin.get(ch);//吃掉回车\n
        var ->qarray[questionallnum].id = questionallnum+1;//编号从1开始
        cout << "输入问卷标题：" << endl;
        getline(cin,_Title);
        //cin >> _Title;                                            //修复当输入的字符串包含空格时，只接收到第一个空格前的字符的bug
        var->qarray[questionallnum].title = _Title;
        cout << "你想要输入几个选项：" << endl;
        cin >> _nums;
        while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
        {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数:";
        cin.ignore();//EOF位置，接收下一个cin函数
        cin>>_nums;
        }
        for(int i=0;i<_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> _items[i];
        var->qarray[questionallnum].items.push_back(_items[i]);
        }
        questionallnum++;
        var->qsize++;
        cout << "是否继续添加？[Y/N]" << endl;
        for(;;){
            cin >> flag;
            if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
            {
                break;
            }else{
                cout << "输入指令不存在！" << endl;
                cout << "请重新输入！" << endl;
            }
        }
        if(flag == "Y" ||flag == "y")
        {
            cout << "继续添加第[" << questionallnum + 1 << "]张问卷" << endl;
        }else{
            break;
        }
    }
    GCU_SaveQuestion_Info(var);
    system("pause");
    system("cls");
}

void GCU_QuestionOp_DEL(QArray *var)//删除指定问卷
{
    //通过问卷编号删除，此时已经发布或者未发布的问卷都将被删除
    //cout << "删除test！" << endl;
    int del_id;
    cout << "输入你想要删除的问卷编号：" << endl;
    cin >> del_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号:";
    cin.ignore();//EOF位置，接收下一个cin函数
    cin>>del_id;
    }
    if(IsidExit(var,del_id) != -1)//id is exit（存在）
    {
        for(int i = del_id - 1;i<var->qsize;i++)
        {
            var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
        }
        var->qsize--;
    }
    questionallnum = questionallnum - 1;
    cout << "问卷ID为[" << del_id << "]的问卷删除成功！" << endl;
    GCU_SaveQuestion_Info(var);
    system("pause");
    system("cls");
}

void GCU_QuestionOp_MOD(QArray *var)
{
    //通过问卷id修改问卷，此时无论发布的还是未发布的问卷都将被修改

    string mod_Title;
    string mod_items[10];//最多容纳的选项 ——> 10个
    int mod_nums,mod_id;
    cout << "输入需要修改的问卷编号：" << endl;
    cin >> mod_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号: " << endl;;
    cin.ignore();//EOF位置，接收下一个cin函数
    cin >> mod_id;
    }

    if(IsidExit(var,mod_id) != -1)//问卷id存在
    {
        cout << "输入修改后的标题：" << endl;
        cin >> mod_Title;
        var->qarray[mod_id-1].title = mod_Title;
        cout << "输入修改后的选项个数：" << endl;
        cin >> mod_nums;
        while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
        {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数:";
        cin.ignore();//EOF位置，接收下一个cin函数
        cin>>mod_nums;
        }

        var->qarray[mod_id-1].items.clear();//清空原有的，不会回收空间，但size变成0，后续可能有bug
        for(int i=0;i<mod_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> mod_items[i];
        var->qarray[mod_id-1].items.push_back(mod_items[i]);
        }
        cout << "修改成功！" << endl;
    }else{
        cout << "问卷id不存在！修改失败！" << endl;
    }
    GCU_SaveQuestion_Info(var);
    system("pause");
    system("cls");
}

void GCU_ShowQuestion_Published(QArray *var)
{
    cout << endl;
    if(questionpublishnum != 0)
    {
    cout << "《已经发布的问卷》" << endl;
    for(int i = 0;i<questionpublishnum;i++)
    {
        cout << "问卷编号[" << var->parray[i].id << "]" << endl;
        cout << "问卷标题[" << var->parray[i].title << "]" << endl;
        for(int j=0;j<var->parray[i].items.size();j++)
        {
            cout << "选项["<<j+1<<"]："  << var->parray[i].items[j] << endl;
        }
        cout << endl;
    }
    }else{
        cout << "还没有发布问卷！" << endl;
    }
    system("pause");
    system("cls");
}

void GCU_AnswerQuestion_User(QArray *var,Collect *vac,int temp,string name)//用户回答问卷
{
    int myselect,itemsize;
    int stu_id = temp;
    string stu_name = name;
    bool writeflag = false;
    #if DEBUG
    cout << "stu_id:" << stu_id << endl;//debug
    cout << "stu_name" << stu_name << endl;//debug
    #endif
    for(int i = answerflag[stu_id];i<questionpublishnum;i++)
    {
        cout << "问卷编号[" << var->parray[i].id << "]" << endl;
        cout << "问卷标题：" << var->parray[i].title << endl;
        for(int j = 0;j<var->parray[i].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->parray[i].items[j] << endl;
            itemsize = var->parray[i].items.size();
        }
        cout << "请选择你的答案 >>> " << endl;
        while(true)
        {
            cin >> myselect;
            if(myselect>0 && myselect <= itemsize)
            {
                break;
            }else{
                cout << "选项不存在！" << endl;
            }
        }

        vac->collectarr[stu_id].results.push_back(myselect);
        vac->collectarr[stu_id].stus = stu_name;
        vac->csize++;

        answerflag[stu_id]++;
        writeflag = true;
        GCU_SaveAnswer_Info(vac,var,stu_id,stu_name);//保存用户答案
        cout << "写入成功！" << endl;
        
    }
    if(writeflag != true)
    {
        cout << "问卷已经全部填写完毕！或者 问卷未发布！" << endl;
    }
        system("pause");
        system("cls");

}

void GCU_CollectAnswer_Admin(Collect *vac)
{
    //cout << "收集问卷答案test!" << endl;
    int size = sizeof(answerflag) / sizeof(answerflag[0]);
    int tnum = 0;
    for(int j = 0;j <size;j++)
    {
        for(int i = 0;i < answerflag[j];i++)
        {
            cout << "填写人：" << vac->collectarr[j].stus << " ";
            cout <<"id["<< i+1 <<"] 的问卷答案为：" << vac->collectarr[j].results[i] << endl;
            tnum++;
        }
    }
    cout << "问卷填写数量：" << tnum << endl;
    //cout << "csize:" << vac->csize << endl;
    system("pause");
    system("cls");
}

void GCU_QuestionOp_Search(QArray *var)//需要测试
{
    int fid;
    cout << "输入您想查询的问卷id：" << endl;
    cin >> fid;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号: " << endl;;
    cin.ignore();//EOF位置，接收下一个cin函数
    cin >> fid;
    }
    if(IsidExit(var,fid) != -1)//问卷id存在
    {
        cout << "问卷id[" << fid << "]的问卷信息如下：" << endl;
        cout << "问卷编号：[" << fid << "]" << endl;
        cout << "问卷标题：" << var->qarray[fid-1].title << endl;
        for(int j=0;j<var->qarray[fid-1].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->qarray[fid-1].items[j] << endl;
        }
        cout << endl;
    }else{
        cout << "问卷不存在！" << endl;
    }
    system("pause");
    system("cls");
}

void GCU_Test(void)//测试API
{
    cout << "功能未开发！" << endl;
    cout << "详情联系QQ2825363541" << endl;
    system("pause");
    system("cls");
}

void GCU_Temp(void)
{
    cout << "该功能模块当前不可用！" << endl;
    cout << "功能后续将向下兼容···" << endl;
    system("pause");
    system("cls");
}

void GCU_ATError(void)
{
    cout << "指令不存在或者错误！" << endl;
    system("pause");
    system("cls");
}