string reverseWords(string s) {
    std::reverse(s.begin(), s.end());
    int n = s.length();
    int start = 0, end = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != ' ') { // i只有在不是空白字符时才进入处理逻辑
            if (end != 0) { // 因为空白字符有多个，所以需要把i的字符搬运到end，end是当前单子后一个，自然要变成空白，前进一步
                s[end++] = ' ';
            }
            start = end; //start转移到end
            while (i < n && s[i] != ' ') {
                s[end++] = s[i++]; //当i再某个单词里的时候，复制
            }
            std::reverse(s.begin() + start, s.begin() + end); //将start和end之前的字符翻转
        }
    }
    return s.substr(0, end); //end后面是积累的多余的空白单词
}