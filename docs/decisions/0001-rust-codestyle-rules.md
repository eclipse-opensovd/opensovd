---
# Configuration for the Jekyll template "Just the Docs"

parent: Decisions
nav_order: 100
title: Define common linting and formating rules for Rust in OpenSOVD

status: "accepted"
decision-makers: OpenSOVD Architecture round
date: 2026-02-6
---

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

# Define common linting and formating rules for Rust in OpenSOVD

## Context and Problem Statement

The goal is to formalize the usage of linting rules for rust using clippy and
set common codestyle rules applied through rustfmt.
This will help having a single style across the different components which
improves understandability and readability across the project context and hence
facilitates easier maintainability long-term.

## Considered Options

- Adopting the existing ruleset used in OpenSOVD CDA
  [[1]](https://github.com/eclipse-opensovd/classic-diagnostic-adapter/blob/main/CODESTYLE.md)
  [[2]](https://github.com/eclipse-opensovd/classic-diagnostic-adapter/blob/main/Cargo.toml#L124)
- Defining a new set of common rules

## Decision Outcome

Chosen option: "Adopting the existing ruleset used in OpenSOVD CDA"
The rules will be placed in the [cicd-workflows repository](https://github.com/eclipse-opensovd/cicd-workflows) to ensure all projects can easily implement them.

## Pros and Cons of the Options

### Adopting the existing ruleset used in OpenSOVD CDA

The ruleset in the CDA is based on the [clippy::pedantic](https://doc.rust-lang.org/stable/clippy/lints.html#pedantic)
set of lints with additional formatting rules related to import grouping and
ordering.
In addition to the pedantic ruleset following lints are explicitly enabled with
the reasoning attached:

```toml
## lints related to runtime panic behavior
# enforce only checked access to slices to avoid runtime panics
indexing_slicing = "deny"
# disallow any unwraps in the production code
# (unwrap in test code is explicitly allowed)
unwrap_used = "deny"
# enforce that arithmetic operations that can produce side effects always use
# either checked or explicit versions of the operations. eg. `.checked_add(...)`
# or `.saturating_sub(...)` to avoid unexpected runtime behavior or panics.
arithmetic_side_effects = "deny"
## lints related to readability of code
# enforce that references are cloned via eg. `Arc::clone` instead of `.clone()`
# making it explit that a reference is cloned here and not the underlying data.
clone_on_ref_ptr = "warn"
# enforce that the type suffix of a literal is always appended directly
# eg. 12u8 instead of 12_u8
separated_literal_suffix = "deny"
```

- Good: the relatively high restrictions enforce via tooling that contributions
  need to have a specific codestyle and coding standard, which makes it easier on
  the reviews

### Defining a new set of common rules

With this option the idea is to take a look at what the CDA currently does and
mark things that people deem too restrictive as optional with appropriate
recommendations attached.

- Good: potentially easier for new projects built upon existing codebases to
  adapt to
- Negative: Could potentially lead to more fragmentation with regards to codestyle
  across the project
