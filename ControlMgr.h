#include <iostream>
#include <memory>
#include "BookReaderMgr.h"
using namespace std;

class ControlMgr
{
private:
    unique_ptr<BookReaderMgr> brm;

public:
    ControlMgr()
    {
        brm = unique_ptr<BookReaderMgr>(new BookReaderMgr());
    }
    ~ControlMgr()
    {
    }

    void EnterOption1();
    void EnterOption21();
    void EnterOption22();
    void EnterOption23();
};