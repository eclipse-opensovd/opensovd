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

#ifndef SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_MOCK_H
#define SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_MOCK_H

#include "diagnostic_entity.h"
#include <string>

namespace mw::diag::sovd {

/// @brief Mock implementation of DiagnosticEntity for testing
/// @details Example implementation of a diagnosable application component
class DiagnosticEntityMock : public DiagnosticEntity {
public:
    /// @brief Construct mock diagnostic entity
    /// @param id Entity identifier
    explicit DiagnosticEntityMock(std::pmr::string id)
        : entity_id_(std::move(id)),
          is_locked_(false) {}

    /// @brief Lock the diagnostic entity
    /// @return Result indicating success or error
    Result<void> Lock() override {
        if (is_locked_) {
            Error err;
            err.sovd_error = "entity_locked";
            err.vendor_error = "LOCK_001";
            err.vendor_message = "Entity is already locked";
            return Result<void>(err);
        }
        
        is_locked_ = true;
        return Result<void>();
    }

    /// @brief Unlock the diagnostic entity
    /// @return Result indicating success or error
    Result<void> Unlock() override {
        if (!is_locked_) {
            Error err;
            err.sovd_error = "entity_not_locked";
            err.vendor_error = "UNLOCK_001";
            err.vendor_message = "Entity is not locked";
            return Result<void>(err);
        }
        
        is_locked_ = false;
        return Result<void>();
    }

    /// @brief Get the kind of diagnostic entity
    /// @return Entity kind (Application)
    Kind GetKind() const override {
        return Kind::kApplication;
    }

    /// @brief Get supported diagnostic modes
    /// @return Result containing vector of supported modes
    Result<std::pmr::vector<Mode>> GetSupportedModes() const override {
        std::pmr::vector<Mode> modes;
        
        // Mock mode 1: Normal operation
        Mode normal_mode;
        normal_mode.id = "normal";
        normal_mode.name = "Normal Operation";
        normal_mode.translation_id = "mode.normal";
        normal_mode.values = {"active", "inactive"};
        modes.push_back(normal_mode);
        
        // Mock mode 2: Diagnostic mode
        Mode diag_mode;
        diag_mode.id = "diagnostic";
        diag_mode.name = "Diagnostic Mode";
        diag_mode.translation_id = "mode.diagnostic";
        diag_mode.values = {"enabled", "disabled"};
        modes.push_back(diag_mode);
        
        return Result<std::pmr::vector<Mode>>(modes);
    }

    /// @brief Apply a diagnostic mode
    /// @param mode_id Mode identifier
    /// @param mode_value Mode value to apply
    /// @param expiration_timeout Optional timeout
    /// @return Result indicating success or error
    Result<void> ApplyMode(
        const std::pmr::string& mode_id,
        const std::pmr::string& mode_value,
        [[maybe_unused]] std::optional<std::chrono::seconds> expiration_timeout) override {
        
        // Validate mode exists
        if (mode_id != "normal" && mode_id != "diagnostic") {
            Error err;
            err.sovd_error = "invalid_mode";
            err.vendor_error = "MODE_001";
            err.vendor_message = "Unknown mode: " + std::string(mode_id);
            return Result<void>(err);
        }
        
        // Mock: store current mode
        current_mode_id_ = mode_id;
        current_mode_value_ = mode_value;
        
        return Result<void>();
    }

    /// @brief Get current mode (for testing)
    const std::pmr::string& GetCurrentModeId() const { return current_mode_id_; }
    const std::pmr::string& GetCurrentModeValue() const { return current_mode_value_; }
    bool IsLocked() const { return is_locked_; }

private:
    std::pmr::string entity_id_;
    bool is_locked_;
    std::pmr::string current_mode_id_;
    std::pmr::string current_mode_value_;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DIAGNOSTIC_ENTITY_MOCK_H
