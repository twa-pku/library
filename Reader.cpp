#include "Reader.h"
#include "Book.h"
using namespace std;

void Reader::minusbook(shared_ptr<Book> &_book)
{
    for (auto p = book.begin(); p != book.end(); p++)
    {
        if ((*p).lock().get() == _book.get())
        {
            book.erase(p);
            return;
        }
    }
}

void Reader::PrintAllInformation(bool deep)
{
    cout << "姓名：" << name << endl;
    cout << "学号：" << id << endl;
    cout << "性别：" << gender << endl;
    cout << "借书本数：" << borrownum << endl;
    if (deep == true && borrownum > 0)
    {
        for (auto p = book.begin(); p != book.end(); p++)
        {
            shared_ptr<Book> tmp = (*p).lock();
            tmp->PrintAllInformation(false);
        }
    }
}

void Reader::load(string filename, set<int> &handle)
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
        gender = str;

        getline(fin, str);
        borrownum = stoi(str);

        if (borrownum > 0)
        {
            getline(fin, str);
            for (int i = 0; i < borrownum; i++)
            {
                getline(fin, str);
                handle.insert(stoi(str));
                getline(fin, str);
                getline(fin, str);
                getline(fin, str);
                getline(fin, str);
            }
        }
        fin.close();
    }
    else
        cout << "没有这个文件" << endl;
    return;
}

void Reader::save(string filename)
{
    ofstream fout(filename + to_string(id));
    fout << id << endl;
    fout << name << endl;
    fout << gender << endl;
    fout << borrownum << endl;
    if (borrownum > 0)
    {
        for (auto p = book.begin(); p != book.end(); p++)
        {
            shared_ptr<Book> tmp = (*p).lock();
            fout << endl;
            fout << tmp->getid() << endl;
            fout << tmp->getname() << endl;
            fout << tmp->getprice() << endl;
            fout << tmp->getauthor() << endl;
        }
    }
    fout.close();

    ofstream fout2(filename + "name/" + name);
    fout2 << id << endl;
    fout2.close();
}