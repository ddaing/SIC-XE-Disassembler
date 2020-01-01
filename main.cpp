#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include "datatypes.h"

string basevalue;

//헤더 출력
void printingHeader(headerRecord headerRecord, string filename) {
	string file = filename + ".asm";
	ofstream myFile(file, ios_base::app);
	//LOC
	myFile << "LOC";
	myFile << "    ";
	//Label
	myFile << left << setw(6) << setfill(' ') << " LABEL";
	myFile << "   ";
	//OPCODE
	myFile << " OPCODE";
	myFile << "   ";
	//OPERAND
	myFile << left << setw(8) << setfill(' ') << "OPERAND";
	myFile << "  ";
	//objectcode
	myFile << "ObjectCode";
	myFile << endl;
	//LOC
	myFile << headerRecord.startAddress.substr(2, 4);
	myFile << "    ";
	//Label
	myFile << left << setw(6) << setfill(' ') << headerRecord.programName;
	myFile << "   ";
	//OPCODE
	myFile << "START ";
	myFile << "   ";
	//objectcode
	myFile << 0;
	myFile << "  ";
	myFile << endl;
}
//텍스트 출력
void printingText(string memory, string label, string instruction, string operand, string rawString, bool format4, string filename) {
	string file = filename + ".asm";
	ofstream myFile(file, ios_base::app);
	//LOC
	myFile << left << setw(4) << setfill(' ') << memory;
	myFile << "    ";
	//Label
	myFile << left << setw(6) << setfill(' ') << label;
	myFile << "   ";
	//instructions
	myFile << left << setw(6) << setfill(' ') << instruction;
	myFile << "   ";
	//paramter
	myFile << left << setw(8) << setfill(' ') << operand;
	myFile << "  ";
	//objectcode
	myFile << rawString << endl;
}
//엔드 출력
void printingEnd(string endAddress, string filename) {
	string file = filename + ".asm";
	ofstream myFile(file, ios_base::app);
	myFile << "                 ";
	myFile << "END   ";
	myFile << "   ";
	//endaddress
	myFile << left << setw(24) << setfill(' ') << endAddress;
	myFile << "  ";
	//objectcode
	myFile << endl;
}
//binarytohex
string binaryToHex(string binary) {
	vector<string> bytes;
	string hexVal = "";

	for (int i = 0; i < binary.length(); i += 4) {
		bytes.push_back(binary.substr(i, 4));
	}

	for (auto const& byte : bytes) {

		if (byte.compare("0000") == 0)
			hexVal.append("0");

		else if (byte.compare("0001") == 0)
			hexVal.append("1");

		else if (byte.compare("0010") == 0)
			hexVal.append("2");

		else if (byte.compare("0011") == 0)
			hexVal.append("3");

		else if (byte.compare("0100") == 0)
			hexVal.append("4");

		else if (byte.compare("0101") == 0)
			hexVal.append("5");

		else if (byte.compare("0110") == 0)
			hexVal.append("6");

		else if (byte.compare("0111") == 0)
			hexVal.append("7");

		else if (byte.compare("1000") == 0)
			hexVal.append("8");

		else if (byte.compare("1001") == 0)
			hexVal.append("9");

		else if (byte.compare("1010") == 0)
			hexVal.append("A");

		else if (byte.compare("1011") == 0)
			hexVal.append("B");

		else if (byte.compare("1100") == 0)
			hexVal.append("C");

		else if (byte.compare("1101") == 0)
			hexVal.append("D");

		else if (byte.compare("1110") == 0)
			hexVal.append("E");

		else if (byte.compare("1111") == 0)
			hexVal.append("F");
	}
	return hexVal;
}
//hextobinary
string hexToBinary(string hexValue) {
	long int i = 0;
	string bin = "";

	while (hexValue[i]) {

		switch (hexValue[i]) {
		case '0':
			bin.append("0000");
			break;
		case '1':
			bin.append("0001");
			break;
		case '2':
			bin.append("0010");
			break;
		case '3':
			bin.append("0011");
			break;
		case '4':
			bin.append("0100");
			break;
		case '5':
			bin.append("0101");
			break;
		case '6':
			bin.append("0110");
			break;
		case '7':
			bin.append("0111");
			break;
		case '8':
			bin.append("1000");
			break;
		case '9':
			bin.append("1001");
			break;
		case 'A':
			bin.append("1010");
			break;
		case 'B':
			bin.append("1011");
			break;
		case 'C':
			bin.append("1100");
			break;
		case 'D':
			bin.append("1101");
			break;
		case 'E':
			bin.append("1110");
			break;
		case 'F':
			bin.append("1111");
			break;
		default:
			cout << "error" << hexValue[i];
		}
		i++;
	}
	return bin;
}
//inlist에 삽입 
void insertToMap(map<string, InstructNode>* inList, string opCode, InstructNode node) {
	inList->insert(map<string, InstructNode>::value_type(opCode, node));
}
//전체 명령어 리스트 1,2,3/4(X)라 표현
void build_list(map<string, InstructNode>* inList) {
	insertToMap(inList, "18", InstructNode("ADD", "X"));
	insertToMap(inList, "58", InstructNode("ADDF", "X"));
	insertToMap(inList, "90", InstructNode("ADDR", "2"));
	insertToMap(inList, "40", InstructNode("AND", "X"));
	insertToMap(inList, "B4", InstructNode("CLEAR", "2"));
	insertToMap(inList, "28", InstructNode("COMP", "X"));
	insertToMap(inList, "88", InstructNode("COMPF", "X"));
	insertToMap(inList, "A0", InstructNode("COMPR", "2"));
	insertToMap(inList, "24", InstructNode("DIV", "X"));
	insertToMap(inList, "64", InstructNode("DIVF", "X"));
	insertToMap(inList, "9C", InstructNode("DIVR", "2"));
	insertToMap(inList, "C4", InstructNode("FIX", "1"));
	insertToMap(inList, "C0", InstructNode("FLOAT", "1"));
	insertToMap(inList, "F4", InstructNode("HIO", "1"));
	insertToMap(inList, "3C", InstructNode("J", "X"));
	insertToMap(inList, "30", InstructNode("JEQ", "X"));
	insertToMap(inList, "34", InstructNode("JGT", "X"));
	insertToMap(inList, "38", InstructNode("JLT", "X"));
	insertToMap(inList, "48", InstructNode("JSUB", "X"));
	insertToMap(inList, "00", InstructNode("LDA", "X"));
	insertToMap(inList, "68", InstructNode("LDB", "X"));
	insertToMap(inList, "50", InstructNode("LDCH", "X"));
	insertToMap(inList, "70", InstructNode("LDF", "X"));
	insertToMap(inList, "08", InstructNode("LDL", "X"));
	insertToMap(inList, "6C", InstructNode("LDS", "X"));
	insertToMap(inList, "74", InstructNode("LDT", "X"));
	insertToMap(inList, "04", InstructNode("LDX", "X"));
	insertToMap(inList, "D0", InstructNode("LPS", "X"));
	insertToMap(inList, "20", InstructNode("MUL", "X"));
	insertToMap(inList, "60", InstructNode("MULF", "X"));
	insertToMap(inList, "98", InstructNode("MULR", "2"));
	insertToMap(inList, "C8", InstructNode("NORM", "1"));
	insertToMap(inList, "44", InstructNode("OR", "X"));
	insertToMap(inList, "D8", InstructNode("RD", "X"));
	insertToMap(inList, "AC", InstructNode("RMO", "2"));
	insertToMap(inList, "4C", InstructNode("RSUB", "X"));
	insertToMap(inList, "A4", InstructNode("SHIFTL", "2"));
	insertToMap(inList, "A8", InstructNode("SHIFTR", "2"));
	insertToMap(inList, "F0", InstructNode("SIO", "1"));
	insertToMap(inList, "EC", InstructNode("SSK", "X"));
	insertToMap(inList, "0C", InstructNode("STA", "X"));
	insertToMap(inList, "78", InstructNode("STB", "X"));
	insertToMap(inList, "54", InstructNode("STCH", "X"));
	insertToMap(inList, "80", InstructNode("STF", "X"));
	insertToMap(inList, "D4", InstructNode("STI", "X"));
	insertToMap(inList, "14", InstructNode("STL", "X"));
	insertToMap(inList, "7C", InstructNode("STS", "X"));
	insertToMap(inList, "E8", InstructNode("STSW", "X"));
	insertToMap(inList, "84", InstructNode("STT", "X"));
	insertToMap(inList, "10", InstructNode("STX", "X"));
	insertToMap(inList, "1C", InstructNode("SUB", "X"));
	insertToMap(inList, "5C", InstructNode("SUBF", "X"));
	insertToMap(inList, "94", InstructNode("SUBR", "2"));
	insertToMap(inList, "B0", InstructNode("SVC", "2"));
	insertToMap(inList, "E0", InstructNode("TD", "X"));
	insertToMap(inList, "F8", InstructNode("TIO", "1"));
	insertToMap(inList, "2C", InstructNode("TIX", "X"));
	insertToMap(inList, "B8", InstructNode("TIXR", "2"));
	insertToMap(inList, "DC", InstructNode("WD", "X"));
}
//opcode -> 명령어
string getMnemonicByOpCode(string opCode) {
	map<string, InstructNode> inList;
	build_list(&inList);
	map<string, InstructNode>::iterator it = inList.find(opCode.c_str());
	if (it != inList.end()) {
		return it->second.command;
	}
}
//opcode-> format
string getFormatByOpCode(string opCode) {
	map<string, InstructNode> inList;
	build_list(&inList);
	map<string, InstructNode>::iterator it = inList.find(opCode.c_str());
	if (it != inList.end()) {
		return it->second.format;
	}
}
//포맷3,4에서 opcode 
string getOpCode(string opCodeByte) {
	string binValue = hexToBinary(opCodeByte);
	string opCodeBinary = binValue.substr(0, binValue.length() - 2);
	opCodeBinary.push_back('0');
	opCodeBinary.push_back('0');
	return binaryToHex(opCodeBinary);
}
//symtab을 입력 받을 때 빈 공간을 구분함
vector<string> splitString(string str) {
	vector<string> strings;
	string s = "";

	for (int i = 0; i < str.length(); ++i) {
		if (isspace(str.at(i))) {
			if (!s.empty()) {
				strings.push_back(s);
				s = "";
			}
		}
		else {
			s += str.at(i);
		}
	}
	strings.push_back(s);
	return strings;
}

//파일을 읽어오는 함수 
vector<string> getFileLines(string fileName) {
	vector<string> lines;
	ifstream in(fileName.c_str());// char*로 변환시켜서 파일 입력 받음 

	string line;
	while (getline(in, line)) {
		lines.push_back(line);//한줄씩 받아와서 lines에 넣어줌.
	}

	in.close();//파일 닫기
	return lines;
}
//
vector<instruction> getInstructions(string rawString, symtabData symtabData, string startAddress) {
	vector<instruction> instructions;
	int LOC = (int)strtol(startAddress.c_str(), NULL, 16);
	while (rawString.length()) {
		instruction instruct;
		bool findByte = false;
		for (int k = 0; k < symtabData.symbols.size(); k++) {
			string targetSymbolValue = symtabData.symbols.at(k).flags;
			//flag도 비교하고 value도 비교해야함 
			int symLOC = (int)strtol(symtabData.symbols.at(k).value.c_str(), NULL, 16);
			if (stoi(targetSymbolValue) != 0 && LOC == symLOC) {
				findByte = true;
				instruct.opCode = "";
				instruct.mnemonic = "BYTE";
				instruct.length = stoi(targetSymbolValue) * 2;
				instruct.rawString = rawString.substr(0, instruct.length);
				instruct.format = stoi(targetSymbolValue);
				instruct.n = 0;
				instruct.i = 0;
				instruct.x = 0;
				instruct.b = 0;
				instruct.p = 0;
				instruct.e = 0;
				instructions.push_back(instruct);
				rawString = rawString.substr(instruct.length);
				LOC += stoi(targetSymbolValue);
				break;
			}
		}
		if (findByte) continue;
		string rawInstructString = "";
		string opCode = rawString.substr(0, 2);
		opCode = getOpCode(opCode); //2바이트에서 뒤에 두 비트를 00으로 만듬. 
		string format = getFormatByOpCode(opCode);

		//포맷 분류
		if (format != "X" && stoi(format) == 2) {//  포맷 2는 4바이트 사용 
			rawInstructString = rawString.substr(0, 4);
			instruct.register1 = rawInstructString.substr(2, 1);
			instruct.register2 = rawInstructString.substr(3, 1);
		}
		else {
			string NIXBPE = (hexToBinary(rawString.substr(1, 1)) + hexToBinary(rawString.substr(2, 1))).substr(2, 6);//opni/xbpe/ n부터 e까지 복사
			instruct.n = stoi(NIXBPE.substr(0, 1));
			instruct.i = stoi(NIXBPE.substr(1, 1));
			instruct.x = stoi(NIXBPE.substr(2, 1));
			instruct.b = stoi(NIXBPE.substr(3, 1));
			instruct.p = stoi(NIXBPE.substr(4, 1));
			instruct.e = stoi(NIXBPE.substr(5, 1));

			int isFormat3 = !instruct.e;//e가 0이면 포맷 3 1이면 포맷 4
			rawInstructString = isFormat3 ? rawString.substr(0, 6) : rawString.substr(0, 8);//포맷 3이면 6바이트, 포맷4이면 8바이트 복사
			format = isFormat3 ? "3" : "4";
			instruct.disp = isFormat3 ? rawInstructString.substr(3, 3) : rawInstructString.substr(3, 5);
		}


		int numFormat = stoi(format);
		string mnemonic = getMnemonicByOpCode(opCode);
		int length = numFormat * 2;

		instruct.opCode = opCode;
		instruct.format = numFormat;
		instruct.mnemonic = mnemonic;
		instruct.length = length;
		instruct.rawString = rawInstructString;
		instructions.push_back(instruct);
		rawString = rawString.substr(instruct.length);
		LOC += instruct.format;
	}
	return instructions;
}
//오브젝트파일읽기
objectFileData getObjectFileData(string fileName, symtabData symtab) {

	vector<string> objectFileLines = getFileLines(fileName);//오브젝트 파일의 모든 내용 읽기 
	objectFileData objectFileData;//object파일 내용을 저장할 구조체 생성

	headerRecord headerRecord; // 헤더저장
	vector<textRecord> textRecords; // 텍스트 저장
	endRecord endRecord; //end 저장 
	string headerLine = objectFileLines.front();//오브젝트 파일 첫줄인 헤더를 받음 
	//헤더 포맷 저장
	headerRecord.programName = headerLine.substr(1, 6);
	headerRecord.startAddress = headerLine.substr(7, 6);
	headerRecord.programLength = headerLine.substr(13, 6);

	//엔드 포맷 저장 
	string endLine = objectFileLines.back();//오브젝트 파일 마지막 줄인 엔드를 받음 
	endRecord.firstExecAddress = endLine.substr(1, 6);

	//텍스트 포맷 저장 
	for (auto const& line : objectFileLines) {
		if (line.front() == 'T') {
			textRecord textRecord;
			textRecord.startAddress = line.substr(1, 6);
			textRecord.recordLength = line.substr(7, 2);
			vector<instruction> instructions;
			string instructsRawString = line.substr(9);
			instructions = getInstructions(instructsRawString, symtab, textRecord.startAddress);
			textRecord.instructions = instructions;
			textRecords.push_back(textRecord);
		}
	}
	objectFileData.headerRecord = headerRecord;
	objectFileData.endRecord = endRecord;
	objectFileData.textRecords = textRecords;
	return objectFileData;
}
//심볼테이블 읽기
symtabData getSymtabData(string fileName) {
	vector<string> symtabLines = getFileLines(fileName);
	symtabData symtabData;
	vector<symbolData> symbols;
	int inSymbolsBlock = 0;
	int inLiteralsBlock = 0;
	for (auto const& line : symtabLines) {
		if (line.empty() || line.at(0) == '-') {
			continue;
		}
		else if (!strcmp(line.substr(0, 6).c_str(), "Symbol")) {
			inSymbolsBlock = 1;
			continue;
		}
		if (inSymbolsBlock) {
			symbolData symbolData;
			vector<string> tokens = splitString(line);
			symbolData.symbol = tokens[0];
			symbolData.value = tokens[1];
			symbolData.flags = tokens[2];

			symbolData.convertedValue = (int)strtol(tokens[1].c_str(), NULL, 16);

			symbols.push_back(symbolData);
		}
	}
	symtabData.symbols = symbols;
	return symtabData;
}
//LOC의 소문자를 대문자로 변경 
string makeUpper(string LOC) {
	for (int i = 0; i < LOC.length(); i++) {
		if (isalpha(LOC.at(i))) {
			LOC.at(i) = toupper(LOC.at(i));
		}
	}
	return LOC;
}
//LOC를 string으로 
string makeString(int targetLOCint) {
	stringstream sstream;
	sstream << setfill('0') << setw(4) << hex << targetLOCint;
	string targetLOC = sstream.str();
	targetLOC = makeUpper(targetLOC);
	return targetLOC;
}
//operand의 symbol 찾기 
string findSymbol(string targetLOC, symtabData symtabData) {
	string operand;
	for (int i = 0; i < symtabData.symbols.size(); i++) {
		string targetSymbolValue = symtabData.symbols.at(i).value.substr(2, 4);

		if (targetLOC.compare(targetSymbolValue) == 0) {
			operand = symtabData.symbols.at(i).symbol;
			break;
		}
		else {
			operand = targetLOC;
		}
	}
	return operand;
}
//다음 LOC 
string getNextLOC(string addr, int format) {
	int decValue;
	stringstream stream;
	stream << addr;
	stream >> hex >> decValue;

	int decAddress = decValue + format;

	stringstream stream2;
	stream2 << setfill('0') << setw(4) << hex << decAddress;
	string hexAddress(stream2.str());

	hexAddress = makeUpper(hexAddress);
	return hexAddress;
}

int main() {

	string filename = "sample"; //파일이름은 sample로 고정
	string objectFile = filename + ".obj";//오브젝트 파일이름
	string symtabFile = filename + ".sym";//symtab 파일이름
	string asmFile = filename + ".asm";//symtab 파일이름

	int n = remove(asmFile.c_str());
	//object파일 읽을 때 바이트 상수인지 확인해줘야 함 
	symtabData symtabData = getSymtabData(symtabFile);//symblo파일 읽기
	objectFileData objectFileData = getObjectFileData(objectFile, symtabData);//object 파일 읽기

	headerRecord headerRecord = objectFileData.headerRecord;
	vector<textRecord> textRecords = objectFileData.textRecords;
	endRecord endRecord = objectFileData.endRecord;

	printingHeader(objectFileData.headerRecord, filename);//헤더 출력

	string currentLOC = objectFileData.headerRecord.startAddress.substr(2, 4);


	for (int i = 0; i < textRecords.size(); i++) {
		vector<instruction> instructions = textRecords.at(i).instructions;
		currentLOC = textRecords.at(i).startAddress.substr(2);
		//텍스트 라인별 파싱
		for (int j = 0; j < instructions.size(); j++) {
			string label = "";
			string operand = "";
			instruction instruction = instructions.at(j);
			//현재 LOC에 라벨이 있을 경우 라벨을 달아줌 
			for (int k = 0; k < symtabData.symbols.size(); k++) {
				string targetLOC = symtabData.symbols.at(k).value.substr(2, 4);
				if (targetLOC.compare(currentLOC) == 0) {
					label = symtabData.symbols.at(k).symbol;
					break;
				}
			}
			//포맷 2일 경우
			if (instruction.format == 2) {
				string registerMnemonics[] = { "A", "X", "L", "B", "S", "T", "F" };
				int registerOneIndex = stoi(instruction.register1);
				int registerTwoIndex = stoi(instruction.register2);
				if (instruction.opCode == "B8" || instruction.opCode == "B4") {
					operand = registerMnemonics[registerOneIndex];
				}
				else {
					operand = registerMnemonics[registerOneIndex] + "," + registerMnemonics[registerTwoIndex];
				}
			}
			//포맷 3일 경우
			else if (instruction.format == 3) {
				int n = instruction.n;
				int i = instruction.i;
				int b = instruction.b;
				int p = instruction.p;
				string disp = instruction.disp;

				if (n == 0 && i == 1) { // immediate
					if (p == 0 && b == 0) {// direct
						operand = to_string((int)strtol(disp.c_str(), NULL, 16));
					}
					else if (p == 1 && b == 0) { //PC
						string nextLOC = getNextLOC(currentLOC, instruction.format);
						int targetLOCint = (int)strtol(nextLOC.c_str(), NULL, 16) + (int)strtol(disp.c_str(), NULL, 16);
						string targetLOC = makeString(targetLOCint);
						operand = findSymbol(targetLOC, symtabData);
					}
					operand = "#" + operand;
				}
				else if (n == 1 && i == 1) { // sic/xe
					if (b == 0 && p == 0) { // Direct
						string targetLOC = "0" + instruction.disp;
						operand = findSymbol(targetLOC, symtabData);
					}
					else if (b == 0 && p == 1) { // PC
						string nextLOC = getNextLOC(currentLOC, instruction.format);
						int intdisp = (int)strtol(disp.c_str(), NULL, 16);
						if (intdisp > 2048) {
							intdisp = -(0x1000 - intdisp);
						}
						int targetLOCint = ((int)strtol(nextLOC.c_str(), NULL, 16) + intdisp);
						string targetLOC = makeString(targetLOCint);
						operand = findSymbol(targetLOC, symtabData);

					}
					else if (b == 1 && p == 0) { // Base				
						int number = (int)strtol(basevalue.c_str(), NULL, 16);
						int targetLOCint = stoi(disp) + number;
						string targetLOC = makeString(targetLOCint);
						operand = findSymbol(targetLOC, symtabData);

					}
				}
				else if (n == 1 && i == 0) { //indirect
					if (b == 0 && p == 1) { // PC
						string nextLOC = getNextLOC(currentLOC, instruction.format);
						int targetLOCint = ((int)strtol(nextLOC.c_str(), NULL, 16) + (int)strtol(disp.c_str(), NULL, 16)) % 4096;
						string targetLOC = makeString(targetLOCint);
						operand = "@" + findSymbol(targetLOC, symtabData);
					}
				}
				if (instruction.x == 1) {
					operand.append(",X");
				}
				if (instruction.opCode == "4C") {
					operand = "";
				}
			}
			//포맷 4
			else if (instruction.format == 4) {
				int n = instruction.n;
				int i = instruction.i;
				int b = instruction.b;
				int p = instruction.p;
				string disp = instruction.disp;
				if (n == 0 && i == 1) {//immediate
					operand = "#" + to_string((int)strtol(disp.c_str(), NULL, 16));
				}
				string targetLOC = instruction.rawString.substr(4, 4);
				operand = findSymbol(targetLOC, symtabData);
				instructions.at(j).mnemonic = "+" + instructions.at(j).mnemonic;
				if (instruction.x == 1) {
					operand.append(",X");
				}
				if (instruction.opCode == "4C") {
					operand = "";
				}
			}
			bool isFormat4 = instruction.format == 4;
			if (instructions.at(j).mnemonic == "BYTE") {
				if (instructions.at(j).length == 6) {
					operand = "C'" + label + "'";
				}
				else {
					operand = "X'" + instructions.at(j).rawString + "'";
				}
			}
			//텍스트 출력 
			printingText(currentLOC, label, instructions.at(j).mnemonic, operand, instructions.at(j).rawString, isFormat4, filename);
			//LDB일 경우 base 출력하고 basevalue를 저장
			if (instructions.at(j).mnemonic == "LDB") {
				printingText("   ", "    ", "BASE", operand.substr(1), "      ", isFormat4, filename);
				for (int k = 0; k < symtabData.symbols.size(); k++) {
					string targetSymbolValue = symtabData.symbols.at(k).symbol;
					if (targetSymbolValue.compare(operand.substr(1)) == 0) {
						basevalue = symtabData.symbols.at(k).value.substr(2, 4);
						break;
					}
				}
			}

			currentLOC = getNextLOC(currentLOC, instruction.format);
			objectFileData.textRecords.front().startAddress = currentLOC;
		}
		//RESW, RESB 출력
		if (i < textRecords.size() - 1) {
			string nextLOC = objectFileData.textRecords.at(i + 1).startAddress;
			int IntcurrentAddress = (int)strtol(currentLOC.c_str(), NULL, 16);
			int IntnextAddress = (int)strtol(nextLOC.c_str(), NULL, 16);
			string opcode;
			string nowsym;
			while (IntcurrentAddress < IntnextAddress) {
				int size = 0;
				string nextSymAddr;
				for (int k = 0; k < symtabData.symbols.size(); k++) {
					string tempLOC = symtabData.symbols.at(k).value.substr(2, 4);
					stringstream ss;
					ss << "00" << hex << IntcurrentAddress;
					string tempcurrentAddress = ss.str();
					if (tempcurrentAddress.compare(tempLOC) == 0) {
						nowsym = symtabData.symbols.at(k).symbol;
						if (k < symtabData.symbols.size()) {
							nextSymAddr = symtabData.symbols.at(k + 1).value.substr(2, 4);
						}
						else {
							nextSymAddr = "-1";
						}
						break;
					}
					else {
						nowsym = tempcurrentAddress;
					}
				}
				//nextsym찾기 
				string operand;
				int IntnextSymAddress = (int)strtol(nextSymAddr.c_str(), NULL, 16);
				if (IntnextAddress > IntnextSymAddress&& IntnextSymAddress != -1) {
					size = IntnextSymAddress - IntcurrentAddress;
				}
				else {
					size = IntnextAddress - IntcurrentAddress;
				}
				if (size % 3 == 0) {
					opcode = "RESW";
					stringstream ss;
					ss << size / 3;
					string temppara = ss.str();
					operand = temppara;
				}
				else {
					opcode = "RESB";
					stringstream ss;
					ss << size;
					string temppara = ss.str();
					operand = temppara;
				}
				stringstream ss;
				ss << "00" << hex << IntcurrentAddress;
				currentLOC = ss.str();
				printingText(currentLOC, nowsym, opcode, operand, "", 0, filename);
				if (IntnextAddress > IntnextSymAddress&& IntnextSymAddress != -1) {

					IntcurrentAddress = IntnextSymAddress;
				}
				else {

					IntcurrentAddress = IntnextAddress;
				}
			}
		}
	}
	printingEnd(objectFileData.endRecord.firstExecAddress, filename);

	char inputstring[100];
	ifstream readFile(asmFile.c_str());
	while (!readFile.eof()) {
		readFile.getline(inputstring, 100);
		cout << inputstring << endl;
	}

	return 0;
}
