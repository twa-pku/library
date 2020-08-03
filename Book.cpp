#include "Book.h"
#include "Reader.h"
using namespace std;

void Book::PrintAllInformation(bool deep)
{
    cout << "编号：" << id << endl;
    cout << "书名：" << name << endl;
    cout << "价格：" << price << endl;
    cout << "作者：" << author << endl;
    if (deep == true)
    {
        cout << "是否被借出：";
        if (isfree == true)
        {
            cout << "否" << endl;
        }
        else
        {
            cout << "是" << endl;
            getreader()->PrintAllInformation(false);
        }
    }
}

void Book::load(string filename, int *handle)
{
    ifstream fin(filename);
    if (fin.good())
    {
        string str;
        getline(fin, str);
        id = stoi(str);

        getline(fin, str);
        name = str;

        getline(fin, str);
        price = stod(str);

        getline(fin, str);
        author = str;

        getline(fin, str);
        if (str == "true")
        {
            isfree = true;
            *handle = 0;
        }
        else if (str == "false")
        {
            isfree = false;
            getline(fin, str);
            getline(fin, str);
            *handle = stoi(str);
        }
        fin.close();
    }
    else
        cout << "没有这个文件" << endl;
    return;
}

void Book::save(string filename)
{
    ofstream fout(filename + to_string(id));
    fout << id << endl;
    fout << name << endl;
    fout << price << endl;
    fout << author << endl;
    if (isfree == true)
        fout << "true" << endl;
    else
    {
        fout << "false" << endl;
        fout << endl;
        fout << getreader()->getid() << endl;
        fout << getreader()->getname() << endl;
        fout << getreader()->getgender() << endl;
    }
    fout.close();

    ofstream fout2(filename + "name/" + name);
    fout2 << id << endl;
    fout2.close();
}
