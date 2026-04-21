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

#ifndef SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_MOCK_H
#define SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_MOCK_H

#include "data_identifier.h"
#include <cstdint>
#include <vector>

namespace mw::diag::uds {

/// @brief Mock implementation of DataIdentifier (read + write) for testing
/// @details Example implementation supporting both read and write operations
class DataIdentifierMock : public DataIdentifier {
public:
    /// @brief Construct mock with data identifier
    /// @param did Data Identifier value
    explicit DataIdentifierMock(uint16_t did) 
        : data_identifier_(did), 
          stored_data_({0x00, 0x00}) {} // Default data

    /// @brief Read current data
    /// @return Result containing stored byte vector
    mw::diag::Result<mw::diag::ByteVector> Read() override {
        mw::diag::ByteVector data(stored_data_.begin(), stored_data_.end());
        return mw::diag::Result<mw::diag::ByteVector>(std::move(data));
    }

    /// @brief Write new data
    /// @param data Data to write
    /// @return Result indicating success or error
    mw::diag::Result<void> Write(mw::diag::ByteSequence data) override {
        if (data.empty()) {
            return mw::diag::Result<void>(mw::diag::ErrorCode::kInternalError);
        }
        
        // Update stored data
        stored_data_.assign(data.begin(), data.end());
        
        return mw::diag::Result<void>();
    }

private:
    uint16_t data_identifier_;
    std::vector<uint8_t> stored_data_;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_MOCK_H
