#pragma once

// C++98 metaprogramming facilities

template<bool flag, typename T, typename U>
struct soSelect {
    typedef T Result;
};

template<typename T, typename U>
struct soSelect<false, T, U> {
    typedef U Result;
};

template<bool flag, typename T = void>
struct soEnableIf { };

template<typename T>
struct soEnableIf<true, T> {
    typedef T Type;
};
