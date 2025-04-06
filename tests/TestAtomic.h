//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "Test.h"
#include <atomic>

//+------------------------------------------------------------------+
//| std::atomic tests context                                        |
//+------------------------------------------------------------------+
class ContextAtomic : public Context {
private:
   std::atomic<LONG64> m_counter = 0;

public:
   inline void Increment() {
      m_counter++;
   }
   
   inline void Add() {
      LONG64 nvalue = m_counter + 1;
      m_counter = nvalue;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking std::atomic increment                               |
//+------------------------------------------------------------------+
class TestAtomicInc : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextAtomic*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking std::atomic add                                     |
//+------------------------------------------------------------------+
class TestAtomicAdd : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextAtomic*>(Context());
      context->Add();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
