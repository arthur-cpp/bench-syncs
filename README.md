# BenchSyncs - Synchronization Primitives Benchmark Plugin

A plugin for [Bench](https://github.com/arthur-cpp/bench) that provides performance testing for various synchronization primitives in Windows.

## Overview

BenchSyncs is a plugin that implements performance tests for different synchronization mechanisms in Windows, including:
- Interlocked operations
- Atomic operations
- Critical Sections (both standard and spin-based)

## Features

- Performance testing of multiple synchronization primitives:
  - Interlocked operations (increment and add)
  - Atomic operations (increment and add)
  - Critical Sections (standard and spin-based)
- Configurable test contexts for each synchronization type
- Thread-safe implementation
- Detailed performance measurements

## Test Types

The plugin provides the following test types:

1. **Interlocked Operations**
   - `interlocked-inc`: Tests InterlockedIncrement
   - `interlocked-add`: Tests InterlockedAdd

2. **Atomic Operations**
   - `atomic-inc`: Tests atomic increment
   - `atomic-add`: Tests atomic add

3. **Critical Sections**
   - `cs`: Tests standard Critical Section
   - `cs-spin`: Tests spin-based Critical Section

4. **Mutexes**
   - `mutex`: Tests std::mutex
   - `mutex-shared`: Tests std::mutex-shared in exclusive mode
   - `mutex-winapi`: Tests Windows API mutex in exclusive mode

5. **SWRLOCK**
   - `srwlock`: Tests SRWLOCK in exclusive mode

## Context Types

Each test type has its corresponding context:

- `ctx-interlocked`: Context for Interlocked operations
- `ctx-atomic`: Context for Atomic operations
- `ctx-cs`: Context for standard Critical Section
- `ctx-cs-spin`: Context for spin-based Critical Section
- `ctx-mutex`: Context for mutexes
- `ctx-srwlock`: Context for SRWLOCK

## Building

The project is built using Visual Studio and requires:
- Windows SDK
- C++17 or later
- Bench framework (version 4)

## Usage

1. Build the plugin
2. Place the resulting DLL in the Bench's `tests` directory
3. Configure the test in Bench's `config.yaml` (check [existing](bench/config.yaml)):

```yaml
tests:
  - name: "Synchronization Test"
    load: "BenchSyncs.dll"
    init: "interlocked-inc"          # or any other test type
    context_init: "ctx-interlocked"  # or any other context type
```

## License

[MIT License](LICENSE). Copyright (c) 2025, [Arthur Valitov](https://github.com/arthur-cpp).
