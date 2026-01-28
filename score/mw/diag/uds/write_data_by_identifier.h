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

#ifndef SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_H
#define SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_H

#include "score/mw/diag/types.h"

namespace mw::diag::uds {

/// @brief Interface for UDS Service 'Write Data by Identifier' (0x2E)
class WriteDataByIdentifier {
public:
    virtual ~WriteDataByIdentifier() = default;

    /// @brief Write data to the data identifier
    /// @param data The byte sequence to write
    /// @return Result indicating success or error
    virtual mw::diag::Result<void> Write(mw::diag::ByteSequence data) = 0;

protected:
    WriteDataByIdentifier() = default;
    WriteDataByIdentifier(const WriteDataByIdentifier&) = delete;
    WriteDataByIdentifier& operator=(const WriteDataByIdentifier&) = delete;
    WriteDataByIdentifier(WriteDataByIdentifier&&) = default;
    WriteDataByIdentifier& operator=(WriteDataByIdentifier&&) = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_WRITE_DATA_BY_IDENTIFIER_H
