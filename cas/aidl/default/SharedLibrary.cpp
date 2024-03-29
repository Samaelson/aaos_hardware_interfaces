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

#define LOG_TAG "android.hardware.cas-SharedLibrary"

#include "SharedLibrary.h"
#include <dlfcn.h>
#include <utils/Log.h>

namespace aidl {
namespace android {
namespace hardware {
namespace cas {

SharedLibrary::SharedLibrary(const String8& path) {
    mLibHandle = dlopen(path.c_str(), RTLD_NOW);
}

SharedLibrary::~SharedLibrary() {
    if (mLibHandle != NULL) {
        dlclose(mLibHandle);
        mLibHandle = NULL;
    }
}

bool SharedLibrary::operator!() const {
    return mLibHandle == NULL;
}

void* SharedLibrary::lookup(const char* symbol) const {
    if (!mLibHandle) {
        return NULL;
    }
    // Clear last error before we load the symbol again,
    // in case the caller didn't retrieve it.
    (void)dlerror();
    return dlsym(mLibHandle, symbol);
}

const char* SharedLibrary::lastError() const {
    const char* error = dlerror();
    return error ? error : "No errors or unknown error";
}

}  // namespace cas
}  // namespace hardware
}  // namespace android
}  // namespace aidl
