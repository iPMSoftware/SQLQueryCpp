#include <iostream>
#include <string>

class SQLQuery {
    public:
    SQLQuery() = default;
    SQLQuery& Create() {
        query_ += "CREATE ";
        return *this;
    }
    SQLQuery& Show() {
        query_ += "SHOW ";
        return *this;
    }
    SQLQuery& Databases() {
        query_ += "DATABASES ";
        return *this;
    }
    SQLQuery& Database(const std::string& database_name) {
        query_ += "DATABASE " + database_name + " ";
        return *this;
    }
    SQLQuery& Drop() {
        query_ += "DROP ";
        return *this;
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    SELECT(T head, U... tail) {
        query_ += (select_started_ ? ", " : "SELECT ");
        select_started_ = true;
        query_ += std::string(head);
        return SELECT(tail...);
    }

    SQLQuery& SELECT() {
        if(!select_started_) {
            query_ += "SELECT";
        }
        query_ += std::string(" ");
        select_started_ = false;
        return *this;
    }

    SQLQuery& FROM(const std::string& from) {
        query_ += "FROM " + from + std::string(" ");
        return *this;
    }

    SQLQuery& DISTINCT(const std::string& distinct) {
        query_ += "DISTINCT " + distinct + " ";
        return *this;
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    COUNT(T head ,U... tail) {
        query_ += (count_started_ ? ", " : "COUNT(");
        count_started_ = true;
        query_ += std::string(head);
        return COUNT(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    COUNT(T head ,U... tail) {
        query_ += (count_started_ ? ", " : "COUNT(");
        count_started_ = true;
        query_ += head.ToString();
        return COUNT(tail...);
    }

    SQLQuery& COUNT() {
        if(!count_started_) {
            query_ += "COUNT";
        }
        query_ += std::string(") ");
        count_started_ = false;
        return *this;
    }

    template<typename T>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    WHERE(T param) {
        query_ += "WHERE " + std::string(param) + " ";
        return *this;
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    WHERE(T head ,U... tail) {
        auto size = sizeof...(U);
        query_ += (where_started_ ? " " : "WHERE (");
        where_started_ = true;
        query_ += std::string(head);
        return WHERE(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    WHERE(T head ,U... tail) {
        query_ += (where_started_ ? " " : "WHERE (");
        where_started_ = true;
        query_ += head.ToString();
        return WHERE(tail...);
    }

    SQLQuery& WHERE() {
        if(!where_started_) {
            query_ += "WHERE";
        }
        query_ += std::string(") ");
        where_started_ = false;
        return *this;
    }

    template<typename T>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    AND(T param) {
        query_ += "AND " + std::string(param) + " ";
        return *this;
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_constructible_v<std::string,T>,SQLQuery&>
    AND(T head ,U... tail) {
        query_ += (and_started_ ? " " : "AND (");
        and_started_ = true;
        query_ += std::string(head);
        return AND(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    AND(T head ,U... tail) {
        query_ += (and_started_ ? " " : "AND (");
        and_started_ = true;
        query_ += head.ToString();
        return AND(tail...);
    }

    SQLQuery& AND() {
        if(!and_started_) {
            query_ += "WHERE";
        }
        query_ += std::string(") ");
        and_started_ = false;
        return *this;
    }

    SQLQuery& OR(const std::string& param) {
        query_ += "OR " + param + " ";
        return *this;
    }

    const std::string& ToString() {
        query_.erase(query_.length()-1);
        return query_;
    }
    private:
    std::string query_ {};
    bool select_started_ {false};
    bool count_started_ {false};
    bool where_started_ {false};
    bool and_started_ {false};
};


