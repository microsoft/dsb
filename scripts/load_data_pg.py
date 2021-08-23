import os
import pg_util

tables = ['call_center',
		'catalog_page', 'catalog_returns',
		'catalog_sales',
		'customer', 'customer_address', 'customer_demographics',
		'date_dim', 'household_demographics', 'income_band', 'inventory', 'item', 'promotion', 'reason', 'ship_mode',
		'store', 'store_returns', 'store_sales',
		'time_dim', 'warehouse',
		'web_page', 'web_returns', 'web_sales', 'web_site'
		]

data_path = # directory of data files
db_name = # database name
bin_path = # path of the binary of Postgres
tmp_csv_path = # path of tmp csv file for bulk loading

create_db = False # If create the database
create_table = False # If create the tables

# start database service
pg_util.start_server()

# postgres credential
user = 'postgres'
password = 'admin'

# create database
if create_db:
	master_conn = pg_util.connect(user = user, password = password)
	pg_util.execute(master_conn.cursor(), 'create database ' + db_name, verbose = True)
	master_conn.close()

# connect to the database
conn = pg_util.connect(user = user, password = password, db_name = db_name)
cursor = conn.cursor()

# create tables
if create_table:
	sql_path = r'D:\scripts\create_tables.sql'
	pg_util.execute(cursor, open(sql_path, 'r').read(), verbose = True)

# insert tuples into tables
for table in tables:
	file_path = os.path.join(data_path, table + '.dat')
	pg_util.execute(cursor, 'delete from ' + table + ';', verbose = True)
	pg_util.bulk_load_from_csv_file(cursor, file_path, tmp_csv_path, table, delimiter = '|')

cursor.close()
conn.close()
