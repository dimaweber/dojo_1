#include "benchmark/benchmark.h"
#include "task_1.hxx"

template<std::derived_from<Sum_3_5> Q>
void bm_task_1 (benchmark::State& state)
{
    const uint64_t n = 1ULL << state.range(0);
    Q              obj;
    for ( auto _: state )
        benchmark::DoNotOptimize(obj(n));
}

BENCHMARK(bm_task_1<Plain_C_1>)->DenseRange(20, 32, 3)->ThreadPerCpu( )->Unit(benchmark::kSecond)->Complexity( );
BENCHMARK(bm_task_1<Plain_C_2>)->DenseRange(20, 32, 3)->ThreadPerCpu( )->Unit(benchmark::kSecond)->Complexity( );
BENCHMARK(bm_task_1<Plain_C_3>)->DenseRange(20, 32, 3)->ThreadPerCpu( )->Unit(benchmark::kSecond)->Complexity( );
BENCHMARK(bm_task_1<Thread_C_1>)->DenseRange(20, 32, 3)->MeasureProcessCPUTime( )->UseRealTime( )->Unit(benchmark::kSecond)->Complexity( );
BENCHMARK(bm_task_1<Thread_C_2>)->DenseRange(20, 32, 3)->MeasureProcessCPUTime( )->UseRealTime( )->Unit(benchmark::kSecond)->Complexity( );
