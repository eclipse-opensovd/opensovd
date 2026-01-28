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

#include "write_data_by_identifier_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::uds {
namespace {

class WriteDataByIdentifierTest : public ::testing::Test {
protected:
    void SetUp() override {
        writer_ = std::make_unique<WriteDataByIdentifierMock>(0x1234);
    }

    void TearDown() override {
        writer_.reset();
    }

    std::unique_ptr<WriteDataByIdentifierMock> writer_;
};

TEST_F(WriteDataByIdentifierTest, WriteValidData) {
    // Prepare data to write
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};
    
    // Write data
    auto result = writer_->Write(ByteSequence(data));
    
    // Verify write was successful
    ASSERT_TRUE(result.has_value());
    
    // Verify data was stored
    const auto& written = writer_->GetLastWrittenData();
    EXPECT_EQ(data.size(), written.size());
    EXPECT_EQ(data, written);
}

TEST_F(WriteDataByIdentifierTest, WriteEmptyData) {
    // Attempt to write empty data
    std::vector<uint8_t> empty_data;
    
    auto result = writer_->Write(ByteSequence(empty_data));
    
    // Verify write failed (empty data not allowed)
    ASSERT_FALSE(result.has_value());
}

TEST_F(WriteDataByIdentifierTest, WriteSingleByte) {
    // Write single byte
    std::vector<uint8_t> data = {0xFF};
    
    auto result = writer_->Write(ByteSequence(data));
    
    ASSERT_TRUE(result.has_value());
    
    const auto& written = writer_->GetLastWrittenData();
    EXPECT_EQ(1u, written.size());
    EXPECT_EQ(0xFF, written[0]);
}

TEST_F(WriteDataByIdentifierTest, WriteMultipleTimes) {
    // First write
    std::vector<uint8_t> data1 = {0xAA, 0xBB};
    writer_->Write(ByteSequence(data1));
    
    // Second write
    std::vector<uint8_t> data2 = {0xCC, 0xDD, 0xEE};
    auto result = writer_->Write(ByteSequence(data2));
    
    ASSERT_TRUE(result.has_value());
    
    // Verify last write is stored
    const auto& written = writer_->GetLastWrittenData();
    EXPECT_EQ(data2.size(), written.size());
    EXPECT_EQ(data2, written);
}

TEST_F(WriteDataByIdentifierTest, WriteLargeData) {
    // Write large data block
    std::vector<uint8_t> large_data(256);
    for (size_t i = 0; i < large_data.size(); ++i) {
        large_data[i] = static_cast<uint8_t>(i);
    }
    
    auto result = writer_->Write(ByteSequence(large_data));
    
    ASSERT_TRUE(result.has_value());
    
    const auto& written = writer_->GetLastWrittenData();
    EXPECT_EQ(256u, written.size());
    EXPECT_EQ(large_data, written);
}

} // namespace
} // namespace mw::diag::uds
