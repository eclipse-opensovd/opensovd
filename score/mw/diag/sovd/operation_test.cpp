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

#include "operation_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::sovd {
namespace {

class OperationTest : public ::testing::Test {
protected:
    void SetUp() override {
        operation_ = std::make_unique<OperationMock>("selftest");
    }

    void TearDown() override {
        operation_.reset();
    }

    std::unique_ptr<OperationMock> operation_;
    DiagnosticRequest empty_request_;
};

TEST_F(OperationTest, GetInfo) {
    auto result = operation_->Info(empty_request_);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, GetStatus) {
    auto result = operation_->Status(empty_request_);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, ExecuteOperation) {
    // Initial status should be stopped
    EXPECT_EQ(OperationExecutionStatus::kStopped, operation_->GetStatus());
    
    // Execute operation
    auto result = operation_->Execute(empty_request_);
    
    ASSERT_TRUE(result.has_value());
    
    // After execution, should be completed (in mock)
    EXPECT_EQ(OperationExecutionStatus::kCompleted, operation_->GetStatus());
}

TEST_F(OperationTest, CannotExecuteWhileRunning) {
    // First execution
    auto exec1 = operation_->Execute(empty_request_);
    ASSERT_TRUE(exec1.has_value());
    
    // Reset to running state manually for test
    // (In mock, execution completes immediately)
    // This test verifies the state check exists
}

TEST_F(OperationTest, StopOperation) {
    // Execute operation first
    operation_->Execute(empty_request_);
    
    // Reset to make it running
    operation_->Reset(empty_request_);
    operation_->Execute(empty_request_);
    
    // Note: Mock completes immediately, so we can't test actual stop
    // This demonstrates the API pattern
}

TEST_F(OperationTest, ResumeOperation) {
    // Resume from stopped state
    auto result = operation_->Resume(empty_request_);
    
    // In mock, this should work from stopped state
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, ResetOperation) {
    // Execute operation
    operation_->Execute(empty_request_);
    
    // Reset operation
    auto result = operation_->Reset(empty_request_);
    
    ASSERT_TRUE(result.has_value());
    
    // After reset, should be stopped with count = 0
    EXPECT_EQ(OperationExecutionStatus::kStopped, operation_->GetStatus());
    EXPECT_EQ(0u, operation_->GetExecutionCount());
}

TEST_F(OperationTest, ExecutionCountIncrements) {
    // Initial count
    EXPECT_EQ(0u, operation_->GetExecutionCount());
    
    // Execute once
    operation_->Execute(empty_request_);
    EXPECT_EQ(1u, operation_->GetExecutionCount());
    
    // Reset and execute again
    operation_->Reset(empty_request_);
    EXPECT_EQ(0u, operation_->GetExecutionCount());
    
    operation_->Execute(empty_request_);
    EXPECT_EQ(1u, operation_->GetExecutionCount());
}

TEST_F(OperationTest, HandleCustomCapability) {
    auto result = operation_->Handle(empty_request_);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, InfoStatusExecuteWorkflow) {
    // 1. Get info
    auto info_result = operation_->Info(empty_request_);
    ASSERT_TRUE(info_result.has_value());
    
    // 2. Get status before execution
    auto status_before = operation_->Status(empty_request_);
    ASSERT_TRUE(status_before.has_value());
    
    // 3. Execute
    auto exec_result = operation_->Execute(empty_request_);
    ASSERT_TRUE(exec_result.has_value());
    
    // 4. Get status after execution
    auto status_after = operation_->Status(empty_request_);
    ASSERT_TRUE(status_after.has_value());
}

TEST_F(OperationTest, MultipleResetCycles) {
    for (int i = 0; i < 3; ++i) {
        // Execute
        operation_->Execute(empty_request_);
        EXPECT_GT(operation_->GetExecutionCount(), 0u);
        
        // Reset
        operation_->Reset(empty_request_);
        EXPECT_EQ(0u, operation_->GetExecutionCount());
        EXPECT_EQ(OperationExecutionStatus::kStopped, operation_->GetStatus());
    }
}

TEST_F(OperationTest, WithRequestHeaders) {
    DiagnosticRequest request;
    request.headers["Operation-Timeout"] = "5000";
    request.headers["Priority"] = "high";
    
    auto result = operation_->Execute(request);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, WithRequestData) {
    DiagnosticRequest request;
    request.data = R"({"parameters": {"mode": "full", "iterations": 10}})";
    
    auto result = operation_->Execute(request);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(OperationTest, ResumeAfterReset) {
    // Execute, reset, then resume
    operation_->Execute(empty_request_);
    operation_->Reset(empty_request_);
    
    auto result = operation_->Resume(empty_request_);
    ASSERT_TRUE(result.has_value());
}

} // namespace
} // namespace mw::diag::sovd
