project('AhogeUtil', 'cpp', version: '0.0.1')

src_list = ['ahoge_string.cpp', 'error.cpp', 'vector.cpp']

lib = static_library('AhogeUtil', src_list)

test_exe = executable('AhogeUtil-test', 'test.cpp', link_with: lib)

test('lib-test', test_exe)
