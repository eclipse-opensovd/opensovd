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

#ifndef SCORE_MW_DIAG_SOVD_OPERATION_MOCK_H
#define SCORE_MW_DIAG_SOVD_OPERATION_MOCK_H

#include "operation.h"
#include <string>

namespace mw::diag::sovd {

/// @brief Mock implementation of Operation for testing
/// @details Example implementation of a diagnostic operation
class OperationMock : public Operation {
public:
    /// @brief Construct mock operation
    /// @param id Operation identifier
    explicit OperationMock(std::pmr::string id)
        : operation_id_(std::move(id)),
          status_(OperationExecutionStatus::kStopped),
          execution_count_(0) {}

    /// @brief Get operation information
    /// @param request Diagnostic request
    /// @return Result containing operation info reply
    Result<OperationInfoReply> Info([[maybe_unused]] const DiagnosticRequest& request) override {
        OperationInfoReply reply;
        // Mock: populate operation info
        // reply.supported_modes_ would contain available modes
        
        return Result<OperationInfoReply>(reply);
    }

    /// @brief Get operation status
    /// @param request Diagnostic request
    /// @return Result containing operation status reply
    Result<OperationStatusReply> Status([[maybe_unused]] const DiagnosticRequest& request) override {
        OperationStatusReply reply;
        // Mock: populate current status
        // reply.capability_ = "some_capability"
        // reply.parameters_ = JSON with current parameters
        
        return Result<OperationStatusReply>(reply);
    }

    /// @brief Execute the operation
    /// @param request Diagnostic request with execution parameters
    /// @return Result containing execution reply
    Result<ExecuteOperationReply> Execute([[maybe_unused]] const DiagnosticRequest& request) override {
        if (status_ == OperationExecutionStatus::kRunning) {
            Error err;
            err.sovd_error = "operation_running";
            err.vendor_error = "OP_001";
            err.vendor_message = "Operation is already running";
            return Result<ExecuteOperationReply>(err);
        }
        
        status_ = OperationExecutionStatus::kRunning;
        execution_count_++;
        
        ExecuteOperationReply reply;
        // Mock: populate execution result
        
        // Simulate completion
        status_ = OperationExecutionStatus::kCompleted;
        
        return Result<ExecuteOperationReply>(reply);
    }

    /// @brief Resume paused operation
    /// @param request Diagnostic request
    /// @return Result containing execution reply
    Result<ExecuteOperationReply> Resume([[maybe_unused]] const DiagnosticRequest& request) override {
        if (status_ != OperationExecutionStatus::kStopped) {
            Error err;
            err.sovd_error = "invalid_state";
            err.vendor_error = "OP_002";
            err.vendor_message = "Operation cannot be resumed from current state";
            return Result<ExecuteOperationReply>(err);
        }
        
        status_ = OperationExecutionStatus::kRunning;
        
        ExecuteOperationReply reply;
        return Result<ExecuteOperationReply>(reply);
    }

    /// @brief Reset operation state
    /// @param request Diagnostic request
    /// @return Result containing execution reply
    Result<ExecuteOperationReply> Reset([[maybe_unused]] const DiagnosticRequest& request) override {
        status_ = OperationExecutionStatus::kStopped;
        execution_count_ = 0;
        
        ExecuteOperationReply reply;
        return Result<ExecuteOperationReply>(reply);
    }

    /// @brief Stop running operation
    /// @param request Diagnostic request
    /// @return Result indicating success or error
    Result<void> Stop([[maybe_unused]] const DiagnosticRequest& request) override {
        if (status_ != OperationExecutionStatus::kRunning) {
            Error err;
            err.sovd_error = "operation_not_running";
            err.vendor_error = "OP_003";
            err.vendor_message = "Operation is not running";
            return Result<void>(err);
        }
        
        status_ = OperationExecutionStatus::kStopped;
        
        return Result<void>();
    }

    /// @brief Handle custom OEM-specific operation
    /// @param request Diagnostic request
    /// @return Result containing JSON data reply
    Result<JsonDataReply> Handle([[maybe_unused]] const DiagnosticRequest& request) override {
        // Mock: handle custom capability
        JsonDataReply reply;
        
        return Result<JsonDataReply>(reply);
    }

    /// @brief Get current operation status (for testing)
    OperationExecutionStatus GetStatus() const { return status_; }
    uint32_t GetExecutionCount() const { return execution_count_; }

private:
    std::pmr::string operation_id_;
    OperationExecutionStatus status_;
    uint32_t execution_count_;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_OPERATION_MOCK_H
