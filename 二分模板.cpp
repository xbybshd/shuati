int vec[20] = { 0 };
int bigger(int l, int r, int val) { // 找x>=val最小数的下标
    while (l < r) {
        int mid = (l + r) >> 1;
        if (vec[mid] >= val)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int smaller(int l, int r, int val) { // 找x<=val最小数的下标
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (vec[mid] <= val)
            l = mid;

        else
            r = mid - 1;
    }
    return l;
}

int find_not_raise(int i, int j, int val) { // 不上升序列，找第一个<val的数的下标
    int l = i;
    int r = j;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (w[mid] >= val) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return l;
}

int find_raise(int i, int j, int val) { // 上升序列，找第一个>val数的下标
    int l = i;
    int r = j;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (u[mid] >= val) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

[l,mid] (mid,r] 时不要加1

[l,mid) [mid,r] 时加1  

这里如果是l<r,那么返回l和r是没有区别的，因为它们最后会变成一样的