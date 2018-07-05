#pragma once
#include <vector>
#include <string>
#include "config.h"
using namespace std;
/* 地址的格式
disk(3位)+扇区+磁盘块 */

class Index
{
public:
    string addr[10];
    int endflag[10] = {0};
    int offset[10] = {0};//块内长度
    /* 索引信息在块中存储的格式
    地址1 空格 地址2 空格 地址3... 空格 flag0 空格 flag1 空格 flag2 ... 空格 长度1 空格... 空格 */

    void init(string addr);
};

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

void Index::init(string addr)
{
    long int addr_dex = atol(addr.c_str());
    int offset = addr_dex % 1000 + 1;//得到最后三位的扇区内偏移地址
    int disk = addr_dex / 100000;//得到磁盘号
    string sector_str = "";
    sector_str.push_back(addr[3]);
    sector_str.push_back(addr[4]);
    sector_str.push_back('\0');
    int sector = atoi(sector_str.c_str());
    //地址转换

    string input = "";
    if(disk == C)
    {
        ifstream file("C:\\Users\\Mark.Wen\\Desktop\\OS_Design\\RunningOS\\Debug\\C.txt");
        for(int i = 0; i < offset + sector * BLOCK_GROUP_SIZE; i++) 
        {
            input = "";
            getline(file, input);
        }
        file.close();
    }
    if(disk == D)
    {
        ifstream file("C:\\Users\\Mark.Wen\\Desktop\\OS_Design\\RunningOS\\Debug\\D.txt");
        for(int i = 0; i < offset + sector * BLOCK_GROUP_SIZE; i++)
        {
            input = "";
            getline(file, input);
        }
        file.close();
    }
    if(disk == E)
    {
        ifstream file("C:\\Users\\Mark.Wen\\Desktop\\OS_Design\\RunningOS\\Debug\\E.txt");
        for(int i = 0; i < offset + sector * BLOCK_GROUP_SIZE; i++)
        {
            input = "";
            getline(file, input);
        }
        file.close();
    }
    input.push_back('\0');
    //寻址工作完成

    int cur = 0, count = 0;
    string temp = "";
    while(count < 10)
    {
        while(input[cur] != ' ')
        {
            Index::addr[count].push_back(input[cur]);
            cur++;
        }
        cur++;
        Index::addr[count].push_back('\0');
        count++;
    }
    //得到所有的索引地址内容

    count = 0;
    while(count < 10)
    {
        while(input[cur] != ' ')
        {
            temp.push_back(input[cur]);
            cur++;
        }
        cur++;
        temp.push_back('\0');
        endflag[count] = atoi(temp.c_str());
        temp = "";
        count++;
    }
    //得到endflag数组

    count = 0;
    while(count < 10)
    {
        while(input[cur] != ' ')
        {
            temp.push_back(input[cur]);
            cur++;
        }
        cur++;
        temp.push_back('\0');
        Index::offset[count] = atoi(temp.c_str());
        temp = "";
        count++;
    }
    //得到偏移地址
}
