




int findSpecialInteger(int* arr, int arrSize) {
    for (int *p = arr, *q = arr + arrSize / 4; ; p++, q++)//p从数组头开始，q从长度1/4开始
        if (*p == *q) return *p;//pq相等，就是超过
    return 0;  
}
