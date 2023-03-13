/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/execution_environment/execution_environment.h"

#include "level_zero/sysman/source/sysman_device_imp.h"

#include <cstring>
#include <vector>

namespace L0 {
namespace Sysman {

SysmanDevice *SysmanDevice::create(NEO::ExecutionEnvironment &executionEnvironment, const uint32_t rootDeviceIndex) {

    SysmanDeviceImp *pSysmanDevice = new SysmanDeviceImp(&executionEnvironment, rootDeviceIndex);
    DEBUG_BREAK_IF(!pSysmanDevice);
    if (pSysmanDevice->init() != ZE_RESULT_SUCCESS) {
        delete pSysmanDevice;
        pSysmanDevice = nullptr;
    }
    return pSysmanDevice;
}

ze_result_t SysmanDevice::fabricPortGet(zes_device_handle_t hDevice, uint32_t *pCount, zes_fabric_port_handle_t *phPort) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->fabricPortGet(pCount, phPort);
}
ze_result_t SysmanDevice::memoryGet(zes_device_handle_t hDevice, uint32_t *pCount, zes_mem_handle_t *phMemory) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->memoryGet(pCount, phMemory);
}

ze_result_t SysmanDevice::powerGet(zes_device_handle_t hDevice, uint32_t *pCount, zes_pwr_handle_t *phPower) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->powerGet(pCount, phPower);
}

ze_result_t SysmanDevice::powerGetCardDomain(zes_device_handle_t hDevice, zes_pwr_handle_t *phPower) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->powerGetCardDomain(phPower);
}

ze_result_t SysmanDevice::engineGet(zes_device_handle_t hDevice, uint32_t *pCount, zes_engine_handle_t *phEngine) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->engineGet(pCount, phEngine);
}

ze_result_t SysmanDevice::frequencyGet(zes_device_handle_t hDevice, uint32_t *pCount, zes_freq_handle_t *phFrequency) {
    auto pSysmanDevice = L0::Sysman::SysmanDevice::fromHandle(hDevice);
    return pSysmanDevice->frequencyGet(pCount, phFrequency);
}

} // namespace Sysman
} // namespace L0
