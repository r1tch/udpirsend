#!/usr/bin/python

import os;

APPNAME = 'udpirsend'
VERSION = '1.0'

out = '.wafbuild'

def options(opt):
  opt.load('compiler_cxx')
  opt.add_option('-d', '--debug', action='store_true', default=False, help='Create debug version')

def configure(ctx):
    ctx.load('compiler_cxx boost')
    ctx.check_boost(lib='system program_options')

    setCxxFlags(ctx)
    setOSXSpecifics(ctx)
    
def build(ctx):
    ctx.load('compiler_cxx boost')
    ctx.program(
        features = 'cxx cxxprogram',
        source = ctx.path.ant_glob('*.cpp'),
        target = APPNAME,
        use = ['BOOST'])

###################################
def setOSXSpecifics(ctx):
    if (ctx.env.DEST_OS == 'darwin'):
        ctx.env.append_unique('INCLUDES', '/opt/local/include')
        ctx.env.append_unique('LIBPATH', '/opt/local/lib')
        ctx.env.append_unique('CXXFLAGS', '-Wno-unused-local-typedef')    # BOOST v1.59 workaround on OSX..

def enforceColorClangOutput():
  if ('CXX' in os.environ and os.environ['CXX'] == 'clang++'):
      return ['-fcolor-diagnostics']
  else:
      return []

def setCxxFlags(ctx):
    print("Debug flag is " + str(ctx.options.debug))
    if ctx.options.debug == True:
        ctx.env.append_unique('CXXFLAGS', ['-g'])
    else:
        ctx.env.append_unique('CXXFLAGS', ['-O3', '-DNDEBUG'])
    
    clangSpecificFlags = enforceColorClangOutput()
  
    ctx.env.append_unique('CXXFLAGS', 
            ['-Wall', '-Werror', '-Woverloaded-virtual', '-std=c++11'] +
            clangSpecificFlags)
 
