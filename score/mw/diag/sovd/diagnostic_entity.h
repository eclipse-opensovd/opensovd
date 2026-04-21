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

#ifndef SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_H
#define SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_H

#include "types.h"
#include <chrono>
#include <memory_resource>
#include <optional>
#include <string>
#include <vector>

namespace mw::diag::sovd {

/// @brief Diagnostic entity representing a diagnosable component
class DiagnosticEntity {
public:
    using Identifier = std::pmr::string;

    /// @brief Kind of diagnostic entity
    enum class Kind {
        kApplication
    };

    /// @brief Mode configuration for a diagnostic entity
    struct Mode {
        std::pmr::string id;
        std::pmr::string name;
        std::optional<std::pmr::string> translation_id;
        std::pmr::vector<std::pmr::string> values;
    };

    virtual ~DiagnosticEntity() = default;

    /// @brief Lock the diagnostic entity for exclusive access
    /// @return Result indicating success or error
    /// @note TO BE CLARIFIED: Required here or handled completely by SOVD Server?
    virtual Result<void> Lock() = 0;

    /// @brief Unlock the diagnostic entity
    /// @return Result indicating success or error
    /// @note TO BE CLARIFIED: Required here or handled completely by SOVD Server?
    virtual Result<void> Unlock() = 0;

    /// @brief Get the kind of this diagnostic entity
    /// @return The entity kind
    virtual Kind GetKind() const = 0;

    /// @brief Get all supported modes for this entity
    /// @return Result containing vector of supported modes
    virtual Result<std::pmr::vector<Mode>> GetSupportedModes() const = 0;

    /// @brief Apply a specific mode to the entity
    /// @param mode_id The identifier of the mode to apply
    /// @param mode_value The value to set for the mode
    /// @param expiration_timeout Optional timeout after which the mode expires
    /// @return Result indicating success or error
    virtual Result<void> ApplyMode(
        const std::pmr::string& mode_id,
        const std::pmr::string& mode_value,
        std::optional<std::chrono::seconds> expiration_timeout) = 0;

protected:
    DiagnosticEntity() = default;
    DiagnosticEntity(const DiagnosticEntity&) = delete;
    DiagnosticEntity& operator=(const DiagnosticEntity&) = delete;
    DiagnosticEntity(DiagnosticEntity&&) = default;
    DiagnosticEntity& operator=(DiagnosticEntity&&) = default;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_H
