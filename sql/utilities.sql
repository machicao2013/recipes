#查找表中的主键
SELECT k.column_name
FROM information_schema.table_constraints t
JOIN information_schema.key_column_usage k
USING (constraint_name,table_schema,table_name)
WHERE t.constraint_type='PRIMARY KEY'
    AND t.table_schema='db'
    AND t.table_name=tbl'

# 查看你的数库有多大
SELECT
    table_schema AS 'Db Name',
    Round( Sum( data_length + index_length ) / 1024 / 1024, 3 ) AS 'Db Size (MB)',
    Round( Sum( data_free ) / 1024 / 1024, 3 ) AS 'Free Space (MB)'
FROM information_schema.tables
GROUP BY table_schema ;

SELECT
    TABLE_NAME AS 'tableName',
    Round( (DATA_LENGTH + INDEX_LENGTH) / 1024 / 1024 , 3 ) AS 'tableSize (MB)',
FROM information_schema.tables
WHERE information_schema.TABLE_NAME='sd_statistic'
