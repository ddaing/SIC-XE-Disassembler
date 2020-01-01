#pragma once
#include <vector>
#include <string>
#include <bitset>

using namespace std;

//명령어 구조체 command와 포맷 저장
class InstructNode {
public:
	string command;
	string format;

	InstructNode(string command, string format) {
		this->command = command;
		this->format = format;
	}
};

//헤더 구조체
typedef struct {
	string programName;
	string startAddress;
	string programLength;
} headerRecord;

//엔드 구조체
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

//텍스트 구조체
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