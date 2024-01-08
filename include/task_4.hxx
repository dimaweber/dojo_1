//
// Created by weber on 03.01.2024.
//

#pragma once

#include <algorithm>
#include <cstdint>
#include <mutex>
#include <set>
#include <vector>

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
protected:
    virtual const std::set<uint64_t>& getCachedPrimes( ) const = 0;

    virtual uint64_t maxCachedPrime ( ) const { return std::ranges::max(getCachedPrimes( )); }

    virtual void onOutOfCachedRange(uint64_t num) const    = 0;
    virtual void onNonCachedPrimeFound(uint64_t num) const = 0;
    virtual bool is_divided_by_cachedPrime(uint64_t num) const;
    virtual bool is_in_cache(uint64_t num) const;

public:
    bool is_prime(uint64_t) const noexcept override;
};

class prime_cached_single_thread : public prime_cached
{
    mutable std::set<uint64_t> primeDividers {predefinedPrimes};

    void populateCache(uint64_t num) const;

protected:
    void onOutOfCachedRange (uint64_t num) const override { populateCache(num); }

    void onNonCachedPrimeFound (uint64_t num) const override { primeDividers.insert(num); }

    const std::set<uint64_t>& getCachedPrimes ( ) const override { return primeDividers; }
};

class prime_thread_cached : public prime_cached
{
public:
    prime_thread_cached( );

    virtual ~prime_thread_cached( )
    {
        finishBuildThread = true;
        buildThread.join( );
    }

protected:
    bool is_in_cache(uint64_t num) const override;
    bool is_divided_by_cachedPrime(uint64_t num) const override;

    struct segment {
        enum class State { Empty, Process, Complete };
        static constexpr size_t emptySegmentWidth = 1000;
        uint64_t                lower {0};
        uint64_t                upper {0};
        std::set<uint64_t>      primes;
        State                   state {State::Empty};

        segment(uint64_t lo);
        void merge(prime_thread_cached::segment& other);
    };

    const std::set<uint64_t>& getCachedPrimes( ) const override;
    void                      onNonCachedPrimeFound(uint64_t num) const override;
    void                      onOutOfCachedRange(uint64_t num) const override;

private:
    segment segmentA;

    mutable std::mutex cachedPrimesAccess;
    std::thread        buildThread;
    bool               finishBuildThread {false};

    uint64_t             maxCachedPrime( ) const override;
    std::vector<segment> segments( );
    void                 processSegment(segment& seg);
    void                 build( );
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
    const prime_cached_single_thread p;

protected:
    virtual const prime_cached& primer ( ) const { return p; }

    uint64_t calculate(uint64_t num) const noexcept override;
};

class l_prime_thread_cached : public l_prime_cached
{
    const prime_thread_cached p;

protected:
    const prime_cached& primer ( ) const { return p; }
};

}  // namespace task_4
