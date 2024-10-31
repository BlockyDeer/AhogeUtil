# AhogeUtil

![Logo](./doc/ahoge_logo.png)

[简体中文](./README_zh_cn.md)

A set of cpp code that I used in my project, which includes a simple vector(`AhogeUtil::Vector2<T>` and `AhogeUtil::Vector3<T>`) and a very simple UTF-32 string(`AhogeUtil::String`).

The library is under developing forever. As you see, some functions are still incomplete.

## Requirements

### Windows

You have to install [glog](https://github.com/google/glog) and [iconv](https://www.gnu.org/software/libiconv/)

### Debian(Ubuntu)

```bash
sudo apt install libgoogle-glog-dev libc6-dev
```

### Arch Linux

To be honest, I don't know what you have to install on Arch Linux.

## Compile The Library

```bash
mkdir build
meson compile -C build
```

## Tips

When constructing `AhogeUtil::String` from `std::string` or a C-style string `char *`, the constructor assumes the input string is UTF-8 encoded. If you are not using UTF-8, you have to resolve this issue yourself. ;) *It's easy, trust me.*

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
