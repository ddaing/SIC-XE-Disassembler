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

//��� ���
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
//�ؽ�Ʈ ���
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
//���� ���
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
//inlist�� ���� 
void insertToMap(map<string, InstructNode>* inList, string opCode, InstructNode node) {
	inList->insert(map<string, InstructNode>::value_type(opCode, node));
}
//��ü ��ɾ� ����Ʈ 1,2,3/4(X)�� ǥ��
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
//opcode -> ��ɾ�
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
//����3,4���� opcode 
string getOpCode(string opCodeByte) {
	string binValue = hexToBinary(opCodeByte);
	string opCodeBinary = binValue.substr(0, binValue.length() - 2);
	opCodeBinary.push_back('0');
	opCodeBinary.push_back('0');
	return binaryToHex(opCodeBinary);
}
//symtab�� �Է� ���� �� �� ������ ������
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

//������ �о���� �Լ� 
vector<string> getFileLines(string fileName) {
	vector<string> lines;
	ifstream in(fileName.c_str());// char*�� ��ȯ���Ѽ� ���� �Է� ���� 

	string line;
	while (getline(in, line)) {
		lines.push_back(line);//���پ� �޾ƿͼ� lines�� �־���.
	}

	in.close();//���� �ݱ�
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
			//flag�� ���ϰ� value�� ���ؾ��� 
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
		opCode = getOpCode(opCode); //2����Ʈ���� �ڿ� �� ��Ʈ�� 00���� ����. 
		string format = getFormatByOpCode(opCode);

		//���� �з�
		if (format != "X" && stoi(format) == 2) {//  ���� 2�� 4����Ʈ ��� 
			rawInstructString = rawString.substr(0, 4);
			instruct.register1 = rawInstructString.substr(2, 1);
			instruct.register2 = rawInstructString.substr(3, 1);
		}
		else {
			string NIXBPE = (hexToBinary(rawString.substr(1, 1)) + hexToBinary(rawString.substr(2, 1))).substr(2, 6);//opni/xbpe/ n���� e���� ����
			instruct.n = stoi(NIXBPE.substr(0, 1));
			instruct.i = stoi(NIXBPE.substr(1, 1));
			instruct.x = stoi(NIXBPE.substr(2, 1));
			instruct.b = stoi(NIXBPE.substr(3, 1));
			instruct.p = stoi(NIXBPE.substr(4, 1));
			instruct.e = stoi(NIXBPE.substr(5, 1));

			int isFormat3 = !instruct.e;//e�� 0�̸� ���� 3 1�̸� ���� 4
			rawInstructString = isFormat3 ? rawString.substr(0, 6) : rawString.substr(0, 8);//���� 3�̸� 6����Ʈ, ����4�̸� 8����Ʈ ����
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
//������Ʈ�����б�
objectFileData getObjectFileData(string fileName, symtabData symtab) {

	vector<string> objectFileLines = getFileLines(fileName);//������Ʈ ������ ��� ���� �б� 
	objectFileData objectFileData;//object���� ������ ������ ����ü ����

	headerRecord headerRecord; // �������
	vector<textRecord> textRecords; // �ؽ�Ʈ ����
	endRecord endRecord; //end ���� 
	string headerLine = objectFileLines.front();//������Ʈ ���� ù���� ����� ���� 
	//��� ���� ����
	headerRecord.programName = headerLine.substr(1, 6);
	headerRecord.startAddress = headerLine.substr(7, 6);
	headerRecord.programLength = headerLine.substr(13, 6);

	//���� ���� ���� 
	string endLine = objectFileLines.back();//������Ʈ ���� ������ ���� ���带 ���� 
	endRecord.firstExecAddress = endLine.substr(1, 6);

	//�ؽ�Ʈ ���� ���� 
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
//�ɺ����̺� �б�
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
//LOC�� �ҹ��ڸ� �빮�ڷ� ���� 
string makeUpper(string LOC) {
	for (int i = 0; i < LOC.length(); i++) {
		if (isalpha(LOC.at(i))) {
			LOC.at(i) = toupper(LOC.at(i));
		}
	}
	return LOC;
}
//LOC�� string���� 
string makeString(int targetLOCint) {
	stringstream sstream;
	sstream << setfill('0') << setw(4) << hex << targetLOCint;
	string targetLOC = sstream.str();
	targetLOC = makeUpper(targetLOC);
	return targetLOC;
}
//operand�� symbol ã�� 
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
//���� LOC 
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

	string filename = "sample"; //�����̸��� sample�� ����
	string objectFile = filename + ".obj";//������Ʈ �����̸�
	string symtabFile = filename + ".sym";//symtab �����̸�
	string asmFile = filename + ".asm";//symtab �����̸�

	int n = remove(asmFile.c_str());
	//object���� ���� �� ����Ʈ ������� Ȯ������� �� 
	symtabData symtabData = getSymtabData(symtabFile);//symblo���� �б�
	objectFileData objectFileData = getObjectFileData(objectFile, symtabData);//object ���� �б�

	headerRecord headerRecord = objectFileData.headerRecord;
	vector<textRecord> textRecords = objectFileData.textRecords;
	endRecord endRecord = objectFileData.endRecord;

	printingHeader(objectFileData.headerRecord, filename);//��� ���

	string currentLOC = objectFileData.headerRecord.startAddress.substr(2, 4);


	for (int i = 0; i < textRecords.size(); i++) {
		vector<instruction> instructions = textRecords.at(i).instructions;
		currentLOC = textRecords.at(i).startAddress.substr(2);
		//�ؽ�Ʈ ���κ� �Ľ�
		for (int j = 0; j < instructions.size(); j++) {
			string label = "";
			string operand = "";
			instruction instruction = instructions.at(j);
			//���� LOC�� ���� ���� ��� ���� �޾��� 
			for (int k = 0; k < symtabData.symbols.size(); k++) {
				string targetLOC = symtabData.symbols.at(k).value.substr(2, 4);
				if (targetLOC.compare(currentLOC) == 0) {
					label = symtabData.symbols.at(k).symbol;
					break;
				}
			}
			//���� 2�� ���
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
			//���� 3�� ���
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
			//���� 4
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
			//�ؽ�Ʈ ��� 
			printingText(currentLOC, label, instructions.at(j).mnemonic, operand, instructions.at(j).rawString, isFormat4, filename);
			//LDB�� ��� base ����ϰ� basevalue�� ����
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
		//RESW, RESB ���
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
				//nextsymã�� 
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
