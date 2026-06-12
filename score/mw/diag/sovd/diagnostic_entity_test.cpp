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

#include "diagnostic_entity_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::sovd {
namespace {

class DiagnosticEntityTest : public ::testing::Test {
protected:
    void SetUp() override {
        entity_ = std::make_unique<DiagnosticEntityMock>("ecu_gateway");
    }

    void TearDown() override {
        entity_.reset();
    }

    std::unique_ptr<DiagnosticEntityMock> entity_;
};

TEST_F(DiagnosticEntityTest, GetKind) {
    auto kind = entity_->GetKind();
    EXPECT_EQ(DiagnosticEntity::Kind::kApplication, kind);
}

TEST_F(DiagnosticEntityTest, LockEntity) {
    // Initially not locked
    EXPECT_FALSE(entity_->IsLocked());
    
    // Lock entity
    auto result = entity_->Lock();
    ASSERT_TRUE(result.has_value());
    
    // Verify locked
    EXPECT_TRUE(entity_->IsLocked());
}

TEST_F(DiagnosticEntityTest, CannotLockTwice) {
    // First lock succeeds
    auto lock1 = entity_->Lock();
    ASSERT_TRUE(lock1.has_value());
    
    // Second lock fails
    auto lock2 = entity_->Lock();
    ASSERT_FALSE(lock2.has_value());
}

TEST_F(DiagnosticEntityTest, UnlockEntity) {
    // Lock then unlock
    entity_->Lock();
    
    auto result = entity_->Unlock();
    ASSERT_TRUE(result.has_value());
    
    EXPECT_FALSE(entity_->IsLocked());
}

TEST_F(DiagnosticEntityTest, CannotUnlockWhenNotLocked) {
    // Attempt to unlock without locking
    auto result = entity_->Unlock();
    ASSERT_FALSE(result.has_value());
}

TEST_F(DiagnosticEntityTest, GetSupportedModes) {
    auto result = entity_->GetSupportedModes();
    
    ASSERT_TRUE(result.has_value());
    
    auto modes = result.value();
    EXPECT_EQ(2u, modes.size());
    
    // Verify normal mode
    EXPECT_EQ("normal", modes[0].id);
    EXPECT_EQ("Normal Operation", modes[0].name);
    EXPECT_TRUE(modes[0].translation_id.has_value());
    EXPECT_EQ("mode.normal", modes[0].translation_id.value());
    EXPECT_EQ(2u, modes[0].values.size());
    
    // Verify diagnostic mode
    EXPECT_EQ("diagnostic", modes[1].id);
    EXPECT_EQ("Diagnostic Mode", modes[1].name);
}

TEST_F(DiagnosticEntityTest, ApplyValidMode) {
    auto result = entity_->ApplyMode("normal", "active", std::nullopt);
    
    ASSERT_TRUE(result.has_value());
    
    // Verify mode was applied
    EXPECT_EQ("normal", entity_->GetCurrentModeId());
    EXPECT_EQ("active", entity_->GetCurrentModeValue());
}

TEST_F(DiagnosticEntityTest, ApplyInvalidMode) {
    auto result = entity_->ApplyMode("unknown_mode", "value", std::nullopt);
    
    // Should fail for unknown mode
    ASSERT_FALSE(result.has_value());
}

TEST_F(DiagnosticEntityTest, ApplyDifferentModes) {
    // Apply normal mode
    entity_->ApplyMode("normal", "active", std::nullopt);
    EXPECT_EQ("normal", entity_->GetCurrentModeId());
    
    // Apply diagnostic mode
    entity_->ApplyMode("diagnostic", "enabled", std::nullopt);
    EXPECT_EQ("diagnostic", entity_->GetCurrentModeId());
    EXPECT_EQ("enabled", entity_->GetCurrentModeValue());
}

TEST_F(DiagnosticEntityTest, ApplyModeWithTimeout) {
    auto timeout = std::chrono::seconds(30);
    auto result = entity_->ApplyMode("diagnostic", "enabled", timeout);
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ("diagnostic", entity_->GetCurrentModeId());
}

TEST_F(DiagnosticEntityTest, LockUnlockCycle) {
    // Multiple lock-unlock cycles
    for (int i = 0; i < 3; ++i) {
        auto lock_result = entity_->Lock();
        ASSERT_TRUE(lock_result.has_value());
        EXPECT_TRUE(entity_->IsLocked());
        
        auto unlock_result = entity_->Unlock();
        ASSERT_TRUE(unlock_result.has_value());
        EXPECT_FALSE(entity_->IsLocked());
    }
}

} // namespace
} // namespace mw::diag::sovd
