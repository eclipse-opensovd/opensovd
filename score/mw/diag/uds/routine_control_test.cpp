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

#include "routine_control_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::uds {
namespace {

class RoutineControlTest : public ::testing::Test {
protected:
    void SetUp() override {
        routine_ = std::make_unique<RoutineControlMock>(0x0100);
    }

    void TearDown() override {
        routine_.reset();
    }

    std::unique_ptr<RoutineControlMock> routine_;
};

TEST_F(RoutineControlTest, StartRoutine) {
    // Start routine
    auto result = routine_->Start({});
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(1u, response.size());
    EXPECT_EQ(0x00, response[0]); // Success status
}

TEST_F(RoutineControlTest, CannotStartTwice) {
    // Start routine
    auto start1 = routine_->Start({});
    ASSERT_TRUE(start1.has_value());
    
    // Attempt to start again (should fail)
    auto start2 = routine_->Start({});
    ASSERT_TRUE(start2.has_value());
    
    auto response = start2.value();
    EXPECT_EQ(0x31, response[0]); // Negative response
}

TEST_F(RoutineControlTest, StopRoutine) {
    // Start routine
    routine_->Start({});
    
    // Stop routine
    auto result = routine_->Stop({});
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(2u, response.size());
    EXPECT_EQ(0x00, response[0]); // Success status
    EXPECT_EQ(1, response[1]);     // Execution count
}

TEST_F(RoutineControlTest, CannotStopNotRunning) {
    // Attempt to stop without starting
    auto result = routine_->Stop({});
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(0x24, response[0]); // Negative response: Request sequence error
}

TEST_F(RoutineControlTest, RequestResults) {
    // Get results before starting
    auto result1 = routine_->RequestResults({});
    ASSERT_TRUE(result1.has_value());
    
    auto response1 = result1.value();
    EXPECT_EQ(4u, response1.size());
    EXPECT_EQ(0x00, response1[0]); // Not running
    EXPECT_EQ(0, response1[1]);     // Execution count = 0
    
    // Start and get results
    routine_->Start({});
    auto result2 = routine_->RequestResults({});
    ASSERT_TRUE(result2.has_value());
    
    auto response2 = result2.value();
    EXPECT_EQ(0x01, response2[0]); // Running
    EXPECT_EQ(1, response2[1]);     // Execution count = 1
}

TEST_F(RoutineControlTest, StartStopMultipleTimes) {
    // First cycle
    routine_->Start({});
    routine_->Stop({});
    
    // Second cycle
    auto start_result = routine_->Start({});
    ASSERT_TRUE(start_result.has_value());
    
    auto stop_result = routine_->Stop({});
    ASSERT_TRUE(stop_result.has_value());
    
    auto response = stop_result.value();
    EXPECT_EQ(2, response[1]); // Execution count = 2
}

TEST_F(RoutineControlTest, ExecutionCountIncrementsOnEachStart) {
    // Start-stop cycle 1
    routine_->Start({});
    routine_->Stop({});
    
    // Start-stop cycle 2
    routine_->Start({});
    routine_->Stop({});
    
    // Start-stop cycle 3
    routine_->Start({});
    auto result = routine_->Stop({});
    
    ASSERT_TRUE(result.has_value());
    auto response = result.value();
    EXPECT_EQ(3, response[1]); // Execution count = 3
}

TEST_F(RoutineControlTest, ResultsWhileRunning) {
    // Start routine
    routine_->Start({});
    
    // Get results while running
    auto result = routine_->RequestResults({});
    
    ASSERT_TRUE(result.has_value());
    auto response = result.value();
    
    EXPECT_EQ(0x01, response[0]); // Running status
    EXPECT_GT(response[1], 0);     // Execution count > 0
}

} // namespace
} // namespace mw::diag::uds
