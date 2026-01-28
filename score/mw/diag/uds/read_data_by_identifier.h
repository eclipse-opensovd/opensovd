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

#ifndef SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_H
#define SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_H

#include "score/mw/diag/types.h"

namespace mw::diag::uds {

/// @brief Interface for UDS Service 'Read Data by Identifier' (0x22)
class ReadDataByIdentifier {
public:
    virtual ~ReadDataByIdentifier() = default;

    /// @brief Read data from the data identifier
    /// @return Result containing the data bytes or error
    virtual mw::diag::Result<mw::diag::ByteVector> Read() = 0;

protected:
    ReadDataByIdentifier() = default;
    ReadDataByIdentifier(const ReadDataByIdentifier&) = delete;
    ReadDataByIdentifier& operator=(const ReadDataByIdentifier&) = delete;
    ReadDataByIdentifier(ReadDataByIdentifier&&) = default;
    ReadDataByIdentifier& operator=(ReadDataByIdentifier&&) = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_READ_DATA_BY_IDENTIFIER_H
