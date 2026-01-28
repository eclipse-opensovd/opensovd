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

#ifndef SCORE_MW_DIAG_SOVD_TYPES_H
#define SCORE_MW_DIAG_SOVD_TYPES_H

#include "third_party/score/result.h"
#include "third_party/json/json.h"
#include <chrono>
#include <memory_resource>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace mw::diag::sovd {

/// @brief Error information for SOVD operations
class Error {
public:
    std::pmr::string sovd_error;
    std::pmr::string vendor_error;
    std::pmr::string vendor_message;
};

/// @brief Result type for SOVD operations
/// @tparam T The type of the value on success
template <typename T>
using Result = score::details::expected<T, Error>;

/// @brief Translation identifier for internationalization
class TranslationIdentifier {
public:
    std::pmr::string id;
};

/// @brief Identifier for data categories
class DataCategoryIdentifier {
public:
    std::pmr::string value;
};

/// @brief Identifier for data groups
class DataGroupIdentifier {
public:
    std::pmr::string value;
};

/// @brief Short description for data groups
class DataGroupShortDesc {
public:
    std::pmr::string description;
};

/// @brief View of a JSON schema
class JsonSchemaView {
public:
    // JSON schema content - implementation details to be defined
    std::pmr::string schema_content;
};

/// @brief Predefined data category identifiers according to SOVD specification
enum class DataCategoryIdentifiers {
    kIdentification,  // 'identData'
    kMeasurement,     // 'currentData'
    kParameter,       // 'storedData'
    kSysInfo          // 'sysInfo'
};

/// @brief Policy for operation invocation behavior
enum class OperationInvocationPolicy {
    kPerformsSynchronousInvocation,
    kRequiresIndividualAsyncInvocations,
    kSupportsConcurrentAsyncInvocations
};

/// @brief Proximity proof requirement
enum class ProximityProof {
    kRequired,
    kNotRequired
};

/// @brief Execution status of an operation
enum class OperationExecutionStatus {
    kFailed,
    kRunning,
    kStopped,
    kCompleted
};

/// @brief JSON type alias to third_party JSON implementation
/// @details Uses the comprehensive JSON mock from third_party/json
///          Provides full JSON functionality including type checking,
///          object/array access, and serialization
using JSON = json::JSON;

/// @brief Key type for header maps
using Key = std::pmr::string;

/// @brief Value type for header maps
using Value = std::pmr::string;

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_TYPES_H
