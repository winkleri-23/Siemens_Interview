#include "pch.h"
#include <utility>
#include <limits.h>
#include "Generator.h"
#include <Windows.h>
#include <mmsystem.h>
#define M_PI (3.14159265358979323846)

#pragma comment(lib, "winmm.lib")





void GeneratorClass::timeCnt() {

    auto previous = 0ms; // variable that remembers what time was the DataGenerator previously called 
    bool firstRun = true; 
    // this loop checks if 1ms has passed, if so - calls the DataGenerator
    while(true) {
        if (ESCAPE) { // user pressed ESC 
            break;
        }
        time_point<Clock> end = Clock::now();
        milliseconds diff = duration_cast<milliseconds>(end - Timestart); // how many ms has passed since the start of the program
        if (firstRun) {
            queue.lock(); 
            data.push(make_pair(diff.count(), DataGenerator(diff)));
            queue.unlock();
            previous = diff;
            firstRun = false;
            continue;
        }
        if (diff != previous && firstRun == false) { 
            queue.lock();
            data.push(make_pair(diff.count(), DataGenerator(diff)));
            queue.unlock();
            previous = diff;
            continue;
        }
    }
    

}


short GeneratorClass::DataGenerator(milliseconds diff) {
   int tmp = round(1000 * sin(((double)diff.count() * 2 * M_PI) / 250));
   if (tmp == -0) { // Making sure 0 is always 0 and not -0.
       return (short)0;
   }
   return (short)tmp;
}


pair<long long int, short> GeneratorClass::GetValue()
{
    queue.lock();
    
    if (data.empty()) { // in case the queue is empty
        queue.unlock();
        return make_pair(0, -1); // inform the app that the queue is empty
    }
    pair<long long int, short > tmp;
    tmp = data.front();
    data.pop();
    queue.unlock();
    return tmp;
}



GeneratorClass::GeneratorClass() {
    Timestart = Clock::now();
    ESCAPE = false;
    for (int i = 0; i < 1; i++) {
        CalculationThreads.emplace_back(&GeneratorClass::timeCnt, this);
    }
}

void GeneratorClass::start() {
    Timestart = Clock::now();
    for (int i = 0; i < 1; i++) {
        CalculationThreads.emplace_back(&GeneratorClass::timeCnt, this);
    }
}


void GeneratorClass::stop() {
    for (auto& i : CalculationThreads) {
        i.join();
    }
}




