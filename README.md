# utf8转 unicode原码/utf32 库

核心字符转换函数为**纯函数**，没有副作用

测试的编译器版本：

- gcc10，gcc11

注意utf32编码与unicode编码相同，可以认为相同。但是要注意utf32的字节序与CPU字节序相同，x86和AMD64等大部分CPU使用小端字节序。

# unicode 与 utf8编码对应范围如下

```bash
 |  Unicode符号范围     | UTF-8编码方式                                        |首字节大小
n|  (十六进制)          | (二进制)                                             |(10进制)
-+----------------------+------------------------------------------------------+---
1|0000 0000 - 0000 007F|                                             0xxxxxxx|[0,127]
2|0000 0080 - 0000 07FF|                                    110xxxxx 10xxxxxx|192,223]
3|0000 0800 - 0000 FFFF|                           1110xxxx 10xxxxxx 10xxxxxx|224,239]
4|0001 0000 - 0010 FFFF|                  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx|240,247]
5|0020 0000 - 03FF FFFF|         111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx|248,251]
6|0400 0000 - 7FFF FFFF|1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx|252,253]
```

# 用法

## 1. 下载本库

```bash
git clone https://gitee.com/ryjer/lib_utf8_unicode.git
```

## 2. 使用示例

通过 `#include`  导入头文件 `utf8_unicode.h`，然后就可以使用其中的函数了

```C
// 先导入 utf8_unicode.h 头文件
#include "utf8_unicode.h"

// 然后下面就可以调用其中的函数了
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
```

# 说明

## 类型

**utf8字符体**类型，支持最长6字节的utf8字符编码。由于C语言不支持直接返回数组，需要使用结构体包装返回

```c++
// 同时表示 字节长度 和 编码内容，同时解决c语言不能返回数组的问题
typedef struct{
    uint8_t 长度;    //以字节为单位
    uint8_t 编码[6]; // 最长6字节
} utf8字符体;
```

**unicode字符**类型，使用**无符号32位整数** uint32 存储解码后的unicode编码

```c++
typedef uint32_t unicode字符;
```

## 1. 获取utf8字符(FILE *输入文件) -> utf8字符体 

功能：从指定输入文件中读取**一个utf8字符**，然后返回包含该utf8字节串的 uint64_t 类型的64位数。

有以下3种思路，最终使用思路2

思路1：利用utf8中非首字节的前两位是`10`的特征，每次取一字节，然后使用掩码取前两位(ch & 11000000)。只要不是`10` 就结束并返回

思路2：根据首字节前几位的**长度指示**，决定下一步应该再取几个字节

思路3：由于首字节前几位的指示位，因而首字节作为数字的大小范围是不重叠的。可以用不同的区间来区分对应utf8的字节数。

## 2. 计算utf8占用字节数(uint8_t 首字节) -> int

**纯函数**

功能：根据utf8编码首字节，计算整个utf8字节串所占字节长度。

提示：需要先从首字节得到整个utf8字节串的字节数，才能读入单个utf字符的编码

## 3. utf8转unicode(utf8字符体 utf8编码) -> unicode字符

**纯函数**

功能：将一个**utf8字符体**转换为**unicode字符原码**返回，注意utf32le与unicode原码相同

返回值：对应的unicode原码

注意：这里使用 **utf8字符体**，并返回 **unicode字符**。这是本文件定义的2种类型

## 4. unicode转utf8(unicode字符 字符编码) -> utf8字符体

**纯函数**

功能：将**unicode字符编码**转换为utf8字节串，包装为**utf8字符体**返回