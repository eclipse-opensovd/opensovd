<!--
# *******************************************************************************
# Copyright (c) 2025 The Contributors to Eclipse OpenSOVD (see CONTRIBUTORS)
#
# See the NOTICE file(s) distributed with this work for additional
# information regarding copyright ownership.
#
# This program and the accompanying materials are made available under the
# terms of the Apache License Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-FileCopyrightText: 2025 The Eclipse OpenSOVD contributors
# SPDX-License-Identifier: Apache-2.0
# *******************************************************************************
-->

# OpenSOVD MVP Roadmap

This document defines the MVP scope for OpenSOVD to realize an end-to-end diagnostic stack by end of 2026.
The core idea is to provide a useable stack first and iterate on features later.

## Context

S-CORE aims to provide a first version of the entire stack by end of 2026.
To integrate OpenSOVD into S-CORE as its diagnostic solution we need to define the scope
and roadmap of a MVP scope of OpenSOVD that S-CORE can use for its v1.0.

## Use-cases

Following use-cases shall be supported by the MVP.

1. Read current and stored DTCs through the SOVD API, filtered by ECU/component.
2. Report new faults from platform and app components via the Fault API and see them appear in SOVD.
3. Clear DTCs (single or batch) over SOVD with proper authorization checks.
4. Retrieve ECU- and app-level metadata (HW revision, SW version) via SOVD.
5. Push configuration updates to a component through SOVD, backed by the S-CORE configuration service.
6. Reach an UDS ECU through the Classic Diagnostic Adapter, at least for read/clear DTC paths.

## Requirements

The following requirements enable the MVP use-cases.
The requirements are formulated loosly as part of this document and will need to be moved to an appropriate place later on.

1. Provide a minimal Diagnostic Fault Manager with persistent storage (DTC state, fault metadata, catalog version).
2. Supply the Fault Library to S-CORE components, including catalog ingestion, debounce, and reset policy handling.
3. Expose an SOVD server that supports authentication, DTC read/clear, and metadata endpoints backed by the DFM.
4. Integrate the S-CORE configuration system so SOVD requests can read/write named configuration sets.
5. Deliver a Classic Diagnostic Adapter that proxies core UDS services (read DTC, clear DTC, ECU metadata) into SOVD.
6. Ensure transport reliability: retryable Fault API submission path and clear semantics in the DFM.
7. Ship a reference tester flow (script) that exercises the end-to-end stack against a demo ECU layout.

## High-level timeline

### 25Q4

- Baseline architecture alignment with S-CORE (interfaces, IPC schema).

### 26Q1

- Fault Library MVP in place, including sample component and generated catalog tooling.
- Prototype DFM with in-memory store and SOVD stub endpoints for DTC read.
- Decision on persistence backend and security primitives (cert handling, auth flow).

### 26Q2

- Persistence layer implemented (DTC store, metadata store) and wired into the DFM.
- SOVD server delivers read/paginate DTCs, component metadata, and supports authenticated sessions.
- Fault API to DFM integration hardened (debounce/reset policies, catalog version checks).
- Initial Classic Diagnostic Adapter tested with SOVD Server.

### 26Q3

- Configuration round-trip: SOVD -> configuration service -> sample component.
- Clear DTC flow including reset policies, transactional updates, and auditing.
- End-to-end demo vehicle layout (mixed SOVD/UDS ECUs), also for component testing.

### 26Q4

- Security and robustness: certificate handling, rate limits, logging, observability.
- Documentation: integrator guide, tester instructions.
- Performance validation on S-CORE reference hardware and readiness for S-CORE v1.0 release.
