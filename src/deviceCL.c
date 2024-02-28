#include "deviceCL.h"
#include "error.h"

// TODO: write macro ?
static char *deviceStr(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  char *retValue = malloc(sizeof(char) * paramSize);
  err = clGetDeviceInfo(device, paramName, paramSize, retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

static cl_device_id deviceId(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_device_id retValue;
  cl_int err = clGetDeviceInfo(device, paramName, sizeof(cl_device_id), &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

cl_name_version *deviceNameVersion(cl_device_id device, cl_device_info paramName, char *errorMsg, size_t *numNameVersions) {
  clGetDeviceInfo(device, paramName, 0, NULL, numNameVersions);
  cl_name_version *nameVersions = malloc(*numNameVersions);
  clGetDeviceInfo(device, paramName, (*numNameVersions), nameVersions, NULL);
  *numNameVersions /= (CL_NAME_VERSION_MAX_NAME_SIZE + sizeof(cl_version));
  return nameVersions;
}

static cl_platform_id devicePlatformId(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_platform_id retValue;
  cl_int err = clGetDeviceInfo(device, paramName, sizeof(cl_platform_id), &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

static size_t deviceSizeT(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  size_t retValue;
  cl_int err = clGetDeviceInfo(device, paramName, sizeof(size_t), &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

static cl_uint deviceUint(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_uint retValue;
  cl_int err = clGetDeviceInfo(device, paramName, sizeof(cl_uint), &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

static cl_ulong deviceUlong(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  size_t paramSize;
  cl_ulong retValue;
  cl_int err = clGetDeviceInfo(device, paramName, sizeof(cl_ulong), &retValue, NULL);
  handleError(err, errorMsg);
  return retValue;
}

// TODO: json function
size_t *deviceMaxWorkItemSizes(cl_device_id device, size_t *numDims) {
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device max work item sizes.");
  size_t *maxWorkItemSizes = malloc(paramSize);
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, paramSize, maxWorkItemSizes, NULL);
  handleError(err, "Couldn't get device max work item sizes.");
  *numDims = paramSize / (sizeof(size_t));
  return maxWorkItemSizes;
}

cl_device_partition_property *devicePartition(cl_device_id device, cl_device_info paramName, char *errorMsg, size_t *numPartitions) {
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, numPartitions);
  handleError(err, errorMsg);
  cl_device_partition_property *partitionProperties = malloc(*numPartitions);
  err = clGetDeviceInfo(device, paramName, (*numPartitions), partitionProperties, NULL);
  handleError(err, errorMsg);
  *numPartitions /= sizeof(cl_device_partition_property);
  return partitionProperties;
}

GArray *devicePartitions(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  GArray *partitionProperties = g_array_new(FALSE, FALSE, sizeof(property));
  size_t numPartitions;
  cl_device_partition_property *partitions = devicePartition(device, paramName, errorMsg, &numPartitions);

  property partitionTypeEqually = {FALSE, "equally"};
  property partitionTypeByCounts = {FALSE, "by_counts"};
  property partitionTypeByCountsListEnd = {FALSE, "by_counts_list_end"};
  property partitionTypeByAffinityDomain = {FALSE, "by_affinity_domain"};

  for (int i = 0; i < numPartitions; i++) {
    if (partitions[i] == CL_DEVICE_PARTITION_EQUALLY) {
      partitionTypeEqually.enabled = TRUE;
    }
    if (partitions[i] == CL_DEVICE_PARTITION_BY_COUNTS) {
      partitionTypeByCounts.enabled = TRUE;
    }
    if (partitions[i] == CL_DEVICE_PARTITION_BY_COUNTS_LIST_END) {
      partitionTypeByCountsListEnd.enabled = TRUE;
    }
    if (partitions[i] == CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN) {
      partitionTypeByAffinityDomain.enabled = TRUE;
    }
  }
  g_array_append_val(partitionProperties, partitionTypeEqually);
  g_array_append_val(partitionProperties, partitionTypeByCounts);
  g_array_append_val(partitionProperties, partitionTypeByCountsListEnd);
  g_array_append_val(partitionProperties, partitionTypeByAffinityDomain);

  return partitionProperties;
}

GArray *deviceSVMCapabilities(cl_device_id device) {
  GArray *svmCapabilities = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_SVM_CAPABILITIES, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device SVM capabilities.");
  cl_device_svm_capabilities devSvmCapabilities;
  err = clGetDeviceInfo(device, CL_DEVICE_SVM_CAPABILITIES, paramSize, &devSvmCapabilities, NULL);
  handleError(err, "Couldn't get device SVM capabilities.");

  {
    property memCacheType = {FALSE, "svm_coarse_grain_buffer"};
    if (devSvmCapabilities & CL_DEVICE_SVM_COARSE_GRAIN_BUFFER) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(svmCapabilities, memCacheType);
  }

  {
    property memCacheType = {FALSE, "svm_fine_grain_buffer"};
    if (devSvmCapabilities & CL_DEVICE_SVM_FINE_GRAIN_BUFFER) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(svmCapabilities, memCacheType);
  }

  {
    property memCacheType = {FALSE, "svm_fine_grain_system"};
    if (devSvmCapabilities & CL_DEVICE_SVM_FINE_GRAIN_SYSTEM) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(svmCapabilities, memCacheType);
  }

  {
    property memCacheType = {FALSE, "svm_atomics"};
    if (devSvmCapabilities & CL_DEVICE_SVM_ATOMICS) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(svmCapabilities, memCacheType);
  }

  return svmCapabilities;
}

GArray *deviceMemCacheType(cl_device_id device) {
  GArray *memCacheTypes = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device memory cache type.");
  cl_device_mem_cache_type devMemCacheTypes;
  err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, paramSize, &devMemCacheTypes, NULL);
  handleError(err, "Couldn't get device memory cache type.");

  {
    property memCacheType = {FALSE, "none"};
    if (devMemCacheTypes & CL_NONE) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(memCacheTypes, memCacheType);
  }

  {
    property memCacheType = {FALSE, "read_only_cache"};
    if (devMemCacheTypes & CL_READ_ONLY_CACHE) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(memCacheTypes, memCacheType);
  }

  {
    property memCacheType = {FALSE, "read_write_cache"};
    if (devMemCacheTypes & CL_READ_WRITE_CACHE) {
      memCacheType.enabled = TRUE;
    }
    g_array_append_val(memCacheTypes, memCacheType);
  }

  return memCacheTypes;
}

GArray *deviceLocalMemType(cl_device_id device) {
  GArray *memTypes = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device local memory type.");
  cl_device_local_mem_type devMemTypes;
  err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, paramSize, &devMemTypes, NULL);
  handleError(err, "Couldn't get device local memory type.");

  {
    property execCapability = {FALSE, "local"};
    if (devMemTypes & CL_LOCAL) {
      execCapability.enabled = TRUE;
    }
    g_array_append_val(memTypes, execCapability);
  }

  {
    property execCapability = {FALSE, "global"};
    if (devMemTypes & CL_GLOBAL) {
      execCapability.enabled = TRUE;
    }
    g_array_append_val(memTypes, execCapability);
  }

  return memTypes;
}

GArray *deviceFPConfig(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  GArray *fpConfigs = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  cl_device_atomic_capabilities devFpConfigs;
  err = clGetDeviceInfo(device, paramName, paramSize, &devFpConfigs, NULL);
  handleError(err, errorMsg);

  {
    property fpConfig = {FALSE, "fp_denorm"};
    if (devFpConfigs & CL_FP_DENORM) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_inf_nan"};
    if (devFpConfigs & CL_FP_INF_NAN) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_round_to_nearest"};
    if (devFpConfigs & CL_FP_ROUND_TO_NEAREST) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_round_to_zero"};
    if (devFpConfigs & CL_FP_ROUND_TO_ZERO) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_round_to_inf"};
    if (devFpConfigs & CL_FP_ROUND_TO_INF) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_fma"};
    if (devFpConfigs & CL_FP_FMA) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_soft_float"};
    if (devFpConfigs & CL_FP_SOFT_FLOAT) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  {
    property fpConfig = {FALSE, "fp_correctly_rounded_divide_sqrt"};
    if (devFpConfigs & CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT) {
      fpConfig.enabled = TRUE;
    }
    g_array_append_val(fpConfigs, fpConfig);
  }

  return fpConfigs;
}

GArray *deviceExecCapabilities(cl_device_id device) {
  GArray *execCapabilities = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_EXECUTION_CAPABILITIES, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device affinity domain.");
  cl_device_affinity_domain devExecCapability;
  err = clGetDeviceInfo(device, CL_DEVICE_EXECUTION_CAPABILITIES, paramSize, &devExecCapability, NULL);
  handleError(err, "Couldn't get device affinity domain.");

  {
    property execCapability = {FALSE, "exec_kernel"};
    if (devExecCapability & CL_EXEC_KERNEL) {
      execCapability.enabled = TRUE;
    }
    g_array_append_val(execCapabilities, execCapability);
  }

  {
    property execCapability = {FALSE, "exec_native_kernel"};
    if (devExecCapability & CL_EXEC_NATIVE_KERNEL) {
      execCapability.enabled = TRUE;
    }
    g_array_append_val(execCapabilities, execCapability);
  }

  return execCapabilities;
}

GArray *deviceEnqueueCapabilities(cl_device_id device) {
  GArray *enqueueCapabilities = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device affinity domain.");
  cl_device_affinity_domain devEnqueueCapability;
  err = clGetDeviceInfo(device, CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES, paramSize, &devEnqueueCapability, NULL);
  handleError(err, "Couldn't get device affinity domain.");

  {
    property enqueueCapability = {FALSE, "queue_supported"};
    if (devEnqueueCapability & CL_DEVICE_QUEUE_SUPPORTED) {
      enqueueCapability.enabled = TRUE;
    }
    g_array_append_val(enqueueCapabilities, enqueueCapability);
  }

  {
    property enqueueCapability = {FALSE, "queue_replaceable_default"};
    if (devEnqueueCapability & CL_DEVICE_QUEUE_REPLACEABLE_DEFAULT) {
      enqueueCapability.enabled = TRUE;
    }
    g_array_append_val(enqueueCapabilities, enqueueCapability);
  }

  return enqueueCapabilities;
}

GArray *deviceAtomicCapabilities(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  GArray *atomicCapabilities = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  cl_device_atomic_capabilities devAtomicCapabilities;
  err = clGetDeviceInfo(device, paramName, paramSize, &devAtomicCapabilities, NULL);
  handleError(err, errorMsg);

  {
    property atomicCapability = {FALSE, "atomic_order_relaxed"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_ORDER_RELAXED) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  {
    property atomicCapability = {FALSE, "atomic_order_acq_rel"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_ORDER_ACQ_REL) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  {
    property atomicCapability = {FALSE, "atomic_order_seq_cst"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_ORDER_SEQ_CST) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  {
    property atomicCapability = {FALSE, "atomic_scope_work_item"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_SCOPE_WORK_ITEM) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  {
    property atomicCapability = {FALSE, "atomic_scope_work_group"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_SCOPE_WORK_GROUP) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  {
    property atomicCapability = {FALSE, "atomic_scope_device"};
    if (devAtomicCapabilities & CL_DEVICE_ATOMIC_SCOPE_DEVICE) {
      atomicCapability.enabled = TRUE;
    }
    g_array_append_val(atomicCapabilities, atomicCapability);
  }

  return atomicCapabilities;
}

GArray *deviceAffinityDomain(cl_device_id device) {
  GArray *affinityDomains = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_PARTITION_AFFINITY_DOMAIN, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device affinity domain.");
  cl_device_affinity_domain devAffinityDomains;
  err = clGetDeviceInfo(device, CL_DEVICE_PARTITION_AFFINITY_DOMAIN, paramSize, &devAffinityDomains, NULL);
  handleError(err, "Couldn't get device affinity domain.");

  {
    property affinityDomain = {FALSE, "affinity_domain_numa"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_NUMA) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  {
    property affinityDomain = {FALSE, "affinity_domain_l4_cache"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  {
    property affinityDomain = {FALSE, "affinity_domain_l3_cache"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  {
    property affinityDomain = {FALSE, "affinity_domain_l2_cache"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  {
    property affinityDomain = {FALSE, "affinity_domain_l1_cache"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  {
    property affinityDomain = {FALSE, "affinity_domain_next_partitionable"};
    if (devAffinityDomains & CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE) {
      affinityDomain.enabled = TRUE;
    }
    g_array_append_val(affinityDomains, affinityDomain);
  }

  return affinityDomains;
}

GArray *deviceQueueProperties(cl_device_id device, cl_device_info paramName, char *errorMsg) {
  GArray *queueProperties = g_array_new(FALSE, FALSE, sizeof(property));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, paramName, 0, NULL, &paramSize);
  handleError(err, errorMsg);
  cl_command_queue_properties devQueueProperty;
  err = clGetDeviceInfo(device, paramName, paramSize, &devQueueProperty, NULL);
  handleError(err, errorMsg);

  {
    property queueProperty = {FALSE, "out_of_order_exec_mode_enable"};
    if (devQueueProperty & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) {
      queueProperty.enabled = TRUE;
    }
    g_array_append_val(queueProperties, queueProperty);
  }

  {
    property queueProperty = {FALSE, "profiling_enable"};
    if (devQueueProperty & CL_QUEUE_PROFILING_ENABLE) {
      queueProperty.enabled = TRUE;
    }
    g_array_append_val(queueProperties, queueProperty);
  }

  {
    property queueProperty = {FALSE, "on_device"};
    if (devQueueProperty & CL_QUEUE_ON_DEVICE) {
      queueProperty.enabled = TRUE;
    }
    g_array_append_val(queueProperties, queueProperty);
  }

  {
    property queueProperty = {FALSE, "on_device_default"};
    if (devQueueProperty & CL_QUEUE_ON_DEVICE_DEFAULT) {
      queueProperty.enabled = TRUE;
    }
    g_array_append_val(queueProperties, queueProperty);
  }

  return queueProperties;
}

GArray *deviceTypes(cl_device_id device) {
  GArray *deviceTypes = g_array_new(FALSE, FALSE, sizeof(char *));
  size_t paramSize;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_TYPE, 0, NULL, &paramSize);
  handleError(err, "Couldn't get device type.");
  cl_device_type deviceType;
  err = clGetDeviceInfo(device, CL_DEVICE_TYPE, paramSize, &deviceType, NULL);
  handleError(err, "Couldn't get device type.");

  char *defaultType = "Default";
  char *cpuType = "CPU";
  char *gpuType = "GPU";
  char *acceleratorType = "Accelerator";

  if (deviceType & CL_DEVICE_TYPE_DEFAULT)
    g_array_append_val(deviceTypes, defaultType);
  else if (deviceType & CL_DEVICE_TYPE_CPU)
    g_array_append_val(deviceTypes, cpuType);
  else if (deviceType & CL_DEVICE_TYPE_GPU)
    g_array_append_val(deviceTypes, gpuType);
  else if (deviceType & CL_DEVICE_TYPE_ACCELERATOR)
    g_array_append_val(deviceTypes, acceleratorType);

  return deviceTypes;
}

// clang-format off
char*            deviceDriverVersion(cl_device_id device)                                  { return deviceStr(device,                CL_DRIVER_VERSION,                                 "Couldn't get device driver version."); }
char*            deviceIlVersion(cl_device_id device)                                      { return deviceStr(device,                CL_DEVICE_IL_VERSION,                              "Couldn't get device il version."); }
char*            deviceLatestConformanceVersionPassed(cl_device_id device)                 { return deviceStr(device,                CL_DEVICE_LATEST_CONFORMANCE_VERSION_PASSED,       "Couldn't get device latest conformance version passed."); }
char*            deviceName(cl_device_id device)                                           { return deviceStr(device,                CL_DEVICE_NAME,                                    "Couldn't get device name."); }
char*            deviceProfile(cl_device_id device)                                        { return deviceStr(device,                CL_DEVICE_PROFILE,                                 "Couldn't get device profile."); }
char*            deviceVendor(cl_device_id device)                                         { return deviceStr(device,                CL_DEVICE_VENDOR,                                  "Couldn't get device vendor."); }
char*            deviceVersion(cl_device_id device)                                        { return deviceStr(device,                CL_DEVICE_VERSION,                                 "Couldn't get device version."); }
cl_device_id     deviceParentId(cl_device_id device)                                       { return deviceId(device,                 CL_DEVICE_PARENT_DEVICE,                           "Couldn't get device parent device."); }
cl_name_version* deviceBuiltInKernels(cl_device_id device, size_t *numNameVersions)        { return deviceNameVersion(device,        CL_DEVICE_BUILT_IN_KERNELS_WITH_VERSION,           "Couldn't get device built-in kernels.", numNameVersions); }
cl_name_version* deviceExtensionsWithVersion(cl_device_id device, size_t *numNameVersions) { return deviceNameVersion(device,        CL_DEVICE_EXTENSIONS_WITH_VERSION,                 "Couldn't get device extensions.", numNameVersions); }
cl_name_version* deviceIlsWithVersion(cl_device_id device, size_t *numNameVersions)        { return deviceNameVersion(device,        CL_DEVICE_ILS_WITH_VERSION,                        "Couldn't get device ils.", numNameVersions); }
cl_name_version* deviceOpenClCAllVersions(cl_device_id device, size_t *numNameVersions)    { return deviceNameVersion(device,        CL_DEVICE_OPENCL_C_ALL_VERSIONS,                   "Couldn't get device OpenCL C all versions.", numNameVersions); }
cl_name_version* deviceOpenClCFeatures(cl_device_id device, size_t *numNameVersions)       { return deviceNameVersion(device,        CL_DEVICE_OPENCL_C_FEATURES,                       "Couldn't get device OpenCL C features.", numNameVersions); }
cl_platform_id   devicePlatform(cl_device_id device)                                       { return devicePlatformId(device,         CL_DEVICE_PLATFORM,                                "Couldn't get device platform id."); }
cl_uint          deviceAddressBits(cl_device_id device)                                    { return deviceUint(device,               CL_DEVICE_ADDRESS_BITS,                            "Couldn't get device address bits."); }
cl_uint          deviceAvailable(cl_device_id device)                                      { return deviceUint(device,               CL_DEVICE_AVAILABLE,                               "Couldn't get device available."); }
cl_uint          deviceCompilerAvailable(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_COMPILER_AVAILABLE,                      "Couldn't get device compiler available."); }
cl_uint          deviceEndianLittle(cl_device_id device)                                   { return deviceUint(device,               CL_DEVICE_ENDIAN_LITTLE,                           "Couldn't get device endian little."); }
cl_uint          deviceErrorCorrectionSupport(cl_device_id device)                         { return deviceUint(device,               CL_DEVICE_ERROR_CORRECTION_SUPPORT,                "Couldn't get device error correction support."); }
cl_uint          deviceGenericAddressSpaceSupport(cl_device_id device)                     { return deviceUint(device,               CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT,           "Couldn't get device generic address space support."); }
cl_uint          deviceGlobalMemCachelineSize(cl_device_id device)                         { return deviceUint(device,               CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,               "Couldn't get device global mem cacheline size."); }
cl_uint          deviceImageBaseAddressAlignment(cl_device_id device)                      { return deviceUint(device,               CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT,            "Couldn't get device image base address alignment."); }
cl_uint          deviceImagePitchAlignment(cl_device_id device)                            { return deviceUint(device,               CL_DEVICE_IMAGE_PITCH_ALIGNMENT,                   "Couldn't get device image pitch alignment."); }
cl_uint          deviceImageSupport(cl_device_id device)                                   { return deviceUint(device,               CL_DEVICE_IMAGE_SUPPORT,                           "Couldn't get device device image support."); }
cl_uint          deviceLinkerAvailable(cl_device_id device)                                { return deviceUint(device,               CL_DEVICE_LINKER_AVAILABLE,                        "Couldn't get device device linker available."); }
cl_uint          deviceMaxClockFrequency(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_MAX_CLOCK_FREQUENCY,                     "Couldn't get device max clock frequency."); }
cl_uint          deviceMaxComputeUnits(cl_device_id device)                                { return deviceUint(device,               CL_DEVICE_MAX_COMPUTE_UNITS,                       "Couldn't get device max compute units."); }
cl_uint          deviceMaxConstantArgs(cl_device_id device)                                { return deviceUint(device,               CL_DEVICE_MAX_CONSTANT_ARGS,                       "Couldn't get device max constant args."); }
cl_uint          deviceMaxNumSubGroups(cl_device_id device)                                { return deviceUint(device,               CL_DEVICE_MAX_NUM_SUB_GROUPS,                      "Couldn't get device max num sub groups."); }
cl_uint          deviceMaxOnDeviceEvents(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_MAX_ON_DEVICE_EVENTS,                    "Couldn't get device max on device events."); }
cl_uint          deviceMaxOnDeviceQueues(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_MAX_ON_DEVICE_QUEUES,                    "Couldn't get device max on device queues."); }
cl_uint          deviceMaxPipeArgs(cl_device_id device)                                    { return deviceUint(device,               CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get device max pipe args."); }
cl_uint          deviceMaxReadImageArgs(cl_device_id device)                               { return deviceUint(device,               CL_DEVICE_MAX_READ_IMAGE_ARGS,                     "Couldn't get device max read image args."); }
cl_uint          deviceMaxReadWriteImageArgs(cl_device_id device)                          { return deviceUint(device,               CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS,               "Couldn't get device max read write image args."); }
cl_uint          deviceMaxSamplers(cl_device_id device)                                    { return deviceUint(device,               CL_DEVICE_MAX_SAMPLERS,                            "Couldn't get device max samplers."); }
cl_uint          deviceMaxWorkItemDimensions(cl_device_id device)                          { return deviceUint(device,               CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,                "Couldn't get device max work item dimensions."); }
cl_uint          deviceMaxWriteImageArgs(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_MAX_WRITE_IMAGE_ARGS,                    "Couldn't get device max write image args."); }
cl_uint          deviceMemBaseAddrAlign(cl_device_id device)                               { return deviceUint(device,               CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get device mem base addr align."); }
cl_uint          deviceNativeVectorWidthChar(cl_device_id device)                          { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,                "Couldn't get device native vector width char."); }
cl_uint          deviceNativeVectorWidthDouble(cl_device_id device)                        { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,              "Couldn't get device native vector width double."); }
cl_uint          deviceNativeVectorWidthFloat(cl_device_id device)                         { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,               "Couldn't get device native vector width float."); }
cl_uint          deviceNativeVectorWidthHalf(cl_device_id device)                          { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,                "Couldn't get device native vector width half."); }
cl_uint          eviceNativeVectorWidthInt(cl_device_id device)                            { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,                 "Couldn't get device native vector width int."); }
cl_uint          eviceNativeVectorWidthLong(cl_device_id device)                           { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,                "Couldn't get device native vector width long."); }
cl_uint          eviceNativeVectorWidthShort(cl_device_id device)                          { return deviceUint(device,               CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,               "Couldn't get device native vector width short."); }
cl_uint          eviceNonUniformWorkGroupSupport(cl_device_id device)                      { return deviceUint(device,               CL_DEVICE_NON_UNIFORM_WORK_GROUP_SUPPORT,          "Couldn't get device device non uniform work group support."); }
cl_uint          deviceNumericVersion(cl_device_id device)                                 { return deviceUint(device,               CL_DEVICE_NUMERIC_VERSION,                         "Couldn't get device numeric version."); }
cl_uint          devicePartitionMaxSubDevices(cl_device_id device)                         { return deviceUint(device,               CL_DEVICE_PARTITION_MAX_SUB_DEVICES,               "Couldn't get device partition max sub devices."); }
cl_uint          devicePipeMaxActiveReservations(cl_device_id device)                      { return deviceUint(device,               CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get device pipe max active reservations."); }
cl_uint          devicePipeMaxPacketSize(cl_device_id device)                              { return deviceUint(device,               CL_DEVICE_MAX_PIPE_ARGS,                           "Couldn't get device pipe max packet size."); }
cl_uint          devicePipeSupport(cl_device_id device)                                    { return deviceUint(device,               CL_DEVICE_PIPE_SUPPORT,                            "Couldn't get device device pipe support."); }
cl_uint          devicePreferredGlobalAtomicAlignment(cl_device_id device)                 { return deviceUint(device,               CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT,       "Couldn't get device preferred global atomic alignment."); }
cl_uint          devicePreferredInteropUserSync(cl_device_id device)                       { return deviceUint(device,               CL_DEVICE_PREFERRED_INTEROP_USER_SYNC,             "Couldn't get device device preferred interop user sync."); }
cl_uint          devicePreferredLocalAtomicAlignment(cl_device_id device)                  { return deviceUint(device,               CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT,        "Couldn't get device preferred local atomic alignment."); }
cl_uint          devicePreferredPlatformAtomicAlignment(cl_device_id device)               { return deviceUint(device,               CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT,     "Couldn't get device preferred platform atomic alignment."); }
cl_uint          devicePreferredVectorWidthChar(cl_device_id device)                       { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,             "Couldn't get device preferred vector width char."); }
cl_uint          devicePreferredVectorWidthDouble(cl_device_id device)                     { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,           "Couldn't get device preferred vector width double."); }
cl_uint          devicePreferredVectorWidthFloat(cl_device_id device)                      { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,            "Couldn't get device preferred vector width float."); }
cl_uint          devicePreferredVectorWidthHalf(cl_device_id device)                       { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,             "Couldn't get device preferred vector width half."); }
cl_uint          devicePreferredVectorWidthInt(cl_device_id device)                        { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,              "Couldn't get device preferred vector width int."); }
cl_uint          devicePreferredVectorWidthLong(cl_device_id device)                       { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,             "Couldn't get device preferred vector width long."); }
cl_uint          devicePreferredVectorWidthShort(cl_device_id device)                      { return deviceUint(device,               CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,            "Couldn't get device preferred vector width short."); }
cl_uint          deviceQueueOnDeviceMaxSize(cl_device_id device)                           { return deviceUint(device,               CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE,                "Couldn't get device queue on device max size."); }
cl_uint          deviceQueueOnDevicePreferredSize(cl_device_id device)                     { return deviceUint(device,               CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE,          "Couldn't get device queue on device preferred size."); }
cl_uint          deviceReferenceCount(cl_device_id device)                                 { return deviceUint(device,               CL_DEVICE_REFERENCE_COUNT,                         "Couldn't get device reference count."); }
cl_uint          deviceSubGroupIndependentForwardProgress(cl_device_id device)             { return deviceUint(device,               CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS,  "Couldn't get device device sub group independent forward progress."); }
cl_uint          deviceVendorID(cl_device_id device)                                       { return deviceUint(device,               CL_DEVICE_VENDOR_ID,                               "Couldn't get device device vendor."); }
cl_uint          deviceWorkGroupCollectiveFunctionsSupport(cl_device_id device)            { return deviceUint(device,               CL_DEVICE_WORK_GROUP_COLLECTIVE_FUNCTIONS_SUPPORT, "Couldn't get device device work group collective functions support."); }
size_t           deviceGlobalVariablePreferredTotalSize(cl_device_id device)               { return deviceSizeT(device,              CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE,    "Couldn't get device global variable preferred total size."); }
size_t           deviceImage2dMaxHeight(cl_device_id device)                               { return deviceSizeT(device,              CL_DEVICE_IMAGE2D_MAX_HEIGHT,                      "Couldn't get device image2d max height."); }
size_t           deviceImage2dMaxWidth(cl_device_id device)                                { return deviceSizeT(device,              CL_DEVICE_IMAGE2D_MAX_WIDTH,                       "Couldn't get device image2d max width."); }
size_t           deviceImage3dMaxDepth(cl_device_id device)                                { return deviceSizeT(device,              CL_DEVICE_IMAGE3D_MAX_DEPTH,                       "Couldn't get device image3d max depth."); }
size_t           deviceImage3dMaxHeight(cl_device_id device)                               { return deviceSizeT(device,              CL_DEVICE_IMAGE3D_MAX_HEIGHT,                      "Couldn't get device image3d max height."); }
size_t           deviceImage3dmaxWidth(cl_device_id device)                                { return deviceSizeT(device,              CL_DEVICE_IMAGE3D_MAX_WIDTH,                       "Couldn't get device image3d max width."); }
size_t           deviceImageMaxArraySize(cl_device_id device)                              { return deviceSizeT(device,              CL_DEVICE_IMAGE_MAX_ARRAY_SIZE,                    "Couldn't get device image max array size."); }
size_t           deviceImageMaxBufferSize(cl_device_id device)                             { return deviceSizeT(device,              CL_DEVICE_IMAGE_MAX_BUFFER_SIZE,                   "Couldn't get device image max buffer size."); }
size_t           deviceMaxGlobalVariableSize(cl_device_id device)                          { return deviceSizeT(device,              CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE,                "Couldn't get device max global variable size."); }
size_t           deviceMaxParameterSize(cl_device_id device)                               { return deviceSizeT(device,              CL_DEVICE_MAX_PARAMETER_SIZE,                      "Couldn't get device max parameter size."); }
size_t           deviceMaxWorkGroupSize(cl_device_id device)                               { return deviceSizeT(device,              CL_DEVICE_MAX_WORK_GROUP_SIZE,                     "Couldn't get device max work group size."); }
size_t           devicePreferredWorkGroupSizeMultiple(cl_device_id device)                 { return deviceSizeT(device,              CL_DEVICE_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,      "Couldn't get device preferred work group size multiple."); }
size_t           devicePrintfBufferSize(cl_device_id device)                               { return deviceSizeT(device,              CL_DEVICE_PRINTF_BUFFER_SIZE,                      "Couldn't get device printf buffer size."); }
size_t           deviceProfilingTimerResolution(cl_device_id device)                       { return deviceSizeT(device,              CL_DEVICE_PROFILING_TIMER_RESOLUTION,              "Couldn't get device profiling timer resolution."); }
cl_ulong         deviceMaxMemAllocSize(cl_device_id device)                                { return deviceUlong(device,              CL_DEVICE_MAX_MEM_ALLOC_SIZE,                      "Couldn't get device max mem alloc size."); }
cl_ulong         deviceGlobalMemCacheSize(cl_device_id device)                             { return deviceUlong(device,              CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,                   "Couldn't get device global mem cache size."); }
cl_ulong         deviceGlobalMemSize(cl_device_id device)                                  { return deviceUlong(device,              CL_DEVICE_GLOBAL_MEM_SIZE,                         "Couldn't get device global mem size."); }
cl_ulong         deviceMaxConstantBufferSize(cl_device_id device)                          { return deviceUlong(device,              CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,                "Couldn't get device max constant buffer size."); }
cl_ulong         deviceLocalMemSize(cl_device_id device)                                   { return deviceUlong(device,              CL_DEVICE_LOCAL_MEM_SIZE,                          "Couldn't get device local mem size."); }
GArray*          deviceAtomicMemoryCapabilities(cl_device_id device)                       { return deviceAtomicCapabilities(device, CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES,              "Couldn't get device atomic capabilities." ); }
GArray*          deviceAtomicFenceCapabilities(cl_device_id device)                        { return deviceAtomicCapabilities(device, CL_DEVICE_ATOMIC_FENCE_CAPABILITIES,               "Couldn't get device atomic capabilities." ); }
GArray*          deviceDoubleFPConfig(cl_device_id device)                                 { return deviceFPConfig(device,           CL_DEVICE_DOUBLE_FP_CONFIG,                        "Couldn't get device atomic capabilities."); }
GArray*          devicePartitionProperties(cl_device_id device)                            { return devicePartitions(device,         CL_DEVICE_PARTITION_PROPERTIES,                    "Couldn't get device partition properties."); }
GArray*          devicePartitionType(cl_device_id device)                                  { return devicePartitions(device,         CL_DEVICE_PARTITION_TYPE,                          "Couldn't get device partition types."); }
GArray*          deviceSingleFPConfig(cl_device_id device)                                 { return deviceFPConfig(device,           CL_DEVICE_SINGLE_FP_CONFIG,                        "Couldn't get device atomic capabilities."); }
GArray*          deviceQueueOnDeviceProperties(cl_device_id device)                        { return deviceQueueProperties(device,    CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES,              "Couldn't get device queue properties." ); }
GArray*          deviceQueueOnHostProperties(cl_device_id device)                          { return deviceQueueProperties(device,    CL_DEVICE_QUEUE_ON_HOST_PROPERTIES,                "Couldn't get device queue properties." ); }
