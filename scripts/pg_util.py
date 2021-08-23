import os
import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT

import util

def bulk_load_from_csv_file(cursor, csv_file, tmp_file, table_name, delimiter):
	# Split the csv file into batches to load incrementally.
	batch_size = 100000
	prev_pos = 0
	count = 0
	with open(csv_file) as fin:
		flag = True
		while flag:
			with open(tmp_file, 'w') as fout:
				cur = 0
				for i in range(batch_size):
					line = fin.readline()
					# Check if we reach EOF
					pos = fin.tell()
					if pos == prev_pos:
						flag = False
						break
					else:
						prev_pos = pos
						fout.write(line)
						count += 1
						cur += 1
				load_from_csv_file(cursor, tmp_file, table_name, delimiter)
				print('.', end = '', flush = True)
	print('loaded', count, 'rows from', csv_file, 'to table', table_name)


def load_from_csv_file(cursor, csv_file, table_name, delimiter):
	sql_cmd = 'copy ' + table_name + " from '" + csv_file + "' with (delimiter '" + delimiter + "', format csv);"
	execute(cursor, sql_cmd)

def execute(cursor, cmd, verbose = False):
	try:
		if verbose:
			print(cmd)
		cursor.execute(cmd)
	except Exception as e:
		print(e)

def connect(user, password, db_name = None):
	try:
		if db_name is not None:
			conn = psycopg2.connect(user=user, password=password, database=db_name)
		else:
			conn = psycopg2.connect(user=user, password=password)
		conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)

	except Exception as e:
		print(e)

	return conn

def restart_server(pg_service_name = 'postgresql-x64-13'):
	stop_server(pg_service_name)
	start_server(pg_service_name)

def stop_server(pg_service_name = 'postgresql-x64-13'):

	cmd = 'net stop ' + pg_service_name
	util.run_cmd(cmd)

def start_server(pg_service_name = 'postgresql-x64-13'):

	cmd = 'net start ' + pg_service_name
	util.run_cmd(cmd)

if __name__ == '__main__':
	pg_service_name = 'postgresql-x64-13'
	start_server(pg_service_name)
