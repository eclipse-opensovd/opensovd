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

#include "read_data_by_identifier_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::uds {
namespace {

class ReadDataByIdentifierTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(ReadDataByIdentifierTest, ReadVIN) {
    // Create mock for VIN (DID 0xF190)
    ReadDataByIdentifierMock vin_reader(0xF190);
    
    // Read VIN data
    auto result = vin_reader.Read();
    
    // Verify result is successful
    ASSERT_TRUE(result.has_value());
    
    // Verify VIN data length (17 bytes)
    auto data = result.value();
    EXPECT_EQ(17u, data.size());
    
    // Verify first byte is 'W' (0x57)
    EXPECT_EQ(0x57, data[0]);
}

TEST_F(ReadDataByIdentifierTest, ReadActiveDiagnosticSession) {
    // Create mock for Active Diagnostic Session (DID 0xF186)
    ReadDataByIdentifierMock session_reader(0xF186);
    
    // Read session data
    auto result = session_reader.Read();
    
    // Verify result is successful
    ASSERT_TRUE(result.has_value());
    
    // Verify session data
    auto data = result.value();
    EXPECT_EQ(1u, data.size());
    EXPECT_EQ(0x01, data[0]); // Default session
}

TEST_F(ReadDataByIdentifierTest, ReadUnknownDID) {
    // Create mock for unknown DID
    ReadDataByIdentifierMock unknown_reader(0xFFFF);
    
    // Read data
    auto result = unknown_reader.Read();
    
    // Verify result is successful (returns generic response)
    ASSERT_TRUE(result.has_value());
    
    // Verify generic response
    auto data = result.value();
    EXPECT_EQ(2u, data.size());
    EXPECT_EQ(0x00, data[0]);
    EXPECT_EQ(0x00, data[1]);
}

TEST_F(ReadDataByIdentifierTest, MultipleReads) {
    // Create mock reader
    ReadDataByIdentifierMock reader(0xF190);
    
    // Read multiple times - should return same data
    auto result1 = reader.Read();
    auto result2 = reader.Read();
    
    ASSERT_TRUE(result1.has_value());
    ASSERT_TRUE(result2.has_value());
    
    auto data1 = result1.value();
    auto data2 = result2.value();
    
    EXPECT_EQ(data1.size(), data2.size());
    EXPECT_EQ(data1, data2);
}

} // namespace
} // namespace mw::diag::uds
