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

	cout << endl << "Вы дали ответ:";
	slovo(question, otvet, prav);
	cout << endl << endl;
	
	if (prav == true){
	slovo("ОТВЕТ ПРАВИЛЬНЫЙ", 0, true);
	}

	else{
		slovo("ОТВЕТ НЕПРАВИЛЬНЫЙ", 0, false);
		cout << endl << endl << "Правильный ответ:";
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
int n = (line.length() / 8) - 1; //Длина раскодированной строки

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
{int otv = 0; //Число правильных ответов
int q_counter = 0; //число вопросов
setlocale(LC_ALL, "rus");
ifstream qu;
qu.open("questions.htm");
if(qu.is_open()){
while(!qu.eof()){
char ch;
qu.get(ch);
if(ch == '\n') q_counter++; //считаем число вопросов
}

qu.clear();
qu.seekg(0); //Опять переходим в начало файла

string testname, line;
	
getline(qu,testname); //Читаем заголовок
cout << "Вас приветствует система тестирования \"Вопросник\"!" << endl;
cout << "Название теста: \"" << testname << "\"." << endl;
cout << "Тест состоит из " << q_counter << " вопросов." << endl << endl;

/*
string name, surname;
bool lat = false;
while(lat == false){
cout << "    Введите ваше имя (ЛАТИНИЦЕЙ): ";
cin >> name;
lat = lat_check(name);
if(lat == false) cout << "    Имя должно содержать только латинские символы" << endl << endl;
}

lat = false;
while(lat == false){
cout << "Введите вашу фамилию (ЛАТИНИЦЕЙ): ";
cin >> surname;
lat = lat_check(surname);
if(lat == false) cout << "Фамилия должна содержать только латинские символы" << endl << endl;
}
*/
cout << endl << "Желаем вам удачи в прохождении теста!" << endl << endl;

/*name += "_";
name += surname;
name += ".htm";

cout << "Статистика будет записана в файл \"" << name << "\"" << endl << endl;*/

system("pause");
system("cls");

int q_num = 1; // номер вопроса
		while(!qu.eof()){
int answer = 0; //номер ответа
		getline(qu, line);//Читаем строку

int key_code[8];//В первых 8 символах зашифрован номер правильного ответа
for (int i = 0; i < 8; i++){
key_code[i] = (int)(unsigned char)line[i] - 109;
}
int key = decode(key_code) - 48; // Номер правильного ответа
string question = decode(line);

	cout << testname<< endl << endl;
	cout << "Вопрос " << q_num++ << " из " << q_counter << endl << endl;
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
	cout << "Введите номер вашего ответа: ";
	cin >> input;
	otvet = otv_convert(input, answer);
	if (otvet == 0) cout << "Ответом может быть только число от 1 до 9" << endl << endl;
	if (otvet == -1) cout << "Ответ больше, чем количество вариантов" << endl << endl;
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
cout << "Не найден файл с зашифрованными вопросами." << endl;
cout << endl;
cout << "Поместите файл с названием \"questions.htm\" в одну папку с данным приложением." << endl;
cout << endl;
cout << "Файл получается в результате шифрования исходного файла приложением-шифровщиком." << endl;  
cout << endl;
}

qu.close();

cout << "Вы завершили тест!" << endl << endl;
cout << "Число правильных ответов: " << otv << " из " << q_counter << endl << endl;
int percent = (float(otv) / float(q_counter)) * 100;
cout << "Процент правильных: " << percent << " %" << endl << endl;
cout << "Ваша оценка: ";
if (percent >= 90) cout << "5";
else if (percent >= 70) cout << "4";
else if (percent >= 50) cout << "3";
else if (percent >= 10) cout << "2";
else if (percent > 0) cout << "1";
else cout << "0";
cout << endl << endl;
system("pause");
}
