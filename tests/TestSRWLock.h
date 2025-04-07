//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "Test.h"

//+------------------------------------------------------------------+
//| SRWLOCK test context                                             |
//+------------------------------------------------------------------+
class ContextSRWLock : public Context {
private:
   LONG64 m_counter = 0;

public:
   inline void Increment() { m_counter++; }
};
//+------------------------------------------------------------------+
//| Benchmarking SRWLOCK (exclusive)                                 |
//+------------------------------------------------------------------+
class TestSRWLock : public Test {
private:
   SRWLOCK m_lock;

public:
   TestSRWLock() {
      InitializeSRWLock(&m_lock);
   }

   virtual int Run() override {
      // acquire exclusive lock (no return checking, like std::lock_guard)
      AcquireSRWLockExclusive(&m_lock);

      // increment
      auto context = static_cast<ContextSRWLock*>(Context());
      context->Increment();

      // release exclusive lock
      ReleaseSRWLockExclusive(&m_lock);
      return TRUE;
   }
};
//+------------------------------------------------------------------+
