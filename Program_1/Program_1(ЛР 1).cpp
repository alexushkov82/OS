#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <process.h>

using namespace std;

volatile int n;

struct arrayS {
private:
	int size;
	char* arr;
public:
	arrayS(int size, char* arr) {
		this->size = size;
		this->arr = arr;
	}

	int getSize() {
		return size;
	}

	char* getArr() {
		return arr;
	}
};

DWORD /*UNIT*/ WINAPI Add(LPVOID temp)
{
	cout << endl << "Thread is started\n";
	string res = string("");
	arrayS* tmp = (arrayS*)temp;
	char* arr = tmp->getArr();
	int size = tmp->getSize();
	for (int i = 0; i < size; i++) {
		int temp = arr[i];
		if (temp > 47 && temp < 59) {
			res += to_string(temp - 48);
			res += '\n';
		}
		Sleep(10);
	}
	if (!res.compare(""))
		cout << "No numbers" << endl;
	else
		cout << res;
	cout << "Thread is finished" << endl;
	return 0;
}

int main()
{
	int size, stopTime;
	string s;

	cout << "Input size of array: ";
	cin >> size;
	cout << "Input time to stop thread: ";
	cin >> stopTime;
	cout << "Input string of char elements of array: ";
	cin >> s;

	char* arr = new char[size];
	srand(time(NULL));
	for (int i = 0; i < size; i++)
		arr[i] = s[i];

	arrayS* temp = new arrayS(size, arr);
	HANDLE worker;
	//UNIT IDworker;
	DWORD IDworker;

	//worker = (HANDLE)
	//	_beginthreadex(NULL, 0, Add, (void*)temp, 0, &IDworker);

	worker = CreateThread(NULL, 0, Add, (void*)temp, 0, &IDworker);
	if (worker == NULL)
		return GetLastError();

	cout << "Suspend worker" << endl;
	SuspendThread(worker);
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	Sleep(stopTime);
	ResumeThread(worker);
	cout << endl << "Continue worker" << endl;
	WaitForSingleObject(worker, INFINITE);
	CloseHandle(worker);
	return 0;
}