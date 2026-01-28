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

#ifndef SCORE_MW_DIAG_UDS_UDS_SERVICE_MOCK_H
#define SCORE_MW_DIAG_UDS_UDS_SERVICE_MOCK_H

#include "uds_service.h"

namespace mw::diag::uds {

/// @brief Mock implementation of generic UDSService for testing
/// @details Example implementation that echoes received messages
class UDSServiceMock : public UDSService {
public:
    /// @brief Construct mock with service identifier
    /// @param sid Service Identifier (e.g., 0x22 for ReadDataByIdentifier)
    explicit UDSServiceMock(uint8_t sid) 
        : service_id_(sid),
          call_count_(0) {}

    /// @brief Handle UDS message
    /// @param message Raw UDS message bytes
    /// @return Result containing response message
    mw::diag::Result<mw::diag::ByteVector> HandleMessage(mw::diag::ByteSequence message) override {
        call_count_++;
        
        if (message.empty()) {
            // Return negative response: Incorrect message length
            mw::diag::ByteVector response = {
                0x7F, // Negative response
                service_id_,
                0x13 // Incorrect message length or invalid format
            };
            return mw::diag::Result<mw::diag::ByteVector>(response);
        }
        
        // Echo back with positive response SID (original SID + 0x40)
        mw::diag::ByteVector response;
        response.push_back(service_id_ + 0x40); // Positive response
        response.insert(response.end(), message.begin(), message.end());
        
        return mw::diag::Result<mw::diag::ByteVector>(response);
    }

    /// @brief Get number of times service was called (for testing)
    uint32_t GetCallCount() const { return call_count_; }

private:
    uint8_t service_id_;
    uint32_t call_count_;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_UDS_SERVICE_MOCK_H
