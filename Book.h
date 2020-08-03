#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Reader;

class Book
{
private:
    int id;
    string name;
    double price;
    string author;
    bool isfree;
    weak_ptr<Reader> reader;

public:
    Book() : isfree(true) {}

    ~Book() {}

    int getid() { return id; }
    string getname() { return name; }
    double getprice() { return price; }
    string getauthor() { return author; }
    bool getstatus() { return isfree; }
    shared_ptr<Reader> getreader() { return reader.lock(); }
    void setid(int _id) { id = _id; }
    void setname(string _name) { name = _name; }
    void setprice(double _price) { price = _price; }
    void setauthor(string _author) { author = _author; }
    void setstatus(bool _isfree) { isfree = _isfree; }
    void setreader(shared_ptr<Reader> &_reader) { reader = _reader; }
    void setnull() { reader.reset(); }

    void PrintAllInformation(bool deep = true);

    void load(string filename, int *handle);

    void save(string filename);
};