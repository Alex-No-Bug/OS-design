// testinsert.cpp : 定义控制台应用程序的入口点。
//



#include<iostream>
#include<cstring>
using namespace std;

void insert_between_two(char* disk, unsigned int sta, unsigned int end, unsigned int &length, string context)
//*length = 1
{
	string temp1 = "";
	string temp2 = "";
	string result = "";

	int index = 0;
	while (index <= sta)
		temp1.push_back(disk[index++]);
	//此时等于换行
	while (index != end)
		index++;
	//此时等于end
	while (index != length)
		temp2.push_back(disk[index++]);
	result = temp1 + context + temp2;

	cout << "result" << result;
	const char* a = result.c_str();
    cout<<"a"<<a<<endl;

	strcpy(disk, a);
	length = result.size();
}
int main()
{
	char* s = "0\n1\n2\n3\n";
	string context = "hhhhhhhhhh";
	unsigned int length = 8;
	insert_between_two(s, 1, 3, length, context);
	cout << s << endl;

}

