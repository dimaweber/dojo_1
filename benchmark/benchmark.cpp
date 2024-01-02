#include "task_1.hxx"
#include <benchmark/benchmark.h>

template <class Q> void bm_task_1(benchmark::State &state) {
  //    constexpr uint64_t base = 1;
  //    const auto n = base << static_cast<uint64_t>(state.range(0));
  const uint64_t n = state.range(0);
  Q obj;
  for (auto _ : state)
    benchmark::DoNotOptimize(obj(n));
}

BENCHMARK(bm_task_1<Plain_C_1>)->Range(1 << 10, 1ULL << 32)->ThreadPerCpu();
BENCHMARK(bm_task_1<Plain_C_2>)->Range(1 << 10, 1ULL << 32)->ThreadPerCpu();
BENCHMARK(bm_task_1<Plain_C_3>)->Range(1 << 10, 1ULL << 32)->ThreadPerCpu();
BENCHMARK(bm_task_1<Thread_C_1>)
    ->Range(1 << 10, 1ULL << 32)
    ->MeasureProcessCPUTime()
    ->UseRealTime();
BENCHMARK(bm_task_1<Thread_C_2>)
    ->Range(1 << 10, 1ULL << 32)
    ->MeasureProcessCPUTime()
    ->UseRealTime();
