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

#ifndef SCORE_MW_DIAG_H
#define SCORE_MW_DIAG_H

/// @file diag.h
/// @brief Main diagnostic API header
/// @details Include this header to access the complete diagnostic API for both UDS and SOVD

#include "diag/types.h"
#include "diag/sovd.h"
#include "diag/uds.h"

/// @namespace mw::diag
/// @brief Root namespace for diagnostic middleware
///
/// This namespace contains the abstraction layer API for diagnostic services,
/// supporting both UDS (Unified Diagnostic Services) and SOVD (Service-Oriented
/// Vehicle Diagnostics) protocols.
///
/// @namespace mw::diag::uds
/// @brief UDS-specific diagnostic services
///
/// Contains interfaces and utilities for implementing UDS diagnostic services
/// according to ISO 14229-1, including:
/// - Read/Write Data by Identifier (0x22/0x2E)
/// - Routine Control (0x31)
/// - Generic UDS service handling
/// - Serialization helpers
///
/// @namespace mw::diag::sovd
/// @brief SOVD-specific diagnostic services
///
/// Contains interfaces for implementing SOVD diagnostic services, including:
/// - Data resources (read-only, writable, and read-write)
/// - Operations (with various invocation policies)
/// - Diagnostic entities and modes
/// - JSON-based request/response handling

#endif // SCORE_MW_DIAG_H
