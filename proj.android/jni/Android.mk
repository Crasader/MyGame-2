LOCAL_PATH := $(call my-dir)
NDK_TOOLCHAIN_VERSION=4.8

APP_CPPFLAGS := -frtti -std=c++11

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)


LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

//��������ӵ�cpp·��
LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/Global.cpp \
				   ../../Classes/MainScene.cpp \
				   ../../Classes/toolFunctions.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/Poker.cpp \
                   ../../Classes/Tool.cpp  \
				   ../../Classes/ShadeLayer.cpp \
				   ../../Classes/GamePlayScene.cpp \
				   ../../Classes/LoginScene.cpp \
				   ../../Classes/PopupLayer.cpp \
				   ../../Classes/PopupScene.cpp \
				   ../../Classes/DebugSimpleServer.cpp \
				   ../../Classes/UserProfileUI.cpp \
				   ../../Classes/TimeLayer.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
