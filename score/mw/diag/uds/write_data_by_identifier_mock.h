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

#ifndef SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_MOCK_H
#define SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_MOCK_H

#include "write_data_by_identifier.h"
#include <cstdint>
#include <vector>

namespace mw::diag::uds {

/// @brief Mock implementation of WriteDataByIdentifier for testing
/// @details Example implementation that validates and stores data
class WriteDataByIdentifierMock : public WriteDataByIdentifier {
public:
    /// @brief Construct mock with data identifier
    /// @param did Data Identifier value
    explicit WriteDataByIdentifierMock(uint16_t did) : data_identifier_(did) {}

    /// @brief Write mock data
    /// @param data Data to write
    /// @return Result indicating success or error
    mw::diag::Result<void> Write(mw::diag::ByteSequence data) override {
        // Mock implementation - validate data length
        if (data.empty()) {
            return mw::diag::Result<void>(mw::diag::ErrorCode::kInternalError);
        }
        
        // Store the data for verification in tests
        last_written_data_.assign(data.begin(), data.end());
        
        return mw::diag::Result<void>();
    }

    /// @brief Get the last written data (for testing)
    const std::vector<uint8_t>& GetLastWrittenData() const {
        return last_written_data_;
    }

private:
    uint16_t data_identifier_;
    std::vector<uint8_t> last_written_data_;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_MOCK_H
