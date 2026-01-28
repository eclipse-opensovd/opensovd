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

#ifndef SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_MOCK_H
#define SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_MOCK_H

#include "routine_control.h"
#include <cstdint>

namespace mw::diag::uds {

/// @brief Mock implementation of RoutineControl for testing
/// @details Example implementation simulating a diagnostic routine
class RoutineControlMock : public RoutineControl {
public:
    /// @brief Construct mock with routine identifier
    /// @param rid Routine Identifier value
    explicit RoutineControlMock(uint16_t rid) 
        : routine_identifier_(rid),
          is_running_(false),
          execution_count_(0) {}

    /// @brief Start the routine
    /// @param data Optional routine parameters
    /// @return Result containing status information
    mw::diag::Result<mw::diag::ByteVector> Start([[maybe_unused]] mw::diag::ByteSequence data) override {
        if (is_running_) {
            // Return error: routine already running
            mw::diag::ByteVector response = {0x31}; // Negative response: Request out of range
            return mw::diag::Result<mw::diag::ByteVector>(response);
        }
        
        is_running_ = true;
        execution_count_++;
        
        // Positive response
        mw::diag::ByteVector response = {0x00}; // Success status
        return mw::diag::Result<mw::diag::ByteVector>(response);
    }

    /// @brief Stop the routine
    /// @param data Optional stop parameters
    /// @return Result containing status information
    mw::diag::Result<mw::diag::ByteVector> Stop([[maybe_unused]] mw::diag::ByteSequence data) override {
        if (!is_running_) {
            // Return error: routine not running
            mw::diag::ByteVector response = {0x24}; // Negative response: Request sequence error
            return mw::diag::Result<mw::diag::ByteVector>(response);
        }
        
        is_running_ = false;
        
        // Positive response with execution count
        mw::diag::ByteVector response = {
            0x00, // Success status
            static_cast<uint8_t>(execution_count_)
        };
        return mw::diag::Result<mw::diag::ByteVector>(response);
    }

    /// @brief Request routine results
    /// @param data Optional request parameters
    /// @return Result containing routine results
    mw::diag::Result<mw::diag::ByteVector> RequestResults([[maybe_unused]] mw::diag::ByteSequence data) override {
        mw::diag::ByteVector response = {
            static_cast<uint8_t>(is_running_ ? 0x01 : 0x00), // Running status
            static_cast<uint8_t>(execution_count_), // Execution count
            0x00, 0x00 // Mock result data
        };
        return mw::diag::Result<mw::diag::ByteVector>(response);
    }

private:
    uint16_t routine_identifier_;
    bool is_running_;
    uint32_t execution_count_;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_MOCK_H
