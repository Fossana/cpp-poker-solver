#ifndef HASH_UTILS_H_
#define HASH_UTILS_H_

#include <functional>
#include <cstddef>

inline void hash_combine(std::size_t& seed) { }

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	hash_combine(seed, rest...);
}

#define MAKE_HASHABLE(type, ...) \
namespace std {\
    template<> struct hash<type> {\
        std::size_t operator()(const type &t) const {\
            std::size_t retval = 0;\
            hash_combine(retval, __VA_ARGS__);\
            return retval;\
        }\
    };\
} // std

#endif // HASH_UTILS_H_