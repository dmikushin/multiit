#ifndef MULTIIT_COMPILETIME_H
#define MULTIIT_COMPILETIME_H

#include <array>
#include <stdint.h>

namespace multiit {

namespace compiletime {

// A group of indexes that iterate from 0 to the given upper value.
// XXX Note: dimensions are in reverse order
template <uint32_t... Dims>
struct MultiIterator
{
	std::array<uint32_t, sizeof...(Dims)> current;

	inline uint32_t* getCurrent() { return &current[0]; }
	inline const uint32_t* getCurrent() const { return &current[0]; }

	MultiIterator() { }

	MultiIterator(const std::array<uint32_t, sizeof...(Dims)>& current_) : current(current_) { }

	template <int i, uint32_t Dim, uint32_t... Rest>
	inline bool next()
	{
		current[i]++;
		if (current[i] >= Dim)
			current[i] = 0;
		else
			return true;

		if constexpr(sizeof...(Rest) > 0)
			return next<i + 1, Rest...>();

		return false;
	}

	virtual bool next()
	{
		return next<0, Dims...>();
	}

	virtual void reset()
	{
		memset(&current[0], 0, sizeof...(Dims));
	}

	virtual ~MultiIterator() { }
};

} // namespace compiletime

} // namespace multiit

#endif // MULTIIT_COMPILETIME_H
