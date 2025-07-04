template <typename T>
constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

// 原理，输入万能引用，类型转换将输入类型去除引用之后，加上右值引用&&,返回