#include <iostream>
#include <map>
#include <string>
#include "Book.h"

class BookManager{
    private:
    map<int,Book*> BookMap;
    string BookRoute;

    int getBookId(){
        string name;
        cin>>name;
        //根据书名找到id
        int id=FindIdByName(name);
        return id;
    }

    int FindIdByName(string name){
        ifstream fin(BookRoute+"name/"+name);
        string idstr;
        fin.getline(idstr,128);
        return stoi(idstr);
    }

    void Addmap(int id){
        if(BookMap.find(id)!=BookMap.end())
        return;
        BookMap[id]=new Book();
        setBookByFile(BookMap[id],BookRoute+to_string(id));
    }

    void setBookByFile(Book* book,string filename){
        ifstream fin(filename);

        string str;
        fin.getline(str);
        book->setid(stoi(str));

        fin.getline(str);
        book->setname(str);

        fin.getline(str);
        book->getprice(stoi(str));

        fin.getline()
    }
    public:
    BookManager(){
        BookRoute="/root/study/library/book/";
    }

    ~BookManager(){
        SaveInfoAndClose();
    }

    string getBookRoute(){return BookRoute;}
    void setBookRoute(string route){BookRoute=route;}

    void AddBook(){
        Book* abook=new Book();
        
        abook->setid(getaid());

        string name;
        cout<<"请输入图书名称：";
        cin>>name;
        abook->setname(name);

        int price;
        cout<<"请输入图书单价：";
        cin>>price;
        //应该检查单价是否正确
        abook->setprice(price);

        string author;
        cout<<"请输入图书作者：";
        cin>>author;
        abook->setauthor(author);

        //save
    }

    void EditBook(){
        cout<<"请输入要更改的图书名称：";
        int id=getBookId();
        Addmap(id);

        while(true){
        cout<<"请输入要更改的图书信息："<<endl;
        cout<<"1、名称"<<endl;
        cout<<"2、单价"<<endl;
        cout<<"3、作者"<<endl;
        cout<<"提示：请输入相应的序号并按回车，输入q返回：";
        char option;
        cin>>option;
        switch(option){
            case "1":
                cout<<"请输入新名称：";
                string newname;
                cin>>newname;
                BookMap[id]->setname(newname);
                return;
            case "2":
                cout<<"请输入新单价：";
                int newprice;
                cin>>newprice;
                //应该检查单价是否正确
                BookMap[id]->setprice(newprice);
                return;
            case "3":
                cout<<"请输入新作者：";
                string newauthor;
                cin>>newauthor;
                BookMap[id]->setauthor(newauthor);
                return;
            case "q":
                return;
            default:
                cout<<"请输入正确的选项！"<<endl;
        }
        }
    }

    void SearchBook(){
        cout<<"请输入要查询的图书名称：";
        int id=getBookId();
        Addmap(id);

        while(true){
        cout<<"请输入要查询的图书信息："<<endl;
        cout<<"1、编号"<<endl;
        cout<<"2、单价"<<endl;
        cout<<"3、作者"<<endl;
        cout<<"提示：请输入相应的序号并按回车，输入q返回：";
        char option;
        cin>>option;
        switch(option){
            case "1":
                cout<<"图书的编号是："<<BookMap[id]->getid()<<endl;
                return;
            case "2":
                cout<<"图书的单价是："<<BookMap[id]->getprice()<<endl;
                return;
            case "3":
                cout<<"图书的作者是："<<BookMap[id]->getauthor()<<endl;
                return;
            case "q":
                return;
            default:
                cout<<"请输入正确的选项！"<<endl;
        }
        }
    }

    void DeleteBook(){
        cout<<"请输入要删除的图书名称：";
        int id=getBookId();
        //删除书的2个文件，如果map有id信息，mapid也要删掉
    }

    void ShowBookInformation(){
        cout<<"请输入要查看的图书名称：";
        int id=getBookId();
        Addmap(id);

        BookMap[id]->PrintAllInfo();
    }

    void ShowAllBorrowedBookInfo(){
        for(auto p=BookMap.begin();p!=BookMap.end();p++){
            if(p->second->isfree==false){
                cout<<p->second->name<<" 被 "<<p->second->reader->name<<" 借走了"<<endl;
            }
        }
    }

    void Borrow(Book* abook, Reader* areader){
        abook->setstatus(false);
        abook->setreader(areader);
    }

    void Return(Book* abook){
        abook->setstatus(true);
        abook->setreader(NULL);
    }

    Book* GetaBookByName(string name){
        int id=FindIdByName(name);
        Addmap(id);
        return BookMap[id];
    }
}