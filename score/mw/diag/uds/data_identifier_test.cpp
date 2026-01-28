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

#include "data_identifier_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::uds {
namespace {

class DataIdentifierTest : public ::testing::Test {
protected:
    void SetUp() override {
        data_id_ = std::make_unique<DataIdentifierMock>(0x5678);
    }

    void TearDown() override {
        data_id_.reset();
    }

    std::unique_ptr<DataIdentifierMock> data_id_;
};

TEST_F(DataIdentifierTest, ReadInitialValue) {
    // Read initial value
    auto result = data_id_->Read();
    
    ASSERT_TRUE(result.has_value());
    
    // Verify default value (0x00, 0x00)
    auto data = result.value();
    EXPECT_EQ(2u, data.size());
    EXPECT_EQ(0x00, data[0]);
    EXPECT_EQ(0x00, data[1]);
}

TEST_F(DataIdentifierTest, WriteAndRead) {
    // Write new value
    std::vector<uint8_t> write_data = {0xAB, 0xCD, 0xEF};
    auto write_result = data_id_->Write(ByteSequence(write_data));
    
    ASSERT_TRUE(write_result.has_value());
    
    // Read back value
    auto read_result = data_id_->Read();
    
    ASSERT_TRUE(read_result.has_value());
    
    auto read_data = read_result.value();
    EXPECT_EQ(write_data.size(), read_data.size());
    EXPECT_EQ(write_data[0], read_data[0]);
    EXPECT_EQ(write_data[1], read_data[1]);
    EXPECT_EQ(write_data[2], read_data[2]);
}

TEST_F(DataIdentifierTest, WriteEmptyDataFails) {
    // Attempt to write empty data
    std::vector<uint8_t> empty_data;
    
    auto result = data_id_->Write(ByteSequence(empty_data));
    
    // Verify write failed
    ASSERT_FALSE(result.has_value());
}

TEST_F(DataIdentifierTest, MultipleWrites) {
    // First write
    std::vector<uint8_t> data1 = {0x11};
    data_id_->Write(ByteSequence(data1));
    
    // Second write
    std::vector<uint8_t> data2 = {0x22, 0x33};
    data_id_->Write(ByteSequence(data2));
    
    // Third write
    std::vector<uint8_t> data3 = {0x44, 0x55, 0x66};
    data_id_->Write(ByteSequence(data3));
    
    // Read should return last written value
    auto result = data_id_->Read();
    
    ASSERT_TRUE(result.has_value());
    
    auto data = result.value();
    EXPECT_EQ(data3.size(), data.size());
    EXPECT_EQ(data3, std::vector<uint8_t>(data.begin(), data.end()));
}

TEST_F(DataIdentifierTest, ReadDoesNotModifyData) {
    // Write data
    std::vector<uint8_t> write_data = {0xAA, 0xBB};
    data_id_->Write(ByteSequence(write_data));
    
    // Multiple reads
    auto read1 = data_id_->Read();
    auto read2 = data_id_->Read();
    auto read3 = data_id_->Read();
    
    ASSERT_TRUE(read1.has_value());
    ASSERT_TRUE(read2.has_value());
    ASSERT_TRUE(read3.has_value());
    
    // All reads should return same data
    EXPECT_EQ(read1.value(), read2.value());
    EXPECT_EQ(read2.value(), read3.value());
}

} // namespace
} // namespace mw::diag::uds
