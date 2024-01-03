//
// Created by weber on 03.01.2024.
//
#include <benchmark/benchmark.h>

#include <random>

#include "task_3.hxx"

auto lcm_SetUp = [] ( ) {
    constexpr size_t                           datasetSize {10'000'000};
    std::vector<std::pair<uint64_t, uint64_t>> vec;
    std::seed_seq                              seed {1};
    std::mt19937                               rng {seed};  // default constructed, seeded with fixed seed
    std::uniform_int_distribution<uint64_t>    dist(1, 1 << 20);
    vec.reserve(datasetSize);
    std::generate_n(std::back_inserter(vec), datasetSize, [&dist, &rng] ( ) {
        return std::make_pair(dist(rng), dist(rng));
    });
    return vec;
};

const std::vector<std::pair<uint64_t, uint64_t>> lcm_vec = lcm_SetUp( );

template<std::derived_from<task_3::lcm> Q>
void bm_task_3 (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto p: lcm_vec ) {
            benchmark::DoNotOptimize(obj(p.first, p.second));
            benchmark::DoNotOptimize(obj(p.second, p.first));
        }
}

template<std::derived_from<task_3::lcm> Q>
void bm_task_3_special (benchmark::State& state)
{
    Q obj;
    for ( auto _: state ) {
        benchmark::DoNotOptimize(obj(420748418, 9659595));
        benchmark::DoNotOptimize(obj(9659595, 420748418));
    }
}

BENCHMARK(bm_task_3<task_3::cpp_standard_lcm>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_3<task_3::lcm_using_gcd>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);

BENCHMARK(bm_task_3_special<task_3::cpp_standard_lcm>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_3_special<task_3::lcm_using_gcd>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
