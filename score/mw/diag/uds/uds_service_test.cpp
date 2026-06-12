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

#include "uds_service_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::uds {
namespace {

class UDSServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Service ID 0x22 (ReadDataByIdentifier)
        service_ = std::make_unique<UDSServiceMock>(0x22);
    }

    void TearDown() override {
        service_.reset();
    }

    std::unique_ptr<UDSServiceMock> service_;
};

TEST_F(UDSServiceTest, HandleValidMessage) {
    // Prepare UDS message
    std::vector<uint8_t> request = {0x22, 0xF1, 0x90};
    
    // Handle message
    auto result = service_->HandleMessage(ByteSequence(request));
    
    ASSERT_TRUE(result.has_value());
    
    // Verify positive response (SID + 0x40 = 0x62)
    auto response = result.value();
    EXPECT_EQ(request.size() + 1, response.size());
    EXPECT_EQ(0x62, response[0]); // Positive response
    
    // Echo of request data
    EXPECT_EQ(request[0], response[1]);
    EXPECT_EQ(request[1], response[2]);
    EXPECT_EQ(request[2], response[3]);
}

TEST_F(UDSServiceTest, HandleEmptyMessage) {
    // Attempt to handle empty message
    std::vector<uint8_t> empty;
    
    auto result = service_->HandleMessage(ByteSequence(empty));
    
    ASSERT_TRUE(result.has_value());
    
    // Verify negative response
    auto response = result.value();
    EXPECT_EQ(3u, response.size());
    EXPECT_EQ(0x7F, response[0]); // Negative response
    EXPECT_EQ(0x22, response[1]); // Service ID
    EXPECT_EQ(0x13, response[2]); // Incorrect message length
}

TEST_F(UDSServiceTest, CallCountIncrementsOnEachCall) {
    // Initial call count
    EXPECT_EQ(0u, service_->GetCallCount());
    
    std::vector<uint8_t> message = {0x22, 0xF1, 0x90};
    
    // First call
    service_->HandleMessage(ByteSequence(message));
    EXPECT_EQ(1u, service_->GetCallCount());
    
    // Second call
    service_->HandleMessage(ByteSequence(message));
    EXPECT_EQ(2u, service_->GetCallCount());
    
    // Third call
    service_->HandleMessage(ByteSequence(message));
    EXPECT_EQ(3u, service_->GetCallCount());
}

TEST_F(UDSServiceTest, HandleSingleByteMessage) {
    std::vector<uint8_t> request = {0x22};
    
    auto result = service_->HandleMessage(ByteSequence(request));
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(2u, response.size());
    EXPECT_EQ(0x62, response[0]); // Positive response
    EXPECT_EQ(0x22, response[1]); // Echo
}

TEST_F(UDSServiceTest, HandleLargeMessage) {
    // Create large message
    std::vector<uint8_t> request(100);
    request[0] = 0x22;
    for (size_t i = 1; i < request.size(); ++i) {
        request[i] = static_cast<uint8_t>(i);
    }
    
    auto result = service_->HandleMessage(ByteSequence(request));
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(request.size() + 1, response.size());
    EXPECT_EQ(0x62, response[0]);
    
    // Verify echo
    for (size_t i = 0; i < request.size(); ++i) {
        EXPECT_EQ(request[i], response[i + 1]);
    }
}

TEST_F(UDSServiceTest, DifferentServiceIDs) {
    // Test with different service ID
    UDSServiceMock service_0x10(0x10); // DiagnosticSessionControl
    
    std::vector<uint8_t> request = {0x10, 0x01};
    auto result = service_0x10.HandleMessage(ByteSequence(request));
    
    ASSERT_TRUE(result.has_value());
    
    auto response = result.value();
    EXPECT_EQ(0x50, response[0]); // Positive response (0x10 + 0x40)
}

TEST_F(UDSServiceTest, CallCountPersistsAcrossMessages) {
    std::vector<uint8_t> msg1 = {0x22, 0xF1, 0x90};
    std::vector<uint8_t> msg2 = {0x22, 0xF1, 0x86};
    std::vector<uint8_t> empty;
    
    service_->HandleMessage(ByteSequence(msg1));
    service_->HandleMessage(ByteSequence(msg2));
    service_->HandleMessage(ByteSequence(empty)); // Error case
    
    // All calls should be counted
    EXPECT_EQ(3u, service_->GetCallCount());
}

} // namespace
} // namespace mw::diag::uds
