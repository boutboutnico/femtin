/*
 * femtin_mpl_utility.hpp
 *
 *  Created on: 3 juin 2015
 *      Author: nboutin
 */

#ifndef FEMTIN_MPL_UTILITY_HPP_
#define FEMTIN_MPL_UTILITY_HPP_

#include <cstdint>

namespace femtin {

/// -------------------------------------------------------------------------------------------
/**
 * @brief An 'if' statement that is handled at compile time.
 *
 * This class is useful when performing compile-time calculations. The class is basically a compile-time version of
 * the ternary ?: operator.
 *
 * @code
 * std::uint32_t value = StaticIf<std::uint32_t, 1 != 0, 100U, 200U>::VALUE;
 * // value is set to 100, because the static condition evaluates to true
 *
 * std::uint32_t value2 = StaticIf<std::uint32_t, 1 == 0, 100U, 200U>::VALUE;
 * // value2 is set to 200 because the static condition evaluates to false
 * @endcode
 *
 * This class is intended to be used inside other template code, in order to make decisions at compile time.
 *
 * @tparam T The type of the result of the expression.
 * @tparam Cond The static condition. This must be an expression that evaluates to either true or false at compile time.
 * @tparam WhenTrue The result of the static expression when the condition is true.
 * @tparam WhenFalse The result of the static expression when the condition is false.
 */
template<typename T, bool Cond, T WhenTrue, T WhenFalse>
struct StaticIf {
	static const T VALUE = WhenTrue;
};

template<typename T, T WhenTrue, T WhenFalse>
struct StaticIf<T, false, WhenTrue, WhenFalse> {
	static const T VALUE = WhenFalse;
};

/// -------------------------------------------------------------------------------------------

/**
 * @brief Compile time calculation for a value raised to a power.
 *
 * This class is used to generate a compile-time constant value of a value raised to a power. For example, to
 * calculate the value of 10^2:
 * @code
 * std::uint32_t value = Power<std::uint32_t, 10U, 2U>::VALUE;
 * // value is set to 100
 * @endcode
 *
 * This is exactly the same as:
 * @code
 * std::uint32_t value = 10U;
 * @endcode
 *
 * This class is intended to be used with other template code to generate constants at compile time.
 */
template<typename T, T Value, uint32_t Pow>
struct Power {
	static const T VALUE = Value * Power<T, Value, Pow - 1U>::VALUE;
};

/// base case
template<typename T, T Value>
struct Power<T, Value, 0U> {
	static const T VALUE = 1U;
};

/// -------------------------------------------------------------------------------------------

template<typename T, int32_t expoDst, int32_t expoSrc>
struct ScaleConverter {

	static const T MULTIPLIER = Power<T, static_cast<T>(10),
			StaticIf<T, expoDst >= expoSrc, 0U,
					static_cast<T>(expoSrc - expoDst)>::VALUE>::VALUE;

	static const T DIVISOR = Power<T, static_cast<T>(10),
			StaticIf<T, !(expoDst >= expoSrc), 0U,
					static_cast<T>(expoDst - expoSrc)>::VALUE>::VALUE;

	static inline T convert(const T _val) {
		return static_cast<T>(_val * MULTIPLIER / DIVISOR);
	}
};
} /// femtin

#endif /* FEMTIN_MPL_UTILITY_HPP_ */
