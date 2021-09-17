import SQL_utils

SQL_engine_path = # directory of Microsoft SQL Server sqlserver.cmd

conn, master_cursor = SQL_utils.start_server(SQL_engine_path, 'localhost')

db_name = # database name
create_db = False # If create the database
create_table = False # If create the tables
load_data = False # If load the data
create_index = True # If create the indexes

create_table_sql = r'D:\scripts\create_tables.sql'
load_data_sql = r'D:\scripts\load_db_files_sqlserver.sql'
create_index_sql = r'D:\scripts\dsb_index_sqlserver.sql'

# create database
if create_db:
	master_cursor.execute('create database ' + db_name)

conn = SQL_utils.TrustedConnection('localhost', db_name)
cursor = conn.cursor()

# create tables
if create_table:
	SQL_utils.execute_from_file(cursor, create_table_sql)

# load data
if load_data:
	SQL_utils.execute_from_file(cursor, load_data_sql)

if create_index:
	SQL_utils.execute_from_file(cursor, create_index_sql)
