#include <benchmark/benchmark.h>

#include <algorithm>
#include <iterator>
#include <random>

#include "task_2.hxx"

auto gcd_SetUp = [] ( ) {
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

const std::vector<std::pair<uint64_t, uint64_t>> gcd_vec = gcd_SetUp( );

template<std::derived_from<task_2::gcd> Q>
void bm_task_2 (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto [m, n]: gcd_vec ) {
            benchmark::DoNotOptimize(obj(m, n));
            benchmark::DoNotOptimize(obj(n, m));
        }
}

template<std::derived_from<task_2::gcd> Q>
void bm_task_2_special (benchmark::State& state)
{
    Q obj;
    for ( auto _: state ) {
        benchmark::DoNotOptimize(obj(420748418, 9659595));
        benchmark::DoNotOptimize(obj(9659595, 420748418));
    }
}

BENCHMARK(bm_task_2<task_2::cpp_standard_gcd>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_1>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_bin>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_no_rec>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_mod>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_knuth>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_schmidt>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_stepanov>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_2<task_2::gcd_opt>)->ThreadPerCpu( )->Complexity( )->Unit(benchmark::kMillisecond);

BENCHMARK(bm_task_2_special<task_2::cpp_standard_gcd>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_2_special<task_2::gcd_no_rec>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_2_special<task_2::gcd_knuth>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_2_special<task_2::gcd_schmidt>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_2_special<task_2::gcd_stepanov>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
BENCHMARK(bm_task_2_special<task_2::gcd_opt>)->ThreadPerCpu( )->Unit(benchmark::kNanosecond)->Repetitions(100);
