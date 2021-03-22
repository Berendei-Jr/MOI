#pragma once

#include <chrono>
#include <iostream>
#include<fstream>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
	explicit LogDuration(int a)
		: start(steady_clock::now())
	{
	}
	auto Time() {
		auto finish = steady_clock::now();
		auto dur = finish - start;
		return duration_cast<milliseconds>(dur).count();
	}
	~LogDuration() {}
private:
	steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuratio