struct Kilograms {
    constexpr Kilograms(long double d)
        : m_d(d)
    {}

    long double m_d;
};

// If you remove constexpr here, compiler will complain due to the static assert!
constexpr Kilograms operator+(Kilograms lhs, const Kilograms& rhs)
{
    return lhs.m_d + rhs.m_d;
}

constexpr bool operator==(Kilograms lhs, const Kilograms& rhs)
{
    return lhs.m_d == rhs.m_d;
}

constexpr Kilograms operator "" _kg(long double d) {
    return Kilograms(d);
}

constexpr Kilograms operator "" _lb(long double d) {
    return Kilograms(d*0.45359237);
}

int main()
{
    // static_assert can help you detect if an expression is compile-time constant.
    // Reference: see google search on how to detect if constexpr is constexpr.
    // http://avidinsight.uk/2015/10/how-to-check-that-a-function-is-constexpr/
 
    //static_assert(70.0_kg + 100.0_lb == 0.0_kg, "need to evaluate at compile time");
    static_assert(70.0_kg + 30.0_kg == 100.0_kg, "need to evaluate at compile time");

    const auto w = 70.0_kg + 100.0_lb;
}
