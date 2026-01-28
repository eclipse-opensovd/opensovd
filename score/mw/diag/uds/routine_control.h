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

#ifndef SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_H
#define SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_H

#include "score/mw/diag/types.h"

namespace mw::diag::uds {

/// @brief Interface for UDS Service 'Routine Control' (0x31)
class RoutineControl {
public:
    virtual ~RoutineControl() = default;

    /// @brief Start the routine (sub-function 0x01)
    /// @param data Input parameters for the routine
    /// @return Result containing response data or error
    virtual mw::diag::Result<mw::diag::ByteVector> Start(mw::diag::ByteSequence data) = 0;

    /// @brief Stop the routine (sub-function 0x02)
    /// @param data Input parameters for stopping
    /// @return Result containing response data or error
    virtual mw::diag::Result<mw::diag::ByteVector> Stop(mw::diag::ByteSequence data) = 0;

    /// @brief Request routine results (sub-function 0x03)
    /// @param data Input parameters for requesting results
    /// @return Result containing routine results or error
    virtual mw::diag::Result<mw::diag::ByteVector> RequestResults(mw::diag::ByteSequence data) = 0;

protected:
    RoutineControl() = default;
    RoutineControl(const RoutineControl&) = delete;
    RoutineControl& operator=(const RoutineControl&) = delete;
    RoutineControl(RoutineControl&&) = default;
    RoutineControl& operator=(RoutineControl&&) = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_ROUTINE_CONTROL_H
