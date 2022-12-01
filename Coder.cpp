#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int check (string line){
char ch;
int counter = 48; //������������� ���� � ������� ASCII
for(int i = 0; i < line.length() - 2; i++){//������� ���� �� ����-�������������� ������� � ������
		if (line[i] == '\t') counter++;
}
if (int(line[line.length() - 1]) < 48 || int(line[line.length() - 1]) > 57) return 1; //�������� ������ �� �����
else if (line[line.length() - 2] != '\t') return 2; //����� �������� �������� �� ���
else if (line[line.length() - 1] == 48) return 3; //�������� ������ - ����
else if (int(line[line.length() - 1]) > counter) return 4;// �������� ������ ������ ����� �������
else return 0;
}

string encode(char ch){
int a = (int)(unsigned char)ch; //�������� ��� ������� � ASCII
int bin[8]; //�������� ����� ��������� ����
for(int i = 7; i >= 0; i--){
	bin[i] = a%2;
	a/=2; //�� �������� �������� ��� ASCII � �������� �����
}
string res(8, '\0'); // ������ ������ ��� ������ ����
for(int i = 0; i < 8; i++){
res[i] = bin[i] + 109; //���� - ��� m; 1 - ��� n
}
return res;
}
void main()
{
setlocale(LC_ALL, "rus");
ifstream qu;
qu.open("questions.txt");
if(qu.is_open()){
string testname, question;
int q_counter = 0; //����� ��������
getline(qu,testname); //������ ���������
if(testname.length() == 0) {cout << "������ ��������� ������." << endl;
		cout << endl;
		cout << "��������� ��������� � ������������� ���������." << endl;
		cout << endl;
		system("pause");
		return;
}
	for(int i = 0; i < testname.length(); i++){
		if (testname[i] == '\t'){
		cout << "� ��������� ���������� ����� ���������." << endl;
		cout << endl;
		cout << "��������� ��������� � ������������� ���������." << endl;
		cout << endl;
		system("pause");
		return;
		}
	}
bool exit = false;
while(!qu.eof()){
q_counter++;//������� ����� ��������
getline(qu, question);
if(question.length() < 2) {
	cout << "������ " << q_counter << ": ������ �������� ����� ���� ��������." << endl << endl;
	cout << "��������� ������������ ������ �������� � ������������� ���������." << endl;
	cout << endl;
	system("pause");
	return;
}
int e_code = check(question);//��� ������ � �������
if(e_code != 0){
	cout << "������ " << q_counter << ": ";
	exit = true;
	if(e_code == 1) cout << "� ����� ������ ��� ������ ����������� ������" << endl;
	else if(e_code == 2) cout << "����� ����������� ������ �� ������ ������ ��������� ��� ������ 9" << endl;
	else if(e_code == 3) cout << "����� ����������� ������ ����� ����" << endl;
	else cout << "����� ����������� ������ ������ ����� �������" << endl;
}
}
if(exit == true){
cout << endl;
cout << "��������� ������������ ������ �������� � ������������� ���������."<<endl;
cout << endl;
system("pause");
return;
}
qu.clear();
qu.seekg(0); //����� ��������� � ������ �����
	getline(qu,testname); //����� ������� �� ������ ������, ������� ����� ������ ���������
	cout << testname << endl << endl; //������� ��������� �� �����
	ofstream fout("questions.htm");
	fout << testname; //������� ��������� � ����
	for(int i = 0; i < q_counter; i++){
		fout << endl;
	getline(qu, question); //������ ������
	cout << i + 1 << ": " << endl << question << endl << endl; //������� ��� �� �����

	//����� ����� ���� ��� �������� ������ ����������� ������ � ������ ������

char *temp_string = new char[question.length() - 1]; //�����
temp_string[0] = question[question.length() - 1]; //��������� � ������
for(int i = 0; i < question.length() - 2; i++){
temp_string[i+1] = question[i];//���������� ��������� ������� � �����
}
for(int i = 0; i < question.length() - 1; i++){
	question[i] = temp_string[i]; //������������ ������� ������� � ������
}
delete[](temp_string); //������� �����

question.erase(question.end() - 1); // � ����� ������ ������� �����, ������� ���

for(int i = 0; i < question.length(); i++){
fout << encode(question[i]); //���������� �������������� �������
}
	}
cout << endl;
cout << q_counter << " �������� ����������� � �������� � ���� \"questions.htm\"" << endl;
cout << "���� ���� �� �� ������ ����� �� ������� ����� - �������������" << endl;
cout << "�������� ���� � ��������� ANSI � ��������� �������� ����������." << endl;
cout << endl;
fout.close();
}
else{
cout << "�� ������ �������� ���� � ���������." << endl;
cout << endl;
cout << "��������� ���� � ��������� \"questions.txt\" � ���� ����� � ������ �����������." << endl;
cout << endl;
cout << "���� ������ ���� � ��������� ANSI � ����� ���������� ���������." << endl;
cout << endl;
}

qu.close();

system("pause");
}