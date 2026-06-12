/********************************************************************************
 * Copyright (c) 2025 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef SCORE_MW_DIAG_SOVD_DATA_RESOURCE_MOCK_H
#define SCORE_MW_DIAG_SOVD_DATA_RESOURCE_MOCK_H

#include "data_resource.h"
#include <string>

namespace mw::diag::sovd {

/// @brief Mock implementation of ReadOnlyDataResource for testing
class ReadOnlyDataResourceMock : public ReadOnlyDataResource {
public:
    /// @brief Construct mock read-only data resource
    /// @param id Resource identifier
    explicit ReadOnlyDataResourceMock(std::pmr::string id)
        : resource_id_(std::move(id)) {}

    /// @brief Get data resource value
    /// @return Result containing JSON data reply
    Result<JsonDataReply> Get() override {
        JsonDataReply reply;
        // Mock: return sample JSON data
        // reply.data_ would contain: {"id": "resource_id", "value": 42}
        
        return Result<JsonDataReply>(reply);
    }

private:
    std::pmr::string resource_id_;
};

/// @brief Mock implementation of WritableDataResource for testing
class WritableDataResourceMock : public WritableDataResource {
public:
    /// @brief Construct mock writable data resource
    /// @param id Resource identifier
    explicit WritableDataResourceMock(std::pmr::string id)
        : resource_id_(std::move(id)) {}

    /// @brief Update data resource value
    /// @param request Diagnostic request with new data
    /// @return Result indicating success or error
    Result<void> Put(const DiagnosticRequest& request) override {
        // Mock: validate and store request data
        if (request.data.empty()) {
            Error err;
            err.sovd_error = "invalid_data";
            err.vendor_error = "DATA_001";
            err.vendor_message = "Request data is empty";
            return Result<void>(err);
        }
        
        last_request_data_ = request.data.json_data;
        
        return Result<void>();
    }

    /// @brief Get last request data (for testing)
    const std::pmr::string& GetLastRequestData() const { return last_request_data_; }

private:
    std::pmr::string resource_id_;
    std::pmr::string last_request_data_;
};

/// @brief Mock implementation of DataResource (read + write) for testing
class DataResourceMock : public DataResource {
public:
    /// @brief Construct mock data resource
    /// @param id Resource identifier
    explicit DataResourceMock(std::pmr::string id)
        : resource_id_(std::move(id)),
          stored_value_(42) {} // Default value

    /// @brief Get data resource value
    /// @return Result containing JSON data reply
    Result<JsonDataReply> Get() override {
        JsonDataReply reply;
        // Mock: return current stored value as JSON
        // reply.data_ would contain: {"id": "resource_id", "value": stored_value_}
        
        return Result<JsonDataReply>(reply);
    }

    /// @brief Update data resource value
    /// @param request Diagnostic request with new data
    /// @return Result indicating success or error
    Result<void> Put([[maybe_unused]] const DiagnosticRequest& request) override {
        // Mock: parse and update stored value
        // In real implementation, would parse JSON from request.data
        stored_value_++;
        
        return Result<void>();
    }

private:
    std::pmr::string resource_id_;
    int stored_value_;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DATA_RESOURCE_MOCK_H
