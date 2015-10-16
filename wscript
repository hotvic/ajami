#! /usr/bin/env python
# encoding: utf-8

VERSION = '0.1'
APPNAME = 'ajami'

top = '.'
out = 'build'

def options(opt):
    opt.load('gnu_dirs compiler_c vala glib2')

    opt.add_option('--clang', action='store_true', default=False, help='Use clang as compiler')
    opt.add_option('--debug', action='store_true', default=False, help='pass debug options to compiler')
    opt.add_option('--enable-double-fft', action='store_true', default=False, help='Enable double precision fourier transform code - not recommended')
    opt.add_option('--disable-osc', action='store_true', default=False, help='do not include Open Sound Control interface')

def configure(cnf):
    from waflib.Tools.compiler_c import c_compiler

    cnf.check_waf_version(mini='1.8.14')

    # use clang as compiler
    if cnf.options.clang:
        c_compiler['linux'] = ['clang']

        if cnf.options.debug:
            cnf.env.CFLAGS = ['-fsanitize=address']
            cnf.env.LINKFLAGS = ['-fsanitize=address']

    cnf.load('gnu_dirs compiler_c vala glib2')

    cnf.env['INSTALL_DATA_DIR'] = '{0}/share/{1}'.format(cnf.env['PREFIX'], APPNAME)

    cnf.check(lib='m', mandatory=True)
    cnf.check(lib='dl', mandatory=True)
    cnf.check(lib='pthread', mandatory=True)
    cnf.check_cfg(package='gtk+-3.0', uselib_store='GTK', args='--cflags --libs', mandatory=True)
    cnf.check_cfg(package='gmodule-export-2.0', uselib_store='GMODULE', args='--libs', mandatory=True)
    cnf.check_cfg(package='jack', uselib_store='JACK', args='--cflags --libs', mandatory=True)
    cnf.check_cfg(package='libxml-2.0', uselib_store='LIBXML', args='--cflags --libs', mandatory=True)

    if cnf.options.enable_double_fft:
        cnf.check_cfg(package='fftw3', uselib_store='FFTW', args='--cflags --libs', mandatory=True)
        cnf.define('FFTW_TYPE', 'double', False)
    else:
        cnf.check_cfg(package='fftw3f', uselib_store='FFTW', args='--cflags --libs', mandatory=True)
        cnf.define('FFTW_TYPE', 'float', False)

    if not cnf.options.disable_osc:
        cnf.check_cfg(package='liblo', uselib_store='OSC', args='--cflags --libs', mandatory=True)

    cnf.define('LIBDIR', cnf.env.LIBDIR)
    cnf.define('PACKAGE_VERSION', VERSION)

    cnf.recurse('src')

def build(bld):
    bld.recurse('data lib src')
