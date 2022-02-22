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

TEST(SqlQueryTestSelectingColumns,Count) {
    auto cmd = SQLQuery().SELECT().COUNT("name").FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT COUNT(name) FROM test_db");
}

TEST(SqlQueryTestSelectingColumns,CountDistinct) {
    auto cmd = SQLQuery().SELECT().COUNT(SQLQuery().DISTINCT("name")).FROM("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT COUNT(DISTINCT name) FROM test_db");
}

TEST(SqlQueryTestFilteringRows,SimpleFilteringNumericValues) {
    auto cmd = SQLQuery().SELECT("*").FROM("test_db").WHERE("age > 20").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT * FROM test_db WHERE age > 20");
}

TEST(SqlQueryTestFilteringRows,SimpleFilteringTextValues) {
    auto cmd = SQLQuery().SELECT("*").FROM("test_db").WHERE("name = 'John'").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT * FROM test_db WHERE name = 'John'");
}

TEST(SqlQueryTestFilteringRows,CombiningFiltersAnd) {
    auto cmd = SQLQuery().SELECT("person").FROM("test_db").WHERE("age > 20").AND("height > 170").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT person FROM test_db WHERE age > 20 AND height > 170");
}

TEST(SqlQueryTestFilteringRows,CombiningFiltersOr) {
    auto cmd = SQLQuery().SELECT("person").FROM("test_db").WHERE("age > 20").OR("height > 170").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT person FROM test_db WHERE age > 20 OR height > 170");
}

TEST(SqlQueryTestFilteringRows,CombiningFiltersAndOr) {
    auto cmd = SQLQuery().SELECT("person").FROM("test_db").WHERE("age > 20",SQLQuery().OR("height > 170")).AND("age < 15",SQLQuery().OR("height < 150")).ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT person FROM test_db WHERE (age > 20 OR height > 170) AND (age < 15 OR height < 150)");
}