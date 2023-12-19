/*
 * Copyright (C) 2018-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/command_stream/aub_command_stream_receiver.h"
#include "shared/source/command_stream/command_stream_receiver.h"
#include "shared/source/command_stream/device_command_stream.h"
#include "shared/source/command_stream/linear_stream.h"
#include "shared/source/execution_environment/root_device_environment.h"
#include "shared/source/os_interface/linux/device_command_stream.inl"
#include "shared/source/os_interface/linux/drm_command_stream.h"
#include "shared/source/os_interface/linux/drm_neo.h"
#include "shared/source/os_interface/os_interface.h"
#include "shared/test/common/fixtures/mock_aub_center_fixture.h"
#include "shared/test/common/helpers/debug_manager_state_restore.h"
#include "shared/test/common/helpers/execution_environment_helper.h"
#include "shared/test/common/os_interface/linux/device_command_stream_fixture.h"
#include "shared/test/common/test_macros/hw_test.h"

#include "gtest/gtest.h"

#include <memory>

using namespace NEO;

struct DeviceCommandStreamLeaksTest : ::testing::Test {
    void SetUp() override {
        HardwareInfo *hwInfo = nullptr;
        executionEnvironment = getExecutionEnvironmentImpl(hwInfo, 1);
        executionEnvironment->incRefInternal();
        MockAubCenterFixture::setMockAubCenter(*executionEnvironment->rootDeviceEnvironments[0]);
    }

    void TearDown() override {
        executionEnvironment->decRefInternal();
    }

    ExecutionEnvironment *executionEnvironment;
};

HWTEST_F(DeviceCommandStreamLeaksTest, WhenCreatingDeviceCsrThenValidPointerIsReturned) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    DrmMockSuccess mockDrm(mockFd, *executionEnvironment->rootDeviceEnvironments[0]);
    EXPECT_NE(nullptr, ptr);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenDefaultDrmCsrWhenItIsCreatedThenGemCloseWorkerInactiveModeIsSelected) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();
    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerActive);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenDefaultDrmCsrWithAubDumWhenItIsCreatedThenGemCloseWorkerInactiveModeIsSelected) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(true, *executionEnvironment, 0, 1));
    auto drmCsrWithAubDump = (CommandStreamReceiverWithAUBDump<DrmCommandStreamReceiver<FamilyType>> *)ptr.get();
    EXPECT_EQ(drmCsrWithAubDump->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerActive);
    auto aubCSR = static_cast<CommandStreamReceiverWithAUBDump<DrmCommandStreamReceiver<FamilyType>> *>(ptr.get())->aubCSR.get();
    EXPECT_NE(nullptr, aubCSR);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenDefaultDrmCsrWhenOsInterfaceIsNullptrThenValidateDrm) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();
    EXPECT_NE(nullptr, executionEnvironment->rootDeviceEnvironments[0]->osInterface);
    auto expected = drmCsr->getOSInterface()->getDriverModel()->template as<NEO::Drm>();
    auto got = executionEnvironment->rootDeviceEnvironments[0]->osInterface->getDriverModel()->as<NEO::Drm>();
    EXPECT_EQ(expected, got);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenDisabledGemCloseWorkerWhenCsrIsCreatedThenGemCloseWorkerInactiveModeIsSelected) {
    DebugManagerStateRestore restorer;
    debugManager.flags.EnableGemCloseWorker.set(0u);

    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();

    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerInactive);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenEnabledGemCloseWorkerWhenCsrIsCreatedThenGemCloseWorkerActiveModeIsSelected) {
    DebugManagerStateRestore restorer;
    debugManager.flags.EnableGemCloseWorker.set(1u);

    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();

    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerActive);
}

HWTEST_F(DeviceCommandStreamLeaksTest, givenDefaultGemCloseWorkerWhenCsrIsCreatedThenGemCloseWorkerActiveModeIsSelected) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();

    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerActive);
}

using DeviceCommandStreamSetInternalUsageTests = DeviceCommandStreamLeaksTest;

HWTEST_F(DeviceCommandStreamSetInternalUsageTests, givenValidDrmCsrThenGemCloseWorkerOperationModeIsSetToInactiveWhenInternalUsageIsSet) {
    std::unique_ptr<CommandStreamReceiver> ptr(DeviceCommandStreamReceiver<FamilyType>::create(false, *executionEnvironment, 0, 1));
    auto drmCsr = (DrmCommandStreamReceiver<FamilyType> *)ptr.get();
    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerActive);

    drmCsr->initializeDefaultsForInternalEngine();
    EXPECT_EQ(drmCsr->peekGemCloseWorkerOperationMode(), GemCloseWorkerMode::gemCloseWorkerInactive);
}
