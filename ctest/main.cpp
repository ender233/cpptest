
#include <iostream>
#include <cstring>
#include <memory>

/**************/
// 没有overlap
void *memcpy(void *dest, const void *src, std::size_t count) {
    if(dest==NULL || src==NULL) return NULL;

    char *tmp = (char *)dest;
    const char *s = (const char *)src;
    while(count--) {
        *tmp++ = *s++;
    }

    return dest;
}

// 需要考虑overlap
void *memmove(void *dest, const void *src, std::size_t count) {
    if (dest == NULL || src == NULL) return NULL;

    char *tmp = (char *) dest;
    const char *s = (const char *) src;

    // 只考虑一种重叠, src尾部和dest有重叠, 其余情况正常处理即可
    bool flag = ((char *)src < (char *)dest)
                && ((char *)dest <= ((char *)src + count));
    if (flag) {
        char *de = (char *)dest + count -1;
        char *sr = (char *)src + count -1;
        while(count--) {
            *de-- = *sr--;
        }
    } else {
        memcpy(dest, src, count);
    }

    return dest;
}

/*******strcpy*******/
char* strcpy(char *dest, const char* src) {
    if(dest==NULL || src ==NULL) return NULL;
    char *tmp = dest;
    while((*dest++=*src++) != '\n');
    return dest;
}

/*******atoi*******/
// - + .
int atoi(const char *str) {
    int res(0);
    bool plus(true);

    // '   123'
    const char *cur = str;
    while(*cur == ' ') ++cur;

    // '  +123'
    if(*cur=='+' || *cur=='-') {
        plus = (*cur++=='+');
    }

    if(*cur<'1' || *cur>'9') return 0;
    while(*cur != '\n' && ('1'<=*cur) && (*cur<='9')) {
        res = res*10 + (*cur-'0');
        ++cur;;
    }

    return plus ? res : (-res);
}

int main() {
    char s1[5] = {'a', 'b', 'c', 'd', 'e'};
    char d1[5];
    memcpy(d1, s1, 5);
    for(int i=0; i<5; ++i) {
        std::cout << d1[i] << std::endl;
    }

    char d2[5];
    memmove(d2, s1, 5);
    for(int i=0; i<5; ++i) {
        std::cout << d2[i] << std::endl;
    }

    std::cout << "\n";
    char s3[5] = {'a', 'b', 'c', 'd', 'e'};
    memmove(s3+2, s3, 3);
    for(int i=0; i<5; ++i) {
        std::cout << s3[i] << std::endl;
    }

    // strcpy test
    const  char *src = "Take the test";
    auto dst = std::make_unique<char[]>(std::strlen(src) + 1);
    strcpy(dst.get(), src);
    dst[0] = 'M';
    std::cout << src << '\n';
    std::cout << dst.get() << '\n';

    // atoi
    const char *str1 = "42";
    const char *str2 = "3.14159";
    const char *str3 = "31337 with words";
    const char *str4 = "words and 2";
    int num1 = atoi(str1);
    int num2 = atoi(str2);
    int num3 = atoi(str3);
    int num4 = atoi(str4);

    std::cout << '\n';
    std::cout << num1 << '\n';
    std::cout << num2 << '\n';
    std::cout << num3 << '\n';
    std::cout << num4 << '\n';
}