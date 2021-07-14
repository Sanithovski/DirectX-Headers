// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#ifndef DIRECTX_HEADERS_MOCK_DEVICE_HPP
#define DIRECTX_HEADERS_MOCK_DEVICE_HPP
#include <directx/d3d12.h>
#include <directx/dxcore.h>
#include <directx/d3dx12.h>
#include "dxguids/dxguids.h"

class MockDevice : public ID3D12Device
{
public:
    UINT STDMETHODCALLTYPE GetNodeCount() override 
    {
        return m_uNodeCount;
    }

    HRESULT STDMETHODCALLTYPE CreateCommandQueue(
            _In_  const D3D12_COMMAND_QUEUE_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppCommandQueue
    ) override 
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CreateCommandAllocator(
        _In_  D3D12_COMMAND_LIST_TYPE type,
        REFIID riid,
        _COM_Outptr_  void **ppCommandAllocator
    ) override
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CreateGraphicsPipelineState(
         _In_  const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
        REFIID riid,
        _COM_Outptr_  void **ppPipelineState
    ) override
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CreateComputePipelineState( 
        _In_  const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
        REFIID riid,
        _COM_Outptr_  void **ppPipelineState
    ) override
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CreateCommandList( 
        _In_  UINT nodeMask,
        _In_  D3D12_COMMAND_LIST_TYPE type,
        _In_  ID3D12CommandAllocator *pCommandAllocator,
        _In_opt_  ID3D12PipelineState *pInitialState,
        REFIID riid,
        _COM_Outptr_  void **ppCommandList
    ) override 
    {
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE CreateDescriptorHeap( 
        _In_  const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc,
        REFIID riid,
        _COM_Outptr_  void **ppvHeap
    ) override 
    {
        return S_OK;
    }

    virtual UINT STDMETHODCALLTYPE GetDescriptorHandleIncrementSize( 
        _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType
    ) override 
    {
        return 0;
    }
        
    virtual HRESULT STDMETHODCALLTYPE CreateRootSignature( 
        _In_  UINT nodeMask,
        _In_reads_(blobLengthInBytes)  const void *pBlobWithRootSignature,
        _In_  SIZE_T blobLengthInBytes,
        REFIID riid,
        _COM_Outptr_  void **ppvRootSignature
    ) override 
    {
        return S_OK;
    }
    
    virtual void STDMETHODCALLTYPE CreateConstantBufferView( 
        _In_opt_  const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor
    ) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CreateShaderResourceView( 
        _In_opt_  ID3D12Resource *pResource,
        _In_opt_  const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor
    ) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CreateUnorderedAccessView( 
        _In_opt_  ID3D12Resource *pResource,
        _In_opt_  ID3D12Resource *pCounterResource,
        _In_opt_  const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor
    ) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CreateRenderTargetView( 
        _In_opt_  ID3D12Resource *pResource,
        _In_opt_  const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor
    ) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CreateDepthStencilView( 
        _In_opt_  ID3D12Resource *pResource,
        _In_opt_  const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CreateSampler( 
        _In_  const D3D12_SAMPLER_DESC *pDesc,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CopyDescriptors( 
        _In_  UINT NumDestDescriptorRanges,
        _In_reads_(NumDestDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
        _In_reads_opt_(NumDestDescriptorRanges)  const UINT *pDestDescriptorRangeSizes,
        _In_  UINT NumSrcDescriptorRanges,
        _In_reads_(NumSrcDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
        _In_reads_opt_(NumSrcDescriptorRanges)  const UINT *pSrcDescriptorRangeSizes,
        _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) override 
    {
        return;
    }
    
    virtual void STDMETHODCALLTYPE CopyDescriptorsSimple( 
        _In_  UINT NumDescriptors,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
        _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) override 
    {
        return;
    }
    
    virtual D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo( 
        _In_  UINT visibleMask,
        _In_  UINT numResourceDescs,
        _In_reads_(numResourceDescs)  const D3D12_RESOURCE_DESC *pResourceDescs) override
    {
        D3D12_RESOURCE_ALLOCATION_INFO mockInfo = {};
        return mockInfo;
    }
    
    virtual D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE GetCustomHeapProperties( 
        _In_  UINT nodeMask,
        D3D12_HEAP_TYPE heapType) override 
    {
        D3D12_HEAP_PROPERTIES mockProps = {};
        return mockProps;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource( 
        _In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
        D3D12_HEAP_FLAGS HeapFlags,
        _In_  const D3D12_RESOURCE_DESC *pDesc,
        D3D12_RESOURCE_STATES InitialResourceState,
        _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
        REFIID riidResource,
        _COM_Outptr_opt_  void **ppvResource) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateHeap( 
        _In_  const D3D12_HEAP_DESC *pDesc,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvHeap) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreatePlacedResource( 
        _In_  ID3D12Heap *pHeap,
        UINT64 HeapOffset,
        _In_  const D3D12_RESOURCE_DESC *pDesc,
        D3D12_RESOURCE_STATES InitialState,
        _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvResource) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateReservedResource( 
        _In_  const D3D12_RESOURCE_DESC *pDesc,
        D3D12_RESOURCE_STATES InitialState,
        _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvResource) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateSharedHandle( 
        _In_  ID3D12DeviceChild *pObject,
        _In_opt_  const SECURITY_ATTRIBUTES *pAttributes,
        DWORD Access,
        _In_opt_  LPCWSTR Name,
        _Out_  HANDLE *pHandle) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE OpenSharedHandle( 
        _In_  HANDLE NTHandle,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvObj) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE OpenSharedHandleByName( 
        _In_  LPCWSTR Name,
        DWORD Access,
        /* [annotation][out] */ 
        _Out_  HANDLE *pNTHandle) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE MakeResident( 
        UINT NumObjects,
        _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects) override
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE Evict( 
        UINT NumObjects,
        _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateFence( 
        UINT64 InitialValue,
        D3D12_FENCE_FLAGS Flags,
        REFIID riid,
        _COM_Outptr_  void **ppFence) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason( void) override 
    {
        return S_OK;
    }
    
    virtual void STDMETHODCALLTYPE GetCopyableFootprints( 
        _In_  const D3D12_RESOURCE_DESC *pResourceDesc,
        _In_range_(0,D3D12_REQ_SUBRESOURCES)  UINT FirstSubresource,
        _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource)  UINT NumSubresources,
        UINT64 BaseOffset,
        _Out_writes_opt_(NumSubresources)  D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
        _Out_writes_opt_(NumSubresources)  UINT *pNumRows,
        _Out_writes_opt_(NumSubresources)  UINT64 *pRowSizeInBytes,
        _Out_opt_  UINT64 *pTotalBytes) override 
    {
        return;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateQueryHeap( 
        _In_  const D3D12_QUERY_HEAP_DESC *pDesc,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvHeap) override 
    {
        return S_OK;    
    }
    
    virtual HRESULT STDMETHODCALLTYPE SetStablePowerState( 
        BOOL Enable) override 
    {
        return S_OK;
    }
    
    virtual HRESULT STDMETHODCALLTYPE CreateCommandSignature( 
        _In_  const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
        _In_opt_  ID3D12RootSignature *pRootSignature,
        REFIID riid,
        _COM_Outptr_opt_  void **ppvCommandSignature) override
    {
        return S_OK;
    }
    
    virtual void STDMETHODCALLTYPE GetResourceTiling( 
        _In_  ID3D12Resource *pTiledResource,
        _Out_opt_  UINT *pNumTilesForEntireResource,
        _Out_opt_  D3D12_PACKED_MIP_INFO *pPackedMipDesc,
        _Out_opt_  D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
        _Inout_opt_  UINT *pNumSubresourceTilings,
        _In_  UINT FirstSubresourceTilingToGet,
        _Out_writes_(*pNumSubresourceTilings)  D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips) override 
    {
        return;
    }
    
    virtual LUID STDMETHODCALLTYPE GetAdapterLuid( void) override 
    {
        LUID mockLuid = {};
        return mockLuid;
    }

    // Major function we need to work with
    virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport( 
        D3D12_FEATURE Feature,
        _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
        UINT FeatureSupportDataSize
    ) override 
    {
        switch( Feature )
        {
            case D3D12_FEATURE_D3D12_OPTIONS:
            {
                D3D12_FEATURE_DATA_D3D12_OPTIONS* pD3D12Options = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS))
                {
                    return E_INVALIDARG;
                }
                pD3D12Options->DoublePrecisionFloatShaderOps       = DriverSupportsDoublePrecisionFloatShaderOps();
                pD3D12Options->OutputMergerLogicOp                 = LogicOpSupported();
                pD3D12Options->MinPrecisionSupport                 = ((MinPrecision() & D3D11_DDI_SHADER_MIN_PRECISION_10_BIT) ? D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT : D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE) |
                                                                    ((MinPrecision() & D3D11_DDI_SHADER_MIN_PRECISION_16_BIT) ? D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT : D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE);
                pD3D12Options->TiledResourcesTier                  = TiledResourcesTier();
                pD3D12Options->ResourceBindingTier                 = ResourceBindingTier();
                pD3D12Options->PSSpecifiedStencilRefSupported      = PSSpecifiedStencilRefSupported();
                pD3D12Options->TypedUAVLoadAdditionalFormats       = TypedUAVLoadAdditionalFormats();
                pD3D12Options->ROVsSupported                       = ROVsSupported();
                pD3D12Options->ConservativeRasterizationTier       = ConservativeRasterizationTier();
                pD3D12Options->MaxGPUVirtualAddressBitsPerResource = MaxGPUVirtualAddressBitsPerResource();
                pD3D12Options->StandardSwizzle64KBSupported        = m_ValidationInfo.m_bSupportsStandardSwizzle ? TRUE : FALSE;
    #ifdef DX_ASTC_PROTOTYPE_ENABLED
                pD3D12Options->ASTCProfile                         = ASTCProfile();
    #endif
                pD3D12Options->CrossNodeSharingTier                = CrossNodeSharingTier();
                pD3D12Options->CrossAdapterRowMajorTextureSupported = m_ValidationInfo.m_bSupportsRowMajorTexture ? TRUE : FALSE;
                pD3D12Options->VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation = VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation();
                pD3D12Options->ResourceHeapTier                    = ResourceHeapTier();
            } return S_OK;

        case D3D12_FEATURE_D3D12_OPTIONS1:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS1* pD3D12Options1 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS1*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1))
            {
                return E_INVALIDARG;
            }
            pD3D12Options1->WaveOps = WaveOpsSupported();
            pD3D12Options1->WaveLaneCountMin = WaveLaneCountMin();
            pD3D12Options1->WaveLaneCountMax = WaveLaneCountMax();
            pD3D12Options1->TotalLaneCount = TotalLaneCount();
            pD3D12Options1->ExpandedComputeResourceStates = TRUE; // RS1 version check
            pD3D12Options1->Int64ShaderOps = Int64ShaderOpsSupported();
        } return S_OK;

        case D3D12_FEATURE_D3D12_OPTIONS2:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS2* pD3D12Options2 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS2*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS2))
            {
                return E_INVALIDARG;
            }
            pD3D12Options2->DepthBoundsTestSupported = DepthBoundsTestSupport();
            pD3D12Options2->ProgrammableSamplePositionsTier = ProgrammableSamplePositionsTier();
        } return S_OK;

        case D3D12_FEATURE_ROOT_SIGNATURE:
        {
            D3D12_FEATURE_DATA_ROOT_SIGNATURE* pRootSig = static_cast<D3D12_FEATURE_DATA_ROOT_SIGNATURE*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE))
            {
                return E_INVALIDARG;
            }
            switch (pRootSig->HighestVersion)
            {
            case D3D_ROOT_SIGNATURE_VERSION_1_0:
            case D3D_ROOT_SIGNATURE_VERSION_1_1:
                break;
            default:
                return E_INVALIDARG;
            }
            pRootSig->HighestVersion = min(pRootSig->HighestVersion,D3D_ROOT_SIGNATURE_VERSION_1_1); 
                                        // Even if old driver, runtime can still convert from 1_1 to 1_0 without behavior change
                                        // (only loses optimizations from new flags, which old driver's can't do anyway)
        } return S_OK;
        case D3D12_FEATURE_ARCHITECTURE:
            {
                D3D12_FEATURE_DATA_ARCHITECTURE* pFData =
                    static_cast< D3D12_FEATURE_DATA_ARCHITECTURE* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                D3D12_FEATURE_DATA_ARCHITECTURE1 CurFData;
                CurFData.NodeIndex = pFData->NodeIndex;
                
                HRESULT hr;
                if (FAILED( hr = CheckFeatureSupport( D3D12_FEATURE_ARCHITECTURE1, &CurFData, sizeof( CurFData ) ) ))
                {
                    return hr;
                }

                pFData->TileBasedRenderer = CurFData.TileBasedRenderer;
                pFData->UMA = CurFData.UMA;
                pFData->CacheCoherentUMA = CurFData.CacheCoherentUMA;
            } return S_OK;
        case D3D12_FEATURE_ARCHITECTURE1:
            {
                D3D12_FEATURE_DATA_ARCHITECTURE1* pFData =
                    static_cast< D3D12_FEATURE_DATA_ARCHITECTURE1* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                try
                {
                    const UINT APINodeIndex = ConvertNodeIndexForCaps(pFData->NodeIndex); // throw( _com_error )

                    pFData->TileBasedRenderer = m_ArchitectureInfo.TileBasedDeferredRenderer;

                    const D3D12INT_MEMORY_ARCHITECTURE& MemArch = MemoryArchitecture(APINodeIndex);
                    pFData->UMA = MemArch.UMA;
                    pFData->CacheCoherentUMA = MemArch.CacheCoherentUMA;
                    pFData->IsolatedMMU = MemArch.IsolatedMMU;
                }
                catch( _com_error& hrEx )
                {
                    return hrEx.Error();
                }
            } return S_OK;

        case D3D12_FEATURE_FEATURE_LEVELS:
            {
                D3D12_FEATURE_DATA_FEATURE_LEVELS* pFData =
                    static_cast< D3D12_FEATURE_DATA_FEATURE_LEVELS* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                if (pFData->NumFeatureLevels == 0 || pFData->pFeatureLevelsRequested == nullptr)
                {
                    return E_INVALIDARG;
                }

                pFData->MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL(0);
                for (UINT i = 0; i < pFData->NumFeatureLevels; ++i)
                {
                    if (pFData->pFeatureLevelsRequested[i] <= FeatureLevel() &&
                        pFData->pFeatureLevelsRequested[i] > pFData->MaxSupportedFeatureLevel)
                    {
                        pFData->MaxSupportedFeatureLevel = pFData->pFeatureLevelsRequested[i];
                    }
                }
                return pFData->MaxSupportedFeatureLevel == D3D_FEATURE_LEVEL(0) ?
                    DXGI_ERROR_UNSUPPORTED : S_OK;
            }

        case D3D12_FEATURE_FORMAT_SUPPORT:
            {
                D3D12_FEATURE_DATA_FORMAT_SUPPORT* pFData = 
                    static_cast< D3D12_FEATURE_DATA_FORMAT_SUPPORT* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                if (!CheckFormatSupportImpl(pFData->Format, pFData->Support1, pFData->Support2))
                {
                    return E_FAIL;
                }
            } return S_OK;

        case D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS:
            {
                D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS* pFData =
                    static_cast< D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                if (!CheckMultisampleQualityLevelsImpl(pFData->Format, pFData->SampleCount,
                                                    pFData->Flags, &pFData->NumQualityLevels))
                {
                    return E_FAIL;
                }
            } return S_OK;
        case D3D12_FEATURE_FORMAT_INFO:
            {
                D3D12_FEATURE_DATA_FORMAT_INFO* pFData = 
                    static_cast< D3D12_FEATURE_DATA_FORMAT_INFO* > ( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }

                if (!CD3D11FormatHelper::APIFormatExists(pFData->Format, FeatureLevel(), m_ValidationInfo.m_ExtendedFormatSupport))
                {
                    return E_INVALIDARG;
                }

                pFData->PlaneCount = CD3D11FormatHelper::GetPlaneCount(pFData->Format);

            } return S_OK;
        case D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT:
            {
                D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT* pFData =
                    static_cast< D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT* >( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pFData ))
                {
                    return E_INVALIDARG;
                }
                *pFData = m_ValidationInfo.m_GPUVACaps;
            } return S_OK;
    #ifdef DX_HARDWARE_JPEG_PROTOTYPE_ENABLED
        case D3D12_FEATURE_JPEG_OPTIONS:
            {
                D3D12_FEATURE_DATA_JPEG_OPTIONS* pJpegOptions = 
                    static_cast<D3D12_FEATURE_DATA_JPEG_OPTIONS*>( pFeatureSupportData );
                if (FeatureSupportDataSize != sizeof( *pJpegOptions ))
                {
                    return E_INVALIDARG;
                }

                *pJpegOptions = D3D12JpegOptions();
            } return S_OK;
    #endif // DX_HARDWARE_JPEG_PROTOTYPE_ENABLED
        case D3D12_FEATURE_SHADER_MODEL:
            {
                D3D12_FEATURE_DATA_SHADER_MODEL* pSM =
                    static_cast<D3D12_FEATURE_DATA_SHADER_MODEL*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pSM))
                {
                    return E_INVALIDARG;
                }
                switch (pSM->HighestShaderModel)
                {
                case D3D_SHADER_MODEL_5_1:
                case D3D_SHADER_MODEL_6_0:
                case D3D_SHADER_MODEL_6_1:
                case D3D_SHADER_MODEL_6_2:
                case D3D_SHADER_MODEL_6_3:
                case D3D_SHADER_MODEL_6_4:
                case D3D_SHADER_MODEL_6_5:
                case D3D_SHADER_MODEL_6_6:
                case D3D_SHADER_MODEL_6_7:
                    break;
                default:
                    return E_INVALIDARG;
                }
                pSM->HighestShaderModel = min(pSM->HighestShaderModel,HighestSupportedShaderModel());
            } return S_OK;
        case D3D12_FEATURE_SUPPORTED_PSO_FLAGS:
            {
                D3D12_FEATURE_DATA_SUPPORTED_PSO_FLAGS* pFlags =
                    static_cast<D3D12_FEATURE_DATA_SUPPORTED_PSO_FLAGS*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pFlags))
                {
                    return E_INVALIDARG;
                }
                if (pFlags->SupportedFlags & ~D3D12_PIPELINE_STATE_FLAG_MASK_WARP)
                {
                    return E_INVALIDARG;
                }
                pFlags->SupportedFlags &= GetValidPipelineStateFlags();
            } return S_OK;
        case D3D12_FEATURE_SHADER_CACHE:
            {
                D3D12_FEATURE_DATA_SHADER_CACHE* pFlags =
                    static_cast<D3D12_FEATURE_DATA_SHADER_CACHE*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pFlags))
                {
                    return E_INVALIDARG;
                }
                pFlags->SupportFlags = D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO;
                if (IsD3D12DDIVersionOrLater(e_DDI_12_1_0010))
                {
                    pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_LIBRARY;
                }
                if (m_pDefShaderCacheSession)
                {
                    pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE;
                    if (m_pDefShaderCacheSession->ResolvedMode() == D3D12_SHADER_CACHE_MODE_DISK)
                    {
                        pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE;
                    }
                }
                if (m_D3D12Options.DriverManagedShaderCachePresent)
                {
                    pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE;
                }
                if (IsShaderCache_ClearPresent())
                {
                    pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_SHADER_CONTROL_CLEAR;
                }
                if (IsShaderCache_DeletePresent())
                {
                    pFlags->SupportFlags |= D3D12_SHADER_CACHE_SUPPORT_SHADER_SESSION_DELETE;
                }
            } return S_OK;
        case D3D12_FEATURE_COMMAND_QUEUE_PRIORITY:
            {
                D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY* pFlags =
                    static_cast<D3D12_FEATURE_DATA_COMMAND_QUEUE_PRIORITY*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pFlags))
                {
                    return E_INVALIDARG;
                }

                if (pFlags->CommandListType >= D3D12_COMMAND_LIST_TYPE_MAX_VALID)
                {
                    return E_INVALIDARG;
                }

                if (pFlags->Priority == D3D12_COMMAND_QUEUE_PRIORITY_NORMAL || pFlags->Priority == D3D12_COMMAND_QUEUE_PRIORITY_HIGH)
                {
                    pFlags->PriorityForTypeIsSupported = TRUE;
                }
                else if (pFlags->Priority == D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME)
                {
                    bool bUmdBasedGlobalPriorityAvailable = false;

                    CheckForGlobalRealtimeCommandQueueSupport(pFlags->CommandListType, bUmdBasedGlobalPriorityAvailable);

                    pFlags->PriorityForTypeIsSupported = (m_bDxgkBasedGlobalPriorityAvailable || bUmdBasedGlobalPriorityAvailable);
                }
                else
                {
                    return E_INVALIDARG;
                }

            } return S_OK;
        case D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT:
            {
                D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT* pProtectedResourceSessionSupport =
                    static_cast<D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_SUPPORT*>(pFeatureSupportData);
                if (   FeatureSupportDataSize != sizeof(*pProtectedResourceSessionSupport)
                    || pProtectedResourceSessionSupport->NodeIndex >= GetNodeCount())
                {
                    return E_INVALIDARG;
                }

                pProtectedResourceSessionSupport->Support = EnsureContentProtectionSupported() ?
                    m_PerNodeContentProtectionResourceCaps[pProtectedResourceSessionSupport->NodeIndex].Support
                    : D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE;

            } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS3:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS3* pD3D12Options3 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS3*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS3))
            {
                return E_INVALIDARG;
            }
            pD3D12Options3->CopyQueueTimestampQueriesSupported = m_D3D12Options.CopyQueueTimestampQueriesSupported;
            pD3D12Options3->CastingFullyTypedFormatSupported = CastingFullyTypedFormatsSupported();
            pD3D12Options3->WriteBufferImmediateSupportFlags = GetCachedWriteBufferImmediateSupportFlags();
            pD3D12Options3->ViewInstancingTier = ViewInstancingTier();
            pD3D12Options3->BarycentricsSupported = BarycentricsSupported();

        } return S_OK;
        case D3D12_FEATURE_EXISTING_HEAPS:
            {
                auto* pSupport = static_cast<D3D12_FEATURE_DATA_EXISTING_HEAPS*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pSupport))
                {
                    return E_INVALIDARG;
                }

                *pSupport = m_ValidationInfo.m_ExistingHeapCaps;
            } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS4:
            {
                auto* pD3D12Options4 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS4*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pD3D12Options4))
                {
                    return E_INVALIDARG;
                }

                // Reserved Buffer Placement was cut, except for 64KB Aligned MSAA Textures
                pD3D12Options4->MSAA64KBAlignedTextureSupported = m_D3D12Options.ReservedBufferPlacementSupported;
                if (m_ValidationInfo.m_ExtendedFormatSupport >= CD3D11FormatHelper::e_Vibranium_FormatFeatures)
                {
                    pD3D12Options4->SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2;
                }
                else if (m_ValidationInfo.m_ExtendedFormatSupport >= CD3D11FormatHelper::e_RS4_FormatFeatures)
                {
                    pD3D12Options4->SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1;
                }
                else
                {
                    pD3D12Options4->SharedResourceCompatibilityTier = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0;
                }
                pD3D12Options4->Native16BitShaderOpsSupported = m_ShaderCaps.Native16BitOps;
            } return S_OK;
        case D3D12_FEATURE_SERIALIZATION:
            {
                auto* pSerialization = static_cast<D3D12_FEATURE_DATA_SERIALIZATION*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pSerialization))
                {
                    return E_INVALIDARG;
                }

                try
                {
                    const UINT APINodeIndex = ConvertNodeIndexForCaps(pSerialization->NodeIndex); // throw( _com_error )
                    const D3D12INT_MEMORY_ARCHITECTURE& MemArch = MemoryArchitecture(APINodeIndex);
                    pSerialization->HeapSerializationTier = MemArch.HeapSerializationTier;
                }
                catch( _com_error& hrEx )
                {
                    return hrEx.Error();
                }
            } return S_OK;
        case D3D12_FEATURE_CROSS_NODE:
            {
                auto* pCrossNode = static_cast<D3D12_FEATURE_DATA_CROSS_NODE*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pCrossNode))
                {
                    return E_INVALIDARG;
                }

                pCrossNode->SharingTier = CrossNodeSharingTier();
                pCrossNode->AtomicShaderInstructions = (m_ValidationInfo.m_bCrossNodeAtomicShaderInstructions ? TRUE : FALSE);
            } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS5:
            {
                auto* pD3D12Options5 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS5*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pD3D12Options5))
                {
                    return E_INVALIDARG;
                }

                *pD3D12Options5 = m_ValidationInfo.m_Options5;
            } return S_OK;
        case D3D12_FEATURE_DISPLAYABLE:
            {
                auto* pD3D12Displayable = static_cast<D3D12_FEATURE_DATA_DISPLAYABLE*>(pFeatureSupportData);
                if (FeatureSupportDataSize != sizeof(*pD3D12Displayable)) // Feature_D3D1XDisplayable
                {
                    return E_INVALIDARG;
                }

                pD3D12Displayable->DisplayableTexture = (m_ValidationInfo.m_bSupportsDisplayable ? TRUE : FALSE);
                pD3D12Displayable->SharedResourceCompatibilityTier = m_ValidationInfo.m_Options4.SharedResourceCompatibilityTier;
            } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS6:
        {
            auto* pD3D12Options6 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS6*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options6))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options6 = m_ValidationInfo.m_Options6;
        } return S_OK;
        case D3D12_FEATURE_QUERY_META_COMMAND:
        {
            if (IsD3D12DDIVersionOrLater(e_DDI_12_6_0061))
            {
                if (FeatureSupportDataSize != sizeof(D3D12_FEATURE_DATA_QUERY_META_COMMAND))
                {
                    return E_INVALIDARG;
                }

                auto* pQueryData = static_cast<D3D12_FEATURE_DATA_QUERY_META_COMMAND*>(pFeatureSupportData);

                // Copy public API data to the DDI version, which does not have a NodeMask.
                D3D12DDICAPS_QUERY_META_COMMAND_CAPS_0061 QueryDataInternal = {};
                QueryDataInternal.CommandId = pQueryData->CommandId;
                QueryDataInternal.pQueryInputData = pQueryData->pQueryInputData;
                QueryDataInternal.QueryInputDataSizeInBytes = pQueryData->QueryInputDataSizeInBytes;
                QueryDataInternal.pQueryOutputData = pQueryData->pQueryOutputData;
                QueryDataInternal.QueryOutputDataSizeInBytes = pQueryData->QueryOutputDataSizeInBytes;

                if (!DeveloperModeEnabled())
                {
                    if (!m_ApprovedMetaCommands.IsMetaCommandSupported(pQueryData->CommandId, m_eDDI))
                    {
                        GetOutermostDevicePrivate()->ReportRetailValidationError(D3D12_MESSAGE_ID_META_COMMAND_ID_INVALID, 0);
                        return E_INVALIDARG;
                    }
                }

                try
                {
                    // TranslateNodeMask and NodeMaskToIndex used instead of GetDDINodeIndex to enable error report.
                    UINT DDIMask = TranslateNodeMask(pQueryData->NodeMask, TranslateNodeMaskFlags::RequireSingleBit);
                    auto nodeIndex = NodeMaskToIndex(DDIMask);
                    
                    return GetCaps(D3D12DDICAPS_TYPE_QUERY_META_COMMAND_CAPS_0061,
                        &nodeIndex,
                        &QueryDataInternal,
                        sizeof(QueryDataInternal));
                }
                catch( _com_error& hrEx)
                {
                    return hrEx.Error();
                }
            }
            else
            {
                return E_INVALIDARG;
            }
        } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS7:
        {
            auto* pD3D12Options7 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS7*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options7))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options7 = m_ValidationInfo.m_Options7;
        } return S_OK;
        case D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT:
            {
                auto* pProtectedResourceSessionTypesCount =
                    static_cast<D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPE_COUNT*>(pFeatureSupportData);
                if (   FeatureSupportDataSize != sizeof(*pProtectedResourceSessionTypesCount)
                    || pProtectedResourceSessionTypesCount->NodeIndex >= GetNodeCount())
                {
                    return E_INVALIDARG;
                }

                pProtectedResourceSessionTypesCount->Count = EnsureContentProtectionSupported() ?
                    static_cast<UINT>(m_PerNodeContentProtectionResourceCaps[pProtectedResourceSessionTypesCount->NodeIndex].ProtectionTypes.size())
                    : 0;

            } return S_OK;
        case D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES:
            {
                auto* pProtectedResourceSessionTypes =
                    static_cast<D3D12_FEATURE_DATA_PROTECTED_RESOURCE_SESSION_TYPES*>(pFeatureSupportData);
                if (   FeatureSupportDataSize != sizeof(*pProtectedResourceSessionTypes)
                    || pProtectedResourceSessionTypes->NodeIndex >= GetNodeCount())
                {
                    return E_INVALIDARG;
                }

                UINT ExpectedCount = EnsureContentProtectionSupported() ?
                    static_cast<UINT>(m_PerNodeContentProtectionResourceCaps[pProtectedResourceSessionTypes->NodeIndex].ProtectionTypes.size())
                    : 0;

                if (pProtectedResourceSessionTypes->Count != ExpectedCount)
                {
                    return E_INVALIDARG;
                }

                if (ExpectedCount > 0)
                {
                    memcpy(pProtectedResourceSessionTypes->pTypes, m_PerNodeContentProtectionResourceCaps[pProtectedResourceSessionTypes->NodeIndex].ProtectionTypes.data(), ExpectedCount * sizeof(*pProtectedResourceSessionTypes->pTypes));
                }

            } return S_OK;
        case D3D12_FEATURE_TRACKED_WORKLOAD:
        {
            auto* pTrackedWorkload = static_cast<D3D12_FEATURE_DATA_TRACKED_WORKLOAD*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pTrackedWorkload))
            {
                return E_INVALIDARG;
            }
            if (pTrackedWorkload->CommandListType >= D3D12_COMMAND_LIST_TYPE_MAX_VALID)
            {
                return E_INVALIDARG;
            }
            if (!Feature_TrackedWorkload::IsEnabled())
            {
                return E_INVALIDARG;
            }
            return CTrackedWorkload::GetTrackedWorkloadSupport(GetDXGIDevice(), m_APIToDDINodeMap[pTrackedWorkload->NodeIndex], pTrackedWorkload->CommandListType, pTrackedWorkload->Support);
        } 
        case D3D12_FEATURE_D3D12_OPTIONS8:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS8 *pD3D12Options8 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS8*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options8))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options8 = m_ValidationInfo.m_Options8;
        } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS9:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS9 *pD3D12Options9 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS9*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options9))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options9 = m_ValidationInfo.m_Options9;
        } return S_OK;
        case D3D12_FEATURE_D3D12_OPTIONS10:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS10* pD3D12Options10 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS10*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options10))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options10 = m_ValidationInfo.m_Options10;
        } return S_OK;
        case D3D12_FEATURE_WAVE_MMA:
        {
            D3D12_FEATURE_DATA_WAVE_MMA *pWaveMMA = static_cast<D3D12_FEATURE_DATA_WAVE_MMA*>(pFeatureSupportData);
            bool bError = false;
            switch(pWaveMMA->InputDataType)
            {
            case D3D12_WAVE_MMA_INPUT_DATATYPE_BYTE:
            case D3D12_WAVE_MMA_INPUT_DATATYPE_FLOAT16:
            case D3D12_WAVE_MMA_INPUT_DATATYPE_FLOAT:
                break;
            default:
                bError = true;
            }
            switch(pWaveMMA->M)
            {
            case D3D12_WAVE_MMA_DIMENSION_16:
            case D3D12_WAVE_MMA_DIMENSION_64:
                break;
            default:
                bError = true;
            }
            switch(pWaveMMA->N)
            {
            case D3D12_WAVE_MMA_DIMENSION_16:
            case D3D12_WAVE_MMA_DIMENSION_64:
                break;
            default:
                bError = true;
            }
            if(bError)
            {
                pWaveMMA->Supported = FALSE;
                pWaveMMA->K = 0;
                pWaveMMA->AccumDataTypes = D3D12_WAVE_MMA_ACCUM_DATATYPE_NONE;
                pWaveMMA->RequiredWaveLaneCountMin = 0;
                pWaveMMA->RequiredWaveLaneCountMax = 0;
                return E_INVALIDARG;
            }
            // DDI is surfaced directly through API
            D3D12DDI_WAVE_MMA_DATA_LATEST *pWaveMMADDI = reinterpret_cast<D3D12DDI_WAVE_MMA_DATA_LATEST*>(pWaveMMA);
            // Need to make an immediate call to get the caps since this is an in/out query.
            return VersionedGetWaveMMAOptions(pWaveMMADDI); 
        }
        case D3D12_FEATURE_D3D12_OPTIONS11:
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS11* pD3D12Options11 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS11*>(pFeatureSupportData);
            if (FeatureSupportDataSize != sizeof(*pD3D12Options11))
            {
                return E_INVALIDARG;
            }

            *pD3D12Options11 = m_ValidationInfo.m_Options11;
        } return S_OK;
        default:
            return E_INVALIDARG;
        }
    }

public: // For simplicity, allow setting the internal state values for this mock class
    // 0: Options
    BOOL m_DoublePrecisionFloatShaderOps = false;
    BOOL m_OutputMergerLogicOp = false;
    D3D12_SHADER_MIN_PRECISION_SUPPORT m_ShaderMinPrecisionSupport10Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE;
    D3D12_SHADER_MIN_PRECISION_SUPPORT m_ShaderMinPrecisionSupport16Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE;
    D3D12_TILED_RESOURCES_TIER m_TiledResourceTier = D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED;
    D3D12_RESOURCE_BINDING_TIER m_ResourceBindingTier = (D3D12_RESOURCE_BINDING_TIER)0;
    BOOL m_PSSpecifiedStencilRefSupported = false;
    BOOL m_TypedUAVLoadAdditionalFormats = false;
    BOOL m_ROVsSupported = false;
    D3D12_CONSERVATIVE_RASTERIZATION_TIER m_ConservativeRasterizationTier = D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED;
    UINT m_MaxGPUVirtualAddressBitsPerResource = 0;
    BOOL m_StandardSwizzle64KBSupported = false;
    D3D12_CROSS_NODE_SHARING_TIER m_CrossNodeSharingTier = D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED;
    BOOL m_CrossAdapterRowMajorTextureSupported = false;
    BOOL m_VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation = false;
    D3D12_RESOURCE_HEAP_TIER m_ResourceHeapTier = (D3D12_RESOURCE_HEAP_TIER)0;
private:
    UINT m_uNodeCount;
};

#endif