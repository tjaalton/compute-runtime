/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "CL/cl.h"

/**********************************
 * Internal only queue properties *
 **********************************/
// Intel evaluation now. Remove it after approval for public release
#define CL_DEVICE_DRIVER_VERSION_INTEL 0x10010

#define CL_DEVICE_DRIVER_VERSION_INTEL_NEO1 0x454E4831 // Driver version is ENH1

/*********************************
 * cl_intel_debug_info extension *
 *********************************/
#define cl_intel_debug_info 1

// New queries for clGetProgramInfo:
#define CL_PROGRAM_DEBUG_INFO_INTEL 0x4100
#define CL_PROGRAM_DEBUG_INFO_SIZES_INTEL 0x4101

// New queries for clGetKernelInfo:
#define CL_KERNEL_BINARY_PROGRAM_INTEL 0x407D
#define CL_KERNEL_BINARIES_INTEL 0x4102
#define CL_KERNEL_BINARY_SIZES_INTEL 0x4103
#define CL_KERNEL_BINARY_GPU_ADDRESS_INTEL 0x10010

/********************************************
 * event properties for performance counter *
 ********************************************/
/* performance counter */
#define CL_PROFILING_COMMAND_PERFCOUNTERS_INTEL 0x407F

/**************************
 * Internal only cl types *
 **************************/

using cl_mem_properties_intel = cl_bitfield;
using cl_mem_flags_intel = cl_mem_flags;
using cl_mem_info_intel = cl_uint;
using cl_mem_advice_intel = cl_uint;
using cl_unified_shared_memory_type_intel = cl_uint;
using cl_unified_shared_memory_capabilities_intel = cl_bitfield;

/******************************
 * Internal only cl_mem_flags *
 ******************************/

#define CL_MEM_FLAGS_INTEL 0x10001
#define CL_MEM_LOCALLY_UNCACHED_RESOURCE (1 << 18)

// Used with clEnqueueVerifyMemory
#define CL_MEM_COMPARE_EQUAL 0u
#define CL_MEM_COMPARE_NOT_EQUAL 1u

#define CL_MEM_FORCE_LINEAR_STORAGE_INTEL (1 << 19)
#define CL_MEM_FORCE_SHARED_PHYSICAL_MEMORY_INTEL (1 << 20)

#define CL_MEM_ALLOCATION_HANDLE_INTEL 0x10050

/******************************
*        UNIFIED MEMORY       *
*******************************/

#define CL_KERNEL_EXEC_INFO_INDIRECT_HOST_ACCESS_INTEL 0x41A0
#define CL_KERNEL_EXEC_INFO_INDIRECT_DEVICE_ACCESS_INTEL 0x41A1
#define CL_KERNEL_EXEC_INFO_INDIRECT_SHARED_ACCESS_INTEL 0x41A2
#define CL_KERNEL_EXEC_INFO_USM_PTRS_INTEL 0x41A3

// New queries for clGetDeviceInfo:
#define CL_DEVICE_HOST_MEM_CAPABILITIES_INTEL 0x4190
#define CL_DEVICE_DEVICE_MEM_CAPABILITIES_INTEL 0x4191
#define CL_DEVICE_SINGLE_DEVICE_SHARED_MEM_CAPABILITIES_INTEL 0x4192
#define CL_DEVICE_CROSS_DEVICE_SHARED_MEM_CAPABILITIES_INTEL 0x4193
#define CL_DEVICE_SHARED_SYSTEM_MEM_CAPABILITIES_INTEL 0x4194

#define CL_MEM_ALLOC_TYPE_INTEL 0x419A
#define CL_MEM_ALLOC_BASE_PTR_INTEL 0x419B
#define CL_MEM_ALLOC_SIZE_INTEL 0x419C

#define CL_MEM_TYPE_UNKNOWN_INTEL 0x4196
#define CL_MEM_TYPE_HOST_INTEL 0x4197
#define CL_MEM_TYPE_DEVICE_INTEL 0x4198
#define CL_MEM_TYPE_SHARED_INTEL 0x4199
