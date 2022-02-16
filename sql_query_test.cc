#include <gtest/gtest.h>

#include "sql_query.h"

TEST(SqlQueryTest,ShowDatabase) {
    auto cmd = SQLQuery().Show().Databases().ToString();
    EXPECT_STREQ(cmd.c_str(),"SHOW DATABASES ");
}

TEST(SqlQueryTest,DropDatabase) {
    auto cmd = SQLQuery().Drop().Databases().ToString();
    EXPECT_STREQ(cmd.c_str(),"DROP DATABASES ");
}

TEST(SqlQueryTest,CreateDatabase) {
    auto cmd = SQLQuery().Create().Database("test_db").ToString();
    EXPECT_STREQ(cmd.c_str(),"CREATE DATABASE test_db");
}

TEST(SqlQueryTest,SelectAll) {
    auto cmd = SQLQuery().SELECT("*").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT *");
}

TEST(SqlQueryTest,SelectTwoRecord) {
    auto cmd = SQLQuery().SELECT("name","surname").ToString();
    EXPECT_STREQ(cmd.c_str(),"SELECT name, surname");
}
