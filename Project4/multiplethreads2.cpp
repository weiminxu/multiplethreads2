#if _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>

int GetRandom(int max)
{
	srand(time_t(NULL));
	return rand() % max;
}

std::string GetTime()
{
	auto nowTime = std::chrono::system_clock::now();
	std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);

	return std::ctime(&sleepTime);
}

double acctBalance = 100;

std::mutex acctLock;

void GetMoney(int id, double withdrawal)
{
	std::lock_guard<std::mutex> lock(acctLock);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << id << "tries to withdrawal $" << withdrawal << "on" << GetTime() << "\n";
	if ((acctBalance - withdrawal) >= 0)
	{
		acctBalance -= withdrawal;
		std::cout << "New Account Balance is $" << acctBalance << "\n";
	}
	else
	{
		std::cout << "Not enough money in account\n";
		std::cout << "Current balance is $" << acctBalance << "\n";
	}
}

int main()
{
	std::thread threads[10];

	for (int i = 0; i < 10; ++i)
	{
		threads[i] = std::thread(GetMoney, i, 15);
	}

	for (int i = 0; i < 10; ++i) 
	{
		threads[i].join();
	}

	return 0;
}