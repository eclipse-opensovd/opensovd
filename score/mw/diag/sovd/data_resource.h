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

#ifndef SCORE_MW_DIAG_SOVD_DATA_RESOURCE_H
#define SCORE_MW_DIAG_SOVD_DATA_RESOURCE_H

#include "diagnostic_reply.h"
#include "diagnostic_request.h"
#include "types.h"

namespace mw::diag::sovd {

/// @brief Interface for read-only SOVD data resources
class ReadOnlyDataResource {
public:
    virtual ~ReadOnlyDataResource() = default;

    /// @brief Get the current value of the data resource
    /// @return Result containing JSON data reply or error
    virtual Result<JsonDataReply> Get() = 0;

protected:
    ReadOnlyDataResource() = default;
    ReadOnlyDataResource(const ReadOnlyDataResource&) = delete;
    ReadOnlyDataResource& operator=(const ReadOnlyDataResource&) = delete;
    ReadOnlyDataResource(ReadOnlyDataResource&&) = default;
    ReadOnlyDataResource& operator=(ReadOnlyDataResource&&) = default;
};

/// @brief Interface for writable SOVD data resources
class WritableDataResource {
public:
    virtual ~WritableDataResource() = default;

    /// @brief Update the value of the data resource
    /// @param request The diagnostic request containing the new value
    /// @return Result indicating success or error
    virtual Result<void> Put(const DiagnosticRequest& request) = 0;

protected:
    WritableDataResource() = default;
    WritableDataResource(const WritableDataResource&) = delete;
    WritableDataResource& operator=(const WritableDataResource&) = delete;
    WritableDataResource(WritableDataResource&&) = default;
    WritableDataResource& operator=(WritableDataResource&&) = default;
};

/// @brief Interface for SOVD data resources supporting both read and write
class DataResource : public ReadOnlyDataResource, public WritableDataResource {
public:
    ~DataResource() override = default;

protected:
    DataResource() = default;
    DataResource(const DataResource&) = delete;
    DataResource& operator=(const DataResource&) = delete;
    DataResource(DataResource&&) = default;
    DataResource& operator=(DataResource&&) = default;
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DATA_RESOURCE_H
