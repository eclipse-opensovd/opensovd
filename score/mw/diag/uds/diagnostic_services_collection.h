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

#ifndef SCORE_MW_DIAG_UDS_DIAGNOSTIC_SERVICES_COLLECTION_H
#define SCORE_MW_DIAG_UDS_DIAGNOSTIC_SERVICES_COLLECTION_H

#include "score/mw/diag/diagnostic_services_collection.h"
#include "score/mw/diag/types.h"
#include <memory>
#include <memory_resource>
#include <string_view>

namespace mw::diag::uds {

// Forward declarations
class DataIdentifier;
class ReadDataByIdentifier;
class WriteDataByIdentifier;
class RoutineControl;
class UDSService;

/// @brief Collection of UDS diagnostic services
/// @details Manages the lifetime of registered UDS services
class UdsDiagnosticServicesCollection : public mw::diag::DiagnosticServicesCollection {
public:
    /// @brief Construct a UDS diagnostic services collection
    /// @param memory_resource The memory resource for allocations
    explicit UdsDiagnosticServicesCollection(std::pmr::memory_resource& memory_resource);

    /// @brief Destructor - releases all registered UDS services
    ~UdsDiagnosticServicesCollection() override;

    UdsDiagnosticServicesCollection(const UdsDiagnosticServicesCollection&) = delete;
    UdsDiagnosticServicesCollection& operator=(const UdsDiagnosticServicesCollection&) = delete;
    UdsDiagnosticServicesCollection(UdsDiagnosticServicesCollection&&) = default;
    UdsDiagnosticServicesCollection& operator=(UdsDiagnosticServicesCollection&&) = default;

private:
    std::pmr::memory_resource& memory_resource_;
};

/// @brief Builder for creating UDS diagnostic services collections
/// @details Provides a fluent API for registering various UDS services
class UdsDiagnosticServicesCollectionBuilder {
public:
    using Identifier = std::string_view;

    /// @brief Construct a builder
    /// @param memory_resource The memory resource for allocations
    explicit UdsDiagnosticServicesCollectionBuilder(std::pmr::memory_resource& memory_resource);

    /// @brief Register a data identifier (read and write)
    /// @tparam DataIdentifierType The concrete type implementing DataIdentifier
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier (typically the DID value)
    /// @param args Constructor arguments for the service instance
    /// @return Reference to this builder for chaining
    template <typename DataIdentifierType, typename... Args>
    UdsDiagnosticServicesCollectionBuilder& With(Identifier identifier, Args&&... args);

    /// @brief Register a read-only data identifier
    /// @tparam ReadDataByIdentifierType The concrete type implementing ReadDataByIdentifier
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier (typically the DID value)
    /// @param args Constructor arguments for the service instance
    /// @return Reference to this builder for chaining
    template <typename ReadDataByIdentifierType, typename... Args>
    UdsDiagnosticServicesCollectionBuilder& With(Identifier identifier, Args&&... args);

    /// @brief Register a write-only data identifier
    /// @tparam WriteDataByIdentifierType The concrete type implementing WriteDataByIdentifier
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier (typically the DID value)
    /// @param args Constructor arguments for the service instance
    /// @return Reference to this builder for chaining
    template <typename WriteDataByIdentifierType, typename... Args>
    UdsDiagnosticServicesCollectionBuilder& With(Identifier identifier, Args&&... args);

    /// @brief Register a routine control service
    /// @tparam RoutineControlType The concrete type implementing RoutineControl
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier (typically the routine ID)
    /// @param args Constructor arguments for the service instance
    /// @return Reference to this builder for chaining
    template <typename RoutineControlType, typename... Args>
    UdsDiagnosticServicesCollectionBuilder& With(Identifier identifier, Args&&... args);

    /// @brief Register a generic UDS service
    /// @tparam UDSServiceType The concrete type implementing UDSService
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier (typically the service ID)
    /// @param args Constructor arguments for the service instance
    /// @return Reference to this builder for chaining
    template <typename UDSServiceType, typename... Args>
    UdsDiagnosticServicesCollectionBuilder& With(Identifier identifier, Args&&... args);

    /// @brief Build the diagnostic services collection
    /// @return Result containing unique pointer to the collection or error
    mw::diag::Result<std::unique_ptr<UdsDiagnosticServicesCollection>> Build();

private:
    std::pmr::memory_resource& memory_resource_;
    // Internal storage for registered services (implementation details)
};

} // namespace mw::diag::uds

#endif // SCORE_MW_DIAG_UDS_DIAGNOSTIC_SERVICES_COLLECTION_H
