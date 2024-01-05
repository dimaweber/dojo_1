//
// Created by weber on 03.01.2024.
//

#include <benchmark/benchmark.h>

#include <random>
#include <ranges>

#include "task_4.hxx"

auto l_prime_SetUp = [] ( ) {
    constexpr size_t                        datasetSize {100'000};
    std::vector<uint64_t>                   vec;
    std::seed_seq                           seed {1};
    std::mt19937                            rng {seed};  // default constructed, seeded with fixed seed
    std::uniform_int_distribution<uint64_t> dist(1, 1 << 30);
    vec.reserve(datasetSize);
    std::generate_n(std::back_inserter(vec), datasetSize, [&dist, &rng] ( ) {
        return dist(rng);
    });
    return vec;
};

const std::vector<uint64_t> l_prime_vec = l_prime_SetUp( );

template<std::derived_from<task_4::prime> Q>
void bm_task_4_is_prime (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto p: l_prime_vec | std::views::take(state.range(0)) ) {
            benchmark::DoNotOptimize(obj.is_prime(p));
        }
}

BENCHMARK(bm_task_4_is_prime<task_4::l_prime_ref>)->RangeMultiplier(10)->Range(10, 10'000'000)->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_4_is_prime<task_4::prime_cached>)->RangeMultiplier(10)->Range(10, 10'000'000)->Complexity( )->Unit(benchmark::kMillisecond);

template<std::derived_from<task_4::l_prime> Q>
void bm_task_4_get_prev_prime (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto p: l_prime_vec | std::views::take(state.range(0)) ) {
            benchmark::DoNotOptimize(obj(p));
        }
}

BENCHMARK(bm_task_4_get_prev_prime<task_4::l_prime_ref>)->RangeMultiplier(10)->Range(10, 10'000'000)->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_4_get_prev_prime<task_4::l_prime_cached>)->RangeMultiplier(10)->Range(10, 10'000'000)->Complexity( )->Unit(benchmark::kMillisecond);
