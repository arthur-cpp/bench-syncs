//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#include "pch.h"
#include "tests/TestInterlocked.h"
#include "tests/TestAtomic.h"
#include "tests/TestCriticalSection.h"
#include "tests/TestMutex.h"
#include "tests/TestSRWLock.h"

//+------------------------------------------------------------------+
//| Main entry point                                                 |
//+------------------------------------------------------------------+
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
   return TRUE;
}
//+------------------------------------------------------------------+
//| Bench API version                                                |
//+------------------------------------------------------------------+
BENCH_API int BtVersion() { return BENCH_API_VERSION; }
//+------------------------------------------------------------------+
//| Create test object                                               |
//+------------------------------------------------------------------+
BENCH_API ITest* BtCreateTest(const char* initializer, UINT64 context) {
   Test* test = nullptr;
   
   // checks, context MUST be providen for this tests
   if (!initializer || !context) return nullptr;

   // instantiate test object
   if (_stricmp(initializer, "interlocked-inc") == 0)      test = new TestInterlockedIncrement();
   else if (_stricmp(initializer, "interlocked-add") == 0) test = new TestInterlockedAdd();
   else if (_stricmp(initializer, "atomic-inc") == 0)      test = new TestAtomicInc();
   else if (_stricmp(initializer, "atomic-add") == 0)      test = new TestAtomicAdd();
   else if (_stricmp(initializer, "cs") == 0)              test = new TestCs();
   else if (_stricmp(initializer, "cs-spin") == 0)         test = new TestCsSpin();
   else if (_stricmp(initializer, "mutex") == 0)           test = new TestMutex();
   else if (_stricmp(initializer, "mutex-shared") == 0)    test = new TestSharedMutex();
   else if (_stricmp(initializer, "mutex-winapi") == 0)    test = new TestWinapiMutex();
   else if (_stricmp(initializer, "srwlock") == 0)         test = new TestSRWLock();

   // set context
   if(test)
      test->Context(context);

   // return test object
   return test;
}
//+------------------------------------------------------------------+
//| Create context                                                   |
//+------------------------------------------------------------------+
BENCH_API UINT64 BtCreateContext(const char* initializer) {
   Context* ctx=nullptr;

   // instantiate context object
   if (initializer) {
      if (_stricmp(initializer, "ctx-interlocked") == 0)    ctx = new ContextInterlocked();
      else if (_stricmp(initializer, "ctx-atomic") == 0)    ctx = new ContextAtomic();
      else if (_stricmp(initializer, "ctx-cs") == 0)        ctx = new ContextCs();
      else if (_stricmp(initializer, "ctx-cs-spin") == 0)   ctx = new ContextCsSpin();
      else if (_stricmp(initializer, "ctx-mutex") == 0)     ctx = new ContextMutex();
      else if (_stricmp(initializer, "ctx-srwlock") == 0)   ctx = new ContextSRWLock();
   }

   return UINT64(ctx);
}
//+------------------------------------------------------------------+
//| Destroy context                                                  |
//+------------------------------------------------------------------+
BENCH_API void BtDestroyContext(UINT64 ctx) {
   auto context = (ContextInterlocked*)(ctx);
   if (context)
      context->Release();
}
//+------------------------------------------------------------------+
