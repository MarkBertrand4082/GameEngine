#pragma once
#include <thread>

class ThreadTest
{
public:
	void TestStaticFunctionPointer();
	void TestInstanceFunctionPointer();
	void TestFunctionObject();
	void TestLambdaFunction();

	void operator()();

private:
	static void StaticThreadFunction();
	void InstanceThreadFunction();

	std::thread m_thread;
};