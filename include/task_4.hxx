//
// Created by weber on 03.01.2024.
//

#pragma once

#include <cstdint>
#include <vector>

namespace task_4
{
class prime
{
    std::vector<uint64_t> primes_cache;

public:
    bool is_prime(uint64_t) const noexcept;
};

}  // namespace task_4
