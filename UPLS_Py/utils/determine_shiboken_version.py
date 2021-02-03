import os, sys

sys.path.append('/usr/local/bin')

def clean_path(path):
    return path if sys.platform != 'win32' else path.replace('\\', '/')

def find_package_path(dir_name):
    for p in sys.path:
        package = os.path.join(p, dir_name)
        if os.path.exists(package):
            return clean_path(os.path.realpath(package))
    return None

def determine_shiboken_version():
	# First check for shiboken6
	path = find_package_path('shiboken6')
	if path:
		print('shiboken6')
	
	path = find_package_path('shiboken2')
	if path:
		print('shiboken2')

determine_shiboken_version()