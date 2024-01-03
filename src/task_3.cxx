//
// Created by weber on 03.01.2024.
//
#include "task_3.hxx"

#include <numeric>

uint64_t task_3::cpp_standard_lcm::calculate(uint32_t m, uint32_t n) const noexcept
{
    return std::lcm(m, n);
}

uint64_t task_3::lcm_using_gcd::calculate(uint32_t m, uint32_t n) const noexcept
{
    if ( m == 0 || n == 0 )
        return 0;
    return m / std::gcd(m, n) * n;
}
