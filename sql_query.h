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

    const std::string& ToString() {
        query_.erase(query_.length()-1);
        return query_;
    }
    private:
    std::string query_ {};
    bool select_started_ {false};
    bool count_started_ {false};
};


