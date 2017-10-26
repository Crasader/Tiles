LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/Scene/GameStartScene.cpp \
                   ../../../Classes/Scene/GameScene.cpp  \
				   ../../../Classes/Scene/GameLogoScene.cpp  \
				   ../../../Classes/AppDelegate.cpp  \
				   ../../../Classes/ConstUtil.hpp \
				   ../../../Classes/SimpleRecognizer.cpp  \
				   ../../../Classes/Card/Card.cpp  \
				   ../../../Classes/Layer/ExchangeLayer.cpp  \
				   ../../../Classes/Layer/GameOverLayer.cpp  \
				   ../../../Classes/Layer/GuideLayer.cpp  \
				   ../../../Classes/Layer/PauseLayer.cpp  \
				   ../../../Classes/Manager/GameManager.cpp \
				   ../../../Classes/Manager/SaveManager.cpp \
				   ../../../Classes/Manager/ResourceManager.cpp  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
