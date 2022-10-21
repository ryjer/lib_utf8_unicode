#ifndef UTF8_UNICODE_H
    #define UTF8_UNICODE_H
    // 将utf8 转换为 utf32小端字节序
    // 包名：utf8 或者 unicode
    #include <stdio.h>
    #include <stdint.h>
    #include <ctype.h>
    #include <stdbool.h>

    // 同时表示 字节长度 和 编码内容，同时解决c语言不能返回数组的问题
    typedef struct{
        int8_t 长度; //以字节为单位
        uint8_t 编码[6]; // 最长6字节
    } utf8字符体;

    // typedef uint32_t unicodeChar;
    typedef uint32_t unicode字符;
    
    // 提供以下函数接口
    utf8字符体   文件_读取utf8字符(FILE *输入文件);                    // √ 已测试 
    void         文件_写入utf8字符(FILE *输出文件, utf8字符体 字符体);  // √ 已测试
    utf8字符体   读取utf8字符();                                       // √ 已测试
    void         写入utf8字符(utf8字符体 字符体);                      // √ 已测试
    int          计算utf8占用字节数(uint8_t 首字节);                   // √ 已测试 
    unicode字符  utf8转unicode(utf8字符体 utf8编码);                   // √ 已测试 
    utf8字符体   unicode转utf8(unicode字符 字符编码);                  // √ 已测试
    // ASCII判断函数
    bool 是数字(unicode字符 字符);
    bool 是10进制数字(unicode字符 字符);
    bool 是16进制数字(unicode字符 字符);
    bool 是小写字母(unicode字符 字符);
    bool 是大写字母(unicode字符 字符);
    bool 是字母(unicode字符 字符);
    bool 是字母数字(unicode字符 字符);
    bool 是标点符号(unicode字符 字符);
    bool 是图形字符(unicode字符 字符);
    bool 是空白(unicode字符 字符);
    bool 是可打印字符(unicode字符 字符);
    bool 是控制字符(unicode字符 字符);
    bool 是ascii(unicode字符 字符);
    // ASCII转换函数
    unicode字符 转小写(unicode字符 字符);
    unicode字符 转大写(unicode字符 字符);
    // 汉字判断函数
    bool 是汉字(unicode字符 字符);         // 不包括标点符号
    bool 是中文标点符号(unicode字符 字符);
    // 数学判断函数
    bool 是数学运算符(unicode字符 字符);
    // 希腊字母判断函数
    bool 是希腊字母(unicode字符 字符);
#endif