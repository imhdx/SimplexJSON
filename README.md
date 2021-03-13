# SimplexJSON

根据[教程](https://github.com/miloyip/json-tutorial) 使用C++重写的JSON解析程序

不过并没有教程完善，并没有完全实现JSON的全部标准。如对Unicode的支持，也没有实现其他类型的数字的解析。

主要重写了解析出来的字符串、数组和对象的存储方式，教程中由于使用C语言的原因，使用指针来实现变长数组等。这部分用C++的vector、unordered_map和string替换，简化了代码的编写， 减少了错误出现的概率，易于调试，不过在性能上有部分损失。

实现了如下解析

- null
- false
- true
- number
- array
- object
- string

## TODO

- 支持simplex_value转换成C++对象


- 完善测试

- 添加更多测试样例

