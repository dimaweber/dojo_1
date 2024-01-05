//
// Created by weber on 03.01.2024.
//
#include "task_4.hxx"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <ranges>

bool task_4::l_prime_ref::is_prime(uint64_t num) const noexcept
{
    if ( num <= 3 ) {
        return num > 1;
    }
    if ( num % 2 == 0 || num % 3 == 0 ) {
        return false;
    }

    for ( int i = 5; i * i <= num; i += 6 ) {
        if ( num % i == 0 || num % (i + 2) == 0 ) {
            return false;
        }
    }

    return true;
}

uint64_t task_4::l_prime_ref::calculate(uint64_t num) const noexcept
{
    for ( int i = num - 1; i > 1; i-- ) {
        if ( is_prime(i) ) {
            return i;
        }
    }
    return 0;
}

void task_4::prime_cached::populateCache(uint64_t num) const
{
    for ( uint64_t i = maxCachedPrime + 2; i * i <= num; i += 2 ) {
        if ( !is_divided_by_cachedPrime(i) ) {
            primeDividers.insert(i);
            maxCachedPrime = i;
        }
    }
}

bool task_4::prime_cached::is_prime(uint64_t num) const noexcept
{
    if ( num < 2 ) {
        return false;
    }
    if ( num == 2 ) {
        return true;
    }
    if ( (num & 1) == 0 ) {
        return false;
    }

    populateCache(num);

    if ( primeDividers.contains(num) ) {
        return true;
    }
    if ( is_divided_by_cachedPrime(num) ) {
        return false;
    }

    primeDividers.insert(num);
    return true;
}

bool task_4::prime_cached::is_divided_by_cachedPrime(uint64_t num) const
{
    return std::ranges::any_of(primeDividers | std::views::take_while([num] (uint64_t e) {
        return e * e <= num;
    }),
        [num] (uint64_t e) {
        return num % e == 0;
    });
}

uint64_t task_4::l_prime_cached::calculate(uint64_t num) const noexcept
{
    if ( num == 0 )
        return 0;
    for ( uint64_t i = num - 1; i >= 2; i-- ) {
        if ( p.is_prime(i) ) {
            return i;
        }
    }
    return 0;
}
