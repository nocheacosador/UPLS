import os, glob, re, sys
from distutils import sysconfig

def clean_path(path):
    return path if sys.platform != 'win32' else path.replace('\\', '/')

def find_package_path(dir_name):
    for p in sys.path:
        package = os.path.join(p, dir_name)
        if os.path.exists(package):
            return clean_path(os.path.realpath(package))
    return None

if __name__ == '__main__':
    print('shiboken6 location: ', find_package_path('PySide6'))