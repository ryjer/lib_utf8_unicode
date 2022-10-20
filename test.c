/* test.c 测试文件
 */
#include "utf8_unicode.h"

// main函数进行测试
int main() {
    FILE * inputFile;
    inputFile = fopen("test.txt", "r");
    utf8字符体 ch = 获取utf8字符(inputFile); // 读取utf8编码
    printf("输入utf8: 长度:%d\t 编码: %02x %02x %02x\n", ch.长度, ch.编码[0], ch.编码[1], ch.编码[2]);
    unicode字符 unicode编码 = utf8转unicode(ch); // 转换为 unicode 编码
    printf("utf8转unicode: %08x\n", unicode编码);
    utf8字符体 字符体 = unicode转utf8(unicode编码);
    printf("unicode转utf8: 长度:%d\t utf8: %x %x %x\n", 字符体.长度, 字符体.编码[0], 字符体.编码[1], 字符体.编码[2]);
    return 0;
}