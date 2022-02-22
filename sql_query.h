#include <iostream>
#include <string>
#include <map>

class SQLQuery {
    public:
    SQLQuery() {
        commands_started_["select"] = false;
        commands_started_["count"] = false;
        commands_started_["where"] = false;
        commands_started_["and"] = false;
    }
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
        query_ += (commands_started_["select"] ? ", " : "SELECT ");
        commands_started_["select"] = true;
        query_ += std::string(head);
        return SELECT(tail...);
    }

    SQLQuery& SELECT() {
        if(!commands_started_["select"]) {
            query_ += "SELECT";
        }
        query_ += std::string(" ");
        commands_started_["select"] = false;
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
        query_ += (commands_started_["where"] ? ", " : "COUNT(");
        commands_started_["where"] = true;
        query_ += std::string(head);
        return COUNT(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    COUNT(T head ,U... tail) {
        query_ += (commands_started_["where"] ? ", " : "COUNT(");
        commands_started_["where"] = true;
        query_ += head.ToString();
        return COUNT(tail...);
    }

    SQLQuery& COUNT() {
        if(!commands_started_["where"]) {
            query_ += "COUNT";
        }
        query_ += std::string(") ");
        commands_started_["where"] = false;
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
        query_ += (commands_started_["where"] ? " " : "WHERE (");
        commands_started_["where"] = true;
        query_ += std::string(head);
        return WHERE(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    WHERE(T head ,U... tail) {
        query_ += (commands_started_["where"] ? " " : "WHERE (");
        commands_started_["where"] = true;
        query_ += head.ToString();
        return WHERE(tail...);
    }

    SQLQuery& WHERE() {
        if(!commands_started_["where"]) {
            query_ += "WHERE";
        }
        query_ += std::string(") ");
        commands_started_["where"] = false;
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
        query_ += (commands_started_["and"] ? " " : "AND (");
        commands_started_["and"] = true;
        query_ += std::string(head);
        return AND(tail...);
    }

    template<typename T, typename... U>
    typename std::enable_if_t<std::is_same_v<T, SQLQuery>,SQLQuery&>
    AND(T head ,U... tail) {
        query_ += (commands_started_["and"] ? " " : "AND (");
        commands_started_["and"] = true;
        query_ += head.ToString();
        return AND(tail...);
    }

    SQLQuery& AND() {
        if(!commands_started_["and"]) {
            query_ += "WHERE";
        }
        query_ += std::string(") ");
        commands_started_["and"] = false;
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

    std::map<std::string,bool> commands_started_ {};
};


