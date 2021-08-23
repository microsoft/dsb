import os
from os import path
import pyodbc
import time

def TrustedConnection(_server, _DBname="master", _driver="SQL Server", _Timeout=0, _verbose=False):
	connString = "Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes;" % (_driver, _server, _DBname)

	conn = pyodbc.connect(connString, timeout=_Timeout, autocommit=True)
	if _verbose == True:
		print("Connecting to %s, %s" % (_server, _DBname))

	return conn

def check_local_server_status():

	status_check_cmd = "sqlcmd -S 127.0.0.1 -Q \"SELECT SERVERPROPERTY('EDITION')\" "
	status = os.popen(status_check_cmd).read()

	if len(status) > 0:
		print("Connected to " + status.strip().replace("  ","").replace('\n','').replace('-','') + "\n")
		return True
	else:
		print("No server running")
		return False


def start_server(_path, _server, timeout=0):

	server_status = check_local_server_status()

	if server_status == False:
		os.system("start %s" % (path.join(_path, "sqlservr.cmd") ) )
		time.sleep(10) #wait for server to start

	conn = TrustedConnection(_server, _verbose=True, _Timeout=timeout)
	master_cursor = conn.cursor()

	return conn, master_cursor

def execute_from_file(_cursor, file):
	print('execute SQL from file:', file)
	with open(file) as f:
		lines = f.read()
		_cursor.execute(lines)
