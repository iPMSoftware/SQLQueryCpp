#include <gtest/gtest.h>

#include "sql_query.h"

TEST(SqlQueryTest,ShowDatabase) {
    auto cmd = SQLQuery().Show().Databases().ToString();
    EXPECT_STREQ(cmd.c_str(),"SHOW DATABASES");
}

TEST(SqlQueryTest,DropDatabase) {
    auto cmd = SQLQuery().Drop().Databases().ToString();
    EXPECT_STREQ(cmd.c_str(),"DROP DATABASES");
}

TEST(SqlQueryTest,CreateDatabase) {
    auto cmd = SQLQuery().Create().Database("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"CREATE DATABASE test_db");
}

TEST(SqlQueryTestSelectingColumns,SelectAll) {
    auto cmd = SQLQuery().SELECT("*").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT *");
}

TEST(SqlQueryTestSelectingColumns,SelectAllFrom) {
    auto cmd = SQLQuery().SELECT("*").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT * FROM test_db");
}

TEST(SqlQueryTestSelectingColumns,SelectTwoRecords) {
    auto cmd = SQLQuery().SELECT("name","surname").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name, surname");
}

TEST(SqlQueryTestSelectingColumns,SelectMultipleRecords) {
    auto cmd = SQLQuery().SELECT("name","surname","age","sex").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name, surname, age, sex");
}

TEST(SqlQueryTestSelectingColumns,SelectRecordFromDatabase) {
    auto cmd = SQLQuery().SELECT("name").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name FROM test_db");
}

TEST(SqlQueryTestSelectingColumns,SelectTwoRecordsFromDatabase) {
    auto cmd = SQLQuery().SELECT("name","surname").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name, surname FROM test_db");
}

TEST(SqlQueryTestSelectingColumns,SelectMultipleRecordsFromDatabase) {
    auto cmd = SQLQuery().SELECT("name","surname","age","sex").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name, surname, age, sex FROM test_db");
}

TEST(SqlQueryTestSelectingColumns,SelectDistinct) {
    auto cmd = SQLQuery().SELECT().DISTINCT("name").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT DISTINCT name");
}

TEST(SqlQueryTestSelectingColumns,SelectDistinctFromDatabase) {
    auto cmd = SQLQuery().SELECT().DISTINCT("name").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT DISTINCT name FROM test_db");
}
