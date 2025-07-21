<!--
   # *******************************************************************************
   # Copyright (c) 2025 Contributors to Eclipse OpenSOVD
   #
   # See the NOTICE file(s) distributed with this work for additional
   # information regarding copyright ownership.
   #
   # This program and the accompanying materials are made available under the
   # terms of the Apache License Version 2.0 which is available at
   # https://www.apache.org/licenses/LICENSE-2.0
   #
   # SPDX-License-Identifier: Apache-2.0
   # *******************************************************************************
-->

# OpenSOVD Design

This is the initial design document for the OpenSOVD project and shall act as a starting point.
It is a derivative of the [S-CORE Diagnostic and Fault Management Feature Request](https://eclipse-score.github.io/score/main/features/diagnostics/index.html).
The intent of this document is to define a high-level architecture - the components listed throughout this document require a detailed design in the future.

## Architecture

The proposed concept consists of three main parts:

1. A framework agnostic library to aggregate faults and integrate the diagnostic system into a target platform software stack such as S-CORE
2. A SOVD based diagnostic system
3. Components to interface the diagnostic system with the outside – e.g. Tester or UDS based ECUs

The diagram below shows the concept with the three subgroups connected.
Solid borders mean the component is in scope of this project and dotted borders indicate components that are perephiral but developed outside of this project.

![High Level Design](_assets/OpenSOVD-design-highlevel.drawio.svg)

The next diagram shows the concept in a distributed view to highlight components that are unique per system or per device.

![High Level Design](_assets/OpenSOVD-design-highlevel-distributed.drawio.svg)

### In scope components

The following components are considered in scope of the OpenSOVD project.
Their functionality is briefly described below.

- Fault Library
  - Provides a framework agnostic interface for apps or FEO activities to report faults - called "Fault API" in the S-CORE architecture.
  - **The Fault lib is the interface between the S-CORE and the OpenSOVD project and should be developed in cooperation - see [ADR S-CORE Interface](./adr/001-adr-score-interface.md).**
  - Relays faults via IPC to central Diagnostic Fault Manager.
  - Enables domain-specific error logic (e.g. debouncing) by exposing a configuration interface
  - Reporting of faults additionally results in a log entry.
  - The interface needs to be specified further but will likely include:
    - Fault ID (FID)
    - time
    - ENUM fault type (like DLT ENUMs)
    - optional meta data
  - Fault lib is the base for activity specific, custom fault handling.
  - Can and should also be used by platform components to report faults.
  - Potentially source of faults to be acted upon - e.g. by S-CORE Health and Lifecycle Management.
  - Also needs to enforce regulatory requirements for certain faults - e.g. emission relevant.
  - Decentral component.

- Diagnostic Fault Manager
  - Aggregates and manages diagnostic fault data from Fault libs across the system.
  - Provides centralized fault status to the SOVD Server.
  - Not part of SOVD specification directly but a stack specific diagnostic implementation.
  - Interfaces with the Diagnostic DB (persistency) to store and retrieve data.
  - Stores (persistently) central configuration (e.g. for debouncing thresholds) which can be loaded during startup by Fault libs.
  - Implements the operation cycle concept (suppressing faults during phases where faults are to be expected).
  - Central component.

- Diagnostic DB
  - Potentially part of the Diagnostic Fault Manager process.
  - Stores static and runtime diagnostic data.
  - Is considered in scope due to the domain specific data format but internally uses S-CORE::Persistency.
  - The data format needs to be specified further but will likely include:
    - Diagnostic Trouble Code (DTC): OEM specific code, relevant for end-user.
    - Fault ID (FID): ECU specific ID to uniquely identify every fault.
    - Count: occurrence count of DTC/fault.
    - Meta data: meta data related to fault occurrence.
  - Central component.

- SOVD Server
  - Central entry point for all diagnostic requests via SOVD.
  - Implements the SOVD API and dispatches requests to services, DB, and fault manager.
  - Manages authentication, configuration, and data access via IPC.
  - SOVD communication via HTTP.
  - Central component.

- Service App
  - Is a base concept to extend the system with system-specific diagnostic services/routines (e.g. DTC clear, ECU reset, Flash Master).
  - Interfaces with the SOVD Server via IPC.
  - Base for all specific service app implementations.
  - Central component derived from base service app.

- SOVD Gateway
  - Forwards SOVD requests to appropriate backend targets (e.g. adapters, proxies, clients).
  - Acts as a router between clients and distributed SOVD components.
  - Supports multi-ECU SOVD communication.
  - Central component and unique per system.

- SOVD Client
  - Off-board, on-board or cloud client that initiates diagnostics via SOVD protocol.
  - Can be used by developers, testers, ECUs or cloud services; should be deployment agnostic.
  - Handles access control on the client side – e.g. by providing relevant certificates.
  - Central component - but could be deployed mutliple times (e.g. one on-baord and one off-baord).

- Classic Diagnostic Adapter
  - Translates SOVD service calls to UDS commands.
  - Enables backward compatibility with legacy ECUs that only support UDS.
  - Configured via ODX files describing ECU-specific UDS expectations.
  - UDS transport layer (e.g. DoIP or other vendor specific transports) shared with UDS2SOVD Proxy.
  - Central component and unique per system.

- UDS2SOVD Proxy
  - Allows for the mapping of any UDS service to SOVD functionality in an arbitrary way for backward-compatible testers.
  - Acts as a local translation layer between UDS clients and SOVD stack.
  - Configured via ODX files to define what is exposed.
  - Implements the UDS session handling concept.
  - UDS transport layer (e.g. DoIP or other vendor specific transports) shared with Classic Diagnostic Adapter.
  - Central component and unique per ECU/System (one per ECU or per System is possible).

### Out of scope components

The following components are out of scope of the project but are included for context.
Each one is briefly described to illustrate its role within the overall system architecture and
to highlight any resulting requirements or constraints imposed by the diagnostic system design.

- Logging
  - Enables the Fault Library to log fault events.
  - All SOVD components can interact with logging.

- Configuration Manager
  - Provides configuration data to the SOVD Server (e.g. ECU layout, variant, parameters).
  - Enables parametrization of applications.

- Authentication Manager
  - Manages authentication and authorization for incoming SOVD requests.
  - Ensures only valid users or clients can access services.

- Crypto
  - Provides cryptographic services – e.g. securely store and retrieve diagnostic certificates.
  - Used by Authentication Manager.

- Persistency
  - Provides persistent data storage.

- Flash Service App
  - Specialized extension of the Service App to handle ECU flashing.
  - Provides routines for software update/bootloader access via diagnostics.

- Rest of Vehicle UDS
  - Represents legacy ECUs in the vehicle that only speak UDS.
  - Interact via the Classic Diagnostic Adapter (SOVD2UDS).

- Rest of Vehicle SOVD
  - Other ECUs in the vehicle that already support SOVD natively.
  - Can communicate directly with the SOVD Gateway.

- UDS Tester
  - Traditional diagnostics tester that uses UDS protocol.
  - Communicates with the UDS2SOVD Proxy for limited diagnostics access.

## Security Impact

The introduction of a SOVD based diagnostic stack has significant security implications due to its capabilities and network-based communication model.
Diagnostics inherently allow access to system information, state manipulation, coding, and
software updates - all of which pose risks if accessed by unauthorized actors.
SOVD, based on REST, includes modern security features such as HTTPS and token-based authentication,
but also introduces a broader attack surface compared to traditional UDS, which relies on more isolated, session-based access.
If improperly secured, diagnostic interfaces could be exploited to trigger unauthorized routines or inject malicious software.
This may enable new threat scenarios and attack paths, particularly over external or less trusted networks.
To mitigate these risks, the diagnostic stack shall enforce secure communication via HTTPS,
authenticate endpoints using certificates (see architecture diagram), and implement strict access control mechanisms.
While diagnostics do not directly impact functional safety, a successful attack could indirectly influence safety-relevant
functions - for example by setting the system into a different state.
Therefore, the overall security architecture must be revisited in detail to assess and mitigate potential risks introduced by the SOVD integration.

Since diagnostics is QM, even being able to breach into the SOVD stack must not violate safety guarantees.
This implies that session/mode-sensitive operations must be treated by the implementing apps in a way that doesn't impact safety.
The client lib(s) need to be developed with the same quality standards as safe components to ensure that and also provide FFI guarantees.

## Safety Impact

At this point in time no direct safety impact is foreseen. The expected ASIL level is QM.
Configuration Management could have a safety impact but is handled in another S-CORE feature request and out of scope of this document.
As pointed out in "Security Impact", a breach in the diagnostic system could theoretically effect safety-relevant
functions - for example by setting the system into a different state.
The Fault Library could also have a safety impact if faults are propagated and act upon by other components - for example Health and Lifecycle Management.

## Open Issues

- Interfacing concept with Autosar Adaptive Diagnostic Stack for mixed stacks and/or a transitional phase
- List regulatory requirements for certain faults/DTCs - e.g. emission relevant faults
- Provide recommended transition/migration scenario for UDS based components moving to SOVD
- Decide if SOVD communication inside the ECU uses IP based communication or an alternative such as UDS (Unix Domain Sockets)
- Decide on a common concept for Service Validation. How are Services Validated and where (Server vs. Service)?
- For Service Validation: How do Services access the state of the ECU and the state of certain apps?
- Add concept of how to interact with ECU State Management
