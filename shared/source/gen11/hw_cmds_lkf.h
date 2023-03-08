/*
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/gen11/hw_cmds_base.h"
#include "shared/source/helpers/hw_info.h"

namespace NEO {

struct LKF : public Gen11Family {
    static const PLATFORM platform;
    static const HardwareInfo hwInfo;
    static FeatureTable featureTable;
    static WorkaroundTable workaroundTable;
    static const uint32_t maxEuPerSubslice = 8;
    static const uint32_t maxSlicesSupported = 1;
    static const uint32_t maxSubslicesSupported = 8;
    static const RuntimeCapabilityTable capabilityTable;
    static void (*setupHardwareInfo)(HardwareInfo *hwInfo, bool setupFeatureTableAndWorkaroundTable, uint64_t hwInfoConfig, const CompilerProductHelper &compilerProductHelper);
    static void setupFeatureAndWorkaroundTable(HardwareInfo *hwInfo);
    static void setupHardwareInfoBase(HardwareInfo *hwInfo, bool setupFeatureTableAndWorkaroundTable, const CompilerProductHelper &compilerProductHelper);
};
class LkfHw1x8x8 : public LKF {
  public:
    static void setupHardwareInfo(HardwareInfo *hwInfo, bool setupFeatureTableAndWorkaroundTable, const CompilerProductHelper &compilerProductHelper);
    static const HardwareInfo hwInfo;

  private:
    static GT_SYSTEM_INFO gtSystemInfo;
};

} // namespace NEO
