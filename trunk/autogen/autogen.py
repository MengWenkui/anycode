#!/urs/bin/evn python

import sys
import copy

class CodeSnippet:
  def __init__(self):
    self.lines = []
    self.tab = 2

  def dump(self):
    for line in self.lines:
      print line

  def add(self, content, indent = 0):
    line = ''
    for i in range(indent * self.tab):
      line += ' '
    line += content
    self.lines.append(line);

  def add_raw(self, raw_code):
    self.lines.extend(raw_code)
 
  def gen_include(self, filename):
    self.add('#include <%s>' %filename)

  def gen_using(self, namespace):
    self.add('using namespace %s;' %namespace);

  def gen_empty_line(self):
    self.add('')

  def gen_header_begin(self, filename):
    newname = filename.replace('_', '').upper()
    self.add('#ifndef TFS_MESSAGE_%s_H_' %newname)
    self.add('#define TFS_MESSAGE_%s_H_' %newname)
    self.gen_empty_line()
    self.gen_include('common/base_packet.h')
    self.gen_empty_line()
  
  def gen_header_end(self):
    self.add('#endif')
  
  def gen_namespace_begin(self):
    self.add('namespace tfs')
    self.add('{')
    self.add('namespace message', 1)
    self.add('{', 1)

  def gen_namespace_end(self):
    self.add('}', 1)
    self.add('}')

  def gen_class_begin(self, class_name, base_name):
    self.add('class %s: public %s' %(class_name, base_name), 2)
    self.add('{', 2)
   
  def gen_class_end(self):
    self.add('};', 2)
  
  def gen_area(self, type):
    self.add('%s:' %type, 3)

  def gen_func_declare(self, class_name):
    self.add('%s();' %class_name, 4)
    self.add('virtual ~%s();' %class_name, 4)
    self.add('virtual int serialize(common::Stream& output) const ;', 4)
    self.add('virtual int deserialize(common::Stream& input);', 4)
    self.add('virtual int64_t length() const;', 4)
    self.gen_empty_line()

  def gen_func_impl(self, class_name):
    self.add('%s::%s()' %(class_name, class_name), 2)
    self.add('{', 2)
    self.add('}', 2)
    self.gen_empty_line()
    
    self.add('%s::~%s()' %(class_name, class_name), 2)
    self.add('{', 2)
    self.add('}', 2)
    self.gen_empty_line()

    self.add('int %s::serialize(Stream& output) const' %class_name, 2)
    self.add('{', 2)
    self.add('}', 2)
    self.gen_empty_line()

    self.add('int %s::deserialize(Stream& input)' %class_name, 2)
    self.add('{', 2)
    self.add('}', 2)
    self.gen_empty_line()

    self.add('int64_t %s::length() const' %class_name, 2)
    self.add('{', 2)
    self.add('}', 2)
 
  def gen_variable(self, type, name):
    self.add('%s %s_;' %(type, name), 4)

  def gen_getter(self, type, name):
    self.add('%s get_%s() const' %(type, name), 4)
    self.add('{', 4)
    self.add('return %s_;' %name, 5)
    self.add('}', 4)
    self.gen_empty_line()

  def gen_setter(self, type, name):
    self.add('void set_%s(const %s %s)' %(name, type, name), 4)
    self.add('{', 4)
    self.add('%s_ = %s;' %(name, name), 5)
    self.add('}', 4)
    self.gen_empty_line()

  def gen_author(self):
    author = '''/*
* (C) 2007-2010 Alibaba Group Holding Limited.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*
* Authors:
*   linqing <linqing.zyd@taobao.com>
*      - initial release
*
*/'''
    self.add(author)
    self.gen_empty_line()

class ClassConfig:
  def __init__(self):
    self.class_name = ''
    self.base_name = ''
    self.var_list = ''
  
  def dump(self):
    print self.class_name
    print self.base_name
    print self.var_list

def gen_header_class(config):
  snippet = CodeSnippet()
  snippet.gen_class_begin(config.class_name, config.base_name)
  snippet.gen_area('public')
  snippet.gen_func_declare(config.class_name)
  for var in config.var_list:
    snippet.gen_setter(var[0], var[1])
    snippet.gen_getter(var[0], var[1])
  snippet.gen_area('private')
  for var in config.var_list:
    snippet.gen_variable(var[0], var[1])
  snippet.gen_class_end()
  return snippet

def gen_source_class(config):
  snippet = CodeSnippet()
  snippet.gen_func_impl(config.class_name)
  return snippet

def gen_code_file(filename, snippet):
  fobj = open(filename, 'w+')
  for line in snippet.lines:
    fobj.write(line)
    fobj.write('\n')
  fobj.close()
 
def gen_source_file(filename, config_list):
  snippet = CodeSnippet()
  snippet.gen_author()
  snippet.gen_include('%s.h' %filename)
  snippet.gen_empty_line()
  snippet.gen_using('tfs::common')
  snippet.gen_empty_line()
  snippet.gen_namespace_begin()
  for config in config_list:
    raw_code = gen_source_class(config)
    snippet.add_raw(raw_code.lines)
    snippet.gen_empty_line() 
  snippet.gen_namespace_end()

  gen_code_file(filename + '.cpp', snippet)

def gen_header_file(filename, config_list):
  snippet = CodeSnippet()
  snippet.gen_author()
  snippet.gen_header_begin(filename)
  snippet.gen_namespace_begin()
  for config in config_list:
    raw_code = gen_header_class(config)
    snippet.add_raw(raw_code.lines)
    snippet.gen_empty_line()
  snippet.gen_namespace_end()
  snippet.gen_header_end()

  gen_code_file(filename + '.h', snippet)
 
def parse_config_file(config_file):
  fobj = open(config_file, 'r')
  elements = [ ]
  config = ClassConfig()
  while True:
    line = fobj.readline()
    if not line:
      break

    line = line[0:len(line)-1]

    if line.startswith('class'):
      items = line.split(' ')
      config.class_name = items[1]
      config.base_name = items[2]
      config.var_list = [ ]
    elif line.startswith('var'):
      items = line.split(' ')
      config.var_list.append((items[1], items[2]))
    elif line.startswith('end'):
      elements.append(copy.deepcopy(config))
    else:
      pass
  
  fobj.close()
  return elements

   
if __name__ == '__main__':
  config_file = ''
  if len(sys.argv) != 2:
    print '%s filename(with no suffix)' %sys.argv[0]
    sys.exit(-1)
  
  config_file = sys.argv[1]
  config_list = parse_config_file(config_file)
  gen_header_file(config_file, config_list)
  gen_source_file(config_file, config_list)
