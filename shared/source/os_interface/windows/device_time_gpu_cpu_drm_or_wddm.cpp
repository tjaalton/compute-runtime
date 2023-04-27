/*
 * Copyright (C) 2018-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/execution_environment/root_device_environment.h"
#include "shared/source/os_interface/os_time.h"
#include "shared/source/os_interface/product_helper.h"
#include "shared/source/os_interface/windows/device_time_wddm.h"
#include "shared/source/os_interface/windows/wddm/wddm.h"

namespace NEO {
bool DeviceTimeWddm::getCpuGpuTime(TimeStampData *pGpuCpuTime, OSTime *osTime) {
    bool retVal = false;

    pGpuCpuTime->cpuTimeinNS = 0;
    pGpuCpuTime->gpuTimeStamp = 0;

    TimeStampDataHeader escapeInfo = {};

    if (runEscape(wddm, escapeInfo)) {
        auto &gfxCoreHelper = wddm->getRootDeviceEnvironment().getHelper<GfxCoreHelper>();
        convertTimestampsFromOaToCsDomain(gfxCoreHelper, escapeInfo.data.out.gpuPerfTicks, escapeInfo.data.out.gpuPerfFreq, static_cast<uint64_t>(wddm->getTimestampFrequency()));

        osTime->getCpuTime(&pGpuCpuTime->cpuTimeinNS);
        pGpuCpuTime->gpuTimeStamp = (unsigned long long)escapeInfo.data.out.gpuPerfTicks;
        retVal = true;
    }

    return retVal;
}
} // namespace NEO