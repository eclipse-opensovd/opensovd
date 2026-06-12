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

#ifndef SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_MOCK_H
#define SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_MOCK_H

#include "read_data_by_identifier.h"
#include <cstdint>

namespace mw::diag::uds {

/// @brief Mock implementation of ReadDataByIdentifier for testing
/// @details Example implementation that returns predefined data
class ReadDataByIdentifierMock : public ReadDataByIdentifier {
public:
    /// @brief Construct mock with data identifier
    /// @param did Data Identifier value (e.g., 0xF190 for VIN)
    explicit ReadDataByIdentifierMock(uint16_t did) : data_identifier_(did) {}

    /// @brief Read mock data
    /// @return Result containing mock byte vector
    mw::diag::Result<mw::diag::ByteVector> Read() override {
        // Mock implementation - return sample data based on DID
        mw::diag::ByteVector data;
        
        switch (data_identifier_) {
            case 0xF190: // VIN
                data = {0x57, 0x42, 0x41, 0x31, 0x32, 0x33, 0x34, 0x35, 
                        0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34};
                break;
            case 0xF186: // Active Diagnostic Session
                data = {0x01}; // Default session
                break;
            default:
                data = {0x00, 0x00}; // Generic response
                break;
        }
        
        return mw::diag::Result<mw::diag::ByteVector>(std::move(data));
    }

private:
    uint16_t data_identifier_;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_MOCK_H
