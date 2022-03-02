#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <time.h>
#include <math.h>

#define mSize 2000

using namespace std;

//密钥[结构体]
struct subK
{
    string k;
};

//初始IP置换函数
string init_IP(const string &str)
{
    int array[] = {58, 50, 42, 34, 26, 18, 10, 2,
                   60, 52, 44, 36, 28, 20, 12, 4,
                   62, 54, 46, 38, 30, 22, 14, 6,
                   64, 56, 48, 40, 32, 24, 16, 8,
                   57, 49, 41, 33, 25, 17, 9, 1,
                   59, 51, 43, 35, 27, 19, 11, 3,
                   61, 53, 45, 37, 29, 21, 13, 5,
                   63, 55, 47, 39, 31, 23, 15, 7};
    string temp = "";
    for (int i = 0; i < 64; i++)
    {
        temp += str[array[i] - 1];
    }
    return temp;
}

//进行异或运算
string xor_T(const string &str1, const string &str2)
{
    string str = "";
    int length = str1.length();
    for (int i = 0; i < length; i++)
    {
        if (str1[i] == str2[i])
        {
            str += '0';
        }
        else
        {
            str += '1';
        }
    }
    return str;
}

// char到int的转换，用于S盒
int toInt_2(const string &str10)
{
    int num = 0;
    if (str10[0] == '1')
    {
        num += 2;
    }
    if (str10[5] == '1')
    {
        num += 1;
    }
    return num;
}

// char到int的转换，用于S盒
int toInt_4(const string &str10)
{
    int num = 0;
    if (str10[1] == '1')
    {
        num += 8;
    }
    if (str10[2] == '1')
    {
        num += 4;
    }
    if (str10[3] == '1')
    {
        num += 2;
    }
    if (str10[4] == '1')
    {
        num += 1;
    }
    return num;
}

//判断S盒中的位置，并返回结果
string judge(const string &str, int s1[4][16])
{
    int n;
    int m;
    string result = "";
    n = toInt_2(str);
    m = toInt_4(str);
    int pos = s1[n][m];
    string s = "";
    while (pos)
    {
        if (pos % 2 == 0)
        {
            s += '0';
        }
        else
        {
            s += '1';
        }
        pos /= 2;
    }
    int strLength = s.length();
    if (strLength < 4)
    {
        for (int i = strLength; i < 4; i++)
        {
            s += '0';
        }
    }
    reverse(s.begin(), s.end());
    return s;
}

// f轮转函数
string f(const string &Ri, const subK subk)
{
    string R(Ri);
    int E[] = {32, 1, 2, 3, 4, 5,
               4, 5, 6, 7, 8, 9,
               8, 9, 10, 11, 12, 13,
               12, 13, 14, 15, 16, 17,
               16, 17, 18, 19, 20, 21,
               20, 21, 22, 23, 24, 25,
               24, 25, 26, 27, 28, 29,
               28, 29, 30, 31, 32, 1};
    string R_E = "";
    for (int i = 0; i < 48; i++)
    {
        R_E += R[E[i] - 1];
    }
    string str2 = xor_T(R_E, subk.k);

    string str10(str2.substr(0, 6));
    string str11(str2.substr(6, 6));
    string str12(str2.substr(12, 6));
    string str13(str2.substr(18, 6));
    string str14(str2.substr(24, 6));
    string str15(str2.substr(30, 6));
    string str16(str2.substr(36, 6));
    string str17(str2.substr(42, 6));

    int S1[4][16] = {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

    int S2[4][16] = {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

    int S3[4][16] = {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};
    int S4[4][16] = {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};
    int S5[4][16] = {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};
    int S6[4][16] = {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};
    int S7[4][16] = {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};
    int S8[4][16] = {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};
    string str100 = judge(str10, S1);
    str100 += judge(str11, S2);
    str100 += judge(str12, S3);
    str100 += judge(str13, S4);
    str100 += judge(str14, S5);
    str100 += judge(str15, S6);
    str100 += judge(str16, S7);
    str100 += judge(str17, S8);
    // P置换
    int p[] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25};
    string finalStr = "";
    for (int i = 0; i < 32; i++)
    {
        finalStr += str100[p[i] - 1];
    }
    return finalStr;
}

// 16轮T迭代，用于加密
string iteration_T(const string &str, const subK subk[])
{
    int times = 0;
    string temp(str);
    string left(temp.substr(0, 32));
    string right(temp.substr(32, 32));
    string temp1;
    while (times < 16)
    {
        temp1 = right;
        right = xor_T(left, f(right, subk[times]));
        left = temp1;
        // cout << "L" << times << ":    " << left << endl;
        // cout << "R" << times << ":    " << right << endl;
        times++;
    }
    return right + left; //交换置换
}

// 16轮T迭代，用于解密
string iteration_T_1(const string &str, const subK subk[])
{
    int times = 15;
    string temp(str);
    string left(temp.substr(0, 32));
    string right(temp.substr(32, 32));
    string temp1;
    while (times >= 0)
    {
        temp1 = right;
        right = xor_T(left, f(right, subk[times]));
        left = temp1;
        // cout << "L" << 16 - times << ":    " << left << endl;
        // cout << "R" << 16 - times << ":    " << right << endl;
        times--;
    }
    return right + left; //交换置换
}

/*
 *函数名称：productSubK
 *函数功能：16个子密钥生成函数
 *函数参数：string key-密钥（bin） 
           subK subk[]-子密钥
 *  返回值：none
 */
void productSubK(const string &key, subK subk[])
{
    string tempKey(key);
    //对密钥进行PC-1置换
    int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
                  1, 58, 50, 42, 34, 26, 18,
                  10, 2, 59, 51, 43, 35, 27,
                  19, 11, 3, 60, 52, 44, 36,
                  3, 55, 47, 39, 31, 23, 15,
                  7, 62, 54, 46, 38, 30, 22,
                  14, 6, 61, 53, 45, 37, 29,
                  21, 13, 5, 28, 20, 12, 4};

    string key_56 = "";
    for (int i = 0; i < 56; i++)
    {
        key_56 += tempKey[PC_1[i] - 1];
    }
    string Ci(key_56.substr(0, 28));
    string Di(key_56.substr(28, 28));
    int times = 0;
    while (times < 16)
    {
        // LS()
        if (times + 1 == 1 || times + 1 == 2 || times + 1 == 9 || times + 1 == 16)
        {
            string block1(Ci.substr(0, 1));
            string temp1(Ci.substr(1, 27));
            Ci = "";
            Ci += temp1;
            Ci += block1;
            string block2(Di.substr(0, 1));
            string temp2(Di.substr(1, 27));
            Di = "";
            Di += temp2;
            Di += block2;
        }
        else
        {
            string block1(Ci.substr(0, 2));
            string temp1(Ci.substr(2, 27));
            Ci = "";
            Ci += temp1;
            Ci += block1;
            string block2(Di.substr(0, 2));
            string temp2(Di.substr(2, 27));
            Di = "";
            Di += temp2;
            Di += block2;
        }
        // PC-2置换
        string subKK(Ci);
        subKK += Di;
        int PC_2[] = {
            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32};
        string aaa = "";
        for (int i = 0; i < 48; i++)
        {
            aaa += subKK[PC_2[i] - 1];
        }
        subk[times].k = "";
        subk[times].k += aaa;
        times++;
    }
}

/*
 *函数名称：res_IP
 *函数功能：对输入字符进行IP逆置换
 *函数参数：string str3
 *  返回值：被逆置换后的字符串
 */
string res_IP(const string &str3)
{
    int res_P[] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};
    string str = "";
    for (int i = 0; i < 64; i++)
    {
        str += str3[res_P[i] - 1];
    }
    return str;
}

/*
 *函数名称：toBin
 *函数功能：正常字符串转二进制字符串
 *函数参数：string input
 *  返回值：二进制化字符串
 */
string toBin(string input)
{
    string t = "";
    int size = input.length();
    for (int i = 0; i < size; i++)
    {
        int num = (int)input[i];
        string temp = "";
        while (num)
        {
            if (num % 2 == 0)
            {
                temp += '0';
            }
            else
            {
                temp += '1';
            }
            num /= 2;
        }
        for (int j = temp.length(); j < 8; j++)
        {
            temp += '0';
        }
        reverse(temp.begin(), temp.end());
        t += temp;
    }
    return t;
}

/*
 *函数名称：getStr
 *函数功能：给明文做padding处理，让其长度变为8的倍数
 *函数参数：string i                         明文
 *  返回值：padding后的字符串
 */
string getStr(const string i)
{
    // padding
    string input = i;
    int size = 8 - input.size() % 8;
    int num = size;
    while (size--)
    {
        input += num + '0';
    }
    input = toBin(input);
    return input;
}

/*
 *函数名称：toStr
 *函数功能：二进制字符串转字符字符串
 *函数参数：string temp-二进制明文
 *  返回值：字符字符串
 */
string toStr(const string temp)
{
    string s = temp;
    string s1 = "";
    int size = s.size() / 8;
    for (int i = 0; i < size; i++)
    {
        string t = s.substr(i * 8, 8);
        int num = 0;
        for (int j = 0; j < 8; j++)
        {
            if (t[j] == '1')
            {
                num += pow(2, 8 - j - 1);
            }
        }
        char c = num;
        s1 += c;
    }
    return s1;
}

/*
 *函数名称：trans
 *函数功能：二进制字符串转字符字符串（这个函数有点多余）
 *函数参数：string temp-二进制明文
 *  返回值：字符字符串
 */
string trans(const string cleartext)
{
    string temp = cleartext;
    temp = toStr(temp);
    return temp;
}

/*
 *函数名称： deal
 *函数功能：去除消息尾部padding部分的内容
 *函数参数： string t     解密后的字符串
 *  返回值：去padding后的字符串
 */
string deal(string t)
{
    char c = t[t.size() - 1];
    int l = c - '0';
    int len = t.size() - l; //实际长度
    string temp(t.substr(0, len));
    return temp;
}

/*
 *函数名称：EE
 *函数功能：将已经padding的明文分为（明文长度/64）段，对每段长为64的subText进行加密
           加密过程为：1、IP置换
                      2、16轮T置换
                      3、IP逆置换
 *函数参数：string m-已padding明文
           subK subk[]-16个子密钥
 *  返回值：被加密的密文
 */
string EE(const string m, subK subk[])
{
    string text = "";
    int times = m.size() / 64;
    for (int i = 0; i < times; i++)
    {
        string temp = m.substr(i * 64, 64);
        temp = init_IP(temp);
        // cout << "初始IP置换结果：" << temp << endl;
        temp = iteration_T(temp, subk);
        temp = res_IP(temp);
        text += temp;
    }
    return text;
}

/*
 *函数名称：DD
 *函数功能：将接受的密文分为（密文长度/64）段，对每段长度为64的subText进行解密
           加密过程为：1、IP置换
                      2、16轮T置换（使用的密钥次序与加密时是相反的，其他相同）
                      3、IP逆置换
 *函数参数：string ciphertext-密文
           subK subk[]-16个子密钥
 *  返回值：被解密的明文
 */
string DD(const string ciphertext, const subK subk[])
{
    int times = ciphertext.size() / 64;
    string text = "";
    for (int i = 0; i < times; i++)
    {
        string temp = ciphertext.substr(i * 64, 64);
        temp = init_IP(temp);
        // cout << "初始IP置换结果：" << temp << endl;
        temp = iteration_T_1(temp, subk);
        temp = res_IP(temp);
        temp = trans(temp);
        text += temp;
    }
    return text;
}

/*
 *函数名称：getKey
 *函数功能：将字符串翻译成响应的二进制格式
 *函数参数：string k-字符串格式的密钥
 *  返回值：二进制格式的密钥
 */
string getKey(const string k)
{
    string input = k;
    input = toBin(input);
    return input;
}

/*
 *函数名称：getFirst
 *函数功能：根据分隔符获得前一部分的字符串
 *函数参数：string s2-有分隔符的字符串
 *  返回值：字符串的前半段
 */
string getFirst(string s2)
{
    string a;
    int size = s2.length();
    for (int i = 0; i < size; i++)
    {
        if (s2[i] == ':' && s2[i + 1] == ':' && s2[i + 2] == ':')
        {
            a = s2.substr(0, i);
            break;
        }
    }
    return a;
}

/*
 *函数名称：getSecond
 *函数功能：根据分隔符获得后一部分的字符串
 *函数参数：string s2-有分隔符的字符串
 *  返回值：字符串的后半段
 */
string getSecond(string s2)
{
    string a;
    int size = s2.length();
    for (int i = 0; i < size; i++)
    {
        if (s2[i] == ':' && s2[i + 1] == ':' && s2[i + 2] == ':')
        {
            a = s2.substr(i + 3, size - i - 3);
            break;
        }
    }
    return a;
}

/*
 *函数名称：hash
 *函数功能：根据用户名和密码，自行设计的一个hash函数计算方法
 *函数参数：string name-用户名
 *         string pass-密码
 *  返回值：hash的结果-密钥key，长度为8
 */
string hash(string name, string pass)
{
    int table[52];
    for (int i = 0; i < 52; i++)
    {
        table[i] = 1;
    }
    //将name与密码合并为一段字符串
    string value = name;
    value += pass;
    int size = value.size();
    // hash
    //num = 字符的ASICC码 mod 52
    //table[num] += 25
    for (int i = 0; i < size; i++)
    {
        int num = (int)value[i];
        num = num % 52;
        table[num] += 25;
    }
    //计算key
    //根据table[]中的数值大小,key += table[i]
    //当key大于pow(2, 20),退出累加计算
    //char c = key %= 129
    //如果c的ASICC码小于40，则c += 41
    //因为一些字符的ASICC码在0-40之间不能显示
    //key += c
    string key = "";
    int k = 0;
    for (int i = 0; i < 52; i++)
    {
        if (table[i] != 1)
        {
            k += i;
            k *= 10;
            if (k > pow(2, 20))
            {
                break;
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        int x = k % 129;
        if (x < 40)
        {
            x += 41;
        }
        char c = x;
        key += c;
        k /= 8;
    }
    return key;
}

/*
 *函数名称：E
 *函数功能：字符串加密入口
 *函数参数：string k-密钥
           string message-明文
 *  返回值：被加密的明文
 */
string E(const string k, const string message)
{
    string m = getStr(message);
    //密钥本地会存，不用生成
    string key = getKey(k);
    subK subk[16];
    productSubK(key, subk);
    // for (int i = 0; i < 16; i++) {
    //     cout << "子密钥" << i + 1 << "为:" << subk[i].k << endl;
    // }
    // cout << "原文为：" << m << endl;

    string text = EE(m, subk);
    // cout << "密文为：" << text << endl;
    return text;
}

/*
 *函数名称：E
 *函数功能：字符串解密入口
 *函数参数：string k-密钥
           string message-密文
 *  返回值：被解密的明文
 */
string D(const string k, const string message)
{
    string key = getKey(k);
    subK subk[16];
    productSubK(key, subk);
    // for (int i = 0; i < 16; i++) {
    //     cout << "子密钥" << i + 1 << "为:" << subk[i].k << endl;
    // }
    // cout << "原文为：" << message << endl;

    //解密
    string text1 = DD(message, subk);
    text1 = deal(text1); //去除padding的部分
    // cout << "解密后：" << text1 << endl;
    return text1;
}

/*
 *函数名称：getTime
 *函数功能：获取本函数执行时间
 *函数参数：none
 *  返回值：字符串格式time
 */
string getTime()
{
    time_t t = time(NULL);
    // cout << t << endl;
    string time = "";
    while (t)
    {
        int t1 = t % 10;
        char c = t1 + '0';
        time += c;
        t /= 10;
    }
    return time;
}

/*
 *函数名称：main
 *函数功能：创建测试用例
 *函数参数：none
 *  返回值：0
 */
int main()
{
    string message = "two tiggers has each other!";
    string key = "12345678";
    string etext = E(key, message);
    cout << "Origial message = " << message << endl;
    cout << "key = " << key << endl;
    cout << "eText = " << etext << endl;
    cout << "dText = " << D(key, etext) << endl;
    return 0;
}
