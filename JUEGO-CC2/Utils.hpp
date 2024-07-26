#ifndef UTILS_HPP
#define UTILS_HPP

template <typename T>
constexpr T clamp(const T& value, const T& low, const T& high) {
    return (value < low) ? low : (value > high ? high : value);
}

#endif // UTILS_HPP
