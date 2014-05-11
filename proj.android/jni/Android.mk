LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
#MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/hellocpp/*.cpp)
#MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
#MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/C2DXShareSDK/*.cpp)

#LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

#声明一个变量MY_CPP_PATH表示源码目录
MY_CPP_PATH := $(LOCAL_PATH)/hellocpp/
MY_CPP_PATH += $(LOCAL_PATH)/../../Classes/

#获取目录下的所有文件 
My_All_Files := $(shell find $(MY_CPP_PATH)/.)
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)

#从My_All_Files中再次提取所有的cpp文件,这里也可以使用filter函数
MY_CPP_LIST := $(foreach c_file,$(My_All_Files), $(wildcard $(c_file)/*.cpp) ) 
MY_CPP_LIST := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(MY_CPP_LIST)



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
