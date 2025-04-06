//+------------------------------------------------------------------+
//|                          Benchmarking synchronization primitives |
//|                               Copyright (c) 2025, Arthur Valitov |
//|                                    https://github.com/arthur-cpp |
//+------------------------------------------------------------------+
#pragma once
#include "../framework.h"

//+------------------------------------------------------------------+
//| Common test wrapper                                              |
//+------------------------------------------------------------------+
class Test : public ITest {
private:
   LPVOID            m_context;

public:
   virtual          ~Test()      {}
   virtual void      Release()   { delete this;  }

   virtual int       RunBefore() { return TRUE;  }
   virtual int       Run()       { return FALSE; }
   virtual int       RunAfter()  { return TRUE;  }

   // set/get context
   inline void   Context(UINT64 ctx) { m_context = LPVOID(ctx); }
   inline LPVOID Context()           { return m_context;        }
};
//+------------------------------------------------------------------+
//| Common context wrapper                                           |
//+------------------------------------------------------------------+
class Context {
public:
   virtual          ~Context() {}
   inline void       Release() { delete this; }
};
//+------------------------------------------------------------------+
