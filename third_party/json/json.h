#ifndef THIRD_PARTY_JSON_JSON_H
#define THIRD_PARTY_JSON_JSON_H

#include <memory_resource>
#include <string>
#include <stdexcept>
#include <sstream>
#include <variant>
#include <unordered_map>
#include <vector>

namespace json {

/// @brief Mock JSON implementation for testing and prototyping
/// @details This is a simplified JSON type that provides basic functionality
/// for storing and accessing JSON-like data. In production, this would be
/// replaced with a proper JSON library (e.g., nlohmann/json, RapidJSON, etc.)
class JSON {
public:
    /// @brief JSON value types
    enum class Type {
        kNull,
        kBoolean,
        kNumber,
        kString,
        kArray,
        kObject
    };

    /// @brief Default constructor - creates null JSON value
    JSON() : type_(Type::kNull) {}

    /// @brief Construct from C-string
    explicit JSON(const char* str) : json_data(str), type_(Type::kString), data_(std::pmr::string(str)) {}

    /// @brief Construct from PMR string
    explicit JSON(std::pmr::string str) : json_data(str), type_(Type::kString), data_(std::move(str)) {}

    /// @brief Construct from std::string
    explicit JSON(const std::string& str) : json_data(str.c_str()), type_(Type::kString), data_(std::pmr::string(str.c_str())) {}

    /// @brief Construct from boolean
    explicit JSON(bool value) : type_(Type::kBoolean), data_(value) {}

    /// @brief Construct from integer
    explicit JSON(int value) : type_(Type::kNumber), data_(static_cast<double>(value)) {}

    /// @brief Construct from double
    explicit JSON(double value) : type_(Type::kNumber), data_(value) {}

    /// @brief Copy constructor
    JSON(const JSON& other) = default;

    /// @brief Move constructor
    JSON(JSON&& other) noexcept = default;

    /// @brief Copy assignment from another JSON
    JSON& operator=(const JSON& other) = default;

    /// @brief Move assignment from another JSON
    JSON& operator=(JSON&& other) noexcept = default;

    /// @brief Assignment from C-string
    JSON& operator=(const char* str) {
        type_ = Type::kString;
        data_ = std::pmr::string(str);
        json_data = str;
        return *this;
    }

    /// @brief Assignment from PMR string
    JSON& operator=(const std::pmr::string& str) {
        type_ = Type::kString;
        data_ = str;
        json_data = str;
        return *this;
    }

    /// @brief Assignment from PMR string (move)
    JSON& operator=(std::pmr::string&& str) {
        type_ = Type::kString;
        json_data = str;
        data_ = std::move(str);
        return *this;
    }

    /// @brief Assignment from std::string
    JSON& operator=(const std::string& str) {
        type_ = Type::kString;
        data_ = std::pmr::string(str.c_str());
        json_data = str.c_str();
        return *this;
    }

    /// @brief Assignment from boolean
    JSON& operator=(bool value) {
        type_ = Type::kBoolean;
        data_ = value;
        return *this;
    }

    /// @brief Assignment from integer
    JSON& operator=(int value) {
        type_ = Type::kNumber;
        data_ = static_cast<double>(value);
        return *this;
    }

    /// @brief Assignment from double
    JSON& operator=(double value) {
        type_ = Type::kNumber;
        data_ = value;
        return *this;
    }

    /// @brief Get the type of the JSON value
    Type type() const { return type_; }

    /// @brief Check if the JSON value is null
    bool is_null() const { return type_ == Type::kNull; }

    /// @brief Check if the JSON value is a boolean
    bool is_boolean() const { return type_ == Type::kBoolean; }

    /// @brief Check if the JSON value is a number
    bool is_number() const { return type_ == Type::kNumber; }

    /// @brief Check if the JSON value is a string
    bool is_string() const { return type_ == Type::kString; }

    /// @brief Check if the JSON value is an array
    bool is_array() const { return type_ == Type::kArray; }

    /// @brief Check if the JSON value is an object
    bool is_object() const { return type_ == Type::kObject; }

    /// @brief Check if the JSON value is empty (null or empty string/array/object)
    bool empty() const {
        switch (type_) {
            case Type::kNull:
                return true;
            case Type::kString:
                return std::get<std::pmr::string>(data_).empty();
            case Type::kArray:
                return std::get<std::pmr::vector<JSON>>(data_).empty();
            case Type::kObject:
                return std::get<std::pmr::unordered_map<std::pmr::string, JSON>>(data_).empty();
            default:
                return false;
        }
    }

    /// @brief Get string value (throws if not a string)
    const std::pmr::string& as_string() const {
        if (type_ != Type::kString) {
            throw std::runtime_error("JSON value is not a string");
        }
        return std::get<std::pmr::string>(data_);
    }

    /// @brief Get boolean value (throws if not a boolean)
    bool as_boolean() const {
        if (type_ != Type::kBoolean) {
            throw std::runtime_error("JSON value is not a boolean");
        }
        return std::get<bool>(data_);
    }

    /// @brief Get number value (throws if not a number)
    double as_number() const {
        if (type_ != Type::kNumber) {
            throw std::runtime_error("JSON value is not a number");
        }
        return std::get<double>(data_);
    }

    /// @brief Get array value (throws if not an array)
    const std::pmr::vector<JSON>& as_array() const {
        if (type_ != Type::kArray) {
            throw std::runtime_error("JSON value is not an array");
        }
        return std::get<std::pmr::vector<JSON>>(data_);
    }

    /// @brief Get object value (throws if not an object)
    const std::pmr::unordered_map<std::pmr::string, JSON>& as_object() const {
        if (type_ != Type::kObject) {
            throw std::runtime_error("JSON value is not an object");
        }
        return std::get<std::pmr::unordered_map<std::pmr::string, JSON>>(data_);
    }

    /// @brief Get mutable array value (throws if not an array)
    std::pmr::vector<JSON>& as_array() {
        if (type_ != Type::kArray) {
            throw std::runtime_error("JSON value is not an array");
        }
        return std::get<std::pmr::vector<JSON>>(data_);
    }

    /// @brief Get mutable object value (throws if not an object)
    std::pmr::unordered_map<std::pmr::string, JSON>& as_object() {
        if (type_ != Type::kObject) {
            throw std::runtime_error("JSON value is not an object");
        }
        return std::get<std::pmr::unordered_map<std::pmr::string, JSON>>(data_);
    }

    /// @brief Array access operator (converts to array if needed)
    JSON& operator[](size_t index) {
        if (type_ == Type::kNull) {
            type_ = Type::kArray;
            data_ = std::pmr::vector<JSON>();
        }
        if (type_ != Type::kArray) {
            throw std::runtime_error("JSON value is not an array");
        }
        auto& arr = std::get<std::pmr::vector<JSON>>(data_);
        if (index >= arr.size()) {
            arr.resize(index + 1);
        }
        return arr[index];
    }

    /// @brief Object access operator (converts to object if needed)
    JSON& operator[](const std::pmr::string& key) {
        if (type_ == Type::kNull) {
            type_ = Type::kObject;
            data_ = std::pmr::unordered_map<std::pmr::string, JSON>();
        }
        if (type_ != Type::kObject) {
            throw std::runtime_error("JSON value is not an object");
        }
        return std::get<std::pmr::unordered_map<std::pmr::string, JSON>>(data_)[key];
    }

    /// @brief Object access operator with C-string key
    JSON& operator[](const char* key) {
        return (*this)[std::pmr::string(key)];
    }

    /// @brief Serialize to string (simple implementation)
    std::pmr::string to_string() const {
        std::pmr::string result;
        switch (type_) {
            case Type::kNull:
                result = "null";
                break;
            case Type::kBoolean:
                result = std::get<bool>(data_) ? "true" : "false";
                break;
            case Type::kNumber: {
                std::ostringstream oss;
                oss << std::get<double>(data_);
                result = oss.str().c_str();
                break;
            }
            case Type::kString:
                result = "\"" + std::get<std::pmr::string>(data_) + "\"";
                break;
            case Type::kArray: {
                result = "[";
                const auto& arr = std::get<std::pmr::vector<JSON>>(data_);
                for (size_t i = 0; i < arr.size(); ++i) {
                    if (i > 0) result += ",";
                    result += arr[i].to_string();
                }
                result += "]";
                break;
            }
            case Type::kObject: {
                result = "{";
                const auto& obj = std::get<std::pmr::unordered_map<std::pmr::string, JSON>>(data_);
                bool first = true;
                for (const auto& [key, value] : obj) {
                    if (!first) result += ",";
                    first = false;
                    result += "\"" + key + "\":" + value.to_string();
                }
                result += "}";
                break;
            }
        }
        return result;
    }

    /// @brief Parse from string (simple implementation - handles basic JSON)
    static JSON parse(const std::pmr::string& str) {
        // Simple mock implementation - just stores the raw string
        // In production, this would be a proper JSON parser
        JSON result;
        result.type_ = Type::kString;
        result.data_ = str;
        return result;
    }

    /// @brief Access to raw JSON data string (for compatibility)
    std::pmr::string json_data;

private:
    Type type_;
    std::variant<
        std::monostate,                                          // kNull
        bool,                                                    // kBoolean
        double,                                                  // kNumber
        std::pmr::string,                                        // kString
        std::pmr::vector<JSON>,                                  // kArray
        std::pmr::unordered_map<std::pmr::string, JSON>         // kObject
    > data_;
};

} // namespace json

#endif // THIRD_PARTY_JSON_JSON_H
