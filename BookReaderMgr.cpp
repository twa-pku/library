#include "BookReaderMgr.h"
using namespace std;

int BookReaderMgr::getReaderId()
{
    string name;
    cin >> name;
    int id = FindReaderIdByName(name);
    return id;
}

int BookReaderMgr::FindReaderIdByName(string name)
{
    ifstream fin(ReaderRoute + "name/" + name);
    if (fin.good())
    {
        string idstr;
        getline(fin, idstr);
        fin.close();
        return stoi(idstr);
    }
    else
    {
        cout << "打开文件发生错误。" << endl;
        return -1;
    }
}

void BookReaderMgr::AddReadermap(int id)
{
    if (ReaderMap.find(id) != ReaderMap.end())
        return;
    ReaderMap[id] = make_shared<Reader>();
    set<int> handle;
    ReaderMap[id]->load(ReaderRoute + to_string(id), handle);
    for (auto p = handle.begin(); p != handle.end(); p++)
    {
        AddBookmap(*p);
        ReaderMap[id]->addbook(BookMap[*p]);
    }
}

int BookReaderMgr::getBookId()
{
    string name;
    cin >> name;
    //根据书名找到id
    int id = FindBookIdByName(name);
    return id;
}

int BookReaderMgr::FindBookIdByName(string name)
{
    ifstream fin(BookRoute + "name/" + name);
    if (fin.good())
    {
        string idstr;
        getline(fin, idstr);
        fin.close();
        return stoi(idstr);
    }
    else
    {
        cout << "打开文件发生错误。" << endl;
        return -1;
    }
}

void BookReaderMgr::AddBookmap(int id)
{
    if (BookMap.find(id) != BookMap.end())
        return;
    BookMap[id] = make_shared<Book>();
    int handleid;
    BookMap[id]->load(BookRoute + to_string(id), &handleid);
    AddReadermap(handleid);
    BookMap[id]->setreader(ReaderMap[handleid]);
}

bool BookReaderMgr::checkReaderid(int id)
{
    ifstream fin(ReaderRoute + to_string(id));
    if (fin.good())
        return false;
    return true;
}

void BookReaderMgr::AddReader()
{
    shared_ptr<Reader> aReader = make_shared<Reader>();

    string name;
    cout << "请输入借书人姓名：";
    cin >> name;
    aReader->setname(name);
    //这里应该检查姓名有没有重

    int id;
    cout << "请输入借书人学号：";
    cin >> id;
    //应该检查学号是否正确
    if (checkReaderid(id) == false)
    {
        cout << "该学号已经注册过了" << endl;
        return;
    }
    aReader->setid(id);

    string gender;
    cout << "请输入借书人性别：";
    cin >> gender;
    aReader->setgender(gender);

    ReaderMap[id] = aReader;
    //save
    aReader->save(ReaderRoute);
}

void BookReaderMgr::EditReader()
{
    cout << "请输入要更改的借书人姓名：";
    int id = getReaderId();
    if (id == -1)
    {
        cout << "姓名不存在。" << endl;
        return;
    }
    AddReadermap(id);

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
        case '1':
        {
            cout << "请输入新姓名：";
            string newname;
            cin >> newname;
            ReaderMap[id]->setname(newname);
            ReaderMap[id]->save(ReaderRoute);
            //这里应该同时更改姓名的索引文件
            return;
        }
        case '2':
        {
            cout << "请输入新学号：";
            int newid;
            cin >> newid;
            //应该检查学号是否正确
            ReaderMap[id]->setid(newid);
            ReaderMap[id]->save(ReaderRoute);
            return;
        }
        case '3':
        {
            cout << "请输入新性别：";
            string newgender;
            cin >> newgender;
            ReaderMap[id]->setgender(newgender);
            ReaderMap[id]->save(ReaderRoute);
            return;
        }
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void BookReaderMgr::SearchReader()
{
    cout << "请输入要查询的借书人姓名：";
    int id = getReaderId();
    if (id == -1)
    {
        cout << "姓名不存在。" << endl;
        return;
    }
    AddReadermap(id);

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
        case '1':
            cout << "借书人的姓名是：" << ReaderMap[id]->getname() << endl;
            return;
        case '2':
            cout << "借书人的学号是：" << ReaderMap[id]->getid() << endl;
            return;
        case '3':
            cout << "借书人的性别是：" << ReaderMap[id]->getgender() << endl;
            return;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void BookReaderMgr::DeleteReader()
{
    cout << "请输入要删除的借书人姓名：";
    int id = getReaderId();
    if (id == -1)
    {
        cout << "姓名不存在。" << endl;
        return;
    }
    AddReadermap(id);

    //是否还有书没还？
    if (ReaderMap[id]->getborrownum() > 0)
    {
        cout << "该借书人还有书未归还" << endl;
        return;
    }
    //删除人的2个文件，如果map有id信息，mapid也要删掉
    string name = ReaderMap[id]->getname();
    system(("rm -rf " + ReaderRoute + to_string(id)).c_str());
    system(("rm -rf " + ReaderRoute + "name/" + name).c_str());
    ReaderMap.erase(id);
    cout << "已删除借书人" << endl;
}

void BookReaderMgr::ShowReaderInformation()
{
    cout << "请输入要查看的借书人姓名：";
    int id = getReaderId();
    if (id == -1)
    {
        cout << "姓名不存在。" << endl;
        return;
    }
    AddReadermap(id);

    ReaderMap[id]->PrintAllInformation();
}

void BookReaderMgr::Borrow(shared_ptr<Book> abook, shared_ptr<Reader> areader)
{
    areader->addborrownum();
    areader->addbook(abook);
    areader->save(ReaderRoute);

    abook->setstatus(false);
    abook->setreader(areader);
    abook->save(BookRoute);

    cout << "借书成功" << endl;
}

void BookReaderMgr::Return(shared_ptr<Book> abook, shared_ptr<Reader> areader)
{
    areader->minusborrownum();
    areader->minusbook(abook);
    areader->save(ReaderRoute);

    abook->setstatus(true);
    abook->setnull();
    abook->save(BookRoute);

    cout << "还书成功" << endl;
}

shared_ptr<Reader> BookReaderMgr::GetaReaderByName(string name)
{
    int id = FindReaderIdByName(name);
    if (id == -1)
    {
        return NULL;
    }
    AddReadermap(id);
    return ReaderMap[id];
}

int BookReaderMgr::getaid()
{
    bookid += 1;
    return bookid;
}

void BookReaderMgr::AddBook()
{
    shared_ptr<Book> abook = make_shared<Book>();

    int id = getaid();
    abook->setid(id);

    string name;
    cout << "请输入图书名称：";
    cin >> name;
    abook->setname(name);
    //应该检查图书名称是否重了
    //这里设计得不合理，应该允许图书重名。

    double price;
    cout << "请输入图书单价：";
    cin >> price;
    //应该检查单价是否正确
    abook->setprice(price);

    string author;
    cout << "请输入图书作者：";
    cin >> author;
    abook->setauthor(author);

    BookMap[id] = abook;
    //save
    abook->save(BookRoute);
}

void BookReaderMgr::EditBook()
{
    cout << "请输入要更改的图书名称：";
    int id = getBookId();
    if (id == -1)
    {
        cout << "这本书不存在。" << endl;
        return;
    }
    AddBookmap(id);

    while (true)
    {
        cout << "请输入要更改的图书信息：" << endl;
        cout << "1、名称" << endl;
        cout << "2、单价" << endl;
        cout << "3、作者" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回：";
        char option;
        cin >> option;
        switch (option)
        {
        case '1':
        {
            cout << "请输入新名称：";
            string newname;
            cin >> newname;
            BookMap[id]->setname(newname);
            BookMap[id]->save(BookRoute);
            //这里应该要改一下书名的索引文件
            return;
        }
        case '2':
        {
            cout << "请输入新单价：";
            int newprice;
            cin >> newprice;
            //应该检查单价是否正确
            BookMap[id]->setprice(newprice);
            BookMap[id]->save(BookRoute);
            return;
        }
        case '3':
        {
            cout << "请输入新作者：";
            string newauthor;
            cin >> newauthor;
            BookMap[id]->setauthor(newauthor);
            BookMap[id]->save(BookRoute);
            return;
        }
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void BookReaderMgr::SearchBook()
{
    cout << "请输入要查询的图书名称：";
    int id = getBookId();
    if (id == -1)
    {
        cout << "这本书不存在。" << endl;
        return;
    }
    AddBookmap(id);

    while (true)
    {
        cout << "请输入要查询的图书信息：" << endl;
        cout << "1、编号" << endl;
        cout << "2、单价" << endl;
        cout << "3、作者" << endl;
        cout << "4、借书人" << endl;
        cout << "提示：请输入相应的序号并按回车，输入q返回：";
        char option;
        cin >> option;
        switch (option)
        {
        case '1':
            cout << "图书的编号是：" << BookMap[id]->getid() << endl;
            return;
        case '2':
            cout << "图书的单价是：" << BookMap[id]->getprice() << endl;
            return;
        case '3':
            cout << "图书的作者是：" << BookMap[id]->getauthor() << endl;
            return;
        case '4':
            if (BookMap[id]->getstatus() == true)
            {
                cout << "图书未被借出。" << endl;
                return;
            }
            cout << "图书的借书人是：" << BookMap[id]->getreader()->getname() << endl;
            return;
        case 'q':
            return;
        default:
            cout << "请输入正确的选项！" << endl;
        }
    }
}

void BookReaderMgr::DeleteBook()
{
    cout << "请输入要删除的图书名称：";
    int id = getBookId();
    if (id == -1)
    {
        cout << "这本书不存在。" << endl;
        return;
    }
    AddBookmap(id);

    //还有人借这本书吗？
    if (BookMap[id]->getstatus() == false)
    {
        cout << "这本书还有人借，不能删除。" << endl;
        return;
    }
    //删除书的2个文件，如果map有id信息，mapid也要删掉
    string name = BookMap[id]->getname();
    system(("rm -rf " + BookRoute + to_string(id)).c_str());
    system(("rm -rf " + BookRoute + "name/" + name).c_str());
    BookMap.erase(id);
    cout << "已删除这本书" << endl;
}

void BookReaderMgr::ShowBookInformation()
{
    cout << "请输入要查看的图书名称：";
    int id = getBookId();
    if (id == -1)
    {
        cout << "这本书不存在。" << endl;
        return;
    }
    AddBookmap(id);

    BookMap[id]->PrintAllInformation();
}

void BookReaderMgr::ShowAllBorrowedBookInfo()
{
    for (auto p = BookMap.begin(); p != BookMap.end(); p++)
    {
        if (p->second->getstatus() == false)
        {
            cout << p->second->getname() << " 被 " << p->second->getreader()->getname() << " 借走了" << endl;
        }
    }
}

shared_ptr<Book> BookReaderMgr::GetaBookByName(string name)
{
    int id = FindBookIdByName(name);
    if (id == -1)
    {
        return NULL;
    }
    AddBookmap(id);
    return BookMap[id];
}

void BookReaderMgr::BorrowBook()
{
    //没有借书人，借书人已经借了这本书，没有这本书，这本书已经被借走了
    cout << "请输入借书人" << endl;
    string reader;
    cin >> reader;
    //检测输入是否合法，获得指针

    shared_ptr<Reader> areader = GetaReaderByName(reader);
    if (areader == NULL)
    {
        cout << "借书人不存在！" << endl;
        return;
    }

    cout << "请输入书名" << endl;
    string book;
    cin >> book;
    //检测输入是否合法，获得指针

    shared_ptr<Book> abook = GetaBookByName(book);
    if (abook == NULL)
    {
        cout << "书不存在！" << endl;
        return;
    }

    if (abook->getstatus() == false)
    {
        cout << "这本书已经被借走了！" << endl;
        return;
    }

    Borrow(abook, areader);
}

void BookReaderMgr::ReturnBook()
{
    cout << "请输入书名" << endl;
    string book;
    cin >> book;
    //检测输入是否合法，获得指针

    shared_ptr<Book> abook = GetaBookByName(book);
    if (abook == NULL)
    {
        cout << "书不存在！" << endl;
        return;
    }

    if (abook->getstatus() == true)
    {
        cout << "这本书没有被借走！" << endl;
        return;
    }

    shared_ptr<Reader> areader = abook->getreader();
    Return(abook, areader);
}

void BookReaderMgr::ShowBorrowInformation()
{
    if (HasShowBorrow == false)
    {
        //导入所有书
        HasShowBorrow = true;
    }
    ShowAllBorrowedBookInfo();
}