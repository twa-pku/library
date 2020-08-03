#include <iostream>
#include <map>
#include "Reader.h"

class ReaderManager
{
private:
    map<int, Reader *> ReaderMap;
    string ReaderRoute;

    int getReaderId()
    {
        string name;
        cin >> name;
        int id = FindIdByName(name);
        return id;
    }

    int FindIdByName(string name) {}

    void Addmap(int id)
    {
        if (ReaderMap.find(id) != ReaderMap.end())
            return;
    }

public:
    ReaderManager()
    {
        ReaderRoute = "/root/study/library/reader/";
    }

    ~ReaderManager()
    {
        SaveInfoAndClose();
    }

    string getReaderRoute() { return ReaderRoute; }
    void setReaderRoute(string route) { ReaderRoute = route; }

    void AddReader()
    {
        Reader *aReader = new Reader();

        string name;
        cout << "请输入借书人姓名：";
        cin >> name;
        aReader->setname(name);

        int id;
        cout << "请输入借书人学号：";
        cin >> id;
        //应该检查学号是否正确
        aReader->setid(id);

        string gender;
        cout << "请输入借书人性别：";
        cin >> gender;
        aReader->setgender(gender);

        //save
    }

    void EditReader()
    {
        cout << "请输入要更改的借书人姓名：";
        int id = getReaderId();
        Addmap(id);

        while (true)
        {
            cout << "请输入要更改的借书人信息：" << endl;
            cout << "1、姓名" << endl;
            cout << "2、学号" << endl;
            cout << "3、性别" << endl;
            cout << "提示：请输入相应的序号并按回车，输入q返回：";
            char option;
            cin >> option;
            switch (option)
            {
            case "1":
                cout << "请输入新姓名：";
                string newname;
                cin >> newname;
                ReaderMap[id]->setname(newname);
                return;
            case "2":
                cout << "请输入新学号：";
                int newid;
                cin >> newid;
                //应该检查学号是否正确
                ReaderMap[id]->setid(newid);
                return;
            case "3":
                cout << "请输入新性别：";
                string newgender;
                cin >> newgender;
                ReaderMap[id]->setgender(newgender);
                return;
            case "q":
                return;
            default:
                cout << "请输入正确的选项！" << endl;
            }
        }
    }

    void SearchReader()
    {
        cout << "请输入要查询的借书人姓名：";
        int id = getReaderId();
        Addmap(id);

        while (true)
        {
            cout << "请输入要查询的借书人信息：" << endl;
            cout << "1、姓名" << endl;
            cout << "2、学号" << endl;
            cout << "3、性别" << endl;
            cout << "提示：请输入相应的序号并按回车，输入q返回：";
            char option;
            cin >> option;
            switch (option)
            {
            case "1":
                cout << "借书人的姓名是：" << ReaderMap[id]->getname() << endl;
                return;
            case "2":
                cout << "借书人的学号是：" << ReaderMap[id]->getid() << endl;
                return;
            case "3":
                cout << "借书人的性别是：" << ReaderMap[id]->getgender() << endl;
                return;
            case "q":
                return;
            default:
                cout << "请输入正确的选项！" << endl;
            }
        }
    }

    void DeleteReader()
    {
        cout << "请输入要删除的借书人姓名：";
        int id = getReaderId();
        //删除人的2个文件，如果map有id信息，mapid也要删掉
    }

    void ShowReaderInformation()
    {
        cout << "请输入要查看的借书人姓名：";
        int id = getReaderId();
        Addmap(id);

        ReaderMap[id]->PrintAllInfo();
    }

    void Borrow(Book *abook, Reader *areader)
    {
        areader->addborrownum();
        areader->addbook(abook);
    }

    void Return(Book *abook, Reader *areader)
    {
        areader->minusborrownum();
        areader->minusbook(abook)
    }

    Reader *GetaReaderByName(string name)
    {
        int id = FindIdByName(name);
        Addmap(id);
        return ReaderMap[id];
    }
}