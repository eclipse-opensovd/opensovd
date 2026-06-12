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

#ifndef SCORE_MW_DIAG_TYPES_H
#define SCORE_MW_DIAG_TYPES_H

#include "third_party/score/result.h"
#include <cstdint>
#include <memory_resource>
#include <span>
#include <vector>

namespace mw::diag {

/// @brief Error codes for diagnostic operations
enum class ErrorCode {
    kUnknown,
    kInternalError
};

/// @brief Byte type for diagnostic data
using ByteType = std::uint8_t;

/// @brief Immutable view of a byte sequence
using ByteSequence = std::span<const ByteType>;

/// @brief Mutable byte vector using polymorphic memory resource
using ByteVector = std::pmr::vector<ByteType>;

/// @brief Result type alias for diagnostic operations
/// @tparam T The type of the value on success
/// @details Uses score::Result with ErrorCode as the error type
template <typename T>
using Result = score::Result<T, ErrorCode>;

} // namespace mw::diag

#endif // SCORE_MW_DIAG_TYPES_H
