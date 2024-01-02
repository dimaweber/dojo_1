//
// Created by weber on 01.01.2024.
//

#include "task_1.hxx"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <random>

template<std::derived_from<Sum_3_5> S>
class Sum35_Test : public testing::Test
{
public:
    Sum35_Test( )
    {
        spdlog::set_level(spdlog::level::info);
        spdlog::set_pattern("[%H:%M:%S %z] [%t] %v");

        std::seed_seq                           seed {1};
        std::mt19937                            rng {seed};
        std::uniform_int_distribution<uint64_t> dist(1, 1 << 20);
        std::generate_n(std::back_inserter(vec), 100, [&dist, &rng] ( ) {
            return dist(rng);
        });
    }

    std::vector<uint64_t> vec;
    S                     obj;
};

using TestedTypes = ::testing::Types<Plain_C_1, Plain_C_2, Plain_C_3, Thread_C_1, Thread_C_2>;
TYPED_TEST_SUITE(Sum35_Test, TestedTypes);

TYPED_TEST(Sum35_Test, Plain)
{
    TypeParam& obj = this->obj;
    EXPECT_EQ(obj(0), 0);
    EXPECT_EQ(obj(1), 0);
    EXPECT_EQ(obj(2), 0);
    EXPECT_EQ(obj(3), 3);
    EXPECT_EQ(obj(4), 3);
    EXPECT_EQ(obj(5), 8);
    EXPECT_EQ(obj(6), 14);
    EXPECT_EQ(obj(7), 14);
    EXPECT_EQ(obj(8), 14);
    EXPECT_EQ(obj(9), 23);
    EXPECT_EQ(obj(10), 33);
    EXPECT_EQ(obj(11), 33);
    EXPECT_EQ(obj(12), 45);
    EXPECT_EQ(obj(13), 45);
    EXPECT_EQ(obj(14), 45);
    EXPECT_EQ(obj(15), 60);
    EXPECT_EQ(obj(16), 60);
    EXPECT_EQ(obj(17), 60);
    EXPECT_EQ(obj(18), 78);
    EXPECT_EQ(obj(41), 408);
    EXPECT_EQ(obj(44), 450);
    EXPECT_EQ(obj(59), 810);
    EXPECT_EQ(obj(29), 45 + 15 * 7 + 45);
    EXPECT_EQ(obj(100001), 2333416668ULL);
}

TYPED_TEST(Sum35_Test, Compare)
{
    Plain_C_1  ref;
    TypeParam& obj = this->obj;

    for ( uint64_t n: this->vec )
        EXPECT_EQ(ref(n), obj(n));
}
