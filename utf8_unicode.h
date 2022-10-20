#ifndef UTF8_UNICODE_H
    #define UTF8_UNICODE_H
    // 将utf8 转换为 utf32小端字节序
    // 包名：utf8 或者 unicode
    #include <stdio.h>
    #include <stdint.h>

    // 同时表示 字节长度 和 编码内容，同时解决c语言不能返回数组的问题
    typedef struct{
        uint8_t 长度; //以字节为单位
        uint8_t 编码[6]; // 最长6字节
    } utf8字符体;

    typedef uint32_t unicodeChar;
    typedef uint32_t unicode字符;

    utf8字符体   从文件读取utf8字符(FILE *输入文件); // √ 已测试 
    void         向文件写入utf8字符(FILE *输出文件, utf8字符体 字符体); // √ 已测试 
    int         计算utf8占用字节数(uint8_t 首字节); // √ 已测试 
    unicode字符    utf8转unicode(utf8字符体 utf8编码); // √ 已测试 
    utf8字符体   unicode转utf8(unicode字符 字符编码); // √ 已测试
#endif