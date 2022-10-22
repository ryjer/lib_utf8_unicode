/* test.c 测试文件
 */
#include "utf8_unicode.h"

// gcc -g -Wall test.c utf8_unicode.c && ./a.out
// 字符类型判断测试
int main() {
    FILE * inputFile;
    inputFile = fopen("test.txt", "r");
    // printf("字符\t utf8\t\t utf32\t\t 汉字\t 标点\t 希腊\t 10数字\t 16数字\t abc\t ABC\t 字母\t AB12\t 符号\t 图形\t 空白\t 打印\t 控制\t ascii\n");
    printf("字符\t utf8\t\t utf32\t\t 数学运算符\n");
    utf8字符体 输入字符 = 文件_读取utf8字符(inputFile); // 读取utf8编码
    while (输入字符.长度 != 0) {
        if (输入字符.长度 == 1 && 输入字符.编码[0] == '\n') {
            printf("\\n");
        } else {
            写入utf8字符(输入字符);
        }
        printf("\t {%d [%02x %02x %02x]}\t ", 输入字符.长度, 输入字符.编码[0], 输入字符.编码[1], 输入字符.编码[2]);
        unicode字符 unicode编码 = utf8转unicode(输入字符); // 转换为 unicode 编码
        printf("%08x\t ", unicode编码);
        // 判断打印
        if (是数学运算符(unicode编码))     {printf("√\t "); } else{printf(" \t ");}
        // if (是汉字(unicode编码))     {printf("√\t "); } else{printf(" \t ");}
        // if (是中文标点符号(unicode编码)){printf("√\t "); } else{printf(" \t ");}
        // if (是希腊字母(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是10进制数字(unicode编码)){printf("√\t "); } else{printf(" \t ");}
        // if (是16进制数字(unicode编码)){printf("√\t "); } else{printf(" \t ");}
        // if (是小写字母(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是大写字母(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是字母(unicode编码))     {printf("√\t "); } else{printf(" \t ");}
        // if (是字母数字(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是标点符号(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是图形字符(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是空白(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是打印字符(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是控制字符(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        // if (是ascii(unicode编码))  {printf("√\t "); } else{printf(" \t ");}
        fputc('\n', stdout);
        // 读入下一个字符
        输入字符=文件_读取utf8字符(inputFile);
    }
    return 0;
}

// 基本编码测试
// int main() {
//     FILE * inputFile;
//     inputFile = fopen("test.txt", "r");
//     printf("字符\t utf8\t\t unicode\t 再编码\t\t 重显\n");
//     utf8字符体 输入字符 = 文件_读取utf8字符(inputFile); // 读取utf8编码
//     while (输入字符.长度 != 0) {
//         写入utf8字符(输入字符);
//         printf("\t {%d {%02x %02x %02x}}\t ", 输入字符.长度, 输入字符.编码[0], 输入字符.编码[1], 输入字符.编码[2]);
//         unicode字符 unicode编码 = utf8转unicode(输入字符); // 转换为 unicode 编码
//         printf("%08x\t ", unicode编码);
//         utf8字符体 字符体 = unicode转utf8(unicode编码);
//         printf("{%d {%x %x %x}}\t ", 字符体.长度, 字符体.编码[0], 字符体.编码[1], 字符体.编码[2]);
//         写入utf8字符(字符体);
//         fputc('\n', stdout);
//         // 读入下一个字符
//         输入字符=文件_读取utf8字符(inputFile);
//     }
//     return 0;
// }