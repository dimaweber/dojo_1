//
// Created by weber on 05.01.2024.
//

#include "task_5.hxx"

#include "task_4.hxx"

namespace task_5
{
std::vector<std::pair<uint64_t, uint64_t>> sexy_prime_ref::calculate(uint64_t num) const noexcept
{
    task_4::l_prime_ref                        ref;
    std::vector<std::pair<uint64_t, uint64_t>> result;
    for ( int n = 2; n <= num; n++ ) {
        if ( ref.is_prime(n) && ref.is_prime(n + 6) ) {
            result.push_back(std::pair<uint64_t, uint64_t> {n, n + 6});
        }
    }
    return result;
}

std::vector<std::pair<uint64_t, uint64_t>> sexy_prime_impl::calculate(uint64_t num) const noexcept
{
    std::vector<std::pair<uint64_t, uint64_t>> ans;
    for ( uint64_t i = 3; i <= num; i += 2 )
        if ( primer( ).is_prime(i) && primer( ).is_prime(i + 6) )
            ans.emplace_back(std::pair<uint64_t, uint64_t> {i, i + 6});
    return ans;
}
}  // namespace task_5
