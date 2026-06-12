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

#ifndef SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_H
#define SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_H

#include "read_data_by_identifier.h"
#include "write_data_by_identifier.h"

namespace mw::diag::uds {

/// @brief Interface for UDS Data Identifier combining read and write capabilities
/// @details Multiple inheritance interface for data identifiers that support
///          both read (0x22) and write (0x2E) operations
class DataIdentifier : public ReadDataByIdentifier, public WriteDataByIdentifier {
public:
    ~DataIdentifier() override = default;

protected:
    DataIdentifier() = default;
    DataIdentifier(const DataIdentifier&) = delete;
    DataIdentifier& operator=(const DataIdentifier&) = delete;
    DataIdentifier(DataIdentifier&&) = default;
    DataIdentifier& operator=(DataIdentifier&&) = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_DATA_IDENTIFIER_H
