//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "Test.h"

//+------------------------------------------------------------------+
//| Interlocked* tests context                                       |
//+------------------------------------------------------------------+
class ContextInterlocked: public Context {
private:
   volatile LONG64 m_counter = 0;

public:
   inline void Increment() { InterlockedIncrement64(&m_counter); }
   inline void Add()       { InterlockedAdd64(&m_counter, 1);    }
};
//+------------------------------------------------------------------+
//| Benchmarking InterlockedIncrement64 function                     |
//+------------------------------------------------------------------+
class TestInterlockedIncrement : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextInterlocked*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking InterlockedAdd64 function                           |
//+------------------------------------------------------------------+
class TestInterlockedAdd : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextInterlocked*>(Context());
      context->Add();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
