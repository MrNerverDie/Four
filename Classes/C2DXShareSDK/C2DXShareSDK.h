//
//  C2DXShareSDK.h
//  C2DXShareSDKSample
//
//  Created by 冯 鸿杰 on 13-12-17.
//
//

#ifndef __C2DXShareSDKSample__C2DXShareSDK__
#define __C2DXShareSDKSample__C2DXShareSDK__

#include <iostream>
#include "cocos2d.h"
#include "C2DXShareSDKTypeDef.h"

USING_NS_CC;

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	ShareSDK
         */
        class C2DXShareSDK
        {
        public:
            
            /**
             *	@brief	初始化ShareSDK
             *
             *	@param 	appKey 	应用Key
             *	@param 	useAppTrusteeship 	是否使用应用信息托管
             */
            static void open(CCString *appKey, bool useAppTrusteeship);

            /**
             *	@brief	关闭ShareSDK
             */
            static void close();
            
            /**
             *	@brief	设置平台配置信息
             *
             *	@param 	platType 	平台类型
             *	@param 	configInfo 	配置信息
             */
            static void setPlatformConfig(C2DXPlatType platType, CCDictionary *configInfo);
            
            /**
             *	@brief	用户授权
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static void authorize(C2DXPlatType platType, C2DXAuthResultEvent callback);
            
            /**
             *	@brief	取消用户授权
             *
             *	@param 	platType 	平台类型
             */
            static void cancelAuthorize(C2DXPlatType platType);

            /**
             *	@brief	用户是否授权
             *
             *	@param 	platType 	平台类型
             *
             *	@return	true 已授权， false 尚未授权
             */
            static bool hasAutorized(C2DXPlatType platType);
            
            /**
             *	@brief	获取用户信息
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static void getUserInfo(C2DXPlatType platType, C2DXGetUserInfoResultEvent callback);

            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void shareContent(C2DXPlatType platType, CCDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	一键分享内容
             *
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void oneKeyShareContent(CCArray *platTypes, CCDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void showShareMenu(CCArray *platTypes, CCDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	pt          弹出分享菜单的位置，仅用于设置iPad分享菜单弹出
             *  @param  direction   弹出分享菜单指向，仅用于设置iPad分享菜单弹出
             *	@param 	callback 	回调方法
             */
            static void showShareMenu(CCArray *platTypes, CCDictionary *content, CCPoint pt, C2DXMenuArrowDirection direction, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享视图
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void showShareView(C2DXPlatType platType, CCDictionary *content, C2DXShareResultEvent callback);


        };
    }
}



#endif /* defined(__C2DXShareSDKSample__C2DXShareSDK__) */
