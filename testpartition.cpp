#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<stdlib.h>
class FileCB
{
public:
    int id;
    string name;
    unsigned long file_size;//文件内容的大小
    unsigned long all_size;//所有占的空间.
    vector<string> control;//权限控制
    string index_addr = "";//索引所在的地址
  //  Index index;
    string master;//主人的id
    /* 文件信息在块中存储的格式
    文件id 空格 文件名 空格 文件内容大小 空格 文件总大小
    空格 第一个用户的用户名 空格
    第一个用户名的权限 第二个用户的用户名 第二个用户名的权限
    空格 | 索引所在的地址 空格 主人的用户名 .(终结符)*/

    void init(string addr);
    void print()
    {
        cout<<id<<endl<<name <<endl<<file_size<<endl<<
        all_size<<endl;
        for(int i=0;i<control.size();i++)
        {
            cout<<control[i]<<endl;
        }
        cout<<index_addr<<endl<<master<<endl;
    }
};
void FileCB::init(string addr)
{
    int i=0;
    string id_s="";
    while(addr[i]!=' ')
    {
       id_s.push_back(addr[i++]);
    }
    id=atoi(id_s.c_str());
    cout<<"id:"<<id<<endl;
    i++;

    while(addr[i]!=' ')
    {
      name.push_back(addr[i++]);
    }
    cout<<"name"<<name<<endl;
    i++;
    string file_s="";
    string all_s="";
    while(addr[i]!=' ')
    {
        file_s.push_back(addr[i++]);
    }
    file_size=atol(file_s.c_str());
    cout<<"file_size"<<file_size<<endl;
    i++;
    while(addr[i]!=' ')
    {
        all_s.push_back(addr[i++]);
    }
    i++;//此时跳过空格
    while(addr[i]!='|')
    {
       string temp="";
       int num=0;
       while(num!=2)
       {
           if(addr[i]==' ')num++;
           temp.push_back(addr[i]);
           i++;
       }
       cout<<"control"<<temp<<endl;//122 C:/a.txt 2311 1111 wd write sunlinag read
       control.push_back(temp);
    }
    i=i+2;
    while(addr[i]!=' ')
    {
        index_addr.push_back(addr[i++]);
    }
    i++;
    while(addr[i]!='.')
    {
        master.push_back(addr[i++]);
    }
}
int main()
{
    /* /* 文件信息在块中存储的格式
    文件id 空格 文件名 空格 文件内容大小 空格 文件总大小
    空格  第一个用户的用户名 空格
    第一个用户名的权限 第二个用户的用户名 第二个用户名的权限
    空格 | 索引所在的地址 空格 主人的用户名 .(终结符)*/
    FileCB f;
    f.init("122 C:/a.txt 2311 1111 wd write sunlinag read | index_address zhuqiang.");
    f.print();
}
