LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Config.cpp \
                   ../../Classes/Fightlayer.cpp \
                   ../../Classes/BaoWuLayer.cpp \
                   ../../Classes/BattleScene.cpp \
                   ../../Classes/Bullet.cpp \
                   ../../Classes/Effect.cpp \
                   	../../Classes/GameData.cpp \
                   ../../Classes/GameMapLayer.cpp \
                   ../../Classes/Gameover.cpp \
                   ../../Classes/GetHeroLayer.cpp \
                   ../../Classes/GroupLayer.cpp \
                   ../../Classes/HeroInfoLayer.cpp \
                   ../../Classes/HeroLayer.cpp \
                   ../../Classes/HeroListLayer.cpp \
                   ../../Classes/HomeLayer.cpp \
                   ../../Classes/JiangLiLayer.cpp \
                   ../../Classes/LoginScene.cpp \
                   ../../Classes/QiangHuaLayer.cpp \
                   ../../Classes/role.cpp \
                   ../../Classes/SceneGame.cpp \
                   ../../Classes/ShengJiLayer.cpp \
                   ../../Classes/shop.cpp \
                   ../../Classes/StoreLayer.cpp \
                   ../../Classes/TipWindows.cpp \
                   ../../Classes/TuJianLayer.cpp \
                   ../../Classes/ZhuangBeiLayer.cpp \
                   ../../Classes/ZhuangBeiShengji.cpp

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
