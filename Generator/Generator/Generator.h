#pragma once

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

#include <chrono>
#include <thread>
#include <queue>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <math.h>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <future>
#include <math.h>
#include <vector>


using namespace std;

using Clock = std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;



class GENERATOR_API GeneratorClass {
public:
	/// <summary>
	/// Constructor 
	//		- store current time to the TimeStart
	//		- starts thread that calls DataGenerator every 1 ms
	/// </summary>
	GeneratorClass();
	
	/// <summary>
	//	Destructor
	//		join all created threads
	/// </summary>
	~GeneratorClass() { stop(); };
	/// <summary>
	/// Getter - ESCAPE
	/// </summary>
	/// <returns></returns>
	const bool GetEscape() { return ESCAPE; };
	/// <summary>
	/// Setter - Escape
	/// </summary>
	/// <param name="value">New value of ESCAPE</param>
	void SetEscape(bool value) { ESCAPE = value; };
	/// <summary>
	/// Returns one pair of <time, value> from the data queue
	/// </summary>
	/// <returns>pair<time, value></returns>
	pair <long long  int, short> GetValue();


	
	
	
private:
	bool ESCAPE; // true if the user pressed ESC

	std::chrono::time_point<Clock> Timestart; // Time when the program was started


	vector<thread> CalculationThreads; // vector of threads that produces data 
	queue <pair<long long int, short>> data; // queue of data - <time, value>
	mutex queue; // lock for data queue


	void start(); // starts all threads
	void stop(); // join all threads
	void timeCnt(); // calls Data Generator for each ms 
	short DataGenerator(std::chrono::milliseconds diff); // Calculates value 
};
