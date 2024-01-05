//
// Created by weber on 03.01.2024.
//

#pragma once

#include <algorithm>
#include <cstdint>
#include <set>

namespace task_4
{
const std::set<uint64_t> predefinedPrimes {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271};

class prime
{
public:
    virtual bool is_prime(uint64_t num) const noexcept = 0;
};

class prime_cached : public prime
{
    mutable std::set<uint64_t> primeDividers {predefinedPrimes};
    mutable uint64_t           maxCachedPrime = std::ranges::max(primeDividers);

    void populateCache(uint64_t num) const;
    bool is_divided_by_cachedPrime(uint64_t num) const;

public:
    bool is_prime(uint64_t) const noexcept override;
};

class l_prime
{
public:
    [[nodiscard]] int64_t operator( ) (uint64_t num) const noexcept { return calculate(num); }

protected:
    [[nodiscard]] virtual uint64_t calculate(uint64_t num) const noexcept = 0;
};

class l_prime_ref : public l_prime, public prime
{
public:
    bool is_prime(uint64_t num) const noexcept override;

protected:
    uint64_t calculate(uint64_t num) const noexcept override;
};

class l_prime_cached : public l_prime
{
    const prime_cached p;

protected:
    uint64_t calculate(uint64_t num) const noexcept override;
};
}  // namespace task_4
