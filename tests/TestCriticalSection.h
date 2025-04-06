//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "Test.h"

//+------------------------------------------------------------------+
//| Critical section common lock/unlock wrapper                      |
//+------------------------------------------------------------------+
class Lockable {
public:
   virtual void Lock()   = 0;
   virtual void Unlock() = 0;
};
//+------------------------------------------------------------------+
//| Lock helper                                                      |
//+------------------------------------------------------------------+
class SyncGuard {
private:
   Lockable         &m_sync;

public:
                     SyncGuard(Lockable& sync) :m_sync(sync) { m_sync.Lock();   }
                    ~SyncGuard()                             { m_sync.Unlock(); }
};
//+------------------------------------------------------------------+
//| Critical section: default version                                |
//+------------------------------------------------------------------+
class Sync: public Lockable {
private:
   CRITICAL_SECTION  m_cs;

public:
                     Sync()      { InitializeCriticalSection(&m_cs); }
                    ~Sync()      { DeleteCriticalSection(&m_cs);     }

   inline void       Lock()      { EnterCriticalSection(&m_cs); }
   inline void       Unlock()    { LeaveCriticalSection(&m_cs); }
};
//+------------------------------------------------------------------+
//| Critical section: set spin count                                 |
//+------------------------------------------------------------------+
class SyncSpin : public Lockable {
private:
   CRITICAL_SECTION  m_cs;

public:
                     SyncSpin()  { InitializeCriticalSectionAndSpinCount(&m_cs, 4000); }
                    ~SyncSpin()  { DeleteCriticalSection(&m_cs); }

   inline void       Lock()      { EnterCriticalSection(&m_cs); }
   inline void       Unlock()    { LeaveCriticalSection(&m_cs); }
};
//+------------------------------------------------------------------+
//| Critical section test context                                    |
//+------------------------------------------------------------------+
class ContextCs : public Context {
private:
   Sync     m_sync;
   LONG64   m_counter = 0;

public:
   inline void Increment() {
      SyncGuard lock(m_sync);
      m_counter++;
   }
};
//+------------------------------------------------------------------+
//| Critical section with spin count test context                    |
//+------------------------------------------------------------------+
class ContextCsSpin : public Context {
private:
   SyncSpin m_sync;
   LONG64   m_counter = 0;

public:
   inline void Increment() {
      SyncGuard lock(m_sync);
      m_counter++;
   }
};

//+------------------------------------------------------------------+
//| Benchmarking critical section                                    |
//+------------------------------------------------------------------+
class TestCs : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextCs*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
//| Benchmarking critical section with spin count                    |
//+------------------------------------------------------------------+
class TestCsSpin : public Test {
public:
   virtual int Run() override {
      auto context = static_cast<ContextCsSpin*>(Context());
      context->Increment();
      return TRUE;
   }
};
//+------------------------------------------------------------------+
