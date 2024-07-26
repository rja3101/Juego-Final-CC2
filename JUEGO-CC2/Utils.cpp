#include "Utils.h"
#include<cmath>
std::string Utils::toString(float f, int precision) {
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << f;
    return out.str();
}

std::string Utils::toString(int i) {
    std::ostringstream out;
    out << i;
    return out.str();
}
int Utils::clamp(int n, int min, int max) {
    return std::max(min, std::min(n, max));
}

float Utils::mirrorXf(float x, float borderL, float borderR) {
    float distance = x - borderL;
    x = borderR - distance;
    return x;
}

float Utils::distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}

float Utils::randomize(int min, int max) {
    return (std::rand() % (max - min + 1)) + min;
}
