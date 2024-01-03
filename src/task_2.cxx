#include "task_2.hxx"

#include <algorithm>
#include <numeric>

uint64_t cpp_standard::calculate(uint64_t m, uint64_t n) const noexcept
{
    return std::gcd(m, n);
}

uint64_t gcd_1::calculate(uint64_t m, uint64_t n) const noexcept
{
    if ( m == 0 )
        return n;
    if ( n == 0 )
        return m;
    if ( m == n )
        return m;
    if ( m == 1 || n == 1 )
        return 1;
    if ( m % 2 == 0 && n % 2 == 0 )
        return 2 * calculate(m / 2, n / 2);
    if ( m % 2 == 0 && n % 2 != 0 )
        return calculate(m / 2, n);
    if ( m % 2 != 0 && n % 2 == 0 )
        return calculate(m, n / 2);
    return calculate((std::max(m, n) - std::min(m, n)) / 2, std::min(m, n));
}

uint64_t gcd_bin::calculate(uint64_t m, uint64_t n) const noexcept
{
    if ( m > n )
        std::swap(m, n);

    if ( m == 0 )
        return n;
    if ( m == n )
        return m;
    if ( m == 1 )
        return 1;

    if ( (m & 1) == 0 && (n & 1) == 0 )
        return calculate(m >> 1, n >> 1) << 1;
    if ( (m & 1) == 0 && (n & 1) == 1 )
        return calculate(m >> 1, n);
    if ( (m & 1) == 1 && (n & 1) == 0 )
        return calculate(m, n >> 1);
    return calculate((n - m) >> 1, m);
}

uint64_t gcd_no_rec::calculate(uint64_t m, uint64_t n) const noexcept
{
    if ( m > n )
        std::swap(m, n);
    uint64_t mult = 0;
    while ( m > 1 && m != n ) {
        while ( (m & 1) == 0 && (n & 1) == 0 ) {
            mult++;
            m >>= 1;
            n >>= 1;
        }
        while ( (m & 1) == 0 )
            m >>= 1;
        while ( (n & 1) == 0 )
            n >>= 1;

        if ( m > n )
            std::swap(m, n);
        if ( m <= 1 || m == n )
            break;

        if ( (m & 1) == 1 && (n & 1) == 1 ) {
            n -= m;
            if ( m > n )
                std::swap(m, n);
        }
    }
    if ( m == 1 )
        return mult;
    return n << mult;
}

uint64_t gcd_mod::calculate(uint64_t m, uint64_t n) const noexcept
{
    if ( m > n )
        std::swap(m, n);
    return m == 0 ? n : calculate(m, n % m);
}

uint64_t gcd_knuth::calculate(uint64_t m, uint64_t n) const noexcept
{
    uint64_t t;
    //    if ( m > n )
    //        std::swap(m, n);
    while ( m > 0 ) {
        t = m;
        m = n % m;
        n = t;
    }
    return n;
}

uint64_t gcd_schmidt::calculate(uint64_t m, uint64_t n) const noexcept
{
    while ( m > 0 && n > 0 )
        m > n ? m %= n : n %= m;
    return m + n;
}

uint64_t gcd_stepanov::calculate(uint64_t m, uint64_t n) const noexcept
{
    while ( true ) {
        if ( n < 1 )
            return m;
        m %= n;
        if ( m < 1 )
            return n;
        n %= m;
    }
}

uint64_t gcd_opt::calculate(uint64_t m, uint64_t n) const noexcept
{
    if ( m > n )
        std::swap(m, n);
    do {
        n %= m;
        if ( n < 1 )
            return m;
        m %= n;
        if ( m < 1 )
            return n;
    } while ( true );
}
