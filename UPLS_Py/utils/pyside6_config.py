#############################################################################
##
## Copyright (C) 2019 The Qt Company Ltd.
## Contact: http://www.qt.io/licensing/
##
## This file is part of the Qt for Python examples of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:BSD$
## You may use this file under the terms of the BSD license as follows:
##
## "Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
##   * Redistributions of source code must retain the above copyright
##     notice, this list of conditions and the following disclaimer.
##   * Redistributions in binary form must reproduce the above copyright
##     notice, this list of conditions and the following disclaimer in
##     the documentation and/or other materials provided with the
##     distribution.
##   * Neither the name of The Qt Company Ltd nor the names of its
##     contributors may be used to endorse or promote products derived
##     from this software without specific prior written permission.
##
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
## OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
## LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
## DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
## THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
##
## $QT_END_LICENSE$
##
#############################################################################

import os, glob, re, sys
from distutils import sysconfig

generic_error = (' Did you forget to activate your virtualenv? Or perhaps'
                 ' you forgot to build / install PySide6 into your currently active Python'
                 ' environment?')
pyside6_error = 'Unable to locate PySide6.' + generic_error
shiboken6_module_error = 'Unable to locate shiboken6-module.' + generic_error
shiboken6_generator_error = 'Unable to locate shiboken6-generator.' + generic_error
pyside6_libs_error = 'Unable to locate the PySide6 shared libraries.' + generic_error
python_link_error = 'Unable to locate the Python library for linking.'
python_include_error = 'Unable to locate the Python include headers directory.'

options = []

# option, function, error, description
options.append(("--shiboken6-module-path",
                lambda: find_shiboken6_module(),
                shiboken6_module_error,
                "Print shiboken6 module location"))
options.append(("--shiboken6-generator-path",
                lambda: find_shiboken6_generator(),
                shiboken6_generator_error,
                "Print shiboken6 generator location"))
options.append(("--pyside6-path", lambda: find_pyside6(), pyside6_error,
                "Print PySide6 location"))

options.append(("--python-include-path",
                lambda: get_python_include_path(),
                python_include_error,
                "Print Python include path"))
options.append(("--shiboken6-generator-include-path",
                lambda: get_package_include_path(Package.shiboken6_generator),
                pyside6_error,
                "Print shiboken6 generator include paths"))
options.append(("--pyside6-include-path",
                lambda: get_package_include_path(Package.pyside6),
                pyside6_error,
                "Print PySide6 include paths"))

options.append(("--python-link-flags-qmake", lambda: python_link_flags_qmake(), python_link_error,
                "Print python link flags for qmake"))
options.append(("--python-link-flags-cmake", lambda: python_link_flags_cmake(), python_link_error,
                "Print python link flags for cmake"))

options.append(("--shiboken6-module-qmake-lflags",
                lambda: get_package_qmake_lflags(Package.shiboken6_module), pyside6_error,
                "Print shiboken6 shared library link flags for qmake"))
options.append(("--pyside6-qmake-lflags",
                lambda: get_package_qmake_lflags(Package.pyside6), pyside6_error,
                "Print PySide6 shared library link flags for qmake"))

options.append(("--shiboken6-module-shared-libraries-qmake",
                lambda: get_shared_libraries_qmake(Package.shiboken6_module), pyside6_libs_error,
                "Print paths of shiboken6 shared libraries (.so's, .dylib's, .dll's) for qmake"))
options.append(("--shiboken6-module-shared-libraries-cmake",
                lambda: get_shared_libraries_cmake(Package.shiboken6_module), pyside6_libs_error,
                "Print paths of shiboken6 shared libraries (.so's, .dylib's, .dll's) for cmake"))

options.append(("--pyside6-shared-libraries-qmake",
                lambda: get_shared_libraries_qmake(Package.pyside6), pyside6_libs_error,
                "Print paths of PySide6 shared libraries (.so's, .dylib's, .dll's) for qmake"))
options.append(("--pyside6-shared-libraries-cmake",
                lambda: get_shared_libraries_cmake(Package.pyside6), pyside6_libs_error,
                "Print paths of PySide6 shared libraries (.so's, .dylib's, .dll's) for cmake"))

options_usage = ''
for i, (flag, _, _, description) in enumerate(options):
    options_usage += '    {:<45} {}'.format(flag, description)
    if i < len(options) - 1:
        options_usage += '\n'

usage = """
Utility to determine include/link options of shiboken6/PySide6 and Python for qmake/CMake projects
that would like to embed or build custom shiboken6/PySide6 bindings.

Usage: pyside6_config.py [option]
Options:
{}
    -a                                            Print all options and their values
    --help/-h                                     Print this help
""".format(options_usage)

option = sys.argv[1] if len(sys.argv) == 2 else '-a'
if option == '-h' or option == '--help':
    print(usage)
    sys.exit(0)


class Package(object):
    shiboken6_module = 1
    shiboken6_generator = 2
    pyside6 = 3


def clean_path(path):
    return path if sys.platform != 'win32' else path.replace('\\', '/')


def shared_library_suffix():
    if sys.platform == 'win32':
        return 'lib'
    elif sys.platform == 'darwin':
        return 'dylib'
    # Linux
    else:
        return 'so.*'


def import_suffixes():
    if (sys.version_info >= (3, 4)):
        import importlib.machinery
        return importlib.machinery.EXTENSION_SUFFIXES
    else:
        import imp
        result = []
        for t in imp.get_suffixes():
            result.append(t[0])
        return result


def is_debug():
    debug_suffix = '_d.pyd' if sys.platform == 'win32' else '_d.so'
    return any([s.endswith(debug_suffix) for s in import_suffixes()])


def shared_library_glob_pattern():
    glob = '*.' + shared_library_suffix()
    return glob if sys.platform == 'win32' else 'lib' + glob


def filter_shared_libraries(libs_list):
    def predicate(lib_name):
        basename = os.path.basename(lib_name)
        if 'shiboken' in basename or 'pyside6' in basename:
            return True
        return False
    result = [lib for lib in libs_list if predicate(lib)]
    return result


# Return qmake link option for a library file name
def link_option(lib):
    # On Linux:
    # Since we cannot include symlinks with wheel packages
    # we are using an absolute path for the libpyside and libshiboken
    # libraries when compiling the project
    baseName = os.path.basename(lib)
    link = ' -l'
    if sys.platform in ['linux', 'linux2']: # Linux: 'libfoo.so' -> '/absolute/path/libfoo.so'
        link = lib
    elif sys.platform in ['darwin']: # Darwin: 'libfoo.so' -> '-lfoo'
        link += os.path.splitext(baseName[3:])[0]
    else: # Windows: 'libfoo.dll' -> 'libfoo.dll'
        link += os.path.splitext(baseName)[0]
    return link


# Locate PySide6 via sys.path package path.
def find_pyside6():
    return find_package_path("PySide6")


def find_shiboken6_module():
    return find_package_path("shiboken6")


def find_shiboken6_generator():
    return find_package_path("shiboken6_generator")


def find_package(which_package):
    if which_package == Package.shiboken6_module:
        return find_shiboken6_module()
    if which_package == Package.shiboken6_generator:
        return find_shiboken6_generator()
    if which_package == Package.pyside6:
        return find_pyside6()
    return None


def find_package_path(dir_name):
    for p in sys.path:
        #if 'site-' in p:
        package = os.path.join(p, dir_name)
        if os.path.exists(package):
            return clean_path(os.path.realpath(package))
    return None


# Return version as "3.5"
def python_version():
    return str(sys.version_info[0]) + '.' + str(sys.version_info[1])


def get_python_include_path():
    return sysconfig.get_python_inc()


def python_link_flags_qmake():
    flags = python_link_data()
    if sys.platform == 'win32':
        libdir = flags['libdir']
        # This will add the "~1" shortcut for directories that
        # contain white spaces
        # e.g.: "Program Files" to "Progra~1"
        for d in libdir.split("\\"):
            if " " in d:
                libdir = libdir.replace(d, d.split(" ")[0][:-1]+"~1")
        return '-L{} -l{}'.format(libdir, flags['lib'])
    elif sys.platform == 'darwin':
        return '-L{} -l{}'.format(flags['libdir'], flags['lib'])

    else:
        # Linux and anything else
        return '-L{} -l{}'.format(flags['libdir'], flags['lib'])


def python_link_flags_cmake():
    flags = python_link_data()
    libdir = flags['libdir']
    lib = re.sub(r'.dll$', '.lib', flags['lib'])
    return '{};{}'.format(libdir, lib)


def python_link_data():
    # @TODO Fix to work with static builds of Python
    libdir = sysconfig.get_config_var('LIBDIR')
    if libdir is None:
        libdir = os.path.abspath(os.path.join(
            sysconfig.get_config_var('LIBDEST'), "..", "libs"))
    version = python_version()
    version_no_dots = version.replace('.', '')

    flags = {}
    flags['libdir'] = libdir
    if sys.platform == 'win32':
        suffix = '_d' if is_debug() else ''
        flags['lib'] = 'python{}{}'.format(version_no_dots, suffix)

    elif sys.platform == 'darwin':
        flags['lib'] = 'python{}'.format(version)

    # Linux and anything else
    else:
        if sys.version_info[0] < 3:
            suffix = '_d' if is_debug() else ''
            flags['lib'] = 'python{}{}'.format(version, suffix)
        else:
            flags['lib'] = 'python{}{}'.format(version, sys.abiflags)

    return flags


def get_package_include_path(which_package):
    package_path = find_package(which_package)
    if package_path is None:
        return None

    includes = "{0}/include".format(package_path)

    return includes


def get_package_qmake_lflags(which_package):
    package_path = find_package(which_package)
    if package_path is None:
        return None

    link = "-L{}".format(package_path)
    glob_result = glob.glob(os.path.join(package_path, shared_library_glob_pattern()))
    for lib in filter_shared_libraries(glob_result):
        link += ' '
        link += link_option(lib)
    return link


def get_shared_libraries_data(which_package):
    package_path = find_package(which_package)
    if package_path is None:
        return None

    glob_result = glob.glob(os.path.join(package_path, shared_library_glob_pattern()))
    filtered_libs = filter_shared_libraries(glob_result)
    libs = []
    if sys.platform == 'win32':
        for lib in filtered_libs:
            libs.append(os.path.realpath(lib))
    else:
        for lib in filtered_libs:
            libs.append(lib)
    return libs


def get_shared_libraries_qmake(which_package):
    libs = get_shared_libraries_data(which_package)
    if libs is None:
        return None

    if sys.platform == 'win32':
        if not libs:
            return ''
        dlls = ''
        for lib in libs:
            dll = os.path.splitext(lib)[0] + '.dll'
            dlls += dll + ' '

        return dlls
    else:
        libs_string = ''
        for lib in libs:
            libs_string += lib + ' '
        return libs_string


def get_shared_libraries_cmake(which_package):
    libs = get_shared_libraries_data(which_package)
    result = ';'.join(libs)
    return result


print_all = option == "-a"
for argument, handler, error, _ in options:
    if option == argument or print_all:
        handler_result = handler()
        if handler_result is None:
            sys.exit(error)

        line = handler_result
        if print_all:
            line = "{:<40}: ".format(argument) + line
        print(line)
