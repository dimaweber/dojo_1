#include <benchmark/benchmark.h>

#include <algorithm>
#include <iterator>
#include <random>

#include "task_2.hxx"

auto SetUp = [] ( ) {
    std::vector<std::pair<uint64_t, uint64_t>> vec;
    std::seed_seq                              seed {1};
    std::mt19937                               rng;  // default constructed, seeded with fixed seed
    std::uniform_int_distribution<uint64_t>    dist(1, 1 << 20);
    std::generate_n(std::back_inserter(vec), 1'000'000, [&dist, &rng] ( ) {
        return std::make_pair(dist(rng), dist(rng));
    });
    return vec;
};

const std::vector<std::pair<uint64_t, uint64_t>> vec = SetUp( );

template<std::derived_from<gcd> Q>
void bm_task_2 (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto p: vec )
            benchmark::DoNotOptimize(obj(p));
}

BENCHMARK(bm_task_2<cpp_standard>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<gcd_1>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<gcd_bin>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<gcd_no_rec>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
