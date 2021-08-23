import os
import pg_util

db_name = # database name
bin_path = # binary of Postgres
sql_path = r'D:\scripts\create_index_pg.sql'

# start database service
pg_util.start_server()

# postgres credential
user = 'postgres'
password = 'admin'

# connect to the database
conn = pg_util.connect(user = user, password = password, db_name = db_name)
cursor = conn.cursor()

# create indexes
pg_util.execute(cursor, open(sql_path, 'r').read(), verbose = True)

cursor.close()
conn.close()
