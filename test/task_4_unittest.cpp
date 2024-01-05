//
// Created by weber on 03.01.2024.
//

#include "task_4.hxx"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <random>

TEST(Prime, isprime)
{
    task_4::prime_cached p;
    EXPECT_FALSE(p.is_prime(0));
    EXPECT_FALSE(p.is_prime(1));
    EXPECT_TRUE(p.is_prime(2));
    EXPECT_TRUE(p.is_prime(3));
    EXPECT_FALSE(p.is_prime(4));
    EXPECT_FALSE(p.is_prime(49));
    EXPECT_TRUE(p.is_prime(5));
    EXPECT_TRUE(p.is_prime(53));
}

TEST(Prime, is_prime_vs_predefined)
{
    task_4::prime_cached p;
    for ( uint64_t n = 0; n <= std::ranges::max(task_4::predefinedPrimes); n++ )
        EXPECT_EQ(p.is_prime(n), std::ranges::find(task_4::predefinedPrimes, n) != task_4::predefinedPrimes.cend( ));
}

template<std::derived_from<task_4::l_prime> S>
class L_Prime_Test : public testing::Test
{
public:
    L_Prime_Test( )
    {
        spdlog::set_level(spdlog::level::info);
        spdlog::set_pattern("[%H:%M:%S %z] [%t] %v");

        vec_known.push_back({0, 0});
        vec_known.push_back({1, 0});
        vec_known.push_back({2, 0});
        vec_known.push_back({3, 2});
        vec_known.push_back({4, 3});
        vec_known.push_back({5, 3});
        vec_known.push_back({6, 5});
        vec_known.push_back({7, 5});
        vec_known.push_back({8, 7});
        vec_known.push_back({9, 7});
        vec_known.push_back({10, 7});
        vec_known.push_back({11, 7});
        vec_known.push_back({12, 11});
        vec_known.push_back({13, 11});
        vec_known.push_back({14, 13});
        vec_known.push_back({15, 13});
        vec_known.push_back({16, 13});
        vec_known.push_back({17, 13});
        vec_known.push_back({18, 17});
        vec_known.push_back({19, 17});
        vec_known.push_back({20, 19});
        vec_known.push_back({21, 19});
        vec_known.push_back({22, 19});
        vec_known.push_back({23, 19});
        vec_known.push_back({24, 23});
        vec_known.push_back({25, 23});
        vec_known.push_back({26, 23});
        vec_known.push_back({27, 23});
        vec_known.push_back({28, 23});
        vec_known.push_back({29, 23});
        vec_known.push_back({30, 29});

        std::seed_seq                           seed {1};
        std::mt19937                            rng {seed};  // default constructed, seeded with fixed seed
        std::uniform_int_distribution<uint32_t> dist(1, 1 << 20);
        constexpr size_t                        datasetSize {1'000};
        vec_rand.reserve(datasetSize);
        std::generate_n(std::back_inserter(vec_rand), datasetSize, [&dist, &rng] ( ) {
            return dist(rng);
        });
    }

    std::vector<std::pair<uint64_t, uint64_t>> vec_known;
    std::vector<uint64_t>                      vec_rand;
    S                                          obj;
};

using TestedTypes = ::testing::Types<task_4::l_prime_cached>;
TYPED_TEST_SUITE(L_Prime_Test, TestedTypes);

TYPED_TEST(L_Prime_Test, CompareToExpected)
{
    TypeParam& obj = this->obj;

    for ( const auto [num, expected]: this->vec_known )
        EXPECT_EQ(obj(num), expected);
}

TYPED_TEST(L_Prime_Test, CompareToRef)
{
    task_4::l_prime_ref ref;
    const TypeParam&    obj = this->obj;

    for ( const auto num: this->vec_rand )
        EXPECT_EQ(obj(num), ref(num));
}
