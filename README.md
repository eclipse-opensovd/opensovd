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

# OpenSOVD

Welcome to the OpenSOVD main repository.

Here are some useful links to get you started:

- [Eclipse OpenSOVD Project Page](https://projects.eclipse.org/projects/automotive.opensovd): get to know the project
- [Eclipse OpenSOVD Kickoff Meeting](https://www.youtube.com/watch?v=VnMauUXT2cI): if you missed the kick-off meeting you can view it on YouTube
- [OpenSOVD High Level Design](./docs/design/design.md): this will be the starting point for the OpenSOVD architecture
- [Eclipse SDV Working Group Slack Workspace](https://join.slack.com/t/sdvworkinggroup/shared_invite/zt-1yxo8mejp-aul08kAuuOwi2LRbSXvCTw): join the Eclipse SDV Slack workspace
- [OpenSOVD Slack Channel](https://app.slack.com/client/T02MS1M89UH/C0958MQNGP2): join the official OpenSOVD Slack channel `#eclipse-opensovd`
- [OpenSOVD Meeting Minutes](https://github.com/eclipse-opensovd/opensovd/discussions): Find all the meeting minutes and discussions
- [Eclipse SDV Working Group Community Calendar](https://calendar.google.com/calendar/u/0?cid=Y18yYW1waTJibW9rYTNxdGVyNGRjZWFwMWQ1Z0Bncm91cC5jYWxlbmRhci5nb29nbGUuY29t): find the OpenSOVD meetings in the Eclipse SDV Community Calendar

## Overview

Eclipse OpenSOVD provides an open source implementation of the Service-Oriented Vehicle Diagnostics (SOVD) standard, as defined in ISO 17978.
The project delivers a modular, standards-compliant software stack that enables secure and efficient access to vehicle diagnostics over service-oriented architectures.
By offering an open and community-driven implementation, Eclipse OpenSOVD serves as a foundation for developers, OEMs, and tool vendors to build, test, and integrate SOVD-based solutions.
The project will hence facilitate adoption and ensure industry coherence with the standard.

Eclipse OpenSOVD complements and integrates the Eclipse S-CORE project by providing an open implementation of the SOVD protocol that can be used for diagnostics and service orchestration within the S-CORE environment.
This integration ensures that diagnostic capabilities are natively supported in SDV architectures,
enabling developers and OEMs to build more robust, maintainable, and standards-compliant vehicle software stacks.

Key components include:

- SOVD Gateway: REST/HTTP API endpoints for diagnostics, logging, and software updates.
- Protocol Adapters: Bridging modern HPCs (e.g., AUTOSAR Adaptive) and legacy ECUs (e.g., UDS-based systems).
- Diagnostic Manager: Service orchestration for fault reset, parameter adjustments, and bulk data transfers.

Future-Proofing:

- Semantic Interoperability: JSON schema extensions for machine-readable diagnostics, enabling AI-driven analysis and cross-domain workflows.
- Edge AI/ML Readiness: Modular design to support lightweight ML models (e.g., predictive fault detection) via collaboration with projects like Eclipse Edge Native.
- Support for Extended Vehicle logging and publish/subscribe mechanisms.

## 🤝 Community Collaboration & Project Structure

Eclipse OpenSOVD thrives through open collaboration, shared responsibility, and transparent decision-making.
To foster this, we organize our work into dedicated work streams, each focusing on a major component (e.g.,
CDA, Client, Server) or a horizontal concern (e.g., Security, Testing, Eclipse S-CORE integration). These
work streams are led by community members who take ownership and drive progress in their respective areas.
To ensure coherence and alignment across the project, we hold a regular Architecture Board meeting, which
serves as the central forum for architectural discussions and key project decisions.
We invite all contributors and interested parties to join these meetings, share their insights, and help
shape the future of OpenSOVD.

Below are links to the current meeting invitations:

- 📅 [Architecture Board](meetings/Eclipse_OpenSOVD_-_Architecture_Board.ics) - Mondays 11:30 to 12:30 CET
- 📅 [Workstream CDA](meetings/Eclipse_OpenSOVD_-_Workstream_CDA.ics) - Mondays 14:00 to 15:00 CET
- 📅 [Workstream Gateway, Client & Server](meetings/Eclipse_OpenSOVD_-_Workstream_Core.ics) - Tuesdays 11:30 to 12:15 CET
- 📅 [Workstream UDS2SOVD](meetings/Eclipse_OpenSOVD_-_Workstream_UDS2SOVD.ics) - Tuesdays 13:00 to 14:00 CET

More work streams and meeting series will be added as the project evolves — stay tuned and get involved!
