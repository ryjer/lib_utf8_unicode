#include "utf8_unicode.h"

// 从文件中读取一个 utf8字符的编码，将其存入 utf8字符体 返回 √
utf8字符体 文件_读取utf8字符(FILE *输入文件) {
    utf8字符体 utf8;
    uint8_t 字节;
    if ((字节=fgetc(输入文件)) == (uint8_t)EOF) { // 读取第一个字节
        utf8.长度 = 0;                   // EOF错误，则长度为0
        return utf8;
    }
    // 判断字节数
    utf8.长度 = 计算utf8占用字节数(字节);
    if (utf8.长度 == -1) {
        fprintf(stderr, "文件 utf8 编码错误，有字符编码不规范!\n");
    }
    // 配置第一个字节
    utf8.编码[0] = 字节;
    // 根据字节数，读入剩余字节
    for (int i = 1; i < utf8.长度; i++) {
        字节 = fgetc(输入文件); // 读入一个字节
        utf8.编码[i] = 字节;
    }
    return utf8;
}
// 从标准输入stdin读取一个 utf字符的编码，将其存入 utf8字符体 返回 √
utf8字符体 读取utf8字符() {
    return 文件_读取utf8字符(stdin);
}
// 向指定输出文件写入一个 utf8字符 √
void 文件_写入utf8字符(FILE *输出文件, utf8字符体 字符体) {
    for (int i = 0; i < 字符体.长度; i++) {
        fputc(字符体.编码[i], 输出文件);
    }
}
// 向标准输出stdout写入一个 utf8字符的编码 √
void 写入utf8字符(utf8字符体 字符体) {
    return 文件_写入utf8字符(stdout, 字符体);
}
// utf8 首字节解析，根据首字节计算utf8总占用字节 √
int 计算utf8占用字节数(uint8_t 首字节) {
    int 占用字节数 = 0;
    uint8_t 第一位 = (首字节 & 0b10000000); // 获取第一位
    if (第一位 == 0) { // 如果是 0xxxxxxx 单字节格式，直接返回1
        return 1;
    } else { // 否则为多字节格式 
        // 每次取第一位，直到取出0为止。计数即为占用字节数
        while ((首字节 & 0b10000000) != 0) { // 00 000000
            占用字节数++;
            首字节 <<= 1;  // 左移1位
        }
    }
    // 错误检查
    if (占用字节数 == 1) {return -1;}
    return 占用字节数;
}
// 将一个 utf8字节串 转换为 unicode编码字符 √
unicode字符 utf8转unicode(utf8字符体 字符体) {
    unicode字符 unicode编码 = 0;
    // 文件结束检查 EOF
    if (字符体.长度 == 0) {
        return (unicode字符) (EOF);
    }
    if (字符体.长度 == 1) { // 单字节编码
        return (unicode字符) (字符体.编码[0]);
    }
    // 循环从编码数组中取位,然后将 unicode 编码对应位置位
    unicode字符 tmp = 0;
    int 位填充指针 = 0; // 用于指示 unicode 中从低位到高位中没有填充的位 位址,协助向左位移
    // 从后向前处理,先首字节后面的 10xxxxxx 格式字节
    for (int i = 字符体.长度-1; i > 0; i--) {
        tmp = (unicode字符) (字符体.编码[i] & 0b00111111);  // 取字节低6位,然后拓展成32位
        unicode编码 |= tmp << 位填充指针; // 根据位指针,将6位填入编码中
        位填充指针 += 6; // 更新位指针位置
    }
    // 处理首字节
    uint8_t 首字节掩码 = 0b11111111 >> (字符体.长度); // 掩码,用于取首字节中的编码位,这里把连续1后面的0也算在内
    uint8_t 首字节有效位 = (字符体.编码[0] & 首字节掩码); // 使用掩码取 低地址 的编码位
    unicode编码 |= (unicode字符) (首字节有效位) << 位填充指针 ; // 根据位指针,将首字节的有效编码填入
    return unicode编码;
}
// 将一个32位 unicode编码字符 转换为 utf8多字节串 √
utf8字符体 unicode转utf8(unicode字符 字符编码) {
    utf8字符体 字符体;
    // 根据 unicode 编码大小判断对应utf8字节数
    if (字符编码 <= 0x0000007F) {
        字符体.长度 = 1;
    } else if (字符编码 <= 0x000007FF) {
        字符体.长度 = 2;
    } else if (字符编码 <= 0x0000FFFF) {
        字符体.长度 = 3;
    } else if (字符编码 <= 0x0010FFFF) {
        字符体.长度 = 4;
    } else if (字符编码 <= 0x03FFFFFF) {
        字符体.长度 = 5;
    } else if (字符编码 <= 0x7FFFFFFF) {
        字符体.长度 = 6;
    } else { // 其它例外情况视作非法
        字符体.长度 = 0;
    }
    // 根据字节长度生成utf字节,从unicode低位每次取6位,最后取首字节
    for (int i = 字符体.长度-1; i > 0; i--) {
        字符体.编码[i] = 字符编码 & 0b00111111; // 取低6位
        字符体.编码[i] |= 0b10000000;
        字符编码 >>= 6;
    }
    if (字符体.长度 == 1) {    // 当为ascii 单字节编码时,没有位长指示,需要单独处理
        字符体.编码[0] = (uint8_t) (字符编码); 
    } else {  // 只有是多字节编码时,才需要首字节添加 标记
        字符体.编码[0] = (uint8_t) (字符编码) | (0b11111110 << (7-字符体.长度));
    }
    return 字符体;
}
/******************************************************************************
*                            ASCII判断函数
 ******************************************************************************/
// 数字集合 {0 1 2 3 4 5 6 7 8 9}
bool 是数字(unicode字符 字符) {
    if (0x30<=字符 && 字符<=0x39) {
        return true;
    } else {
        return false;
    }
}
// 数字集合 {0 1 2 3 4 5 6 7 8 9}
bool 是10进制数字(unicode字符 字符) {
    if (0x30<=字符 && 字符<=0x39) {
        return true;
    } else {
        return false;
    }
}
// {0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f}
bool 是16进制数字(unicode字符 字符) {
    if (字符 <= 0x7F && isxdigit(字符)) {
        return true;
    } else {
        return false;
    }
}
// 集合 {a b c d e f g h i j k l m n o p q r s t u v w x y z}
bool 是小写字母(unicode字符 字符) {
    if (字符 <= 0x7F && islower(字符)) {
        return true;
    } else {
        return false;
    }
}
// 集合 {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z}
bool 是大写字母(unicode字符 字符) {
    if (字符 <= 0x7F && isupper(字符)) {
        return true;
    } else {
        return false;
    }
}
// 小写字母和大写字母
bool 是字母(unicode字符 字符) {
    if (字符 <= 0x7F && isalpha(字符)) {
        return true;
    } else {
        return false;
    }
}
// 字母和10进制数字
bool 是字母数字(unicode字符 字符) {
    if (字符 <= 0x7F && isalnum(字符)) {
        return true;
    } else {
        return false;
    }
}
// 集合{! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~}
bool 是标点符号(unicode字符 字符) {
    if (字符 <= 0x7F && ispunct(字符)) { 
        return true;
    } else {
        return false;
    }
}
// 字母、数字、标点 等可显示的图形
bool 是图形字符(unicode字符 字符) {
    if ((字符 <= 0x7F && isgraph(字符))) { 
        return true;
    } else {
        return false;
    }
}
// 空格 制表\t 换行\n 垂直制表\v 换页\f 回车\r
bool 是空白(unicode字符 字符) {
    if ((字符<=0x7F && isspace(字符)) || (字符==0x00A0 || 字符==0x3000)) { // 不间断空格\u00A0，全角空格(中文符号)\u3000,中文文章中使用;
        return true;
    } else {
        return false;
    }
}
// {数字、字母、标点符号、空白}
bool 是打印字符(unicode字符 字符) {
    if (字符 <= 0x7F && isprint(字符)) {
        return true;
    } else {
        return false;
    }
}
// 不可打印控制字符
bool 是控制字符(unicode字符 字符) {
    if (字符 <= 0x7F && iscntrl(字符)) {
        return true;
    } else {
        return false;
    }
}
// 是 ASCII 码
bool 是ascii(unicode字符 字符) {
    if (字符 <= 0x7F) {
        return true;
    } else {
        return false;
    }
}
/******************************************************************************
*                            ASCII转换函数
 ******************************************************************************/
// 转小写字母, 不能转换则直接返回
unicode字符 转小写(unicode字符 字符) {
    if (!是小写字母(字符)) {
        return (unicode字符)tolower(字符);
    } else {
        return 字符;
    }
}
// 转大写字母
unicode字符 转大写(unicode字符 字符) {
    if (!是大写字母(字符)) {
        return (unicode字符)toupper(字符);
    } else {
        return 字符;
    }
}
// 16进制字符转 uint类型，不进行错误检查，请保证输入正确
uint8_t 十六进制字符转数字(unicode字符 字符) {
    if (isdigit(字符)) {
        return 字符 - '0';
    } else {
        return 10 + (tolower(字符)-'a');
    }
}
/******************************************************************************
*                            汉字判断函数
 ******************************************************************************/
// 常见汉字，不包括标点符号，注意部分汉字可能无法识别
bool 是汉字(unicode字符 字符) {
    if ((0x4E00<=字符&&字符<=0x9FD5)||(0x3400<=字符&&字符<=0x4DB5)||(0x20000<=字符&&字符<=0x2A6D6)) {
        return true;
    } else {
        return false;
    }
}
// 常见中文标点
bool 是中文标点符号(unicode字符 字符) {
    if ((0x3000<=字符&&字符<=0x303F) || (0xFF00<=字符&&字符<=0xFFEF) || (0x2000<=字符&&字符<=0x206F)) { //后面是CJK横排标点符号[0x3000,0x303F]和半宽和全宽格式字符[0xFF00, 0xFFEF]
        return true;
    } else {
        return false;
    }
}
/******************************************************************************
*                            数学判断函数
 ******************************************************************************/
// 常见数学运算符，不包括ascii数学符号和其它罕见数学符号
bool 是数学运算符(unicode字符 字符) { // 标准乘号×和除÷不在数学平面上，其unicode为0xd7、0xf7
    if ((0x2200<=字符&&字符<=0x22FF)||(0x2A00<=字符&&字符<=0x2AFF)||(字符==0xd7||字符==0xf7)){
        return true;
    } else {
        return false;
    }
}
/******************************************************************************
*                            希腊字母判断函数
 ******************************************************************************/
// 在Unicode码表中，希腊字母和科普特语coptic字母是放在一起的。这里全部视作希腊字母
bool 是希腊字母(unicode字符 字符) {
    if ((0x0370<=字符&&字符<=0x03FF)) {
        return true;
    } else {
        return false;
    }
}