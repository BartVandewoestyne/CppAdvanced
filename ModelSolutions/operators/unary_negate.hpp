#ifndef unary_negate_HPP
#define unary_negate_HPP

//#include <>
namespace tass{
    
    template <class Predicate>
    class unary_negate
    {
    public:
        unary_negate(const Predicate& p) :
            _predicate(p) {}

        inline bool operator()(const typename Predicate::argument_type& arg) {
            return !_predicate(arg);
        }
    private:
        Predicate _predicate;
    };

    template<class Predicate>
    unary_negate<Predicate> not1(const Predicate& p){
        return unary_negate<Predicate>(p);
    }
}

#endif // unary_negate_HPP
