
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          Marcio Paiva <mpaivabarbosa@gmail.com>                        |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/concat.h"

/**
 * Phalcon\Db\Dialect\Postgresql
 *
 * Generates database specific SQL for the PostgreSQL RBDM
 */


/**
 * Phalcon\Db\Dialect\Oracle initializer
 */
PHALCON_INIT_CLASS(Phalcon_Db_Dialect_Oracle){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\Db\\Dialect, Oracle, db_dialect_oracle, "phalcon\\db\\dialect", phalcon_db_dialect_oracle_method_entry, 0);

	zend_declare_property_string(phalcon_db_dialect_oracle_ce, SL("_escapeChar"), "\"", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_db_dialect_oracle_ce TSRMLS_CC, 1, phalcon_db_dialectinterface_ce);

	return SUCCESS;
}

/**
 * Gets the column name in PostgreSQL
 *
 * @param Phalcon\Db\ColumnInterface $column
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, getColumnDefinition){

	zval *column, *size, *column_type, *column_sql = NULL;
	zval *scale;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &column) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(column) != IS_OBJECT) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Column definition must be an object compatible with Phalcon\\Db\\ColumnInterface");
		return;
	}
	
	PHALCON_INIT_VAR(size);
	PHALCON_CALL_METHOD(size, column, "getsize");
	
	PHALCON_INIT_VAR(column_type);
	PHALCON_CALL_METHOD(column_type, column, "gettype");
	
	switch (phalcon_get_intval(column_type)) {
	
		case 0:
			PHALCON_INIT_VAR(column_sql);
			ZVAL_STRING(column_sql, "NUMBER", 1);
			break;
	
		case 1:
			PHALCON_INIT_NVAR(column_sql);
			ZVAL_STRING(column_sql, "DATE", 1);
			break;
	
		case 2:
			PHALCON_INIT_NVAR(column_sql);
			PHALCON_CONCAT_SVS(column_sql, "VARCHAR2(", size, ")");
			break;
	
		case 3:
			PHALCON_INIT_VAR(scale);
			PHALCON_CALL_METHOD(scale, column, "getscale");
	
			PHALCON_INIT_NVAR(column_sql);
			PHALCON_CONCAT_SVSVS(column_sql, "NUMBER(", size, ",", scale, ")");
			break;
	
		case 4:
			PHALCON_INIT_NVAR(column_sql);
			ZVAL_STRING(column_sql, "TIMESTAMP", 1);
			break;
	
		case 5:
			PHALCON_INIT_NVAR(column_sql);
			PHALCON_CONCAT_SVS(column_sql, "CHAR(", size, ")");
			break;
	
		case 6:
			PHALCON_INIT_NVAR(column_sql);
			ZVAL_STRING(column_sql, "TEXT", 1);
			break;
	
		case 7:
			PHALCON_INIT_NVAR(column_sql);
			ZVAL_STRING(column_sql, "BINARY_FLOAT", 1);
			break;
	
		default:
			PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Unrecognized PostgreSQL data type");
			return;
	
	}
	
	RETURN_CTOR(column_sql);
}

/**
 * Generates SQL to add a column to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon\Db\ColumnInterface $column
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, addColumn){

	zval *table_name, *schema_name, *column;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to modify a column in a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon\Db\ColumnInterface $column
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, modifyColumn){

	zval *table_name, *schema_name, *column;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to delete a column from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $columnName
 * @return 	string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, dropColumn){

	zval *table_name, *schema_name, *column_name;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to add an index to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon\Db\Index $index
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, addIndex){

	zval *table_name, *schema_name, *index;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
  * Generates SQL to delete an index from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $indexName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, dropIndex){

	zval *table_name, *schema_name, *index_name;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to add the primary key to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon\Db\Index $index
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, addPrimaryKey){

	zval *table_name, *schema_name, *index;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to delete primary key from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, dropPrimaryKey){

	zval *table_name, *schema_name;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &table_name, &schema_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to add an index to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon\Db\ReferenceInterface $reference
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, addForeignKey){

	zval *table_name, *schema_name, *reference;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &reference) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to delete a foreign key from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $referenceName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, dropForeignKey){

	zval *table_name, *schema_name, *reference_name;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &reference_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to add the table creation options
 *
 * @param array $definition
 * @return array
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, _getTableOptions){

	zval *definition, *empty_array;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &definition) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_INIT_VAR(empty_array);
	array_init(empty_array);
	RETURN_CTOR(empty_array);
}

/**
 * Generates SQL to create a table in PostgreSQL
 *
 * @param 	string $tableName
 * @param string $schemaName
 * @param array $definition
 * @return 	string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, createTable){

	zval *table_name, *schema_name, *definition;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &definition) == FAILURE) {
		RETURN_MM_NULL();
	}

	PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Not implemented yet");
	return;
}

/**
 * Generates SQL to drop a table
 *
 * @param  string $tableName
 * @param  string $schemaName
 * @param  boolean $ifExists
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, dropTable){

	zval *table_name, *schema_name, *if_exists = NULL, *table = NULL;
	zval *sql = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|z", &table_name, &schema_name, &if_exists) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!if_exists) {
		PHALCON_INIT_VAR(if_exists);
		ZVAL_BOOL(if_exists, 1);
	}
	
	if (zend_is_true(schema_name)) {
		PHALCON_INIT_VAR(table);
		PHALCON_CONCAT_VSV(table, schema_name, ".", table_name);
	} else {
		PHALCON_CPY_WRT(table, table_name);
	}
	if (zend_is_true(if_exists)) {
		PHALCON_INIT_VAR(sql);
		PHALCON_CONCAT_SV(sql, "DROP TABLE IF EXISTS ", table);
	} else {
		PHALCON_INIT_NVAR(sql);
		PHALCON_CONCAT_SV(sql, "DROP TABLE ", table);
	}
	
	
	RETURN_CTOR(sql);
}

/**
 * Generates SQL checking for the existence of a schema.table
 *
 * <code>echo $dialect->tableExists("posts", "blog")</code>
 * <code>echo $dialect->tableExists("posts")</code>
 *
 * @param string $tableName
 * @param string $schemaName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, tableExists){

	zval *table_name, *schema_name = NULL, *sql = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table_name, &schema_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema_name) {
		PHALCON_INIT_VAR(schema_name);
	}
	
	if (zend_is_true(schema_name)) {
		PHALCON_INIT_VAR(sql);
		PHALCON_CONCAT_SVSVS(sql, "SELECT CASE WHEN COUNT(*) > 0 THEN 1 ELSE 0 END RET FROM ALL_TABLES WHERE UPPER(TABLE_NAME)=UPPER('", table_name, "') AND UPPER(OWNER)=UPPER('", schema_name, "')");
	} else {
		PHALCON_INIT_NVAR(sql);
		PHALCON_CONCAT_SVS(sql, "SELECT CASE WHEN COUNT(*) > 0 THEN 1 ELSE 0 END RET FROM ALL_TABLES WHERE UPPER(TABLE_NAME)=UPPER('", table_name, "')");
	}
	
	RETURN_CTOR(sql);
}

/**
 * Generates a SQL describing a table
 *
 * <code>print_r($dialect->describeColumns("posts") ?></code>
 *
 * @param string $table
 * @param string $schema
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, describeColumns){

	zval *table, *schema = NULL, *sql = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table, &schema) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema) {
		PHALCON_INIT_VAR(schema);
	}
	
	if (zend_is_true(schema)) {
		PHALCON_INIT_VAR(sql);
		PHALCON_CONCAT_SVSVS(sql, "SELECT TC.COLUMN_NAME, TC.DATA_TYPE, TC.DATA_LENGTH, TC.NULLABLE,C.CONSTRAINT_TYPE,TC.DATA_DEFAULT, CC.POSITION FROM ALL_TAB_COLUMNS TC LEFT JOIN (ALL_CONS_COLUMNS CC JOIN ALL_CONSTRAINTS C ON (CC.CONSTRAINT_NAME = C.CONSTRAINT_NAME AND CC.TABLE_NAME = C.TABLE_NAME AND CC.OWNER = C.OWNER AND C.CONSTRAINT_TYPE = 'P')) ON TC.TABLE_NAME = CC.TABLE_NAME AND TC.COLUMN_NAME = CC.COLUMN_NAME WHERE UPPER(TC.TABLE_NAME) = UPPER('", table, "') AND UPPER(TC.OWNER) = UPPER('", schema, "') ORDER BY TC.COLUMN_ID");
	} else {
		PHALCON_INIT_NVAR(sql);
		PHALCON_CONCAT_SVS(sql, "SELECT TC.COLUMN_NAME, TC.DATA_TYPE, TC.DATA_LENGTH, TC.NULLABLE,C.CONSTRAINT_TYPE,TC.DATA_DEFAULT, CC.POSITION FROM ALL_TAB_COLUMNS TC LEFT JOIN (ALL_CONS_COLUMNS CC JOIN ALL_CONSTRAINTS C ON (CC.CONSTRAINT_NAME = C.CONSTRAINT_NAME AND CC.TABLE_NAME = C.TABLE_NAME AND CC.OWNER = C.OWNER AND C.CONSTRAINT_TYPE = 'P')) ON TC.TABLE_NAME = CC.TABLE_NAME AND TC.COLUMN_NAME = CC.COLUMN_NAME WHERE UPPER(TC.TABLE_NAME) = UPPER('", table, "') ORDER BY TC.COLUMN_ID");
	}
	
	RETURN_CTOR(sql);
}

/**
 * List all tables on database
 *
 * <code>print_r($dialect->listTables("blog") ?></code>
 *
 * @param       string $schemaName
 * @return      array
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, listTables){

	zval *schema_name = NULL, *sql = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &schema_name) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema_name) {
		PHALCON_INIT_VAR(schema_name);
	}

	if(zend_is_true(schema_name)) {
		PHALCON_INIT_NVAR(sql);
		PHALCON_CONCAT_SVS(sql, "SELECT TABLE_NAME, OWNER FROM ALL_TABLES WHERE OWNER=UPPER('", schema_name, "') ORDER BY OWNER, TABLE_NAME");
	} else {
		PHALCON_INIT_NVAR(sql);
		ZVAL_STRING(sql, "SELECT TABLE_NAME, OWNER FROM ALL_TABLES ORDER BY OWNER, TABLE_NAME ", 1);
	}


	RETURN_CTOR(sql);}

/**
 * Generates SQL to query indexes on a table
 *
 * @param string $table
 * @param string $schema
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, describeIndexes){


	zval *table, *schema = NULL, *sql;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table, &schema) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema) {
		PHALCON_INIT_VAR(schema);
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CONCAT_SVS(sql, "SELECT 0 as C0, I.TABLE_NAME, 3 AS C3, I.INDEX_NAME, IC.COLUMN_POSITION, IC.COLUMN_NAME FROM ALL_INDEXES I JOIN ALL_IND_COLUMNS IC ON I.INDEX_NAME = IC.INDEX_NAME WHERE  I.TABLE_NAME = UPPER('", table, "')");
	RETURN_CTOR(sql);}

/**
 * Generates SQL to query foreign keys on a table
 *
 * @param string $table
 * @param string $schema
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, describeReferences){


	zval *table, *schema = NULL, *sql;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table, &schema) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema) {
		PHALCON_INIT_VAR(schema);
	}

	PHALCON_INIT_VAR(sql);
	ZVAL_STRING(sql, "SELECT AC.TABLE_NAME, CC.COLUMN_NAME, AC.CONSTRAINT_NAME, AC.R_OWNER, RCC.TABLE_NAME R_TABLE_NAME, RCC.COLUMN_NAME R_COLUMN_NAME FROM ALL_CONSTRAINTS AC JOIN ALL_CONS_COLUMNS CC ON AC.CONSTRAINT_NAME = CC.CONSTRAINT_NAME JOIN ALL_CONS_COLUMNS RCC ON AC.R_OWNER = RCC.OWNER AND AC.R_CONSTRAINT_NAME = RCC.CONSTRAINT_NAME WHERE AC.CONSTRAINT_TYPE='R' ", 1);
	if (zend_is_true(schema)) {
		PHALCON_SCONCAT_SVSVS(sql, "AND AC.OWNER=UPPER('", schema, "') AND AC.TABLE_NAME = UPPER('", table, "')");
	} else {
		PHALCON_SCONCAT_SVS(sql, "AND AC.TABLE_NAME = UPPER('", table, "')");
	}


	RETURN_CTOR(sql);}

/**
 * Generates the SQL to describe the table creation options
 *
 * @param string $table
 * @param string $schema
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, tableOptions){

	zval *table, *schema = NULL;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table, &schema) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (!schema) {
		PHALCON_INIT_VAR(schema);
	}
	
	PHALCON_MM_RESTORE();
	RETURN_EMPTY_STRING();
}

/**
 * Builds a SELECT statement
 *
 * @param array $definition
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect_Oracle, select){

	zval *definition, *escape_char = NULL, *columns, *selected_columns;
	zval *column = NULL, *column_item = NULL, *column_sql = NULL, *columns_sql = NULL;
	zval *column_domain = NULL, *column_domain_sql = NULL, *column_alias = NULL;
	zval *column_alias_sql = NULL, *tables, *selected_tables;
	zval *table = NULL, *sql_table = NULL, *tables_sql = NULL, *sql, *joins;
	zval *join = NULL, *type = NULL, *sql_join = NULL, *join_conditions_array = NULL;
	zval *join_expressions = NULL, *join_condition = NULL, *join_expression = NULL;
	zval *join_conditions = NULL, *where_conditions;
	zval *where_expression, *group_items, *group_fields;
	zval *group_field = NULL, *group_expression = NULL, *group_sql;
	zval *group_clause, *having_conditions, *having_expression;
	zval *order_fields, *order_items, *order_item = NULL;
	zval *order_expression = NULL, *order_sql_item = NULL, *sql_order_type = NULL;
	zval *order_sql_item_type = NULL, *order_sql, *limit_value;
	zval *number, *offset, *sql_limit=NULL, *one, *ini_range, *end_range;
	HashTable *ah0, *ah1, *ah2, *ah3, *ah4, *ah5;
	HashPosition hp0, hp1, hp2, hp3, hp4, hp5;
	zval **hd;

	PHALCON_MM_GROW();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &definition) == FAILURE) {
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(definition) != IS_ARRAY) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid SELECT definition");
		return;
	}
	if (!phalcon_array_isset_string(definition, SS("tables"))) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The index 'tables' is required in the definition array");
		return;
	}

	if (!phalcon_array_isset_string(definition, SS("columns"))) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The index 'columns' is required in the definition array");
		return;
	}

	if (PHALCON_GLOBAL(db).escape_identifiers) {
		PHALCON_OBS_VAR(escape_char);
		phalcon_read_property(&escape_char, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
	} else {
		PHALCON_INIT_NVAR(escape_char);
	}

	PHALCON_OBS_VAR(columns);
	phalcon_array_fetch_string(&columns, definition, SL("columns"), PH_NOISY_CC);
	if (Z_TYPE_P(columns) == IS_ARRAY) {

		PHALCON_INIT_VAR(selected_columns);
		array_init(selected_columns);

		if (!phalcon_is_iterable(columns, &ah0, &hp0, 0, 0 TSRMLS_CC)) {
			return;
		}

		while (zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) == SUCCESS) {

			PHALCON_GET_FOREACH_VALUE(column);

			/**
			 * Escape column name
			 */
			PHALCON_OBS_NVAR(column_item);
			phalcon_array_fetch_long(&column_item, column, 0, PH_NOISY_CC);
			if (Z_TYPE_P(column_item) == IS_ARRAY) {
				PHALCON_INIT_NVAR(column_sql);
				PHALCON_CALL_METHOD_PARAMS_2(column_sql, this_ptr, "getsqlexpression", column_item, escape_char);
			} else {
				if (PHALCON_IS_STRING(column_item, "*")) {
					PHALCON_CPY_WRT(column_sql, column_item);
				} else {
					if (PHALCON_GLOBAL(db).escape_identifiers) {
						PHALCON_INIT_NVAR(column_sql);
						PHALCON_CONCAT_VVV(column_sql, escape_char, column_item, escape_char);
					} else {
						PHALCON_CPY_WRT(columns_sql, column_item);
					}
				}
			}

			/**
			 * Escape column domain
			 */
			if (phalcon_array_isset_long(column, 1)) {

				PHALCON_OBS_NVAR(column_domain);
				phalcon_array_fetch_long(&column_domain, column, 1, PH_NOISY_CC);
				if (zend_is_true(column_domain)) {
					if (PHALCON_GLOBAL(db).escape_identifiers) {
						PHALCON_INIT_NVAR(column_domain_sql);
						PHALCON_CONCAT_VVVSV(column_domain_sql, escape_char, column_domain, escape_char, ".", column_sql);
					} else {
						PHALCON_INIT_NVAR(column_domain_sql);
						PHALCON_CONCAT_VSV(column_domain_sql, column_domain, ".", column_sql);
					}
				} else {
					PHALCON_CPY_WRT(column_domain_sql, column_sql);
				}
			} else {
				PHALCON_CPY_WRT(column_domain_sql, column_sql);
			}

			/**
			 * Escape column alias
			 */
			if (phalcon_array_isset_long(column, 2)) {

				PHALCON_OBS_NVAR(column_alias);
				phalcon_array_fetch_long(&column_alias, column, 2, PH_NOISY_CC);
				if (zend_is_true(column_alias)) {
					if (PHALCON_GLOBAL(db).escape_identifiers) {
						PHALCON_INIT_NVAR(column_alias_sql);
						PHALCON_CONCAT_VSVVV(column_alias_sql, column_domain_sql, " AS ", escape_char, column_alias, escape_char);
					} else {
						PHALCON_INIT_NVAR(column_alias_sql);
						PHALCON_CONCAT_VSV(column_alias_sql, column_domain_sql, " AS ", column_alias);
					}
				} else {
					PHALCON_CPY_WRT(column_alias_sql, column_domain_sql);
				}
			} else {
				PHALCON_CPY_WRT(column_alias_sql, column_domain_sql);
			}

			phalcon_array_append(&selected_columns, column_alias_sql, PH_SEPARATE TSRMLS_CC);

			zend_hash_move_forward_ex(ah0, &hp0);
		}

		PHALCON_INIT_VAR(columns_sql);
		phalcon_fast_join_str(columns_sql, SL(", "), selected_columns TSRMLS_CC);
	} else {
		PHALCON_CPY_WRT(columns_sql, columns);
	}

	/**
	 * Check and escape tables
	 */
	PHALCON_OBS_VAR(tables);
	phalcon_array_fetch_string(&tables, definition, SL("tables"), PH_NOISY_CC);
	if (Z_TYPE_P(tables) == IS_ARRAY) {

		PHALCON_INIT_VAR(selected_tables);
		array_init(selected_tables);

		if (!phalcon_is_iterable(tables, &ah1, &hp1, 0, 0 TSRMLS_CC)) {
			return;
		}

		while (zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) == SUCCESS) {

			PHALCON_GET_FOREACH_VALUE(table);

			PHALCON_INIT_NVAR(sql_table);
			PHALCON_CALL_METHOD_PARAMS_2(sql_table, this_ptr, "getsqltable", table, escape_char);
			phalcon_array_append(&selected_tables, sql_table, PH_SEPARATE TSRMLS_CC);

			zend_hash_move_forward_ex(ah1, &hp1);
		}

		PHALCON_INIT_VAR(tables_sql);
		phalcon_fast_join_str(tables_sql, SL(", "), selected_tables TSRMLS_CC);
	} else {
		PHALCON_CPY_WRT(tables_sql, tables);
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CONCAT_SVSV(sql, "SELECT ", columns_sql, " FROM ", tables_sql);

	/**
	 * Check for joins
	 */
	if (phalcon_array_isset_string(definition, SS("joins"))) {

		PHALCON_OBS_VAR(joins);
		phalcon_array_fetch_string(&joins, definition, SL("joins"), PH_NOISY_CC);

		if (!phalcon_is_iterable(joins, &ah2, &hp2, 0, 0 TSRMLS_CC)) {
			return;
		}

		while (zend_hash_get_current_data_ex(ah2, (void**) &hd, &hp2) == SUCCESS) {

			PHALCON_GET_FOREACH_VALUE(join);

			PHALCON_OBS_NVAR(type);
			phalcon_array_fetch_string(&type, join, SL("type"), PH_NOISY_CC);

			PHALCON_OBS_NVAR(table);
			phalcon_array_fetch_string(&table, join, SL("source"), PH_NOISY_CC);

			PHALCON_INIT_NVAR(sql_table);
			PHALCON_CALL_METHOD_PARAMS_2(sql_table, this_ptr, "getsqltable", table, escape_char);
			phalcon_array_append(&selected_tables, sql_table, PH_SEPARATE TSRMLS_CC);

			PHALCON_INIT_NVAR(sql_join);
			PHALCON_CONCAT_SVSV(sql_join, " ", type, " JOIN ", sql_table);

			/**
			 * Check if the join has conditions
			 */
			if (phalcon_array_isset_string(join, SS("conditions"))) {

				PHALCON_OBS_NVAR(join_conditions_array);
				phalcon_array_fetch_string(&join_conditions_array, join, SL("conditions"), PH_NOISY_CC);
				if (phalcon_fast_count_ev(join_conditions_array TSRMLS_CC)) {

					PHALCON_INIT_NVAR(join_expressions);
					array_init(join_expressions);

					if (!phalcon_is_iterable(join_conditions_array, &ah3, &hp3, 0, 0 TSRMLS_CC)) {
						return;
					}

					while (zend_hash_get_current_data_ex(ah3, (void**) &hd, &hp3) == SUCCESS) {

						PHALCON_GET_FOREACH_VALUE(join_condition);

						PHALCON_INIT_NVAR(join_expression);
						PHALCON_CALL_METHOD_PARAMS_2(join_expression, this_ptr, "getsqlexpression", join_condition, escape_char);
						phalcon_array_append(&join_expressions, join_expression, PH_SEPARATE TSRMLS_CC);

						zend_hash_move_forward_ex(ah3, &hp3);
					}

					PHALCON_INIT_NVAR(join_conditions);
					phalcon_fast_join_str(join_conditions, SL(" AND "), join_expressions TSRMLS_CC);
					PHALCON_SCONCAT_SV(sql_join, " ON ", join_conditions);
				}
			}

			phalcon_concat_self(&sql, sql_join TSRMLS_CC);

			zend_hash_move_forward_ex(ah2, &hp2);
		}

	}

	/**
	 * Check for a WHERE clause
	 */
	if (phalcon_array_isset_string(definition, SS("where"))) {

		PHALCON_OBS_VAR(where_conditions);
		phalcon_array_fetch_string(&where_conditions, definition, SL("where"), PH_NOISY_CC);
		if (Z_TYPE_P(where_conditions) == IS_ARRAY) {
			PHALCON_INIT_VAR(where_expression);
			PHALCON_CALL_METHOD_PARAMS_2(where_expression, this_ptr, "getsqlexpression", where_conditions, escape_char);
			PHALCON_SCONCAT_SV(sql, " WHERE ", where_expression);
		} else {
			PHALCON_SCONCAT_SV(sql, " WHERE ", where_conditions);
		}
	}

	/**
	 * Check for a GROUP clause
	 */
	if (phalcon_array_isset_string(definition, SS("group"))) {

		PHALCON_INIT_VAR(group_items);
		array_init(group_items);

		PHALCON_OBS_VAR(group_fields);
		phalcon_array_fetch_string(&group_fields, definition, SL("group"), PH_NOISY_CC);

		if (!phalcon_is_iterable(group_fields, &ah4, &hp4, 0, 0 TSRMLS_CC)) {
			return;
		}

		while (zend_hash_get_current_data_ex(ah4, (void**) &hd, &hp4) == SUCCESS) {

			PHALCON_GET_FOREACH_VALUE(group_field);

			PHALCON_INIT_NVAR(group_expression);
			PHALCON_CALL_METHOD_PARAMS_2(group_expression, this_ptr, "getsqlexpression", group_field, escape_char);
			phalcon_array_append(&group_items, group_expression, PH_SEPARATE TSRMLS_CC);

			zend_hash_move_forward_ex(ah4, &hp4);
		}

		PHALCON_INIT_VAR(group_sql);
		phalcon_fast_join_str(group_sql, SL(", "), group_items TSRMLS_CC);

		PHALCON_INIT_VAR(group_clause);
		PHALCON_CONCAT_SV(group_clause, " GROUP BY ", group_sql);
		phalcon_concat_self(&sql, group_clause TSRMLS_CC);

		/**
		 * Check for a HAVING clause
		 */
		if (phalcon_array_isset_string(definition, SS("having"))) {
			PHALCON_OBS_VAR(having_conditions);
			phalcon_array_fetch_string(&having_conditions, definition, SL("having"), PH_NOISY_CC);

			PHALCON_INIT_VAR(having_expression);
			PHALCON_CALL_METHOD_PARAMS_2(having_expression, this_ptr, "getsqlexpression", having_conditions, escape_char);
			PHALCON_SCONCAT_SV(sql, " HAVING ", having_expression);
		}
	}

	/**
	 * Check for a ORDER clause
	 */
	if (phalcon_array_isset_string(definition, SS("order"))) {

		PHALCON_OBS_VAR(order_fields);
		phalcon_array_fetch_string(&order_fields, definition, SL("order"), PH_NOISY_CC);

		PHALCON_INIT_VAR(order_items);
		array_init(order_items);

		if (!phalcon_is_iterable(order_fields, &ah5, &hp5, 0, 0 TSRMLS_CC)) {
			return;
		}

		while (zend_hash_get_current_data_ex(ah5, (void**) &hd, &hp5) == SUCCESS) {

			PHALCON_GET_FOREACH_VALUE(order_item);

			PHALCON_OBS_NVAR(order_expression);
			phalcon_array_fetch_long(&order_expression, order_item, 0, PH_NOISY_CC);

			PHALCON_INIT_NVAR(order_sql_item);
			PHALCON_CALL_METHOD_PARAMS_2(order_sql_item, this_ptr, "getsqlexpression", order_expression, escape_char);

			/**
			 * In the numeric 1 position could be a ASC/DESC clause
			 */
			if (phalcon_array_isset_long(order_item, 1)) {
				PHALCON_OBS_NVAR(sql_order_type);
				phalcon_array_fetch_long(&sql_order_type, order_item, 1, PH_NOISY_CC);

				PHALCON_INIT_NVAR(order_sql_item_type);
				PHALCON_CONCAT_VSV(order_sql_item_type, order_sql_item, " ", sql_order_type);
			} else {
				PHALCON_CPY_WRT(order_sql_item_type, order_sql_item);
			}

			phalcon_array_append(&order_items, order_sql_item_type, PH_SEPARATE TSRMLS_CC);

			zend_hash_move_forward_ex(ah5, &hp5);
		}

		PHALCON_INIT_VAR(order_sql);
		phalcon_fast_join_str(order_sql, SL(", "), order_items TSRMLS_CC);
		PHALCON_SCONCAT_SV(sql, " ORDER BY ", order_sql);
	}

        /**
	 * Oracle does not implement the LIMIT clause as some RDBMS do.
	 * We have to simulate it with subqueries and ROWNUM.
	 * Unfortunately because we use the column wildcard "*",
	 * this puts an extra column into the query result set.
	 */
	if (phalcon_array_isset_string(definition, SS("limit"))) {

		PHALCON_OBS_VAR(limit_value);
		phalcon_array_fetch_string(&limit_value, definition, SL("limit"), PH_NOISY_CC);
		if (Z_TYPE_P(limit_value) == IS_ARRAY) {

			PHALCON_OBS_VAR(number);
			phalcon_array_fetch_string(&number, limit_value, SL("number"), PH_NOISY_CC);

			/**
			 * Check for a OFFSET condition
			 */
			 if (phalcon_array_isset_string(limit_value, SS("offset"))) {
				PHALCON_OBS_VAR(offset);
				phalcon_array_fetch_string(&offset, limit_value, SL("offset"), PH_NOISY_CC);

				PHALCON_INIT_VAR(one);
				ZVAL_LONG(one, 1);

				PHALCON_INIT_VAR(ini_range);
				phalcon_add_function(ini_range, offset, one TSRMLS_CC);

				PHALCON_INIT_VAR(end_range);
				phalcon_add_function(end_range, offset, number TSRMLS_CC);

				PHALCON_INIT_VAR(sql_limit);
				PHALCON_SCONCAT_SVSVSV(sql_limit,"SELECT Z2.* FROM (SELECT Z1.*, ROWNUM DB_ROWNUM FROM ( ", sql, " ) Z1 ) Z2 WHERE Z2.DB_ROWNUM BETWEEN ", ini_range , " AND ",  end_range );
				sql = sql_limit;
		    } else {
		        if (phalcon_array_isset_string(definition, SS("where"))) {
		          PHALCON_SCONCAT_SV(sql, " AND ROWNUM <= ", number);
		        } else {
		          PHALCON_SCONCAT_SV(sql, " WHERE ROWNUM <= ", number);
		        }
			}
		} else {
		    if (phalcon_array_isset_string(definition, SS("where"))) {
		        PHALCON_SCONCAT_SV(sql, " AND ROWNUM <= ", limit_value);
		    } else {
		        PHALCON_SCONCAT_SV(sql, " WHERE ROWNUM <= ", limit_value);
		    }
		}
	}


	RETURN_CTOR(sql);}
