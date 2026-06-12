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

#ifndef SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REPLY_H
#define SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REPLY_H

#include "diagnostic_entity.h"
#include "types.h"
#include <chrono>
#include <memory_resource>
#include <unordered_map>
#include <vector>

namespace mw::diag::sovd {

/// @brief Base class for diagnostic replies
class DiagnosticReply {
public:
    virtual ~DiagnosticReply() = default;

    // TODO: add public Getters/Setters!

protected:
    std::pmr::unordered_map<Key, Value> headers_;
};

/// @brief Proximity challenge information
class ProximityChallenge {
public:
    /// @brief Challenge string to be solved
    std::pmr::string challenge;

    /// @brief Timestamp when the challenge expires
    std::chrono::system_clock::time_point valid_until;
};

/// @brief Reply containing JSON data
class JsonDataReply : public DiagnosticReply {
public:
    // TODO: add public Getters/Setters!

protected:
    /// @brief JSON data created from content of deriving classes
    JSON data_;
};

/// @brief Reply for operation information requests
class OperationInfoReply : public JsonDataReply {
public:
    // TODO: add public Getters/Setters!

private:
    std::pmr::vector<DiagnosticEntity::Mode> supported_modes_;
    ProximityChallenge proximity_challenge_;
};

/// @brief Reply for operation status requests
class OperationStatusReply : public JsonDataReply {
public:
    // TODO: add public Getters/Setters!

private:
    std::pmr::string capability_;
    JSON parameters_;
    OperationExecutionStatus status_;
};

/// @brief Reply for operation execution requests
class ExecuteOperationReply : public JsonDataReply {
public:
    // TODO: add public Getters/Setters!

private:
    OperationExecutionStatus status_;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REPLY_H
