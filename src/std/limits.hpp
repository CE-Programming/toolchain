#ifndef LIMITS_HPP
#define LIMITS_HPP

namespace std
{

enum float_denorm_style
{
    denorm_indeterminate = -1,
    denorm_absent        = 0,
    denorm_present       = 1
};

enum float_round_style
{
    round_indeterminate       = -1,
    round_toward_zero         = 0,
    round_to_nearest          = 1,
    round_toward_infinity     = 2,
    round_toward_neg_infinity = 3
};

template <class T>
class numeric_limits
{
public:
    static constexpr bool is_specialized = false;
};

} // namespace std

#endif /* LIMITS_HPP */
