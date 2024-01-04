#include "device.h"
#include "deviceCL.h"
#include "json_object.h"
#include "version.h"
#include <stdio.h>

json_object *AddDevices(json_object *Platform) {

  json_object *Devices = json_object_new_array();
  json_object_object_add(Platform, "devices", Devices);
  return Devices;
}

json_object *AddDevice(json_object *Devices) {
  json_object *Device = json_object_new_object();
  json_object_array_add(Devices, Device);
  return Device;
}

void AddDevice_Id(json_object *Device, cl_device_id device) { json_object_object_add(Device, "id", json_object_new_uint64((intptr_t)device)); }

void AddDevice_PlatformId(json_object *Device, cl_device_id device) {
  cl_platform_id platformID = devicePlatform(device);
  json_object_object_add(Device, "platform_id", json_object_new_uint64((intptr_t)platformID));
}

void AddDevice_Name(json_object *Device, cl_device_id device) {
  char *name = deviceName(device);
  json_object_object_add(Device, "name", json_object_new_string(name));
}

void AddDevice_Vendor(json_object *Device, cl_device_id device) {
  char *vendor = deviceVendor(device);
  json_object_object_add(Device, "vendor", json_object_new_string(vendor));
}

void AddDevice_Version(json_object *Device, cl_device_id device) {
  char *version = deviceVersion(device);
  json_object_object_add(Device, "version", json_object_new_string(version));
}

void AddDevice_DriverVersion(json_object *Device, cl_device_id device) {
  char *driverVersion = deviceDriverVersion(device);
  json_object_object_add(Device, "driver_version", json_object_new_string(driverVersion));
}

void AddDevice_Profile(json_object *Device, cl_device_id device) {
  char *profile = deviceProfile(device);
  json_object_object_add(Device, "profile", json_object_new_string(profile));
}

void AddDevice_Types(json_object *Device, cl_device_id device) {
  json_object *Types = json_object_new_array();
  GArray *types = deviceTypes(device);
  for (int i = 0; i < types->len; i++) {
    json_object_array_add(Types, json_object_new_string(g_array_index(types, char *, i)));
  }
  json_object_object_add(Device, "types", Types);
}

void AddDevice_AtomicMemoryCapabilities(json_object *Device, cl_device_id device) {
  getProperties(deviceAtomicMemoryCapabilities(device), "atomic_memory_capabilities", Device);
}

void AddDevice_AtomicFenceCapabilities(json_object *Device, cl_device_id device) {
  getProperties(deviceAtomicFenceCapabilities(device), "atomic_fence_capabilities", Device);
}

void AddDevice_AffinityDomain(json_object *Device, cl_device_id device) {
  getProperties(deviceAffinityDomain(device), "affinity_domain", Device);
}

void AddDevice_AddressBits(json_object *Device, cl_device_id device) {
  cl_uint addressBits = deviceAddressBits(device);
  json_object_object_add(Device, "address_bits", json_object_new_uint64(addressBits));
}

void AddDevice_Available(json_object *Device, cl_device_id device) {
  cl_uint available = deviceAvailable(device);
  json_object_object_add(Device, "available", json_object_new_boolean(available));
}

void AddDevice_BuiltInKernels(json_object *Device, cl_device_id device) {
  size_t numBuiltInKernels;
  cl_name_version *builtInKernels = deviceBuiltInKernels(device, &numBuiltInKernels);
  json_object *BuiltInKernels = json_object_new_array();
  for (int i = 0; i < numBuiltInKernels; i++) {
    json_object *BuiltInKernel = json_object_new_object();
    json_object_object_add(BuiltInKernel, "name", json_object_new_string(builtInKernels[i].name));
    json_object_object_add(BuiltInKernel, "version", json_object_new_string(versionStr(builtInKernels[i].version)));
    json_object_array_add(BuiltInKernels, BuiltInKernel);
  }
  json_object_object_add(Device, "built_in_kernels", BuiltInKernels);
}

void AddDevice_CompilerAvailable(json_object *Device, cl_device_id device) {
  cl_uint compilerAvailable = deviceCompilerAvailable(device);
  json_object_object_add(Device, "compiler_available", json_object_new_boolean(compilerAvailable));
}

void AddDevice_DoubleFPConfig(json_object *Device, cl_device_id device) {
  getProperties(deviceDoubleFPConfig(device), "double_fp_config", Device);
}

void AddDevice_EndianLittle(json_object *Device, cl_device_id device) {
  cl_uint endianLittle = deviceEndianLittle(device);
  json_object_object_add(Device, "endian_little", json_object_new_boolean(endianLittle));
}

void AddDevice_EnqueueCapabilities(json_object *Device, cl_device_id device) {
  getProperties(deviceEnqueueCapabilities(device), "enqueue_capabilities", Device);
}

void AddDevice_ErrorCorrectionSupport(json_object *Device, cl_device_id device) {
  cl_uint errorCorrectionSupport = deviceErrorCorrectionSupport(device);
  json_object_object_add(Device, "error_correction_support", json_object_new_boolean(errorCorrectionSupport));
}

void AddDevice_ExecCapabilities(json_object *Device, cl_device_id device) {
  getProperties(deviceExecCapabilities(device), "exec_capabilities", Device);
}

void AddDevice_Extensions(json_object *Device, cl_device_id device) {
  size_t numDeviceExtensions;
  cl_name_version *extensions = deviceExtensionsWithVersion(device, &numDeviceExtensions);
  json_object *Extensions = json_object_new_array();
  for (int i = 0; i < numDeviceExtensions; i++) {
    json_object *Extension = json_object_new_object();
    json_object_object_add(Extension, "name", json_object_new_string(extensions[i].name));
    json_object_object_add(Extension, "version", json_object_new_string(versionStr(extensions[i].version)));
    json_object_array_add(Extensions, Extension);
  }
  json_object_object_add(Device, "extensions", Extensions);
}

void AddDevice_GenericAddressSpaceSupport(json_object *Device, cl_device_id device) {
  cl_uint genericAddressSpaceSupport = deviceGenericAddressSpaceSupport(device);
  json_object_object_add(Device, "generic_address_space_support", json_object_new_boolean(genericAddressSpaceSupport));
}

void AddDevice_GlobalMemSize(json_object *Device, cl_device_id device) {
  cl_ulong globalMemSize = deviceGlobalMemSize(device);
  json_object_object_add(Device, "global_mem_size", json_object_new_uint64(globalMemSize));
}

void AddDevice_GlobalMemCacheSize(json_object *Device, cl_device_id device) {
  cl_ulong globalMemCacheSize = deviceGlobalMemCacheSize(device);
  json_object_object_add(Device, "global_mem_cache_size", json_object_new_uint64(globalMemCacheSize));
}

void AddDevice_GlobalMemCachelineSize(json_object *Device, cl_device_id device) {
  cl_uint globalMemCachelineSize = deviceGlobalMemCachelineSize(device);
  json_object_object_add(Device, "global_mem_cacheline_size", json_object_new_uint64(globalMemCachelineSize));
}

void AddDevice_GlobalVariablePreferredTotalSize(json_object *Device, cl_device_id device) {
  size_t globalVariablePreferredTotalSize = deviceGlobalVariablePreferredTotalSize(device);
  json_object_object_add(Device, "global_variable_preferred_total_size", json_object_new_uint64(globalVariablePreferredTotalSize));
}

void AddDevice_IlVersion(json_object *Device, cl_device_id device) {
  char *ilVersion = deviceIlVersion(device);
  json_object_object_add(Device, "il_version", json_object_new_string(ilVersion));
}

void AddDevice_IlsWithVersion(json_object *Device, cl_device_id device) {
  size_t numIls;
  cl_name_version *ils = deviceIlsWithVersion(device, &numIls);
  json_object *Ils = json_object_new_array();
  for (int i = 0; i < numIls; i++) {
    json_object *Il = json_object_new_object();
    json_object_object_add(Il, "name", json_object_new_string(ils[i].name));
    json_object_object_add(Il, "version", json_object_new_string(versionStr(ils[i].version)));
    json_object_array_add(Ils, Il);
  }
  json_object_object_add(Device, "ils", Ils);
}

void AddDevice_ImageBaseAddressAlignment(json_object *Device, cl_device_id device) {
  cl_uint imageBaseAddressAlignment = deviceImageBaseAddressAlignment(device);
  json_object_object_add(Device, "image_base_address_alignment", json_object_new_uint64(imageBaseAddressAlignment));
}

void AddDevice_ImageMaxArraySize(json_object *Device, cl_device_id device) {
  size_t imageMaxArraySize = deviceImageMaxArraySize(device);
  json_object_object_add(Device, "image_max_array_size", json_object_new_uint64(imageMaxArraySize));
}

void AddDevice_ImageMaxBufferSize(json_object *Device, cl_device_id device) {
  size_t imageMaxBufferSize = deviceImageMaxBufferSize(device);
  json_object_object_add(Device, "image_max_buffer_size", json_object_new_uint64(imageMaxBufferSize));
}

void AddDevice_ImagePitchAlignment(json_object *Device, cl_device_id device) {
  cl_uint imagePitchAlignment = deviceImagePitchAlignment(device);
  json_object_object_add(Device, "image_pitch_alignment", json_object_new_uint64(imagePitchAlignment));
}

void AddDevice_ImageSupport(json_object *Device, cl_device_id device) {
  cl_uint imageSupport = deviceImageSupport(device);
  json_object_object_add(Device, "image_support", json_object_new_boolean(imageSupport));
}

void AddDevice_Image2dMaxHeight(json_object *Device, cl_device_id device) {
  size_t image2dMaxHeight = deviceImage2dMaxHeight(device);
  json_object_object_add(Device, "image2d_max_height", json_object_new_uint64(image2dMaxHeight));
}

void AddDevice_Image2dMaxWidth(json_object *Device, cl_device_id device) {
  size_t image2dMaxWidth = deviceImage2dMaxWidth(device);
  json_object_object_add(Device, "image2d_max_width", json_object_new_uint64(image2dMaxWidth));
}

void AddDevice_Image3dMaxDepth(json_object *Device, cl_device_id device) {
  size_t image3dMaxDepth = deviceImage3dMaxDepth(device);
  json_object_object_add(Device, "image3d_max_depth", json_object_new_uint64(image3dMaxDepth));
}

void AddDevice_Image3dMaxHeight(json_object *Device, cl_device_id device) {
  size_t image3dMaxHeight = deviceImage3dMaxHeight(device);
  json_object_object_add(Device, "image3d_max_height", json_object_new_uint64(image3dMaxHeight));
}

void AddDevice_Image3dmaxWidth(json_object *Device, cl_device_id device) {
  size_t image3dmaxWidth = deviceImage3dmaxWidth(device);
  json_object_object_add(Device, "image3d_max_width", json_object_new_uint64(image3dmaxWidth));
}

void AddDevice_LatestConformanceVersionPassed(json_object *Device, cl_device_id device) {
  char *latestConformanceVersionPassed = deviceLatestConformanceVersionPassed(device);
  json_object_object_add(Device, "latest_conformance_version_passed", json_object_new_string(latestConformanceVersionPassed));
}

void AddDevice_LinkerAvailable(json_object *Device, cl_device_id device) {
  cl_uint linkerAvailable = deviceLinkerAvailable(device);
  json_object_object_add(Device, "linker_available", json_object_new_boolean(linkerAvailable));
}

void AddDevice_LocalMemSize(json_object *Device, cl_device_id device) {
  cl_ulong localMemSize = deviceLocalMemSize(device);
  json_object_object_add(Device, "local_mem_size", json_object_new_uint64(localMemSize));
}

void AddDevice_LocalMemType(json_object *Device, cl_device_id device) { getProperties(deviceLocalMemType(device), "local_mem_type", Device); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AddDevice_MaxComputeUnits(json_object *Device, cl_device_id device) {
  cl_uint maxComputeUnits = deviceMaxComputeUnits(device);
  json_object_object_add(Device, "max_compute_units", json_object_new_uint64(maxComputeUnits));
}

void AddDevice_MaxConstantArgs(json_object *Device, cl_device_id device) {
  cl_uint maxConstantArgs = deviceMaxConstantArgs(device);
  json_object_object_add(Device, "max_constant_args", json_object_new_uint64(maxConstantArgs));
}

void AddDevice_MaxClockFrequency(json_object *Device, cl_device_id device) {
  cl_uint maxClockFrequency = deviceMaxClockFrequency(device);
  json_object_object_add(Device, "max_clock_frequency", json_object_new_uint64(maxClockFrequency));
}

void AddDevice_MaxConstantBufferSize(json_object *Device, cl_device_id device) {
  cl_ulong maxConstantBufferSize = deviceMaxConstantBufferSize(device);
  json_object_object_add(Device, "max_constant_buffer_size", json_object_new_uint64(maxConstantBufferSize));
}

void AddDevice_MaxGlobalVariableSize(json_object *Device, cl_device_id device) {
  size_t maxGlobalVariableSize = deviceMaxGlobalVariableSize(device);
  json_object_object_add(Device, "max_global_variable_size", json_object_new_uint64(maxGlobalVariableSize));
}

void AddDevice_MaxMemAllocSize(json_object *Device, cl_device_id device) {
  cl_ulong maxMemAllocSize = deviceMaxMemAllocSize(device);
  json_object_object_add(Device, "max_mem_alloc_size", json_object_new_uint64(maxMemAllocSize));
}

void AddDevice_MaxNumSubGroups(json_object *Device, cl_device_id device) {
  cl_uint maxNumSubGroups = deviceMaxNumSubGroups(device);
  json_object_object_add(Device, "max_num_sub_groups", json_object_new_uint64(maxNumSubGroups));
}

void AddDevice_MaxOnDeviceEvents(json_object *Device, cl_device_id device) {
  cl_uint maxOnDeviceEvents = deviceMaxOnDeviceEvents(device);
  json_object_object_add(Device, "max_on_device_events", json_object_new_uint64(maxOnDeviceEvents));
}

void AddDevice_MaxOnDeviceQueues(json_object *Device, cl_device_id device) {
  cl_uint maxOnDeviceQueues = deviceMaxOnDeviceQueues(device);
  json_object_object_add(Device, "max_on_device_queues", json_object_new_uint64(maxOnDeviceQueues));
}

void AddDevice_MaxParameterSize(json_object *Device, cl_device_id device) {
  size_t maxParameterSize = deviceMaxParameterSize(device);
  json_object_object_add(Device, "max_parameter_size", json_object_new_uint64(maxParameterSize));
}

void AddDevice_MaxPipeArgs(json_object *Device, cl_device_id device) {
  cl_uint maxPipeArgs = deviceMaxPipeArgs(device);
  json_object_object_add(Device, "max_pipe_args", json_object_new_uint64(maxPipeArgs));
}

void AddDevice_MaxReadImageArgs(json_object *Device, cl_device_id device) {
  cl_uint maxReadImageArgs = deviceMaxReadImageArgs(device);
  json_object_object_add(Device, "max_read_image_args", json_object_new_uint64(maxReadImageArgs));
}

void AddDevice_MaxReadWriteImageArgs(json_object *Device, cl_device_id device) {
  cl_uint maxReadWriteImageArgs = deviceMaxReadWriteImageArgs(device);
  json_object_object_add(Device, "max_read_write_image_args", json_object_new_uint64(maxReadWriteImageArgs));
}

void AddDevice_MaxSamplers(json_object *Device, cl_device_id device) {
  cl_uint maxSamplers = deviceMaxSamplers(device);
  json_object_object_add(Device, "max_samplers", json_object_new_uint64(maxSamplers));
}

void AddDevice_MaxWorkGroupSize(json_object *Device, cl_device_id device) {
  size_t maxWorkGroupSize = deviceMaxWorkGroupSize(device);
  json_object_object_add(Device, "max_work_group_size", json_object_new_uint64(maxWorkGroupSize));
}

void AddDevice_MaxWorkItemDimensions(json_object *Device, cl_device_id device) {
  cl_uint maxWorkItemDimensions = deviceMaxWorkItemDimensions(device);
  json_object_object_add(Device, "max_work_item_dimensions", json_object_new_uint64(maxWorkItemDimensions));
}

void AddDevice_MaxWorkItemSizes(json_object *Device, cl_device_id device) {
  char buffer[12];
  size_t numDims;
  size_t *maxWorkItemSizes = deviceMaxWorkItemSizes(device, &numDims);
  json_object *Sizes = json_object_new_array();
  for (int i = 0; i < numDims; i++) {
    json_object *Size = json_object_new_object();
    sprintf(buffer, "%d", i);
    json_object_object_add(Size, (char *)buffer, json_object_new_uint64(maxWorkItemSizes[i]));
    json_object_array_add(Sizes, Size);
  }
  json_object_object_add(Device, "max_work_item_sizes", Sizes);
}

void AddDevice_MaxWriteImageArgs(json_object *Device, cl_device_id device) {
  cl_uint maxWriteImageArgs = deviceMaxWriteImageArgs(device);
  json_object_object_add(Device, "max_write_image_args", json_object_new_uint64(maxWriteImageArgs));
}

void AddDevice_MemBaseAddrAlign(json_object *Device, cl_device_id device) {
  cl_uint memBaseAddrAlign = deviceMemBaseAddrAlign(device);
  json_object_object_add(Device, "mem_base_addr_align ", json_object_new_uint64(memBaseAddrAlign));
}

void AddDevice_MemCacheType(json_object *Device, cl_device_id device) { getProperties(deviceMemCacheType(device), "mem_cache_type", Device); }

void AddDevice_NativeVectorWidthChar(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthChar = deviceNativeVectorWidthChar(device);
  json_object_object_add(Device, "native_vector_width_char", json_object_new_uint64(nativeVectorWidthChar));
}

void AddDevice_NativeVectorWidthDouble(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthDouble = deviceNativeVectorWidthDouble(device);
  json_object_object_add(Device, "native_vector_width_double", json_object_new_uint64(nativeVectorWidthDouble));
}

void AddDevice_NativeVectorWidthFloat(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthFloat = deviceNativeVectorWidthFloat(device);
  json_object_object_add(Device, "native_vector_width_float", json_object_new_uint64(nativeVectorWidthFloat));
}

void AddDevice_NativeVectorWidthHalf(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthHalf = deviceNativeVectorWidthHalf(device);
  json_object_object_add(Device, "native_vector_width_half", json_object_new_uint64(nativeVectorWidthHalf));
}

void AddDevice_NativeVectorWidthInt(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthInt = eviceNativeVectorWidthInt(device);
  json_object_object_add(Device, "native_vector_width_int", json_object_new_uint64(nativeVectorWidthInt));
}

void AddDevice_NativeVectorWidthLong(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthLong = eviceNativeVectorWidthLong(device);
  json_object_object_add(Device, "native_vector_width_long", json_object_new_uint64(nativeVectorWidthLong));
}

void AddDevice_NativeVectorWidthShort(json_object *Device, cl_device_id device) {
  cl_uint nativeVectorWidthShort = eviceNativeVectorWidthShort(device);
  json_object_object_add(Device, "native_vector_width_short", json_object_new_uint64(nativeVectorWidthShort));
}

void AddDevice_NonUniformWorkGroupSupport(json_object *Device, cl_device_id device) {
  cl_uint nonUniformWorkGroupSupport = eviceNonUniformWorkGroupSupport(device);
  json_object_object_add(Device, "non_uniform_work_group_support", json_object_new_boolean(nonUniformWorkGroupSupport));
}

void AddDevice_NumericVersion(json_object *Device, cl_device_id device) {
  cl_uint numericVersion = deviceNumericVersion(device);
  json_object_object_add(Device, "numeric_version", json_object_new_string(versionStr(numericVersion)));
}

void AddDevice_OpenClCAllVersions(json_object *Device, cl_device_id device) {
  size_t numC;
  cl_name_version *cs = deviceOpenClCAllVersions(device, &numC);
  json_object *Cs = json_object_new_array();
  for (int i = 0; i < numC; i++) {
    json_object *C = json_object_new_object();
    json_object_object_add(C, "name", json_object_new_string(cs[i].name));
    json_object_object_add(C, "version", json_object_new_string(versionStr(cs[i].version)));
    json_object_array_add(Cs, C);
  }
  json_object_object_add(Device, "opencl_c_all_versions", Cs);
}

void AddDevice_OpenClCFeatures(json_object *Device, cl_device_id device) {
  size_t numCFeatures;
  cl_name_version *cfs = deviceOpenClCFeatures(device, &numCFeatures);
  json_object *Cfs = json_object_new_array();
  for (int i = 0; i < numCFeatures; i++) {
    json_object *Cf = json_object_new_object();
    json_object_object_add(Cf, "name", json_object_new_string(cfs[i].name));
    json_object_object_add(Cf, "version", json_object_new_string(versionStr(cfs[i].version)));
    json_object_array_add(Cfs, Cf);
  }
  json_object_object_add(Device, "opencl_c_features", Cfs);
}

void AddDevice_ParentId(json_object *Device, cl_device_id device) {
  cl_device_id parentId = deviceParentId(device);
  json_object_object_add(Device, "parent_id", json_object_new_uint64((intptr_t)parentId));
}

void AddDevice_PartitionMaxSubDevices(json_object *Device, cl_device_id device) {
  cl_uint partitionMaxSubDevices = devicePartitionMaxSubDevices(device);
  json_object_object_add(Device, "partition_max_sub_devices", json_object_new_uint64(partitionMaxSubDevices));
}

void AddDevice_PartitionProperties(json_object *Device, cl_device_id device) {
  getProperties(devicePartitionProperties(device), "partition_properties", Device);
}

void AddDevice_PartitionType(json_object *Device, cl_device_id device) { getProperties(devicePartitionType(device), "partition_types", Device); }

void AddDevice_PipeMaxActiveReservations(json_object *Device, cl_device_id device) {
  cl_uint pipeMaxActiveReservations = devicePipeMaxActiveReservations(device);
  json_object_object_add(Device, "pipe_max_active_reservations", json_object_new_uint64(pipeMaxActiveReservations));
}

void AddDevice_PipeMaxPacketSize(json_object *Device, cl_device_id device) {
  cl_uint pipeMaxPacketSize = devicePipeMaxPacketSize(device);
  json_object_object_add(Device, "pipe_max_packet_size ", json_object_new_uint64(pipeMaxPacketSize));
}

void AddDevice_PipeSupport(json_object *Device, cl_device_id device) {
  cl_uint pipeSupport = devicePipeSupport(device);
  json_object_object_add(Device, "pipe_support", json_object_new_boolean(pipeSupport));
}

void AddDevice_PreferredGlobalAtomicAlignment(json_object *Device, cl_device_id device) {
  cl_uint preferredGlobalAtomicAlignment = devicePreferredGlobalAtomicAlignment(device);
  json_object_object_add(Device, "preferred_global_atomic_alignment", json_object_new_uint64(preferredGlobalAtomicAlignment));
}

void AddDevice_PreferredInteropUserSync(json_object *Device, cl_device_id device) {
  cl_uint preferredInteropUserSync = devicePreferredInteropUserSync(device);
  json_object_object_add(Device, "preferred_interop_user_sync", json_object_new_boolean(preferredInteropUserSync));
}

void AddDevice_PreferredLocalAtomicAlignment(json_object *Device, cl_device_id device) {
  cl_uint preferredLocalAtomicAlignment = devicePreferredLocalAtomicAlignment(device);
  json_object_object_add(Device, "preferred_local_atomic_alignment", json_object_new_uint64(preferredLocalAtomicAlignment));
}

void AddDevice_PreferredPlatformAtomicAlignment(json_object *Device, cl_device_id device) {
  cl_uint preferredPlatformAtomicAlignment = devicePreferredPlatformAtomicAlignment(device);
  json_object_object_add(Device, "preferred_platform_atomic_alignment", json_object_new_uint64(preferredPlatformAtomicAlignment));
}

void AddDevice_PreferredVectorWidthChar(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthChar = devicePreferredVectorWidthChar(device);
  json_object_object_add(Device, "preferred_vector_width_char", json_object_new_uint64(preferredVectorWidthChar));
}

void AddDevice_PreferredVectorWidthDouble(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthDouble = devicePreferredVectorWidthDouble(device);
  json_object_object_add(Device, "preferred_vector_width_double", json_object_new_uint64(preferredVectorWidthDouble));
}

void AddDevice_PreferredVectorWidthFloat(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthFloat = devicePreferredVectorWidthFloat(device);
  json_object_object_add(Device, "preferred_vector_width_float", json_object_new_uint64(preferredVectorWidthFloat));
}

void AddDevice_PreferredVectorWidthHalf(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthHalf = devicePreferredVectorWidthHalf(device);
  json_object_object_add(Device, "preferred_vector_width_half", json_object_new_uint64(preferredVectorWidthHalf));
}

void AddDevice_PreferredVectorWidthInt(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthInt = devicePreferredVectorWidthInt(device);
  json_object_object_add(Device, "preferred_vector_width_int", json_object_new_uint64(preferredVectorWidthInt));
}

void AddDevice_PreferredVectorWidthLong(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthLong = devicePreferredVectorWidthLong(device);
  json_object_object_add(Device, "preferred_vector_width_long", json_object_new_uint64(preferredVectorWidthLong));
}

void AddDevice_PreferredVectorWidthShort(json_object *Device, cl_device_id device) {
  cl_uint preferredVectorWidthShort = devicePreferredVectorWidthShort(device);
  json_object_object_add(Device, "preferred_vector_width_short", json_object_new_uint64(preferredVectorWidthShort));
}

void AddDevice_PreferredWorkGroupSizeMultiple(json_object *Device, cl_device_id device) {
  size_t preferredWorkGroupSizeMultiple = devicePreferredWorkGroupSizeMultiple(device);
  json_object_object_add(Device, "preferred_work_group_size_multiple", json_object_new_uint64(preferredWorkGroupSizeMultiple));
}

void AddDevice_PrintfBufferSize(json_object *Device, cl_device_id device) {
  size_t printfBufferSize = devicePrintfBufferSize(device);
  json_object_object_add(Device, "printf_buffer_size", json_object_new_uint64(printfBufferSize));
}

void AddDevice_ProfilingTimerResolution(json_object *Device, cl_device_id device) {
  size_t profilingTimerResolution = deviceProfilingTimerResolution(device);
  json_object_object_add(Device, "profiling_timer_resolution", json_object_new_uint64(profilingTimerResolution));
}

void AddDevice_QueueOnDeviceMaxSize(json_object *Device, cl_device_id device) {
  cl_uint queueOnDeviceMaxSize = deviceQueueOnDeviceMaxSize(device);
  json_object_object_add(Device, "queue_on_device_max_size", json_object_new_uint64(queueOnDeviceMaxSize));
}

void AddDevice_QueueOnDeviceProperties(json_object *Device, cl_device_id device) {
  getProperties(deviceQueueOnDeviceProperties(device), "queue_on_device_properties", Device);
}

void AddDevice_QueueOnHostProperties(json_object *Device, cl_device_id device) {
  getProperties(deviceQueueOnHostProperties(device), "queue_on_host_properties", Device);
}

void AddDevice_QueueOnDevicePreferredSize(json_object *Device, cl_device_id device) {
  cl_uint queueOnDevicePreferredSize = deviceQueueOnDevicePreferredSize(device);
  json_object_object_add(Device, "queue_on_device_preferred_size", json_object_new_uint64(queueOnDevicePreferredSize));
}

void AddDevice_ReferenceCount(json_object *Device, cl_device_id device) {
  cl_uint referenceCount = deviceReferenceCount(device);
  json_object_object_add(Device, "reference_count", json_object_new_uint64(referenceCount));
}

void AddDevice_SingleFPConfig(json_object *Device, cl_device_id device) {
  getProperties(deviceSingleFPConfig(device), "single_fp_config", Device);
}

void AddDevice_SubGroupIndependentForwardProgress(json_object *Device, cl_device_id device) {
  cl_uint subGroupIndependentForwardProgress = deviceSubGroupIndependentForwardProgress(device);
  json_object_object_add(Device, "sub_group_independent_forward_progress", json_object_new_boolean(subGroupIndependentForwardProgress));
}

void AddDevice_SVMCapabilities(json_object *Device, cl_device_id device) {
  getProperties(deviceSVMCapabilities(device), "svm_capabilities", Device);
}

void AddDevice_VendorID(json_object *Device, cl_device_id device) {
  cl_uint vendorID = deviceVendorID(device);
  json_object_object_add(Device, "vendor_id", json_object_new_uint64(vendorID));
}

void AddDevice_WorkGroupCollectiveFunctionsSupport(json_object *Device, cl_device_id device) {
  cl_uint workGroupCollectiveFunctionsSupport = deviceWorkGroupCollectiveFunctionsSupport(device);
  json_object_object_add(Device, "work_group_collective_functions_support", json_object_new_boolean(workGroupCollectiveFunctionsSupport));
}
