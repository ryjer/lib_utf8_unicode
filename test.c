/* test.c 测试文件
 */
#include "utf8_unicode.h"

// main函数进行测试
int main() {
    FILE * inputFile;
    inputFile = fopen("test.txt", "r");
    printf("字符\t utf8\t\t unicode\t 再编码\t\t 重显\n");
    // 第1个utf8编码
    utf8字符体 输入字符 = 读取utf8字符(); // 读取utf8编码
    写入utf8字符(输入字符);
    printf("\t {%d {%02x %02x %02x}}\t ", 输入字符.长度, 输入字符.编码[0], 输入字符.编码[1], 输入字符.编码[2]);
    unicode字符 unicode编码 = utf8转unicode(输入字符); // 转换为 unicode 编码
    printf("%08x\t ", unicode编码);
    utf8字符体 字符体 = unicode转utf8(unicode编码);
    printf("{%d {%x %x %x}}\t ", 字符体.长度, 字符体.编码[0], 字符体.编码[1], 字符体.编码[2]);
    写入utf8字符(字符体);
    fputc('\n', stdout);
     // 第2个utf8编码
    return 0;
}