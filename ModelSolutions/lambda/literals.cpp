

#include <cstdio> // less names to filter than with iostream

struct Kilograms
{
    long double k;

    constexpr Kilograms(long double d) : k(d) { }
    friend constexpr Kilograms operator+(Kilograms&& a, Kilograms&& b);
};

constexpr Kilograms operator "" _kg(long double d) {
    return Kilograms(d);
}

constexpr Kilograms operator "" _lb(long double d) {
    return Kilograms(d * 0.45359237);
}

// This one takes rvalue references, or better named universal reference ?
// To allow literals (==temporary Kilograms objects) to be passed
constexpr Kilograms operator+(Kilograms&& a, Kilograms&& b) {
    return Kilograms(a.k + b.k);
}

// This would also actually evaluate as constexpr
// const auto w = 70.0_kg + 100.0_lb;

int main()
{
    /**
     * By forcing 'w' as constexpr, compiler evaluates at compile time
     * Without, it moves to runtime
     * 
     * check with `nm literals | c++filt`
     *
     * Compiled originally with Apple LLVM version 6.0 (clang-600.0.51) (based on LLVM 3.5svn)
     */
    constexpr auto w = 70.0_kg + 100.0_lb;

    printf("%f kg\n", (double)w.k);
}
