//
// Created by weber on 05.01.2024.
//
#include "task_5.hxx"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <random>
#include <ranges>

template<std::derived_from<task_5::sexy_prime> S>
class Sexy_Prime_Test : public testing::Test
{
public:
    Sexy_Prime_Test( )
    {
        spdlog::set_level(spdlog::level::info);
        spdlog::set_pattern("[%H:%M:%S %z] [%t] %v");
        std::seed_seq                           seed {1};
        std::mt19937                            rng {seed};  // default constructed, seeded with fixed seed
        std::uniform_int_distribution<uint32_t> dist(1, 251281);
        constexpr size_t                        datasetSize {200};
        vec_rand.reserve(datasetSize);
        std::generate_n(std::back_inserter(vec_rand), datasetSize, [&dist, &rng] ( ) {
            return dist(rng);
        });

        vec_known.push_back({5, 11});
        vec_known.push_back({7, 13});
        vec_known.push_back({11, 17});
        vec_known.push_back({13, 19});
        vec_known.push_back({17, 23});
        vec_known.push_back({23, 29});
    }

    std::vector<std::pair<uint64_t, uint64_t>> vec_known;
    std::vector<uint64_t>                      vec_rand;
    S                                          obj;
};

using TestedTypes = ::testing::Types<task_5::sexy_prime_ref, task_5::sexy_prime_impl>;
TYPED_TEST_SUITE(Sexy_Prime_Test, TestedTypes);

TYPED_TEST(Sexy_Prime_Test, CompareToExpected)
{
    TypeParam& obj = this->obj;

    for ( const auto& p: this->vec_known ) {
        auto ans    = obj(p.first);
        auto expect = this->vec_known | std::views::take_while([&p] (const auto& p1) {
            return p1.first <= p.first;
        });
        EXPECT_TRUE(std::ranges::equal(ans, expect));
    }
}

TYPED_TEST(Sexy_Prime_Test, CompareToRef)
{
    task_5::sexy_prime_ref ref;
    const TypeParam&       obj = this->obj;

    for ( const auto num: this->vec_rand )
        EXPECT_EQ(obj(num), ref(num));
}
