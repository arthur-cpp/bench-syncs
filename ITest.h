//+------------------------------------------------------------------+
//|                                                     Bench Plugin |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once

#define BENCH_API __declspec(dllexport)
#define BENCH_API_VERSION 4
//+------------------------------------------------------------------+
//| Interface to the test                                            |
//+------------------------------------------------------------------+
class ITest {
public:
   virtual void      Release()   =0;   // release object

   virtual int       RunBefore() = 0;  // before test
   virtual int       Run()       = 0;  // measured test function
   virtual int       RunAfter()  = 0;  // after test
};
//+------------------------------------------------------------------+
