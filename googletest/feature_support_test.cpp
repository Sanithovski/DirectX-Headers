// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "gtest/gtest.h"

#include <directx/d3d12.h>
#include <directx/dxcore.h>
#include <directx/d3dx12.h>
#include "dxguids/dxguids.h"

class FeatureSupportTest : public ::testing::Test {
protected: 
    void SetUp() override {
        IDXCoreAdapterFactory* factory;
        if (FAILED(DXCoreCreateAdapterFactory(&factory))) {
            return;
        }

        IDXCoreAdapterList* list = nullptr;
        if (FAILED(factory->CreateAdapterList(1, &DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE, &list))) {
            return;
        }

        if (FAILED(list->GetAdapter(0, &adapter))) {
            adapter = nullptr;
            return;
        }

        if (FAILED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
            device = nullptr;
            return;
        }
    }

    IDXCoreAdapter* adapter = nullptr;
    ID3D12Device* device = nullptr;
};

TEST_F(FeatureSupportTest, Initialization) {
    CD3DX12FeatureSupport feature_struct = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(feature_struct.GetStatus());
}
