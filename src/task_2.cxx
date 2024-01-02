#include "task_2.hxx"

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
    uint64_t mult = 1;
    while ( m > 1 && m != n ) {
        if ( (m & 1) == 0 && (n & 1) == 0 ) {
            mult <<= 1;
            m >>= 1;
            n >>= 1;
        } else if ( (m & 1) == 0 && (n & 1) == 1 ) {
            m >>= 1;
        } else if ( (m & 1) == 1 && (n & 1) == 0 ) {
            n >>= 1;
        } else {
            n -= m;
        }
        if ( m > n )
            std::swap(m, n);
    }
    if ( m == 1 )
        return mult;
    return n * mult;
}
