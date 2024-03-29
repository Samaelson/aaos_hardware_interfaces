/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <mutex>

#include <aidl/android/hardware/audio/core/sounddose/BnSoundDose.h>
#include <aidl/android/media/audio/common/AudioDevice.h>
#include <aidl/android/media/audio/common/AudioFormatDescription.h>

namespace aidl::android::hardware::audio::core::sounddose {

// Interface used for processing the data received by a stream.
class StreamDataProcessorInterface {
  public:
    virtual ~StreamDataProcessorInterface() = default;

    virtual void startDataProcessor(
            uint32_t samplerate, uint32_t channelCount,
            const ::aidl::android::media::audio::common::AudioFormatDescription& format) = 0;
    virtual void setAudioDevice(
            const ::aidl::android::media::audio::common::AudioDevice& audioDevice) = 0;
    virtual void process(const void* buffer, size_t size) = 0;
};

class SoundDose : public BnSoundDose {
  public:
    SoundDose() : mRs2Value(DEFAULT_MAX_RS2){};

    ndk::ScopedAStatus setOutputRs2UpperBound(float in_rs2ValueDbA) override;
    ndk::ScopedAStatus getOutputRs2UpperBound(float* _aidl_return) override;
    ndk::ScopedAStatus registerSoundDoseCallback(
            const std::shared_ptr<ISoundDose::IHalSoundDoseCallback>& in_callback) override;

  private:
    std::shared_ptr<ISoundDose::IHalSoundDoseCallback> mCallback;
    float mRs2Value;
};

}  // namespace aidl::android::hardware::audio::core::sounddose
