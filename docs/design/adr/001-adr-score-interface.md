<!--
SPDX-FileCopyrightText: 2025 The Eclipse OpenSOVD contributors

SPDX-License-Identifier: Apache-2.0
-->

# 2025-07-21 Interface between OpenSOVD and S-CORE

<!-- This template is intended for use by all contributors making architectural decisions in the OpenSOVD project -->

Date: 2025-07-21

Status: accepted

Author: @timkl7

Reviewer: Attendees [OpenSOVD Architecture Board 2025-07-21](https://github.com/eclipse-opensovd/opensovd/discussions/8) and [S-CORE Architecture Workshop 2025-07](https://github.com/orgs/eclipse-score/discussions/1247)

## Context

<!-- Describe the context and problem statement -->

It is a goal of OpenSOVD to integrate with [S-CORE](https://github.com/eclipse-score) as its diagnostic stack [S-CORE Diagnostic and Fault Management](https://eclipse-score.github.io/score/main/features/diagnostics/index.html).
Consequently, a clearly defined technical and organizational interface is required between S-CORE and OpenSOVD.

## Decision

<!-- Document decision and reasoning, referencing an option from below -->

The `Fault library` component will act as the defined technical and organizational interface between S-CORE and OpenSOVD.
More details in [Option 1](#option-1---fault-library-as-interface).

This decision has been accepted in the OpenSOVD Architecture Board and the S-CORE Architecture Community.

## Consequences

<!-- Describe positive and negative consequences of the decision and impact to other components -->

S-CORE and OpenSOVD will need to align and co-develop the `Fault library` component.
This introduces both an organizational and a technical dependency between the two projects

## Options

<!-- Describe the options including pros and cons in detail -->

### Option 1 - Fault library as interface

The `Fault library` will serve as the primary API entry point for the diagnostic system.
Within this setup, S-CORE will assume responsibility for safety-relevant functionality up to ASIL-B,
while OpenSOVD will remain outside the safety scope.

This interface model reflects the fact that S-CORE has additional requirements for the `Fault library` that are not applicable to OpenSOVD.
By respecting this separation of concerns, we allow S-CORE to maintain its safety guarantees while enabling OpenSOVD to remain lightweight and flexible.

Furthermore, this approach enables OpenSOVD to provide a fully standalone, end-to-end diagnostic stack that can also operate independently of S-CORE.
This maximizes reuse, modularity, and potential adoption in both integrated and standalone scenarios.

This makes Option 1 the most pragmatic and scalable path forward for both OpenSOVD and S-CORE.

### Option 2 – No dedicated interface (rejected)

S-CORE and OpenSOVD could each implement their own diagnostic logic and data flow without a shared interface like the `Fault library`.

This was rejected because it would lead to duplicated functionality, diverging APIs, and increased integration effort. It would also hinder reuse and make safety certification boundaries harder to manage.

## Appendix

<!-- Add additional information regarding the decision here -->

- Notes from the [S-CORE Architecture Workshop 2025-07](https://github.com/orgs/eclipse-score/discussions/1247) which informed this decision
