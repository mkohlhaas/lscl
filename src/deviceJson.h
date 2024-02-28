#include "json_types.h"
#include <CL/cl.h>

json_object* AddDevices(json_object *Platform);
json_object* AddDevice(json_object *Devices);
void         AddDevice_Id                                  (json_object *Device, cl_device_id device);
void         AddDevice_PlatformId                          (json_object *Device, cl_device_id device);
void         AddDevice_Name                                (json_object *Device, cl_device_id device);
void         AddDevice_Vendor                              (json_object *Device, cl_device_id device);
void         AddDevice_Version                             (json_object *Device, cl_device_id device);
void         AddDevice_DriverVersion                       (json_object *Device, cl_device_id device);
void         AddDevice_Profile                             (json_object *Device, cl_device_id device);
void         AddDevice_Types                               (json_object *Device, cl_device_id device);
void         AddDevice_AtomicMemoryCapabilities            (json_object *Device, cl_device_id device);
void         AddDevice_AtomicFenceCapabilities             (json_object *Device, cl_device_id device);
void         AddDevice_AffinityDomain                      (json_object *Device, cl_device_id device);
void         AddDevice_AddressBits                         (json_object *Device, cl_device_id device);
void         AddDevice_Available                           (json_object *Device, cl_device_id device);
void         AddDevice_BuiltInKernels                      (json_object *Device, cl_device_id device);
void         AddDevice_CompilerAvailable                   (json_object *Device, cl_device_id device);
void         AddDevice_DoubleFPConfig                      (json_object *Device, cl_device_id device);
void         AddDevice_EndianLittle                        (json_object *Device, cl_device_id device);
void         AddDevice_EnqueueCapabilities                 (json_object *Device, cl_device_id device);
void         AddDevice_ErrorCorrectionSupport              (json_object *Device, cl_device_id device);
void         AddDevice_ExecCapabilities                    (json_object *Device, cl_device_id device);
void         AddDevice_Extensions                          (json_object *Device, cl_device_id device);
void         AddDevice_GenericAddressSpaceSupport          (json_object *Device, cl_device_id device);
void         AddDevice_GlobalMemSize                       (json_object *Device, cl_device_id device);
void         AddDevice_GlobalMemCacheSize                  (json_object *Device, cl_device_id device);
void         AddDevice_GlobalMemCachelineSize              (json_object *Device, cl_device_id device);
void         AddDevice_GlobalVariablePreferredTotalSize    (json_object *Device, cl_device_id device);
void         AddDevice_IlVersion                           (json_object *Device, cl_device_id device);
void         AddDevice_IlsWithVersion                      (json_object *Device, cl_device_id device);
void         AddDevice_ImageBaseAddressAlignment           (json_object *Device, cl_device_id device);
void         AddDevice_ImageMaxArraySize                   (json_object *Device, cl_device_id device);
void         AddDevice_ImageMaxBufferSize                  (json_object *Device, cl_device_id device);
void         AddDevice_ImagePitchAlignment                 (json_object *Device, cl_device_id device);
void         AddDevice_ImageSupport                        (json_object *Device, cl_device_id device);
void         AddDevice_Image2dMaxHeight                    (json_object *Device, cl_device_id device);
void         AddDevice_Image2dMaxWidth                     (json_object *Device, cl_device_id device);
void         AddDevice_Image3dMaxDepth                     (json_object *Device, cl_device_id device);
void         AddDevice_Image3dMaxHeight                    (json_object *Device, cl_device_id device);
void         AddDevice_Image3dmaxWidth                     (json_object *Device, cl_device_id device);
void         AddDevice_LatestConformanceVersionPassed      (json_object *Device, cl_device_id device);
void         AddDevice_LinkerAvailable                     (json_object *Device, cl_device_id device);
void         AddDevice_LocalMemSize                        (json_object *Device, cl_device_id device);
void         AddDevice_LocalMemType                        (json_object *Device, cl_device_id device);
void         AddDevice_MaxComputeUnits                     (json_object *Device, cl_device_id device);
void         AddDevice_MaxConstantArgs                     (json_object *Device, cl_device_id device);
void         AddDevice_MaxClockFrequency                   (json_object *Device, cl_device_id device);
void         AddDevice_MaxConstantBufferSize               (json_object *Device, cl_device_id device);
void         AddDevice_MaxConstantBufferSize               (json_object *Device, cl_device_id device);
void         AddDevice_MaxGlobalVariableSize               (json_object *Device, cl_device_id device);
void         AddDevice_MaxMemAllocSize                     (json_object *Device, cl_device_id device);
void         AddDevice_MaxNumSubGroups                     (json_object *Device, cl_device_id device);
void         AddDevice_MaxOnDeviceEvents                   (json_object *Device, cl_device_id device);
void         AddDevice_MaxOnDeviceQueues                   (json_object *Device, cl_device_id device);
void         AddDevice_MaxParameterSize                    (json_object *Device, cl_device_id device);
void         AddDevice_MaxPipeArgs                         (json_object *Device, cl_device_id device);
void         AddDevice_MaxReadImageArgs                    (json_object *Device, cl_device_id device);
void         AddDevice_MaxReadWriteImageArgs               (json_object *Device, cl_device_id device);
void         AddDevice_MaxSamplers                         (json_object *Device, cl_device_id device);
void         AddDevice_MaxWorkGroupSize                    (json_object *Device, cl_device_id device);
void         AddDevice_MaxWorkItemDimensions               (json_object *Device, cl_device_id device);
void         AddDevice_MaxComputeUnits                     (json_object *Device, cl_device_id device);
void         AddDevice_MaxWriteImageArgs                   (json_object *Device, cl_device_id device);
void         AddDevice_MemBaseAddrAlign                    (json_object *Device, cl_device_id device);
void         AddDevice_MemCacheType                        (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthChar               (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthDouble             (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthFloat              (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthHalf               (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthInt                (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthLong               (json_object *Device, cl_device_id device);
void         AddDevice_NativeVectorWidthShort              (json_object *Device, cl_device_id device);
void         AddDevice_NonUniformWorkGroupSupport          (json_object *Device, cl_device_id device);
void         AddDevice_NumericVersion                      (json_object *Device, cl_device_id device);
void         AddDevice_OpenClCAllVersions                  (json_object *Device, cl_device_id device);
void         AddDevice_OpenClCFeatures                     (json_object *Device, cl_device_id device);
void         AddDevice_ParentId                            (json_object *Device, cl_device_id device);
void         AddDevice_PartitionMaxSubDevices              (json_object *Device, cl_device_id device);
void         AddDevice_PartitionProperties                 (json_object *Device, cl_device_id device);
void         AddDevice_PartitionType                       (json_object *Device, cl_device_id device);
void         AddDevice_PipeMaxActiveReservations           (json_object *Device, cl_device_id device);
void         AddDevice_PipeMaxPacketSize                   (json_object *Device, cl_device_id device);
void         AddDevice_PipeSupport                         (json_object *Device, cl_device_id device);
void         AddDevice_PreferredGlobalAtomicAlignment      (json_object *Device, cl_device_id device);
void         AddDevice_PreferredInteropUserSync            (json_object *Device, cl_device_id device);
void         AddDevice_PreferredLocalAtomicAlignment       (json_object *Device, cl_device_id device);
void         AddDevice_PreferredPlatformAtomicAlignment    (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthChar            (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthDouble          (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthFloat           (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthHalf            (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthChar            (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthInt             (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthLong            (json_object *Device, cl_device_id device);
void         AddDevice_PreferredVectorWidthShort           (json_object *Device, cl_device_id device);
void         AddDevice_PreferredWorkGroupSizeMultiple      (json_object *Device, cl_device_id device);
void         AddDevice_PrintfBufferSize                    (json_object *Device, cl_device_id device);
void         AddDevice_ProfilingTimerResolution            (json_object *Device, cl_device_id device);
void         AddDevice_QueueOnDeviceMaxSize                (json_object *Device, cl_device_id device);
void         AddDevice_QueueOnDeviceProperties             (json_object *Device, cl_device_id device);
void         AddDevice_QueueOnHostProperties               (json_object *Device, cl_device_id device);
void         AddDevice_QueueOnDevicePreferredSize          (json_object *Device, cl_device_id device);
void         AddDevice_ReferenceCount                      (json_object *Device, cl_device_id device);
// TODO: void         AddDevice_SingleFPConfig                      (json_object *Device, cl_device_id device);
void         AddDevice_SubGroupIndependentForwardProgress  (json_object *Device, cl_device_id device);
void         AddDevice_SVMCapabilities                     (json_object *Device, cl_device_id device);
void         AddDevice_VendorID                            (json_object *Device, cl_device_id device);
void         AddDevice_WorkGroupCollectiveFunctionsSupport (json_object *Device, cl_device_id device);
