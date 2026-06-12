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

#ifndef SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REQUEST_H
#define SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REQUEST_H

#include "types.h"
#include <memory_resource>
#include <optional>
#include <unordered_map>

namespace mw::diag::sovd {

/// @brief Request data for diagnostic operations
class DiagnosticRequest {
public:
    /// @brief HTTP-style headers for the request
    std::pmr::unordered_map<Key, Value> headers;

    /// @brief Optional proximity challenge response
    std::optional<std::pmr::string> proximity_response;

    /// @brief JSON payload data
    JSON data;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DIAGNOSTIC_REQUEST_H
