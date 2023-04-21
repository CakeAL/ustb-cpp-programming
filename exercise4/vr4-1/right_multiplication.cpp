#include <iostream>
#include <cstring> //头文件加上这句，否则编译因为strlen问题不通过

const int maxn = 5000;
const int maxn2 = maxn * 2;

// 读入数字字符串，解析并存放到数组中
int read_str(char *s, int *a)
{
    int n = int(strlen(s)); //进行强制类型转换，size_t -> int
    for (int i = 0; i < n; ++i)
    {
        a[i] = s[n - i - 1] - '0';
    }
    return n;
}

int main(int argc, char *argv[])
{
    char s[maxn];
    int a[maxn2], b[maxn2], c[maxn2];
    int n1, n2;
    std::cin >> s;
    n1 = read_str(s, a);
    std::cin >> s;
    n2 = read_str(s, b);

    // 卷积操作
    for (int i = 0; i < n1 + n2; ++i) c[i] = 0;
    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < n2; ++j)
        {
            c[i + j] += a[i] * b[j];
            // 这里错了，原来是c[i+j-1] -1导致一开始i+j得0的时候存入了c[-1]位置导致末尾结果丢失
        }

    // 进位
    for (int i = 0, m = 0; i < n1 + n2; ++i)
    {
        c[i] += m;
        m = c[i] / 10;
        c[i] %= 10;
    }

    int n = n1 + n2 - 1;
    for (; c[n] == 0; --n);
    for (; n >= 0; --n)
    {
        std::cout << c[n];
    }
    std::cout << std::endl;
    return 0;
}
