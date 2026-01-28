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

#ifndef SCORE_MW_DIAG_UDS_SERIALIZATION_HELPER_H
#define SCORE_MW_DIAG_UDS_SERIALIZATION_HELPER_H

#include "score/mw/diag/types.h"
#include "score/mw/diag/uds/types.h"

namespace mw::diag::uds::details {

/// @brief Utility class for serializing and deserializing UDS messages
class SerializationHelper {
public:
    /// @brief Serialize a response payload into bytes
    /// @tparam ResponsePayload The type of the response payload
    /// @param payload The response payload to serialize
    /// @return Result containing serialized bytes or error
    template <typename ResponsePayload>
    static mw::diag::Result<mw::diag::ByteVector> SerializeResponse(const ResponsePayload& payload);

    /// @brief Deserialize request bytes and invoke callable with the deserialized payload
    /// @tparam RequestPayload The type of the request payload
    /// @tparam Callable The type of the callable to invoke
    /// @param bytes The request bytes to deserialize
    /// @param callable The callable to invoke with deserialized payload
    /// @return Result indicating success or error
    template <typename RequestPayload, typename Callable>
    static mw::diag::Result<void> DeserializeRequest(
        const mw::diag::ByteVector& bytes,
        Callable& callable);
};

} // namespace mw::diag::uds::details

#endif // SCORE_MW_DIAG_UDS_SERIALIZATION_HELPER_H
