

char s0[100000];
char* delete_blank(char* s) {
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    int len = strlen(s);
    int blank = 0;
    while (s[j] == ' ') {
        i++;
        j++;
        k++;
    } //去除先导空格
    while (s[j] != 0) {
        s[i] = s[j];
        //printf("%s   %d   %d\n",s,i,j);
        if (s[i] == s[j + 1] && s[i] == ' ') { //去除中间空格
            j++;
        }
        else {
            i++;
            j++;
        }
    }
    //  printf("%s   %d   %d\n",s,i,j);
    i--; //回到结束初始状态
    j--;
    while (s[i] == ' ') {
        i--; //去除后序空格
    }
    s[i + 1] = 0; //此时i指向最后一个不为空格的元素
    return s + k; //返回起始地址
}

void reverse(char* s, int len) {

    int length = len >> 1;
    for (int i = 0; i < length; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
        //printf("%s\n",s);
    }
}

char* reverseWords(char* s) {
    memset(s0, 0, sizeof(s0));
    if (!strlen(s))
        return s;
    memcpy(s0, s, strlen(s));
    char* s1 = delete_blank(s0); //去除所有空格
    //printf("%s   %d\n",s1,strlen(s1));
    int len = strlen(s1);
    reverse(s1, len); //全部翻转一次
    //printf("%s  %d\n",s1,len);
    int i = 0;
    int j = 0;
    while (j <= len) { //j小于等于字符串长度
        while (s1[j] != ' ' && j != len) { //j到空格和字符串长度停下来
            j++;
        }
        reverse(s1 + i, j - i); //翻转i到j之间的，不为j的字符串
        //printf("%s   %d   %d\n",s1,i,j);
        j++; //j跳到下一个有字符的
        i = j;
    }
    return s1;
}