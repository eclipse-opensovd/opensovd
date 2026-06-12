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

#ifndef SCORE_MW_DIAG_DIAGNOSTIC_SERVICES_COLLECTION_H
#define SCORE_MW_DIAG_DIAGNOSTIC_SERVICES_COLLECTION_H

namespace mw::diag {

/// @brief Abstract base class for diagnostic services collections
/// @details Provides lifetime control for contained services
class DiagnosticServicesCollection {
public:
    virtual ~DiagnosticServicesCollection() = default;

protected:
    DiagnosticServicesCollection() = default;
    DiagnosticServicesCollection(const DiagnosticServicesCollection&) = delete;
    DiagnosticServicesCollection& operator=(const DiagnosticServicesCollection&) = delete;
    DiagnosticServicesCollection(DiagnosticServicesCollection&&) = default;
    DiagnosticServicesCollection& operator=(DiagnosticServicesCollection&&) = default;
};

} // namespace mw::diag

#endif // SCORE_MW_DIAG_DIAGNOSTIC_SERVICES_COLLECTION_H
