//
// Created by weber on 03.01.2024.
//
#include "task_4.hxx"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <execution>
#include <ranges>
#include <thread>

namespace task_4
{
bool l_prime_ref::is_prime(uint64_t num) const noexcept
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

uint64_t l_prime_ref::calculate(uint64_t num) const noexcept
{
    for ( int i = num - 1; i > 1; i-- ) {
        if ( is_prime(i) ) {
            return i;
        }
    }
    return 0;
}

void prime_cached_single_thread::populateCache(uint64_t num) const
{
    for ( uint64_t i = maxCachedPrime( ) + 2; i * i <= num; i += 2 ) {
        if ( !is_divided_by_cachedPrime(i) ) {
            primeDividers.insert(i);
        }
    }
}

bool prime_cached::is_prime(uint64_t num) const noexcept
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

    if ( num > std::pow(maxCachedPrime( ), 2) )
        onOutOfCachedRange(num);

    if ( is_in_cache(num) )
        return true;

    if ( is_divided_by_cachedPrime(num) ) {
        return false;
    }

    onNonCachedPrimeFound(num);
    return true;
}

bool prime_cached::is_divided_by_cachedPrime(uint64_t num) const
{
    return std::ranges::any_of(getCachedPrimes( ) | std::views::take_while([num] (uint64_t e) {
        return e * e <= num;
    }),
        [num] (uint64_t e) {
        return num % e == 0;
    });
}

bool prime_cached::is_in_cache(uint64_t num) const
{
    return getCachedPrimes( ).contains(num);
}

uint64_t l_prime_cached::calculate(uint64_t num) const noexcept
{
    if ( num == 0 )
        return 0;
    for ( uint64_t i = num - 1; i >= 2; i-- ) {
        if ( primer( ).is_prime(i) ) {
            return i;
        }
    }
    return 0;
}

void prime_thread_cached::segment::merge(prime_thread_cached::segment& other)
{
    assert(lower == other.upper || upper == other.lower);
    assert(state == State::Complete && other.state == State::Complete);
    primes.merge(other.primes);
    lower = std::min(lower, other.lower);
    upper = std::max(upper, other.upper);
}

prime_thread_cached::segment::segment(uint64_t lo) : lower {lo}, upper {lo + emptySegmentWidth}
{
}

prime_thread_cached::prime_thread_cached( ) : segmentA {2}
{
    segmentA.primes = {2, 3, 5, 7, 11, 13, 19, 23, 29};
    segmentA.upper  = maxCachedPrime( ) + 1;
    segmentA.state  = segment::State::Complete;

    buildThread = std::thread(&prime_thread_cached::build, this);
}

const std::set<uint64_t>& prime_thread_cached::getCachedPrimes( ) const
{
    return segmentA.primes;
}

uint64_t prime_thread_cached::maxCachedPrime( ) const
{
    std::lock_guard lock(cachedPrimesAccess);
    return prime_cached::maxCachedPrime( );
}

std::vector<prime_thread_cached::segment> prime_thread_cached::segments( )
{
    double               max64 = std::numeric_limits<uint64_t>::max( );
    std::vector<segment> vec;
    double               m = maxCachedPrime( );
    for ( uint64_t i = m + 1; i < std::min(max64, m * m); i += segment::emptySegmentWidth ) {
        vec.emplace_back(i);
    }
    return vec;
}

void prime_thread_cached::processSegment(prime_thread_cached::segment& seg)
{
    assert(seg.state == segment::State::Empty);
    assert((seg.lower & 1) == 0);
    assert((seg.upper & 1) == 0);

    seg.state = segment::State::Process;

    for ( uint64_t i = seg.lower + 1; i < seg.upper; i += 2 ) {
        if ( finishBuildThread )
            break;
        if ( !is_in_cache(i) && !is_divided_by_cachedPrime(i) )
            seg.primes.insert(i);
    }

    seg.state = segment::State::Complete;
}

void prime_thread_cached::build( )
{
    spdlog::debug("started");

    using namespace std::chrono_literals;
    while ( !finishBuildThread ) {
        std::this_thread::sleep_for(1s);
        auto vec = segments( );
        std::for_each(std::execution::par, vec.begin( ), vec.end( ), [this] (segment& seg) {
            processSegment(seg);
        });

        {
            std::lock_guard lock(cachedPrimesAccess);
            for ( auto seg: vec ) {
                if ( finishBuildThread )
                    return;
                segmentA.merge(seg);
            }
            segmentA.upper = maxCachedPrime( ) + 1;
        }
        vec.clear( );
    }
    spdlog::debug("finished");
}

void prime_thread_cached::onOutOfCachedRange(uint64_t num) const
{
}

void prime_thread_cached::onNonCachedPrimeFound(uint64_t num) const
{
}

bool prime_thread_cached::is_divided_by_cachedPrime(uint64_t num) const
{
    std::lock_guard lock(cachedPrimesAccess);
    return prime_cached::is_divided_by_cachedPrime(num);
}

bool prime_thread_cached::is_in_cache(uint64_t num) const
{
    std::lock_guard lock(cachedPrimesAccess);
    return prime_cached::is_in_cache(num);
}
}  // namespace task_4
