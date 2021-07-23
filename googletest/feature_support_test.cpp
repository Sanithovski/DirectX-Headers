// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "gtest/gtest.h"

#include <directx/d3d12.h>
#include <directx/dxcore.h>
#include <directx/d3dx12.h>
#include "dxguids/dxguids.h"

#include "MockDevice.hpp"

class FeatureSupportTest : public ::testing::Test {
protected: 
    void SetUp() override {
        device = new MockDevice(1);
    }

    void TearDown() override {
        delete device;
    }

    MockDevice* device = nullptr;
};

TEST_F(FeatureSupportTest, Initialization) {
    CD3DX12FeatureSupport feature_struct = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(feature_struct.GetStatus(), S_OK);
    
    CD3DX12FeatureSupport feature_struct_another(device);
    EXPECT_EQ(feature_struct_another.GetStatus(), S_OK);
}

// 0: D3D12_OPTIONS
// Arbitarily set support status for caps and see if the returned results are correct
TEST_F(FeatureSupportTest, D3D12Options) {
    device->m_DoublePrecisionFloatShaderOps = true;
    device->m_OutputMergerLogicOp = true;
    device->m_ShaderMinPrecisionSupport10Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT;
    device->m_ShaderMinPrecisionSupport16Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT;
    device->m_TiledResourcesTier = D3D12_TILED_RESOURCES_TIER_3;
    device->m_ResourceBindingTier = D3D12_RESOURCE_BINDING_TIER_3;
    device->m_PSSpecifiedStencilRefSupported = true;
    device->m_ConservativeRasterizationTier = D3D12_CONSERVATIVE_RASTERIZATION_TIER_2;
    device->m_MaxGPUVirtualAddressBitsPerResource = 10;
    device->m_ResourceHeapTier = D3D12_RESOURCE_HEAP_TIER_2;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_TRUE(features.DoublePrecisionFloatShaderOps());
    EXPECT_TRUE(features.OutputMergerLogicOp());
    EXPECT_EQ(features.MinPrecisionSupport(), D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT | D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT);
    EXPECT_EQ(features.TiledResourcesTier(), D3D12_TILED_RESOURCES_TIER_3);
    EXPECT_EQ(features.ResourceBindingTier(), D3D12_RESOURCE_BINDING_TIER_3);
    EXPECT_TRUE(features.PSSpecifiedStencilRefSupported());
    EXPECT_FALSE(features.TypedUAVLoadAdditionalFormats());
    EXPECT_FALSE(features.ROVsSupported());
    EXPECT_EQ(features.ConservativeRasterizationTier(), D3D12_CONSERVATIVE_RASTERIZATION_TIER_2);
    EXPECT_EQ(features.MaxGPUVirtualAddressBitsPerResource(), 10);
    EXPECT_FALSE(features.StandardSwizzle64KBSupported());
    EXPECT_EQ(features.CrossNodeSharingTier(), D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED);
    EXPECT_FALSE(features.CrossAdapterRowMajorTextureSupported());
    EXPECT_FALSE(features.VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation());
    EXPECT_EQ(features.ResourceHeapTier(), D3D12_RESOURCE_HEAP_TIER_2);
}

// 1: Architecture & 16: Architecture1
// Test where architecture1 is available
TEST_F(FeatureSupportTest, Architecture1Available)
{
    device->m_Architecture1Available = true;
    device->m_TileBasedRenderer[0] = false;
    device->m_UMA[0] = true;
    device->m_CacheCoherentUMA[0] = true;
    device->m_IsolatedMMU[0] = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.TileBasedRenderer(0));
    EXPECT_TRUE(features.UMA(0));
    EXPECT_TRUE(features.CacheCoherentUMA(0));
    EXPECT_TRUE(features.IsolatedMMU(0));
}

// Test where architecture1 is not available
TEST_F(FeatureSupportTest, Architecture1Unavailable)
{
    device->m_Architecture1Available = false; // Architecture1 not available
    device->m_TileBasedRenderer[0] = false;
    device->m_UMA[0] = true;
    device->m_CacheCoherentUMA[0] = false;
    device->m_IsolatedMMU[0] = true; // Notice that if architecture1 is not available, IslatedMMU cap should not be present

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.TileBasedRenderer(0));
    EXPECT_TRUE(features.UMA(0));
    EXPECT_FALSE(features.CacheCoherentUMA(0));
    EXPECT_FALSE(features.IsolatedMMU(0)); // If Architecture1 is not available, IsolatedMMU should not be available
}

// Test on devices with more than one graphics node
TEST_F(FeatureSupportTest, ArchitectureMulticore)
{
    device->SetNodeCount(3);
    device->m_Architecture1Available = true;
    device->m_TileBasedRenderer = {false, true, true};
    device->m_UMA = {true, false, false};
    device->m_CacheCoherentUMA = {false, false, true};
    device->m_IsolatedMMU = {false, true, false};

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    
    EXPECT_FALSE(features.TileBasedRenderer(0));
    EXPECT_TRUE(features.TileBasedRenderer(1));
    EXPECT_TRUE(features.TileBasedRenderer(2));
    
    EXPECT_TRUE(features.UMA(0));
    EXPECT_FALSE(features.UMA(1));
    EXPECT_FALSE(features.UMA(2));

    EXPECT_FALSE(features.CacheCoherentUMA(0));
    EXPECT_FALSE(features.CacheCoherentUMA(1));
    EXPECT_TRUE(features.CacheCoherentUMA(2));

    EXPECT_FALSE(features.IsolatedMMU(0));
    EXPECT_TRUE(features.IsolatedMMU(1));
    EXPECT_FALSE(features.IsolatedMMU(2));
}

// 2: Feature Levels
// Basic test with a high feature level
TEST_F(FeatureSupportTest, FeatureLevelBasic)
{
    device->m_FeatureLevel = D3D_FEATURE_LEVEL_12_2;
    
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.HighestFeatureLevel(), D3D_FEATURE_LEVEL_12_2);
}

// Test through all supported feature levels
TEST_F(FeatureSupportTest, FeatureLevelAll)
{
    std::vector<D3D_FEATURE_LEVEL> allLevels = {
        D3D_FEATURE_LEVEL_1_0_CORE,
        D3D_FEATURE_LEVEL_9_1,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_2
    };

    for (unsigned int i = 0; i < allLevels.size(); i++) {
        device->m_FeatureLevel = allLevels[i];
        CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
        EXPECT_EQ(features.HighestFeatureLevel(), allLevels[i]);
    }
}

// Test with a feature level higher than the current highest level
TEST_F(FeatureSupportTest, FeatureLevelHigher)
{
    device->m_FeatureLevel = (D3D_FEATURE_LEVEL)(D3D_FEATURE_LEVEL_12_2 + 1);
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.HighestFeatureLevel(), D3D_FEATURE_LEVEL_12_2);
}

// 3: Format Support
// Forward call to the old API. Basic correctness check
TEST_F(FeatureSupportTest, FormatSupportPositive)
{
    device->m_FormatSupport1 = D3D12_FORMAT_SUPPORT1_BUFFER | D3D12_FORMAT_SUPPORT1_TEXTURE3D | D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON | D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT;
    device->m_FormatSupport2 = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD | D3D12_FORMAT_SUPPORT2_TILED;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    D3D12_FORMAT_SUPPORT1 support1;
    D3D12_FORMAT_SUPPORT2 support2;

    HRESULT result = features.FormatSupport(DXGI_FORMAT_R32G32_UINT, support1, support2); // Some random input
    EXPECT_EQ(support1, D3D12_FORMAT_SUPPORT1_BUFFER | D3D12_FORMAT_SUPPORT1_TEXTURE3D | D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON | D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT);
    EXPECT_EQ(support2, D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD | D3D12_FORMAT_SUPPORT2_TILED);
    EXPECT_EQ(result, S_OK);
}

// Negative test
TEST_F(FeatureSupportTest, FormatSupportNegative)
{
    device->m_FormatSupport1 = D3D12_FORMAT_SUPPORT1_NONE;
    device->m_FormatSupport2 = D3D12_FORMAT_SUPPORT2_NONE;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    D3D12_FORMAT_SUPPORT1 support1;
    D3D12_FORMAT_SUPPORT2 support2;

    HRESULT result = features.FormatSupport(DXGI_FORMAT_UNKNOWN, support1, support2);
    EXPECT_EQ(support1, D3D12_FORMAT_SUPPORT1_NONE);
    EXPECT_EQ(support2, D3D12_FORMAT_SUPPORT2_NONE);
    EXPECT_EQ(result, E_FAIL);
}

// 4: Multisample Quality Levels
// Forwarding call. Check if the API received the correct information.
TEST_F(FeatureSupportTest, MultisampleQualityLevelsPositive)
{
    device->m_NumQualityLevels = 42; // Arbitrary return value
    
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    DXGI_FORMAT inFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
    UINT inSampleCount = 10;
    D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS inFlags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
    UINT NumQualityLevels;
    
    HRESULT result = features.MultisampleQualityLevels(inFormat, inSampleCount, inFlags, NumQualityLevels);

    EXPECT_EQ(device->m_FormatReceived, inFormat);
    EXPECT_EQ(device->m_SampleCountReceived, inSampleCount);
    EXPECT_EQ(device->m_MultisampleQualityLevelFlagsReceived, inFlags);
    EXPECT_EQ(result, S_OK);
    EXPECT_EQ(NumQualityLevels, 42);
}

// Test where the feature check fails
TEST_F(FeatureSupportTest, MultisampleQualityLevelsNegative)
{
    device->m_NumQualityLevels = 42;
    device->m_MultisampleQualityLevelsSucceed = false; // Simulate failure

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    DXGI_FORMAT inFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
    UINT inSampleCount = 6;
    D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS inFlags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
    UINT NumQualityLevels;
    
    HRESULT result = features.MultisampleQualityLevels(inFormat, inSampleCount, inFlags, NumQualityLevels);

    EXPECT_EQ(device->m_FormatReceived, inFormat);
    EXPECT_EQ(device->m_SampleCountReceived, inSampleCount);
    EXPECT_EQ(device->m_MultisampleQualityLevelFlagsReceived, inFlags);
    EXPECT_EQ(result, E_FAIL);
    EXPECT_EQ(NumQualityLevels, 0);
}

// 5: Format Info
// Forward call to old API. Basic sanity check
TEST_F(FeatureSupportTest, FormatInfoPositive)
{
    device->m_PlaneCount = 4;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    DXGI_FORMAT inFormat = DXGI_FORMAT_D32_FLOAT;
    UINT8 PlaneCount;
    HRESULT result = features.FormatInfo(inFormat, PlaneCount);

    EXPECT_EQ(PlaneCount, 4);
    EXPECT_EQ(result, S_OK);
    EXPECT_EQ(device->m_FormatReceived, inFormat);
}

// Test when feature check fails
TEST_F(FeatureSupportTest, FormatInfoNegative)
{
    device->m_PlaneCount = 6;
    device->m_DXGIFormatSupported = false;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    DXGI_FORMAT inFormat = DXGI_FORMAT_BC1_UNORM;
    UINT8 PlaneCount;
    HRESULT result = features.FormatInfo(inFormat, PlaneCount);

    EXPECT_EQ(result, E_INVALIDARG);
    //EXPECT_EQ(PlaneCount, 0); TODO: Check if PlaneCount should be set to 0
    EXPECT_EQ(device->m_FormatReceived, inFormat);
}

// 6: GPUVA Support
TEST_F(FeatureSupportTest, GPUVASupport)
{
    device->m_MaxGPUVirtualAddressBitsPerProcess = 16;
    device->m_MaxGPUVirtualAddressBitsPerResource = 12;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.MaxGPUVirtualAddressBitsPerProcess(), 16);
    EXPECT_EQ(features.MaxGPUVirtualAddressBitsPerResource(), 12);
}

// 8: Options1
// Basic tests
TEST_F(FeatureSupportTest, Options1Basic)
{
    device->m_WaveOpsSupported = true;
    device->m_WaveLaneCountMin = 2;
    device->m_WaveLaneCountMax = 4;
    device->m_TotalLaneCount = 8;
    device->m_ExpandedComputeResourceStates = true;
    device->m_Int64ShaderOpsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_TRUE(features.WaveOps());
    EXPECT_EQ(features.WaveLaneCountMin(), 2);
    EXPECT_EQ(features.WaveLaneCountMax(), 4);
    EXPECT_EQ(features.TotalLaneCount(), 8);
    EXPECT_TRUE(features.ExpandedComputeResourceStates());
    EXPECT_TRUE(features.Int64ShaderOps());
}

// Unavailable test
// Test where device does not support Options1
TEST_F(FeatureSupportTest, Options1Unavailable)
{
    device->m_Options1Available = false;
    device->m_WaveOpsSupported = true;
    device->m_WaveLaneCountMin = 2;
    device->m_WaveLaneCountMax = 4;
    device->m_TotalLaneCount = 8;
    device->m_ExpandedComputeResourceStates = true;
    device->m_Int64ShaderOpsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_FALSE(features.WaveOps());
    EXPECT_EQ(features.WaveLaneCountMin(), 0);
    EXPECT_EQ(features.WaveLaneCountMax(), 0);
    EXPECT_EQ(features.TotalLaneCount(), 0);
    EXPECT_FALSE(features.ExpandedComputeResourceStates());
    EXPECT_FALSE(features.Int64ShaderOps());
}

// 10: Protected Resource Session Support
// Basic test
TEST_F(FeatureSupportTest, ProtectedResourceSessionSupportBasic)
{
    device->m_ProtectedResourceSessionSupport[0] = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(0), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED);
}

// Negative test
TEST_F(FeatureSupportTest, ProtectedResourceSessionSupportNegative)
{
    device->m_ProtectedResourceSessionSupport[0] = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED;
    device->m_ContentProtectionSupported = false;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
}

// Multicore test
TEST_F(FeatureSupportTest, ProtectedResourceSessionSupportMulticore)
{
    device->SetNodeCount(4);
    device->m_ProtectedResourceSessionSupport =
    {
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE
    };

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(0), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(1), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(2), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(3), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
}

// Unavailable test
TEST_F(FeatureSupportTest, ProtectedResourceSessionSupportNotAvailable)
{
    device->m_ProtectedResourceSessionAvailable = false;
    device->m_ProtectedResourceSessionSupport[0] = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(0), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
}


// Multicore Unavailable test
TEST_F(FeatureSupportTest, ProtectedResourceSessionSupportNotAvailableMulticore)
{
    device->m_ProtectedResourceSessionAvailable = false;
    device->SetNodeCount(4);
    device->m_ProtectedResourceSessionSupport =
    {
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED,
        D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE
    };

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(0), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(1), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(2), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
    EXPECT_EQ(features.ProtectedResourceSessionSupport(3), D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE);
}

// 12: Root Signature
// Basic test (highest supported version in header)
TEST_F(FeatureSupportTest, RootSignatureBasic)
{
    device->m_RootSignatureHighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.HighestRootSignatureVersion(), D3D_ROOT_SIGNATURE_VERSION_1_1);
}

// Lower version test
TEST_F(FeatureSupportTest, RootSignatureLower)
{
    device->m_RootSignatureHighestVersion = D3D_ROOT_SIGNATURE_VERSION_1;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.HighestRootSignatureVersion(), D3D_ROOT_SIGNATURE_VERSION_1);
}

// Higher version test
TEST_F(FeatureSupportTest, RootSignatureHigher)
{
    device->m_RootSignatureHighestVersion = (D3D_ROOT_SIGNATURE_VERSION)(D3D_ROOT_SIGNATURE_VERSION_1_1 + 1);
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.HighestRootSignatureVersion(), D3D_ROOT_SIGNATURE_VERSION_1_1);
}

// Unavailable test
TEST_F(FeatureSupportTest, RootSignatureUnavailable)
{
    device->m_RootSignatureAvailable = false;
    device->m_RootSignatureHighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.HighestRootSignatureVersion(), 0);
}

// 18: Options2
// Basic test
TEST_F(FeatureSupportTest, D3D12Options2Basic)
{
    device->m_DepthBoundsTestSupport = true;
    device->m_ProgrammableSamplePositionsTier = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_TRUE(features.DepthBoundsTestSupported());
    EXPECT_EQ(features.ProgrammableSamplePositionsTier(), D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2);
}

// Unavailable test
TEST_F(FeatureSupportTest, D3D12Options2Unavailable)
{
    device->m_Options2Available = false;
    device->m_DepthBoundsTestSupport = true;
    device->m_ProgrammableSamplePositionsTier = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_FALSE(features.DepthBoundsTestSupported());
    EXPECT_EQ(features.ProgrammableSamplePositionsTier(), D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_NOT_SUPPORTED);
}

// 19: Shader Cache
// Basic test
TEST_F(FeatureSupportTest, ShaderCacheBasic)
{
    D3D12_SHADER_CACHE_SUPPORT_FLAGS outFlags = D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO 
        | D3D12_SHADER_CACHE_SUPPORT_LIBRARY
        | D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE
        | D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE
        | D3D12_SHADER_CACHE_SUPPORT_SHADER_CONTROL_CLEAR
        | D3D12_SHADER_CACHE_SUPPORT_SHADER_SESSION_DELETE;
    device->m_ShaderCacheSupportFlags = outFlags;
    
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ShaderCacheSupportFlags(), outFlags);
}

// Unavailable test
TEST_F(FeatureSupportTest, ShaderCacheUnavailable)
{
    device->m_ShaderCacheAvailable = false;
    D3D12_SHADER_CACHE_SUPPORT_FLAGS outFlags = D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO 
        | D3D12_SHADER_CACHE_SUPPORT_LIBRARY
        | D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE
        | D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE
        | D3D12_SHADER_CACHE_SUPPORT_SHADER_CONTROL_CLEAR
        | D3D12_SHADER_CACHE_SUPPORT_SHADER_SESSION_DELETE;
    device->m_ShaderCacheSupportFlags = outFlags;
    
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_EQ(features.GetStatus(), S_OK);
    EXPECT_EQ(features.ShaderCacheSupportFlags(), D3D12_SHADER_CACHE_SUPPORT_NONE);
}

// 20: Command Queue Priority
// Basic positive test
TEST_F(FeatureSupportTest, CommandQueuePriorityBasic)
{
    device->m_GlobalRealtimeCommandQueueSupport = true;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_TRUE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL));
    EXPECT_TRUE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_HIGH));
    EXPECT_TRUE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME));
}

// Negative tests
TEST_F(FeatureSupportTest, CommandQueuePriorityNegative)
{
    device->m_GlobalRealtimeCommandQueueSupport = false;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE, D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME)); // Global realtime not on
    EXPECT_FALSE(features.CommandQueuePrioritySupported((D3D12_COMMAND_LIST_TYPE)(D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE+1), D3D12_COMMAND_QUEUE_PRIORITY_NORMAL)); // Unknown command list type
    EXPECT_FALSE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_COMPUTE, (D3D12_COMMAND_QUEUE_PRIORITY)10)); // Unknown Priority level
}

// Unavailable test
TEST_F(FeatureSupportTest, CommandQueuePriorityUnavailable)
{
    device->m_CommandQueuePriorityAvailable = false;
    
    device->m_GlobalRealtimeCommandQueueSupport = true;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_NORMAL));
    EXPECT_FALSE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_HIGH));
    EXPECT_FALSE(features.CommandQueuePrioritySupported(D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME));
}

// 21: Options3
// Basic Test
TEST_F(FeatureSupportTest, Options3Basic)
{
    device->m_CopyQueueTimestampQueriesSupported = true;
    device->m_CastingFullyTypedFormatsSupported = true;
    device->m_GetCachedWriteBufferImmediateSupportFlags = D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT | D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE;
    device->m_ViewInstancingTier = D3D12_VIEW_INSTANCING_TIER_3;
    device->m_BarycentricsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_TRUE(features.CopyQueueTimestampQueriesSupported());
    EXPECT_TRUE(features.CastingFullyTypedFormatSupported());
    EXPECT_EQ(features.WriteBufferImmediateSupportFlags(), D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT | D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE);
    EXPECT_EQ(features.ViewInstancingTier(), D3D12_VIEW_INSTANCING_TIER_3);
    EXPECT_TRUE(features.BarycentricsSupported());
}

// Unavailable Test
TEST_F(FeatureSupportTest, Options3Unavailable)
{
    device->m_Options3Available = false;
    device->m_CopyQueueTimestampQueriesSupported = true;
    device->m_CastingFullyTypedFormatsSupported = true;
    device->m_GetCachedWriteBufferImmediateSupportFlags = D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT | D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE;
    device->m_ViewInstancingTier = D3D12_VIEW_INSTANCING_TIER_3;
    device->m_BarycentricsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_FALSE(features.CopyQueueTimestampQueriesSupported());
    EXPECT_FALSE(features.CastingFullyTypedFormatSupported());
    EXPECT_EQ(features.WriteBufferImmediateSupportFlags(), D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE);
    EXPECT_EQ(features.ViewInstancingTier(), D3D12_VIEW_INSTANCING_TIER_NOT_SUPPORTED);
    EXPECT_FALSE(features.BarycentricsSupported());
}

// 22: Existing Heaps
// Basic Test
TEST_F(FeatureSupportTest, ExistingHeapsBasic)
{
    device->m_ExistingHeapCaps = true;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_TRUE(features.ExistingHeapsSupported());
}

// Unavailable Test
TEST_F(FeatureSupportTest, ExistingHeapsUnavailable)
{
    device->m_ExistingHeapsAvailable = false;
    device->m_ExistingHeapCaps = true;
    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.ExistingHeapsSupported());
}

// 23: Options4
// Basic Test
TEST_F(FeatureSupportTest, Options4Basic)
{
    device->m_MSAA64KBAlignedTextureSupported = true;
    device->m_SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3; // Duplicate member
    device->m_Native16BitShaderOpsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_TRUE(features.MSAA64KBAlignedTextureSupported());
    EXPECT_EQ(features.SharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3);
    EXPECT_TRUE(features.Native16BitShaderOpsSupported());
}

// Unavailable Test
TEST_F(FeatureSupportTest, Options4Unavailable)
{
    device->m_Options4Available = false;
    device->m_MSAA64KBAlignedTextureSupported = true;
    device->m_SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3; // Duplicate member
    device->m_Native16BitShaderOpsSupported = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);
    EXPECT_FALSE(features.MSAA64KBAlignedTextureSupported());
    EXPECT_EQ(features.SharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0);
    EXPECT_FALSE(features.Native16BitShaderOpsSupported());
}

// 24: Serialization
// Basic Test
TEST_F(FeatureSupportTest, SerializationBasic)
{
    device->m_HeapSerializationTier[0] = D3D12_HEAP_SERIALIZATION_TIER_10;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.HeapSerializationTier(), D3D12_HEAP_SERIALIZATION_TIER_10);
}

// Multicore Test
TEST_F(FeatureSupportTest, SerializationMulticore)
{
    device->SetNodeCount(3);
    device->m_HeapSerializationTier = 
    {
        D3D12_HEAP_SERIALIZATION_TIER_10,
        D3D12_HEAP_SERIALIZATION_TIER_0,
        D3D12_HEAP_SERIALIZATION_TIER_10
    };

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.HeapSerializationTier(), D3D12_HEAP_SERIALIZATION_TIER_10);
    EXPECT_EQ(features.HeapSerializationTier(1), D3D12_HEAP_SERIALIZATION_TIER_0);
    EXPECT_EQ(features.HeapSerializationTier(2), D3D12_HEAP_SERIALIZATION_TIER_10);
}

// Unavailable Test
TEST_F(FeatureSupportTest, SerializationUnavailable)
{
    device->m_SerializationAvailable = false;
    device->SetNodeCount(3);
    device->m_HeapSerializationTier = 
    {
        D3D12_HEAP_SERIALIZATION_TIER_10,
        D3D12_HEAP_SERIALIZATION_TIER_0,
        D3D12_HEAP_SERIALIZATION_TIER_10
    };

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.HeapSerializationTier(), D3D12_HEAP_SERIALIZATION_TIER_0);
    EXPECT_EQ(features.HeapSerializationTier(1), D3D12_HEAP_SERIALIZATION_TIER_0);
    EXPECT_EQ(features.HeapSerializationTier(2), D3D12_HEAP_SERIALIZATION_TIER_0);
}

// 25: Cross Node
// Basic Test
TEST_F(FeatureSupportTest, CrossNodeBasic)
{
    device->m_CrossNodeSharingTier = D3D12_CROSS_NODE_SHARING_TIER_3; // Duplicated Cap
    device->m_AtomicShaderInstructions = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.CrossNodeSharingTier(), D3D12_CROSS_NODE_SHARING_TIER_3);
    EXPECT_TRUE(features.CrossNodeAtomicShaderInstructions());
}

// Unavailable Test
TEST_F(FeatureSupportTest, CrossNodeUnavailable)
{
    device->m_CrossNodeAvailable = false;
    device->m_CrossNodeSharingTier = D3D12_CROSS_NODE_SHARING_TIER_3; // Duplicated Cap
    device->m_AtomicShaderInstructions = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.CrossNodeSharingTier(), D3D12_CROSS_NODE_SHARING_TIER_3); // It is still correctly initialized by Options1
    EXPECT_FALSE(features.CrossNodeAtomicShaderInstructions());
}

// 27: Options5
// Basic Test
TEST_F(FeatureSupportTest, Options5Basic)
{
    device->m_RaytracingTier = D3D12_RAYTRACING_TIER_1_1;
    device->m_RenderPassesTier = D3D12_RENDER_PASS_TIER_2;
    device->m_SRVOnlyTiledResourceTier3 = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.RaytracingTier(), D3D12_RAYTRACING_TIER_1_1);
    EXPECT_EQ(features.RenderPassesTier(), D3D12_RENDER_PASS_TIER_2);
    EXPECT_TRUE(features.SRVOnlyTiledResourceTier3());
}

// Unavailable Test
TEST_F(FeatureSupportTest, Options5Unavailable)
{
    device->m_Options5Available = false;
    device->m_RaytracingTier = D3D12_RAYTRACING_TIER_1_1;
    device->m_RenderPassesTier = D3D12_RENDER_PASS_TIER_2;
    device->m_SRVOnlyTiledResourceTier3 = true;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_EQ(features.RaytracingTier(), D3D12_RAYTRACING_TIER_NOT_SUPPORTED);
    EXPECT_EQ(features.RenderPassesTier(), D3D12_RENDER_PASS_TIER_0);
    EXPECT_FALSE(features.SRVOnlyTiledResourceTier3());
}

// 28: Displayable
// Basic Test
TEST_F(FeatureSupportTest, DisplayableBasic)
{
    device->m_DisplayableTexture = true;
    device->m_SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_TRUE(features.DisplayableTexture());
    EXPECT_EQ(features.SharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3);
    EXPECT_EQ(features.DisplayableSharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3);
}

// Unavailable Test
TEST_F(FeatureSupportTest, DisplayableUnavailable)
{
    device->m_DisplayableAvailable = false;
    device->m_DisplayableTexture = true;
    device->m_SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3;

    CD3DX12FeatureSupport features = CD3DX12FeatureSupport::Create(device);

    EXPECT_FALSE(features.DisplayableTexture());
    EXPECT_EQ(features.SharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_3); // Still initialized by Options4
    EXPECT_EQ(features.DisplayableSharedResourceCompatibilityTier(), D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0); // This should have been affected
}

// TODO: Duplicate caps tests