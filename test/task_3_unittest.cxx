//
// Created by weber on 03.01.2024.
//

#include "task_3.hxx"

#include <gtest/gtest.h>

#include <iterator>
#include <random>

template<std::derived_from<task_3::lcm> S>
class LCM_Test : public testing::Test
{
public:
    LCM_Test( )
    {
        std::seed_seq                           seed {1};
        std::mt19937                            rng {seed};  // default constructed, seeded with fixed seed
        std::uniform_int_distribution<uint32_t> dist(1, 1 << 20);
        constexpr size_t                        datasetSize {1'000'000};
        vec.reserve(datasetSize);
        std::generate_n(std::back_inserter(vec), datasetSize, [&dist, &rng] ( ) {
            return std::make_pair(dist(rng), dist(rng));
        });
    }

    std::vector<std::pair<uint32_t, uint32_t>> vec;
    S                                          obj;
};

using TestedTypes = ::testing::Types<task_3::cpp_standard_lcm, task_3::lcm_using_gcd>;
TYPED_TEST_SUITE(LCM_Test, TestedTypes);

TYPED_TEST(LCM_Test, Plain)
{
    TypeParam& obj = this->obj;
    EXPECT_EQ(obj(0, 0), 0);
    EXPECT_EQ(obj(2, 3), 6);
    EXPECT_EQ(obj(4, 6), 12);
    EXPECT_EQ(obj(8, 12), 24);
}

TYPED_TEST(LCM_Test, CompareToStandard)
{
    task_3::cpp_standard_lcm ref;
    TypeParam&               obj = this->obj;

    for ( const auto& n: this->vec )
        EXPECT_EQ(ref(n), obj(n));
}
