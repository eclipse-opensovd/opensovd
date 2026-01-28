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

#ifndef SCORE_MW_DIAG_SOVD_OPERATION_H
#define SCORE_MW_DIAG_SOVD_OPERATION_H

#include "diagnostic_reply.h"
#include "diagnostic_request.h"
#include "types.h"

namespace mw::diag::sovd {

/// @brief Interface for SOVD operations
class Operation {
public:
    virtual ~Operation() = default;

    /// @brief Get information about the operation
    /// @param request The diagnostic request
    /// @return Result containing operation information or error
    virtual Result<OperationInfoReply> Info(const DiagnosticRequest& request) = 0;

    /// @brief Get the current status of the operation
    /// @param request The diagnostic request
    /// @return Result containing operation status or error
    virtual Result<OperationStatusReply> Status(const DiagnosticRequest& request) = 0;

    /// @brief Execute the operation
    /// @param request The diagnostic request containing operation parameters
    /// @return Result containing execution reply or error
    virtual Result<ExecuteOperationReply> Execute(const DiagnosticRequest& request) = 0;

    /// @brief Resume a previously stopped operation
    /// @param request The diagnostic request
    /// @return Result containing execution reply or error
    virtual Result<ExecuteOperationReply> Resume(const DiagnosticRequest& request) = 0;

    /// @brief Reset the operation to its initial state
    /// @param request The diagnostic request
    /// @return Result containing execution reply or error
    virtual Result<ExecuteOperationReply> Reset(const DiagnosticRequest& request) = 0;

    /// @brief Stop a running operation
    /// @param request The diagnostic request
    /// @return Result indicating success or error
    virtual Result<void> Stop(const DiagnosticRequest& request) = 0;

    /// @brief Handle OEM-specific capabilities
    /// @param request The diagnostic request
    /// @return Result containing JSON data reply or error
    /// @note Only to be overridden by deriving classes if required
    virtual Result<JsonDataReply> Handle(const DiagnosticRequest& request) = 0;

protected:
    Operation() = default;
    Operation(const Operation&) = delete;
    Operation& operator=(const Operation&) = delete;
    Operation(Operation&&) = default;
    Operation& operator=(Operation&&) = default;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_OPERATION_H
