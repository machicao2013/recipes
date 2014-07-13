#include "FooCalc.h"
#include <iostream>
using namespace std;

FooCalc::FooCalc()
{
    cout << "FooCalc Constructor is invoked" << endl;
}

FooCalc::~FooCalc()
{
    cout << "FooCalc Destructor is invoked" << endl;
}

void FooCalc::Init()
{
    cout << "FooCalc is inited" << endl;
}

void FooCalc::Finalize()
{
    cout << "FooCalc is Finalized" << endl;
}

int FooCalc::Add(int a, int b)
{
    return (a + b);
}

int FooCalc::Sub(int a, int b)
{
    return (a - b);
}
