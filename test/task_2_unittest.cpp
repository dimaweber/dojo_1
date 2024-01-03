//
// Created by weber on 02.01.2024.
//

#include "task_2.hxx"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <random>

template<std::derived_from<gcd> S>
class GCD_Test : public testing::Test
{
public:
    GCD_Test( )
    {
        spdlog::set_level(spdlog::level::info);
        spdlog::set_pattern("[%H:%M:%S %z] [%t] %v");

        std::seed_seq                           seed {1};
        std::mt19937                            rng;  // default constructed, seeded with fixed seed
        std::uniform_int_distribution<uint64_t> dist(1, 1 << 20);
        constexpr size_t                        datasetSize {1'000'000};
        vec.reserve(datasetSize);
        std::generate_n(std::back_inserter(vec), datasetSize, [&dist, &rng] ( ) {
            return std::make_pair(dist(rng), dist(rng));
        });
    }

    std::vector<std::pair<uint64_t, uint64_t>> vec;
    S                                          obj;
};

using TestedTypes = ::testing::Types<cpp_standard, gcd_1, gcd_bin, gcd_no_rec, gcd_mod, gcd_no_rec, gcd_knuth, gcd_schmidt, gcd_stepanov, gcd_opt>;
TYPED_TEST_SUITE(GCD_Test, TestedTypes);

TYPED_TEST(GCD_Test, Plain)
{
    TypeParam& obj = this->obj;
    EXPECT_EQ(obj(0, 0), 0);
    EXPECT_EQ(obj(42, 0), 42);
    EXPECT_EQ(obj(0, 42), 42);
    EXPECT_EQ(obj(42, 42), 42);
    EXPECT_EQ(obj(1, 2), 1);
    EXPECT_EQ(obj(4, 6), 2);
    EXPECT_EQ(obj(6, 4), 2);
    EXPECT_EQ(obj(12, 15), 3);
}

TYPED_TEST(GCD_Test, CompareToStandard)
{
    cpp_standard ref;
    TypeParam&   obj = this->obj;

    for ( const auto& n: this->vec )
        EXPECT_EQ(ref(n), obj(n));
}
