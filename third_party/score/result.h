#ifndef THIRD_PARTY_SCORE_RESULT_H
#define THIRD_PARTY_SCORE_RESULT_H

#include <variant>
#include <stdexcept>
#include <utility>

namespace score {

/// @brief Mock implementation of Result type for error handling
/// @tparam T The type of the value on success
/// @tparam E The type of the error on failure (defaults to int)
/// @details This is a simplified mock implementation similar to std::expected (C++23)
template <typename T, typename E = int>
class Result {
public:
    /// @brief Construct a successful result with a value
    /// @param value The success value
    Result(T value) : data_(std::move(value)) {}

    /// @brief Construct a failed result with an error
    /// @param error The error value
    Result(E error) : data_(error) {}

    /// @brief Check if the result contains a value
    /// @return true if result is successful, false if it contains an error
    bool has_value() const noexcept {
        return std::holds_alternative<T>(data_);
    }

    /// @brief Check if the result contains an error
    /// @return true if result contains an error, false if successful
    bool has_error() const noexcept {
        return std::holds_alternative<E>(data_);
    }

    /// @brief Get the contained value
    /// @return Reference to the contained value
    /// @throws std::runtime_error if result contains an error
    T& value() & {
        if (!has_value()) {
            throw std::runtime_error("Result does not contain a value");
        }
        return std::get<T>(data_);
    }

    /// @brief Get the contained value (const)
    /// @return Const reference to the contained value
    /// @throws std::runtime_error if result contains an error
    const T& value() const & {
        if (!has_value()) {
            throw std::runtime_error("Result does not contain a value");
        }
        return std::get<T>(data_);
    }

    /// @brief Get the contained value (rvalue)
    /// @return Rvalue reference to the contained value
    /// @throws std::runtime_error if result contains an error
    T&& value() && {
        if (!has_value()) {
            throw std::runtime_error("Result does not contain a value");
        }
        return std::get<T>(std::move(data_));
    }

    /// @brief Get the contained error
    /// @return Reference to the contained error
    /// @throws std::runtime_error if result contains a value
    E& error() & {
        if (!has_error()) {
            throw std::runtime_error("Result does not contain an error");
        }
        return std::get<E>(data_);
    }

    /// @brief Get the contained error (const)
    /// @return Const reference to the contained error
    /// @throws std::runtime_error if result contains a value
    const E& error() const & {
        if (!has_error()) {
            throw std::runtime_error("Result does not contain an error");
        }
        return std::get<E>(data_);
    }

    /// @brief Boolean conversion operator
    /// @return true if result is successful
    explicit operator bool() const noexcept {
        return has_value();
    }

private:
    std::variant<T, E> data_;
};

/// @brief Specialization of Result for void success type
/// @tparam E The type of the error on failure
template <typename E>
class Result<void, E> {
public:
    /// @brief Construct a successful result
    Result() : has_value_(true), error_() {}

    /// @brief Construct a failed result with an error
    /// @param error The error value
    Result(E error) : has_value_(false), error_(std::move(error)) {}

    /// @brief Check if the result is successful
    /// @return true if result is successful, false if it contains an error
    bool has_value() const noexcept {
        return has_value_;
    }

    /// @brief Check if the result contains an error
    /// @return true if result contains an error, false if successful
    bool has_error() const noexcept {
        return !has_value_;
    }

    /// @brief Get the contained error
    /// @return Reference to the contained error
    /// @throws std::runtime_error if result is successful
    E& error() & {
        if (has_value_) {
            throw std::runtime_error("Result does not contain an error");
        }
        return error_;
    }

    /// @brief Get the contained error (const)
    /// @return Const reference to the contained error
    /// @throws std::runtime_error if result is successful
    const E& error() const & {
        if (has_value_) {
            throw std::runtime_error("Result does not contain an error");
        }
        return error_;
    }

    /// @brief Boolean conversion operator
    /// @return true if result is successful
    explicit operator bool() const noexcept {
        return has_value_;
    }

private:
    bool has_value_;
    E error_;
};

namespace details {

/// @brief Expected type for result handling (similar to std::expected)
/// @tparam T Value type on success
/// @tparam E Error type on failure
/// @note This is an alias to Result for consistency
template <typename T, typename E>
using expected = Result<T, E>;

} // namespace details

} // namespace score

#endif // THIRD_PARTY_SCORE_RESULT_H
