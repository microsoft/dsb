import os
import subprocess
import shutil

bin_dir = r'D:\code\v2.11.0rc2\tools'
bin_path = os.path.join(bin_dir, 'dsdgen.exe')

scale = 10
file_dir = # directory of database files

if os.path.exists(file_dir):
	shutil.rmtree(file_dir)

if not os.path.exists(file_dir):
	os.makedirs(file_dir)

# WARNING: This code hasn't been valiated. Somewhat the dir parameter is not
# taken in to account by the code. The output db files are generated in bin_dir
cmd = [bin_path, '/scale', str(scale), '/terminate', 'N', '/force', '/dir',  file_dir]
print(cmd)
subprocess.call(cmd, cwd = bin_dir)
