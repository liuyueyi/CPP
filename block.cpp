#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define KB_4 4096
#define KB_8 8192
#define KB_16 16384
#define KB_32 32768
#define KB_64 65536L
#define KB_128  131072L
#define KB_256 262144L
#define KB_512 524288L
#define MB_1 1048576L
#define MB_2 2097152L
#define MB_4 4194304L

using namespace std;

string int_to_str(int i)
{
	stringstream ss;
	ss << i ;
	return ss.str();
}

bool write_file(char * block, int length, const string & filename)
{
	ofstream ofs(filename.c_str());
	if(!ofs.is_open())
	{
		cout << "Failed to open the file!" << endl;
		return false;
	}
	
	ofs.write(block, length);

	ofs.close();
	return true;
}

void test()
{
	
	const int size = MB_2;
	ifstream ifs("1GB");
	if(!ifs.is_open())
	{
		cout << "Failed to open the file!" << endl;
		return ;
	}

	string block_id = "";
	string head = "2MB/";
	
	char block[size];
	
	int i = 1;
	do
	{	
		block_id = head + int_to_str(i++);
		if(ifs.read(block, size) == 0)
			break;
		
		if(!write_file(block, size, block_id))
		{
			cout << "error!" << endl;
			break;
		}
	}while(!ifs.eof());
	ifs.close();
	cout << "over!" << endl;
}

int main()
{
	const int size[] = {KB_4, KB_8, KB_16, KB_32, KB_64, KB_128, KB_256, KB_512, MB_1};
	string head[] = {"4KB/","8KB/","16KB/","32KB/","64KB/","128KB/","256KB/","512KB/","1MB/"};
	
	for(int n = 0; n < 9; n++)
	{
		ifstream ifs("1GB");
		if(!ifs.is_open())
		{
			cout << "Failed to open the file!" << endl;
			return -1;
		}

		string block_id = "";
	
		char block[size[n]];
	
		int i = 1;
		do
		{	
			block_id = head[n] + int_to_str(i++);
			if(ifs.read(block, size[n]) == 0)
				break;
		
			if(!write_file(block, size[n], block_id))
			{
				cout << "error!" << endl;
				break;
			}
		}while(!ifs.eof());
		ifs.close();
		cout << "over!" << endl;
	}
	
	
	
	return 0;
}
