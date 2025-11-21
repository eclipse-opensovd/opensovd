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
The core idea is to provide an end-to-end useable stack with reduced feature-set first and increase feature scope later.

## Context

S-CORE aims to provide a first version of the entire stack by end of 2026.
To integrate OpenSOVD into S-CORE as its diagnostic solution we need to define the scope
and roadmap of a MVP scope of OpenSOVD that S-CORE can use for its v1.0.

## Use-cases

Following use-cases shall be supported by the MVP.

1. Read DTCs through the SOVD API.
1. Report new faults from platform and app components via the Fault API and handle them in the DFM.
1. Clear DTCs over SOVD.
1. Reach an UDS ECU through the Classic Diagnostic Adapter, at least for read/clear DTC paths.
1. A sample Diagnostic service can be triggered via SOVD (Diagnostic service = a function which can be triggered via SOVD).
1. OPTIONAL: Retrieve ECU- and app-level metadata (HW revision, SW version) via SOVD.
1. OPTIONAL: Read/write component configuration through SOVD, backed by the S-CORE configuration service.

## Requirements

The following requirements enable the MVP use-cases.
The requirements are formulated loosly as part of this document and will need to be moved to an appropriate place later on.

1. Provide a minimal Diagnostic Fault Manager with persistent storage (DTC state, catalog version).
1. Supply the Fault Library to S-CORE components, including catalog ingestion.
1. Expose an SOVD server that supports DTC read/clear, trigger service and connection to Classic Diagnostic Adapter.
1. Deliver a Classic Diagnostic Adapter that proxies core UDS services (read DTC, clear DTC) into SOVD.
1. Ship a reference tester flow (script) that exercises the end-to-end stack against a demo ECU layout.
1. Create a concept of how security and IAM can be implemented by the integrator. (Secure Diagnostics on SOVD with Secure Diagnostic communication / authentication / roles + right management)
1. OPTIONAL: Integrate the S-CORE configuration system so SOVD requests can read/write named configuration sets.

## High level scope

OpenSOVD Scope v1:

- blue boxes: partially in scope (not full feature set as described above)
- red lines: connections in scope

![High Level Design](_assets/OpenSOVD-design-highlevel-scope-v1.drawio.svg)

## High-level timeline

### 25Q4

- Baseline architecture alignment with S-CORE (interfaces, IPC schema, persistency, roadmap, scope).
- Base concept for SOVD Server aligned.

### 26Q1

- Fault Library MVP in place, including sample component and catalog handling.
- Prototype DFM with in-memory store and SOVD stub endpoints for DTC read.
- Decision on persistence backend and security concept to enable integration specific security extension.

### 26Q2

- Persistence layer implemented (DTC store) and wired into the DFM.
- SOVD server delivers read/paginate DTCs.
- Fault Lib to DFM integration hardened (catalog version checks).
- Classic Diagnostic Adapter connected to SOVD Server (via Gateway).

### 26Q3

- Clear DTC flow.
- End-to-end demo vehicle layout (mixed SOVD/UDS ECUs), also for component testing. Using docker network as a development environment.

### 26Q4

- Robustness: rate limits, logging, observability.
- Documentation: integrator guide, tester instructions.
- Performance validation on S-CORE reference hardware and readiness for S-CORE v1.0 release.
