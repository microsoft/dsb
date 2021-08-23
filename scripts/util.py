import os

def run_cmd(cmd, verbose = False):
	if verbose:
		print(cmd)
	status = os.popen(cmd).read()
	print(status)
