import os

build_path = 'build'

def main():
	if not os.path.exists(build_path):
		os.mkdir(build_path)
	os.chdir(build_path)
	os.system('cmake ..')
	
	os.system("pause")
if '__main__' == __name__:
    main()
	