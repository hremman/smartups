#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <thread>

#define SIZEOF_CHAR_ARRAY(a) sizeof(a) / sizeof(const char *)


inline void sleepFor(int msec){
    std::this_thread::sleep_for( std::chrono::milliseconds(msec) );
}
inline void sleep__1_5__sec () {
    sleepFor(1500);
}


#endif // COMMONS_HPP
