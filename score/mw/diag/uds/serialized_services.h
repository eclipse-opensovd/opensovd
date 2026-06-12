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

#ifndef SCORE_MW_DIAG_UDS_SERIALIZED_SERVICES_H
#define SCORE_MW_DIAG_UDS_SERIALIZED_SERVICES_H

#include "data_identifier.h"
#include "read_data_by_identifier.h"
#include "routine_control.h"
#include "serialization_helper.h"
#include "write_data_by_identifier.h"

namespace mw::diag::uds {

/// @brief CRTP base class for automatic serialization of ReadDataByIdentifier
/// @tparam T The derived class type
/// @details Uses CRTP pattern to provide automatic serialization/deserialization
template <typename T>
class SerializedReadDataByIdentifier : public ReadDataByIdentifier {
public:
    /// @brief Read data with automatic serialization
    /// @return Result containing serialized bytes or error
    mw::diag::Result<mw::diag::ByteVector> Read() override;

protected:
    ~SerializedReadDataByIdentifier() override = default;
};

/// @brief CRTP base class for automatic serialization of WriteDataByIdentifier
/// @tparam T The derived class type
/// @details Uses CRTP pattern to provide automatic serialization/deserialization
template <typename T>
class SerializedWriteDataByIdentifier : public WriteDataByIdentifier {
public:
    /// @brief Write data with automatic deserialization
    /// @param data The byte sequence to deserialize and write
    /// @return Result indicating success or error
    mw::diag::Result<void> Write(mw::diag::ByteSequence data) override;

protected:
    ~SerializedWriteDataByIdentifier() override = default;
};

/// @brief CRTP base class for automatic serialization of DataIdentifier
/// @tparam T The derived class type
/// @details Combines read and write with automatic serialization/deserialization
template <typename T>
class SerializedDataByIdentifier : public DataIdentifier {
public:
    /// @brief Read data with automatic serialization
    /// @return Result containing serialized bytes or error
    mw::diag::Result<mw::diag::ByteVector> Read() override;

    /// @brief Write data with automatic deserialization
    /// @param data The byte sequence to deserialize and write
    /// @return Result indicating success or error
    mw::diag::Result<void> Write(mw::diag::ByteSequence data) override;

protected:
    ~SerializedDataByIdentifier() override = default;
};

/// @brief CRTP base class for automatic serialization of RoutineControl
/// @tparam T The derived class type
/// @details Uses CRTP pattern to provide automatic serialization/deserialization
template <typename T>
class SerializedRoutineControl : public RoutineControl {
public:
    /// @brief Start routine with automatic serialization
    /// @param data Input parameters
    /// @return Result containing serialized response or error
    mw::diag::Result<mw::diag::ByteVector> Start(mw::diag::ByteSequence data) override;

    /// @brief Stop routine with automatic serialization
    /// @param data Input parameters
    /// @return Result containing serialized response or error
    mw::diag::Result<mw::diag::ByteVector> Stop(mw::diag::ByteSequence data) override;

    /// @brief Request results with automatic serialization
    /// @param data Input parameters
    /// @return Result containing serialized response or error
    mw::diag::Result<mw::diag::ByteVector> RequestResults(mw::diag::ByteSequence data) override;

protected:
    ~SerializedRoutineControl() override = default;
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_SERIALIZED_SERVICES_H
