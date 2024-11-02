project('AhogeUtil', 'cpp', version: '0.0.1')

glog_dep = dependency('glog', required: true)

inc = include_directories('.')

src_list = ['ahoge_string.cpp', 'error.cpp', 'vector.cpp']

lib = static_library('AhogeUtil', src_list, dependencies: [glog_dep])
