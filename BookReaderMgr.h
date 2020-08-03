#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <cstdlib>
#include <memory>
#include "Reader.h"
#include "Book.h"
using namespace std;

class BookReaderMgr
{
private:
    bool HasShowBorrow;
    int bookid;
    map<int, shared_ptr<Reader>> ReaderMap;
    string ReaderRoute;
    map<int, shared_ptr<Book>> BookMap;
    string BookRoute;

    int getReaderId();
    int FindReaderIdByName(string name);
    void AddReadermap(int id);

    int getBookId();
    int FindBookIdByName(string name);
    void AddBookmap(int id);

public:
    BookReaderMgr() : HasShowBorrow(false), bookid(0)
    {
        //bookid应该从一个文件中读取，否则下次仍然从1开始编号图书
        ReaderRoute = "/root/study/library/reader/";
        BookRoute = "/root/study/library/book/";
    }
    ~BookReaderMgr()
    {
        //应该保存bookid
    }

    string getReaderRoute() { return ReaderRoute; }
    void setReaderRoute(string route) { ReaderRoute = route; }
    string getBookRoute() { return BookRoute; }
    void setBookRoute(string route) { BookRoute = route; }

    bool checkReaderid(int id);
    void AddReader();
    void EditReader();
    void SearchReader();
    void DeleteReader();
    void ShowReaderInformation();
    shared_ptr<Reader> GetaReaderByName(string name);

    void Borrow(shared_ptr<Book> abook, shared_ptr<Reader> areader);
    void Return(shared_ptr<Book> abook, shared_ptr<Reader> areader);

    int getaid();
    void AddBook();
    void EditBook();
    void SearchBook();
    void DeleteBook();
    void ShowBookInformation();
    void ShowAllBorrowedBookInfo();
    shared_ptr<Book> GetaBookByName(string name);

    void BorrowBook();
    void ReturnBook();
    void ShowBorrowInformation();
};