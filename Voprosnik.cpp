#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;


void slovo(string question, int otvet, bool prav){
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO default_attributes;
GetConsoleScreenBufferInfo(hStdOut, &default_attributes);

if (prav == true) SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
else SetConsoleTextAttribute(hStdOut,FOREGROUND_RED | FOREGROUND_INTENSITY);

for (int i = 0, a = 0; i < question.length(); i++){
		if(question[i] == '\t') a++;
		if (a == otvet){
		if (question[i] != '\t') cout << question[i];
		else cout << " ";
		}

		}
SetConsoleTextAttribute(hStdOut, default_attributes.wAttributes);

}

void show_answer(string question, int otvet, int key, bool prav){

	cout << endl << "�� ���� �����:";
	slovo(question, otvet, prav);
	cout << endl << endl;
	
	if (prav == true){
	slovo("����� ����������", 0, true);
	}

	else{
		slovo("����� ������������", 0, false);
		cout << endl << endl << "���������� �����:";
		slovo(question, key, true);
	}
	cout << endl;
	}

int otv_convert(string input, int n){
	int a = (int)(unsigned char)input[0] - 48;
	if(input.length() == 1){
		if (a > 0 && a < 10){
		if (a <= n) return a;
		else return -1;
		}
	else return 0;
	}
	else return 0;
}

bool lat_check(string line){
	for(int i = 0; i < line.length(); i++){
		int n = (int)(unsigned char)line[i];
	if (n < 65 || n > 90 && n < 97 || n > 122) return false;
	}
	return true;
}
int decode(int bin[8]){
int sum = 0;
int a = 128;
for(int i = 0; i < 8; i++){
sum += bin[i] * a;
a /= 2;
}
return sum;
}

string decode(string line){
int n = (line.length() / 8) - 1; //����� ��������������� ������

int t = 8;
string result(n, '\0');
for(int i = 0; i < n; i++){
int code[8];
for(int j = 0; j < 8; j++){
code[j] = (int)(unsigned char)line[t++] - 109;
}
result[i] = char(decode(code));
}
return result;
}
void main()
{int otv = 0; //����� ���������� �������
int q_counter = 0; //����� ��������
setlocale(LC_ALL, "rus");
ifstream qu;
qu.open("questions.htm");
if(qu.is_open()){
while(!qu.eof()){
char ch;
qu.get(ch);
if(ch == '\n') q_counter++; //������� ����� ��������
}

qu.clear();
qu.seekg(0); //����� ��������� � ������ �����

string testname, line;
	
getline(qu,testname); //������ ���������
cout << "��� ������������ ������� ������������ \"���������\"!" << endl;
cout << "�������� �����: \"" << testname << "\"." << endl;
cout << "���� ������� �� " << q_counter << " ��������." << endl << endl;

/*
string name, surname;
bool lat = false;
while(lat == false){
cout << "    ������� ���� ��� (���������): ";
cin >> name;
lat = lat_check(name);
if(lat == false) cout << "    ��� ������ ��������� ������ ��������� �������" << endl << endl;
}

lat = false;
while(lat == false){
cout << "������� ���� ������� (���������): ";
cin >> surname;
lat = lat_check(surname);
if(lat == false) cout << "������� ������ ��������� ������ ��������� �������" << endl << endl;
}
*/
cout << endl << "������ ��� ����� � ����������� �����!" << endl << endl;

/*name += "_";
name += surname;
name += ".htm";

cout << "���������� ����� �������� � ���� \"" << name << "\"" << endl << endl;*/

system("pause");
system("cls");

int q_num = 1; // ����� �������
		while(!qu.eof()){
int answer = 0; //����� ������
		getline(qu, line);//������ ������

int key_code[8];//� ������ 8 �������� ���������� ����� ����������� ������
for (int i = 0; i < 8; i++){
key_code[i] = (int)(unsigned char)line[i] - 109;
}
int key = decode(key_code) - 48; // ����� ����������� ������
string question = decode(line);

	cout << testname<< endl << endl;
	cout << "������ " << q_num++ << " �� " << q_counter << endl << endl;
	for(int i = 0; i < question.length(); i++){
	if(question[i] != '\t') cout << question[i];
	else if(answer == 0){
	cout << endl << endl << ++answer << ". ";
	}
	else 
		cout << endl << ++answer << ". ";
	}
	cout << endl << endl;
int otvet = 0;
while(otvet < 1){
	string input;
	cout << "������� ����� ������ ������: ";
	cin >> input;
	otvet = otv_convert(input, answer);
	if (otvet == 0) cout << "������� ����� ���� ������ ����� �� 1 �� 9" << endl << endl;
	if (otvet == -1) cout << "����� ������, ��� ���������� ���������" << endl << endl;
}

	bool prav;
	if (otvet == key) { prav = true;
	otv++;
	}
	else prav = false;

show_answer(question, otvet, key, prav);

cout << endl;
	system("pause");
system("cls");
		}

}
else{
cout << "�� ������ ���� � �������������� ���������." << endl;
cout << endl;
cout << "��������� ���� � ��������� \"questions.htm\" � ���� ����� � ������ �����������." << endl;
cout << endl;
cout << "���� ���������� � ���������� ���������� ��������� ����� �����������-�����������." << endl;  
cout << endl;
}

qu.close();

cout << "�� ��������� ����!" << endl << endl;
cout << "����� ���������� �������: " << otv << " �� " << q_counter << endl << endl;
int percent = (float(otv) / float(q_counter)) * 100;
cout << "������� ����������: " << percent << " %" << endl << endl;
cout << "���� ������: ";
if (percent >= 90) cout << "5";
else if (percent >= 70) cout << "4";
else if (percent >= 50) cout << "3";
else if (percent >= 10) cout << "2";
else if (percent > 0) cout << "1";
else cout << "0";
cout << endl << endl;
system("pause");
}
