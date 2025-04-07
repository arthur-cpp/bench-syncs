//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "Test.h"
#include <mutex>
#include <shared_mutex>

//+------------------------------------------------------------------+
//| std::mutex tests context                                         |
//+------------------------------------------------------------------+
class ContextMutex : public Context {
private:
   LONG64 m_counter = 0;

public:
   inline void Increment() { m_counter++; }
};
//+------------------------------------------------------------------+
//| Benchmarking std::mutex                                          |
//+------------------------------------------------------------------+
class TestMutex : public Test {
private:
   std::mutex  m_sync;

public:
   virtual int Run() override {
      // lock
      std::lock_guard<std::mutex> lock(m_sync);
      // increment
      auto context = static_cast<ContextMutex*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking std::shared_mutex                                   |
//+------------------------------------------------------------------+
class TestSharedMutex : public Test {
private:
   std::shared_mutex m_sync;

public:
   virtual int Run() override {
      // lock
      std::lock_guard<std::shared_mutex> lock(m_sync);
      // increment
      auto context = static_cast<ContextMutex*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking Windows API mutex object                            |
//+------------------------------------------------------------------+
class TestWinapiMutex : public Test {
private:
   HANDLE m_mutex = nullptr;

public:
   TestWinapiMutex()  { m_mutex = CreateMutex(nullptr, FALSE, nullptr); }
   ~TestWinapiMutex() { if (m_mutex) CloseHandle(m_mutex);              }

   virtual int Run() override {
      // acquire ownership (assume success, like std::lock_guard)
      WaitForSingleObject(m_mutex, INFINITE);

      // increment
      auto context = static_cast<ContextMutex*>(Context());
      context->Increment();

      // release mutex
      ReleaseMutex(m_mutex);
      return TRUE;
   }
};
//+------------------------------------------------------------------+
