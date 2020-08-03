#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Book;

class Reader
{
private:
    int id;
    string name;
    string gender;
    int borrownum;
    vector<weak_ptr<Book>> book;

public:
    Reader() : borrownum(0) {}

    ~Reader() {}

    int getid() { return id; }
    string getname() { return name; }
    string getgender() { return gender; }
    int getborrownum() { return borrownum; }
    vector<weak_ptr<Book>> &getbook() { return book; }
    void setid(int _id) { id = _id; }
    void setname(string _name) { name = _name; }
    void setgender(string _gender) { gender = _gender; }
    void addborrownum() { borrownum += 1; }
    void minusborrownum() { borrownum -= 1; }
    void addbook(shared_ptr<Book> &_book) { book.push_back(_book); }
    void minusbook(shared_ptr<Book> &_book);

    void PrintAllInformation(bool deep = true);

    void load(string filename, set<int> &handle);

    void save(string filename);
};