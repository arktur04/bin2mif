#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

std::vector<unsigned char> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    // read the data:
	std::vector<unsigned char> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

unsigned getWidth(unsigned size)
{
	return size / 4 + ((size % 4)? 1: 0);
}

int main(int argc, char *argv[])
{
	if(argc < 5)
	{
		std::cout << "������ ���� ���������: ���_��������_����� ���_���������_����� ������_�������_���������� ������_��������_����������" << std::endl;
		std::cout << "��������: out_file.v 11 8" << std::endl;
		return 0;
	}
	std::vector<unsigned char> inputFile = readFile(argv[1]);
	std::ofstream out(argv[2], std::ofstream::out);
	unsigned num = 0;
	unsigned inSize = atoi(argv[3]), outSize = atoi(argv[4]);
	unsigned inWidth = getWidth(inSize),
		depth = pow(2, inSize),
		outWidth = getWidth(outSize);
	out << "width=" << outSize << ";" << std::endl;
	out << "depth=" << depth << ";" << std::endl;
	out << "address_radix=hex;" << std::endl;
	out << "data_radix=hex;" << std::endl;
	out << "content begin" << std::endl;
	out.fill('0');
	for(auto ch:inputFile)
	{
		out << std::setw(inWidth) << std::hex << num++ << ": " << std::setw(outWidth) << std::right << std::hex << (int)ch << ";" << std::endl;
	}
	out << "end" << std::endl;
	out.close();
    return 0;
}
