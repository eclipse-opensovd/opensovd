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

#include "data_resource_mock.h"
#include <gtest/gtest.h>

namespace mw::diag::sovd {
namespace {

class ReadOnlyDataResourceTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource_ = std::make_unique<ReadOnlyDataResourceMock>("vehicle.vin");
    }

    void TearDown() override {
        resource_.reset();
    }

    std::unique_ptr<ReadOnlyDataResourceMock> resource_;
};

TEST_F(ReadOnlyDataResourceTest, GetData) {
    auto result = resource_->Get();
    
    // Verify successful get
    ASSERT_TRUE(result.has_value());
}

TEST_F(ReadOnlyDataResourceTest, MultipleGets) {
    // Multiple reads should succeed
    auto result1 = resource_->Get();
    auto result2 = resource_->Get();
    auto result3 = resource_->Get();
    
    ASSERT_TRUE(result1.has_value());
    ASSERT_TRUE(result2.has_value());
    ASSERT_TRUE(result3.has_value());
}

class WritableDataResourceTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource_ = std::make_unique<WritableDataResourceMock>("config.timeout");
    }

    void TearDown() override {
        resource_.reset();
    }

    std::unique_ptr<WritableDataResourceMock> resource_;
};

TEST_F(WritableDataResourceTest, PutValidData) {
    DiagnosticRequest request;
    request.data = R"({"value": 5000})";
    
    auto result = resource_->Put(request);
    
    ASSERT_TRUE(result.has_value());
    
    // Verify data was stored
    EXPECT_EQ(R"({"value": 5000})", resource_->GetLastRequestData());
}

TEST_F(WritableDataResourceTest, PutEmptyDataFails) {
    DiagnosticRequest request;
    request.data = ""; // Empty data
    
    auto result = resource_->Put(request);
    
    // Should fail for empty data
    ASSERT_FALSE(result.has_value());
}

TEST_F(WritableDataResourceTest, MultiplePuts) {
    DiagnosticRequest req1;
    req1.data = R"({"value": 1000})";
    resource_->Put(req1);
    
    DiagnosticRequest req2;
    req2.data = R"({"value": 2000})";
    resource_->Put(req2);
    
    DiagnosticRequest req3;
    req3.data = R"({"value": 3000})";
    auto result = resource_->Put(req3);
    
    ASSERT_TRUE(result.has_value());
    
    // Last write should be stored
    EXPECT_EQ(R"({"value": 3000})", resource_->GetLastRequestData());
}

class DataResourceTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource_ = std::make_unique<DataResourceMock>("sensor.temperature");
    }

    void TearDown() override {
        resource_.reset();
    }

    std::unique_ptr<DataResourceMock> resource_;
};

TEST_F(DataResourceTest, GetData) {
    auto result = resource_->Get();
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(DataResourceTest, PutData) {
    DiagnosticRequest request;
    request.data = R"({"temperature": 25.5})";
    
    auto result = resource_->Put(request);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(DataResourceTest, PutThenGet) {
    // Put data
    DiagnosticRequest request;
    request.data = R"({"temperature": 30.0})";
    auto put_result = resource_->Put(request);
    
    ASSERT_TRUE(put_result.has_value());
    
    // Get data
    auto get_result = resource_->Get();
    
    ASSERT_TRUE(get_result.has_value());
}

TEST_F(DataResourceTest, MultipleGetPutCycles) {
    for (int i = 0; i < 5; ++i) {
        // Put
        DiagnosticRequest request;
        request.data = R"({"value": )" + std::to_string(i) + "}";
        auto put_result = resource_->Put(request);
        ASSERT_TRUE(put_result.has_value());
        
        // Get
        auto get_result = resource_->Get();
        ASSERT_TRUE(get_result.has_value());
    }
}

TEST_F(DataResourceTest, GetWithoutPut) {
    // Get should work even without prior Put
    auto result = resource_->Get();
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(DataResourceTest, WithHeaders) {
    DiagnosticRequest request;
    request.headers["Content-Type"] = "application/json";
    request.headers["Authorization"] = "Bearer token123";
    request.data = R"({"value": 42})";
    
    auto result = resource_->Put(request);
    
    ASSERT_TRUE(result.has_value());
}

TEST_F(DataResourceTest, WithProximityResponse) {
    DiagnosticRequest request;
    request.proximity_response = "proximity_challenge_response";
    request.data = R"({"value": 100})";
    
    auto result = resource_->Put(request);
    
    ASSERT_TRUE(result.has_value());
}

} // namespace
} // namespace mw::diag::sovd
