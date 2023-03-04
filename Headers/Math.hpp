#pragma once

namespace Math {
	template<typename T>
	inline int signof(T n) {
		return (n > 0) - (n < 0);
	}
}
