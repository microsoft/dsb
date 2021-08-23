DECLARE @path VARCHAR(max)

SET @path = -- path to the database files

DECLARE @tables TABLE (table_name VARCHAR(max))
INSERT @tables(table_name) values
	('call_center'),
	('catalog_page'), ('catalog_returns'), ('catalog_sales'),
	('customer'), ('customer_address'), ('customer_demographics'),
	('date_dim'), ('household_demographics'), ('income_band'), ('inventory'), ('item'), ('promotion'), ('reason'), ('ship_mode'),
	('store'), ('store_returns'), ('store_sales'),
	('time_dim'), ('warehouse'),
	('web_page'), ('web_returns'), ('web_sales'), ('web_site')


DECLARE @sql varchar(max)

WHILE EXISTS (SELECT * from @tables)
BEGIN
	DECLARE @table VARCHAR(max)
	SELECT @table = MIN(table_name) from @tables
	SET @sql = 'DELETE FROM ' + @table
	EXEC(@sql)

	SET @sql = 'BULK INSERT ' + @table + ' FROM ''' + @path + @table + '.dat'' WITH
	(
		FORMAT = ''CSV'',
		FIRSTROW = 1,
		FIELDTERMINATOR = ''|'',
		ROWTERMINATOR = ''\n'',
		KEEPNULLS
	)'
	EXEC(@sql)

	DELETE from @tables where table_name = @table
END
