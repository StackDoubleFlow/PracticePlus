LOCAL_PATH := $(call my-dir)

TARGET_ARCH_ABI := arm64-v8a

include $(CLEAR_VARS)
LOCAL_MODULE := hook
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
include $(CLEAR_VARS)
LOCAL_MODULE	        := modloader
LOCAL_SRC_FILES         := ./extern/beatsaber-hook/libs/arm64-v8a/libmodloader.so
LOCAL_EXPORT_C_INCLUDES := ./extern/beatsaber-hook/include/
include $(PREBUILT_SHARED_LIBRARY)

# Build the beatsaber-hook shared library, SPECIFICALLY VERSIONED!
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_0_6_0
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_0_6_0.so
include $(PREBUILT_SHARED_LIBRARY)

# Build the CustomUI shared library
include $(CLEAR_VARS)
LOCAL_MODULE := customui
LOCAL_EXPORT_C_INCLUDES := ./extern/BeatSaberQuestCustomUI/shared
LOCAL_SRC_FILES := ./extern/BeatSaberQuestCustomUI/libs/arm64-v8a/libcustomui.so
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: modloader - version: 1.0.2
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: custom-ui - version: 0.1.1
include $(CLEAR_VARS)
LOCAL_MODULE := custom-ui_0_1_1
LOCAL_EXPORT_C_INCLUDES := extern/custom-ui
LOCAL_SRC_FILES := extern/libcustom-ui_0_1_1.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := PracticePlus_0_3_0
LOCAL_SRC_FILES := $(call rwildcard,src/,*.cpp)
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_SHARED_LIBRARIES += beatsaber-hook_0_6_0
LOCAL_SHARED_LIBRARIES += customui
LOCAL_SHARED_LIBRARIES += custom-ui_0_1_1
LOCAL_LDLIBS += -llog
LOCAL_CFLAGS += -I'c:/Program Files/Unity/Hub/Editor/2019.3.1f1/Editor/Data/il2cpp/libil2cpp' -DID='"PracticePlus"' -DVERSION='"0.3.0"' -I'./shared' -I'./extern'
LOCAL_CPPFLAGS += -std=c++2a
LOCAL_C_INCLUDES += ./include ./src
include $(BUILD_SHARED_LIBRARY)
