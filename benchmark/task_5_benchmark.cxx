//
// Created by weber on 05.01.2024.
//
#include <benchmark/benchmark.h>

#include <iterator>
#include <random>
#include <ranges>

#include "task_5.hxx"

auto sexy_prime_SetUp = [] ( ) {
    constexpr size_t                        datasetSize {100'000};
    std::vector<uint64_t>                   vec;
    std::seed_seq                           seed {1};
    std::mt19937                            rng {seed};  // default constructed, seeded with fixed seed
    std::uniform_int_distribution<uint64_t> dist(1, 251281);
    vec.reserve(datasetSize);
    std::generate_n(std::back_inserter(vec), datasetSize, [&dist, &rng] ( ) {
        return dist(rng);
    });
    return vec;
};

const std::vector<uint64_t> sexy_prime_vec = sexy_prime_SetUp( );

template<std::derived_from<task_5::sexy_prime> Q>
void bm_task_5_get_sexy_prime (benchmark::State& state)
{
    Q obj;
    for ( auto _: state )
        for ( auto p: sexy_prime_vec | std::views::take(state.range(0)) ) {
            benchmark::DoNotOptimize(obj(p));
        }
}

BENCHMARK(bm_task_5_get_sexy_prime<task_5::sexy_prime_ref>)->RangeMultiplier(10)->Range(10, std::size(sexy_prime_vec))->Complexity( )->Unit(benchmark::kMillisecond);
BENCHMARK(bm_task_5_get_sexy_prime<task_5::sexy_prime_impl>)->RangeMultiplier(10)->Range(10, std::size(sexy_prime_vec))->Complexity( )->Unit(benchmark::kMillisecond);
