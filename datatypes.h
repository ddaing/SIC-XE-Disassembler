#pragma once
#include <vector>
#include <string>
#include <bitset>

using namespace std;

//��ɾ� ����ü command�� ���� ����
class InstructNode {
public:
	string command;
	string format;

	InstructNode(string command, string format) {
		this->command = command;
		this->format = format;
	}
};

//��� ����ü
typedef struct {
	string programName;
	string startAddress;
	string programLength;
} headerRecord;

//���� ����ü
typedef struct {
	string firstExecAddress;
} endRecord;


typedef struct {
	string rawString;
	int    format;
	int    length;
	string opCode;
	string mnemonic;
	int    n;
	int    i;
	int    x;
	int    b;
	int    p;
	int    e;
	string register1;
	string register2;
	string disp;
	string byte;
} instruction;

//�ؽ�Ʈ ����ü
typedef struct {
	string               startAddress;
	string               recordLength;
	vector<instruction>  instructions;
} textRecord;

typedef struct {
	//headerRecord     headerRecord;
	::headerRecord     headerRecord;
	vector<textRecord> textRecords;
	//endRecord        endRecord;
	::endRecord        endRecord;
} objectFileData;

// symtab file data
typedef struct {
	string symbol;
	string value;
	string flags;
	string convertedValue;
} symbolData;

typedef struct {
	vector<symbolData> symbols;

} symtabData;