# AhogeUtil

![Logo](./doc/ahoge_logo.png)

[English](./README.md)

一些我自己在项目中用的代码。目前包括向量（`AhogeUtil::Vector2<T>` and `AhogeUtil::Vector3<T>`），以及一个简单~~（简陋）~~的UTF-32字符串（`AhogeUtil::String`）。~~*你就说这个字符串能不能用吧*~~

该库永远都在开发中，除非我弃坑C++。如你所见，还缺失不少功能。*在做了在做了*

## 依赖

### Windows

你需要安装 [glog](https://github.com/google/glog) 和 [iconv](https://www.gnu.org/software/libiconv/)。

### Debian(Ubuntu)

```bash
sudo apt install libgoogle-glog-dev libc6-dev
```

### Arch Linux

说真的，我真的不知道在Arch Linux下需要装哪些包。

## 编译

```bash
mkdir build
meson compile -C build
```

## 提示

从`std::string`或C风格的字符串`char *`构造`AhogeUtil::String`时，构造函数会假设输入的字符串是UTF-8编码的，如果你使用的不是UTF-8。你将不得不自己修复这一问题。 ：）（非常简单的）

## LICENSE

Copyright (c) 2024 BlockyDeer\<blockydeer@outlook.com\>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
