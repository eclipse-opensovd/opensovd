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

#ifndef SCORE_MW_DIAG_SOVD_DIAGNOSTIC_SERVICES_COLLECTION_H
#define SCORE_MW_DIAG_SOVD_DIAGNOSTIC_SERVICES_COLLECTION_H

#include "score/mw/diag/diagnostic_services_collection.h"
#include "score/mw/diag/types.h"
#include "score/mw/diag/sovd/diagnostic_entity.h"
#include "score/mw/diag/sovd/types.h"
#include <memory>
#include <memory_resource>
#include <string_view>

namespace mw::diag::sovd {

// Forward declarations
class ReadOnlyDataResource;
class WritableDataResource;
class DataResource;
class Operation;

/// @brief Collection of SOVD diagnostic services
/// @details Upon destruction, releases all functionality and registered services
///          of the referenced DiagnosticEntity from the underlying binding implementation
class SovdDiagnosticServicesCollection : public mw::diag::DiagnosticServicesCollection {
public:
    /// @brief Construct a diagnostic services collection
    /// @param entity The diagnostic entity to associate with this collection
    /// @param memory_resource The memory resource for allocations
    explicit SovdDiagnosticServicesCollection(
        DiagnosticEntity& entity,
        std::pmr::memory_resource& memory_resource);

    /// @brief Destructor - releases all services from the diagnostic entity
    ~SovdDiagnosticServicesCollection() override;

    SovdDiagnosticServicesCollection(const SovdDiagnosticServicesCollection&) = delete;
    SovdDiagnosticServicesCollection& operator=(const SovdDiagnosticServicesCollection&) = delete;
    SovdDiagnosticServicesCollection(SovdDiagnosticServicesCollection&&) = default;
    SovdDiagnosticServicesCollection& operator=(SovdDiagnosticServicesCollection&&) = default;

private:
    DiagnosticEntity& entity_;
    std::pmr::memory_resource& memory_resource_;
};

/// @brief Builder for creating SOVD diagnostic services collections
/// @details Provides a fluent API for registering various diagnostic services
class SovdDiagnosticServicesCollectionBuilder {
public:
    using Identifier = std::string_view;

    /// @brief Construct a builder for a diagnostic entity
    /// @param entity The diagnostic entity to build services for
    /// @param memory_resource The memory resource for allocations
    explicit SovdDiagnosticServicesCollectionBuilder(
        DiagnosticEntity& entity,
        std::pmr::memory_resource& memory_resource);

    /// @brief Register a read-only data resource
    /// @tparam ReadOnlyDataResourceType The concrete type implementing ReadOnlyDataResource
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier for the resource
    /// @param schema JSON schema view for the resource
    /// @param category_id Data category identifier
    /// @param group_id Optional data group identifier
    /// @param args Constructor arguments for the resource instance
    /// @return Reference to this builder for chaining
    template <typename ReadOnlyDataResourceType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        Identifier identifier,
        const JsonSchemaView& schema,
        const DataCategoryIdentifier& category_id,
        std::optional<DataGroupIdentifier> group_id,
        Args&&... args);

    /// @brief Register a writable data resource
    /// @tparam WritableDataResourceType The concrete type implementing WritableDataResource
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier for the resource
    /// @param category_id Data category identifier
    /// @param group_id Optional data group identifier
    /// @param args Constructor arguments for the resource instance
    /// @return Reference to this builder for chaining
    template <typename WritableDataResourceType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        Identifier identifier,
        const DataCategoryIdentifier& category_id,
        std::optional<DataGroupIdentifier> group_id,
        Args&&... args);

    /// @brief Register a data resource (read and write)
    /// @tparam DataResourceType The concrete type implementing DataResource
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier for the resource
    /// @param schema JSON schema view for the resource
    /// @param category_id Data category identifier
    /// @param group_id Optional data group identifier
    /// @param args Constructor arguments for the resource instance
    /// @return Reference to this builder for chaining
    template <typename DataResourceType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        Identifier identifier,
        const JsonSchemaView& schema,
        const DataCategoryIdentifier& category_id,
        std::optional<DataGroupIdentifier> group_id,
        Args&&... args);

    /// @brief Register a data category
    /// @tparam DataCategoryType The concrete type for the data category
    /// @tparam Args Constructor argument types
    /// @param category_id Data category identifier
    /// @param translation_id Optional translation identifier
    /// @param args Constructor arguments for the category instance
    /// @return Reference to this builder for chaining
    template <typename DataCategoryType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        const DataCategoryIdentifier& category_id,
        std::optional<TranslationIdentifier> translation_id,
        Args&&... args);

    /// @brief Register a data group
    /// @tparam DataGroupType The concrete type for the data group
    /// @tparam Args Constructor argument types
    /// @param group_id Data group identifier
    /// @param short_desc Short description of the data group
    /// @param translation_id Optional translation identifier
    /// @param category_id Parent data category identifier
    /// @param args Constructor arguments for the group instance
    /// @return Reference to this builder for chaining
    template <typename DataGroupType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        const DataGroupIdentifier& group_id,
        const DataGroupShortDesc& short_desc,
        std::optional<TranslationIdentifier> translation_id,
        const DataCategoryIdentifier& category_id,
        Args&&... args);

    /// @brief Register an operation
    /// @tparam OperationType The concrete type implementing Operation
    /// @tparam Args Constructor argument types
    /// @param identifier Unique identifier for the operation
    /// @param invocation_policy The invocation policy for the operation
    /// @param translation_id Optional translation identifier
    /// @param args Constructor arguments for the operation instance
    /// @return Reference to this builder for chaining
    template <typename OperationType, typename... Args>
    SovdDiagnosticServicesCollectionBuilder& With(
        Identifier identifier,
        OperationInvocationPolicy invocation_policy,
        std::optional<TranslationIdentifier> translation_id,
        Args&&... args);

    /// @brief Build the diagnostic services collection
    /// @return Result containing unique pointer to the collection or error
    mw::diag::Result<std::unique_ptr<SovdDiagnosticServicesCollection>> Build();

private:
    DiagnosticEntity& entity_;
    std::pmr::memory_resource& memory_resource_;
    // Internal storage for registered services (implementation details)
};

} // namespace mw::diag::sovd

#endif // SCORE_MW_DIAG_SOVD_DIAGNOSTIC_SERVICES_COLLECTION_H
