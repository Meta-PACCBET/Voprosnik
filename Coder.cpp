#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int check (string line){
char ch;
int counter = 48; //соответствует нулю в таблице ASCII
for(int i = 0; i < line.length() - 2; i++){//считаем табы до пред-предпоследнего символа в строке
		if (line[i] == '\t') counter++;
}
if (int(line[line.length() - 1]) < 48 || int(line[line.length() - 1]) > 57) return 1; //концевой символ не число
else if (line[line.length() - 2] != '\t') return 2; //перед концевым символом не таб
else if (line[line.length() - 1] == 48) return 3; //концевой символ - ноль
else if (int(line[line.length() - 1]) > counter) return 4;// концевой символ больше числа ответов
else return 0;
}

string encode(char ch){
int a = (int)(unsigned char)ch; //Числовой код символа в ASCII
int bin[8]; //Двоичная форма числового кода
for(int i = 7; i >= 0; i--){
	bin[i] = a%2;
	a/=2; //Мы перевели числовой код ASCII в двоичную форму
}
string res(8, '\0'); // Создаём строку для записи кода
for(int i = 0; i < 8; i++){
res[i] = bin[i] + 109; //Ноль - это m; 1 - это n
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
int q_counter = 0; //число вопросов
getline(qu,testname); //читаем заголовок
if(testname.length() == 0) {cout << "Строка заголовка пустая." << endl;
		cout << endl;
		cout << "Исправьте заголовок и перезапустите программу." << endl;
		cout << endl;
		system("pause");
		return;
}
	for(int i = 0; i < testname.length(); i++){
		if (testname[i] == '\t'){
		cout << "В заголовке содержатся знаки табуляции." << endl;
		cout << endl;
		cout << "Исправьте заголовок и перезапустите программу." << endl;
		cout << endl;
		system("pause");
		return;
		}
	}
bool exit = false;
while(!qu.eof()){
q_counter++;//подсчёт числа вопросов
getline(qu, question);
if(question.length() < 2) {
	cout << "Вопрос " << q_counter << ": строка содержит менее двух символов." << endl << endl;
	cout << "Исправьте некорректные строки вопросов и перезапустите программу." << endl;
	cout << endl;
	system("pause");
	return;
}
int e_code = check(question);//код ошибки в вопросе
if(e_code != 0){
	cout << "Вопрос " << q_counter << ": ";
	exit = true;
	if(e_code == 1) cout << "в конце строки нет номера правильного ответа" << endl;
	else if(e_code == 2) cout << "номер правильного ответа не отделён знаком табуляции или больше 9" << endl;
	else if(e_code == 3) cout << "номер правильного ответа равен нулю" << endl;
	else cout << "номер правильного ответа больше числа ответов" << endl;
}
}
if(exit == true){
cout << endl;
cout << "Исправьте некорректные строки вопросов и перезапустите программу."<<endl;
cout << endl;
system("pause");
return;
}
qu.clear();
qu.seekg(0); //Опять переходим в начало файла
	getline(qu,testname); //Нужно перейти на первый вопрос, поэтому снова читаем заголовок
	cout << testname << endl << endl; //Выводим заголовок на экран
	ofstream fout("questions.htm");
	fout << testname; //Выводим заголовок в файл
	for(int i = 0; i < q_counter; i++){
		fout << endl;
	getline(qu, question); //читаем вопрос
	cout << i + 1 << ": " << endl << question << endl << endl; //выводим его на экран

	//Далее кусок кода для переноса номера правильного ответа в начало строки

char *temp_string = new char[question.length() - 1]; //Буфер
temp_string[0] = question[question.length() - 1]; //Переносим в начало
for(int i = 0; i < question.length() - 2; i++){
temp_string[i+1] = question[i];//Дописываем остальные символы в буфер
}
for(int i = 0; i < question.length() - 1; i++){
	question[i] = temp_string[i]; //Переписываем символы обратно в строку
}
delete[](temp_string); //Удаляем буфер

question.erase(question.end() - 1); // В конце строки остался номер, удаляем его

for(int i = 0; i < question.length(); i++){
fout << encode(question[i]); //Записываем закодированные вопросы
}
	}
cout << endl;
cout << q_counter << " вопросов зашифрованы и записаны в файл \"questions.htm\"" << endl;
cout << "Если выше вы НЕ ВИДИТЕ текст на русском языке - пересохраните" << endl;
cout << "исходный файл в кодировке ANSI и повторите операцию шифрования." << endl;
cout << endl;
fout.close();
}
else{
cout << "Не найден исходный файл с вопросами." << endl;
cout << endl;
cout << "Поместите файл с названием \"questions.txt\" в одну папку с данным приложением." << endl;
cout << endl;
cout << "Файл должен быть в кодировке ANSI и иметь корректную структуру." << endl;
cout << endl;
}

qu.close();

system("pause");
}