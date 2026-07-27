#include <iostream>
inline void HandleAssert(bool cond, const char *str, const char *file,
                         int line) {
    if (!cond) {
        std::cout.flush();
        std::cerr.flush();
        std::cerr << "[ASSERT FAILED] " << file << ":" << line << " -> (" << str
                  << ")\n";
        std::abort();
    }
}

#define ASSERT(cond)                                                           \
    HandleAssert(static_cast<bool>(cond), #cond, __FILE__, __LINE__)
