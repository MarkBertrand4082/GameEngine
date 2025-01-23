#include <iostream>
#include <chrono>

#include "ThreadTest.h"

void ThreadTest::TestStaticFunctionPointer()
{
	m_thread = std::thread(&ThreadTest::InstanceThreadFunction,ThreadTest());
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Display From MainThread" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	m_thread.join();
}

void ThreadTest::InstanceThreadFunction()
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "thread isntance function pointer Executing" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}