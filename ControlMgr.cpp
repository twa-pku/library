#include "ControlMgr.h"
using namespace std;

void ControlMgr::EnterOption1()
{
    while (true)
    {
        cout << "=====图书信息管理=====" << endl;
        cout << "1、图书信息管理" << endl;
        cout << "2、借书人管理" << endl;
        cout << "3、图书借还管理" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回";
        char option1;
        cin >> option1;
        switch (option1)
        {
        case '1':
            EnterOption21();
            break;
        case '2':
            EnterOption22();
            break;
        case '3':
            EnterOption23();
            break;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
    return;
}

void ControlMgr::EnterOption21()
{
    while (true)
    {
        cout << "=====图书管理系统-图书信息管理=====" << endl;
        cout << "1、图书基本信息的录入" << endl;
        cout << "2、图书基本信息的修改" << endl;
        cout << "3、图书基本信息的查询" << endl;
        cout << "4、图书信息的删除" << endl;
        cout << "5、显示图书基本信息" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回";
        char option21;
        cin >> option21;
        switch (option21)
        {
        case '1':
            brm->AddBook();
            break;
        case '2':
            brm->EditBook();
            break;
        case '3':
            brm->SearchBook();
            break;
        case '4':
            brm->DeleteBook();
            break;
        case '5':
            brm->ShowBookInformation();
            break;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void ControlMgr::EnterOption22()
{
    while (true)
    {
        cout << "=====图书管理系统-借书人管理=====" << endl;
        cout << "1、注册借书人" << endl;
        cout << "2、修改借书人信息" << endl;
        cout << "3、查询借书人信息" << endl;
        cout << "4、删除借书人" << endl;
        cout << "5、显示借书人信息" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回";
        char option22;
        cin >> option22;
        switch (option22)
        {
        case '1':
            brm->AddReader();
            break;
        case '2':
            brm->EditReader();
            break;
        case '3':
            brm->SearchReader();
            break;
        case '4':
            brm->DeleteReader();
            break;
        case '5':
            brm->ShowReaderInformation();
            break;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void ControlMgr::EnterOption23()
{
    while (true)
    {
        cout << "=====图书管理系统-图书借还管理=====" << endl;
        cout << "1、办理借书手续" << endl;
        cout << "2、办理还书手续" << endl;
        cout << "3、显示借还信息" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回";
        char option23;
        cin >> option23;
        switch (option23)
        {
        case '1':
            brm->BorrowBook();
            break;
        case '2':
            brm->ReturnBook();
            break;
        case '3':
            brm->ShowBorrowInformation();
            break;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}