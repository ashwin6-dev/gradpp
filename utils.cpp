#include "includes/utils.h"

template <typename T>
std::vector<T> merge_vectors(std::vector<T> left, std::vector<T> right)
{
    std::vector<T> res;
    for (T t : left) {
        res.push_back(t);
    }

    for (T t : right) {
        res.push_back(t);
    }

    return res;
}