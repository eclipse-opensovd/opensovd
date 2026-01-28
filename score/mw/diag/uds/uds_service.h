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

#ifndef SCORE_MW_DIAG_UDS_UDS_SERVICE_H
#define SCORE_MW_DIAG_UDS_UDS_SERVICE_H

#include "score/mw/diag/types.h"

namespace mw::diag::uds {

/// @brief Interface for a generic UDS Service
/// @details Allows implementation of custom UDS services not covered by specific interfaces
class UDSService {
public:
    virtual ~UDSService() = default;

    /// @brief Handle a UDS message
    /// @param message The incoming UDS message bytes
    /// @return Result containing response bytes or error
    virtual mw::diag::Result<mw::diag::ByteVector> HandleMessage(mw::diag::ByteSequence message) = 0;

protected:
    UDSService() = default;
    UDSService(const UDSService&) = delete;
    UDSService& operator=(const UDSService&) = delete;
    UDSService(UDSService&&) = default;
    UDSService& operator=(UDSService&&) = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_UDS_SERVICE_H
