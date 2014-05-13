//
//  C2DXShareSDKTypeDef.h
//  C2DXShareSDKSample
//
//  Created by 冯 鸿杰 on 13-12-17.
//
//

#ifndef C2DXShareSDKSample_C2DXShareSDKTypeDef_h
#define C2DXShareSDKSample_C2DXShareSDKTypeDef_h

#include "cocos2d.h"
#include <stdint.h>

USING_NS_CC;

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	平台类型
         */
        enum C2DXPlatType
        {
            C2DXPlatTypeSinaWeibo = 1,         /**< 新浪微博 */
            C2DXPlatTypeTencentWeibo = 2,      /**< 腾讯微博 */
            C2DXPlatTypeSohuWeibo = 3,         /**< 搜狐微博 */
            C2DXPlatType163Weibo = 4,          /**< 网易微博 */
            C2DXPlatTypeDouBan = 5,            /**< 豆瓣社区 */
            C2DXPlatTypeQZone = 6,             /**< QQ空间 */
            C2DXPlatTypeRenren = 7,            /**< 人人网 */
            C2DXPlatTypeKaixin = 8,            /**< 开心网 */
            C2DXPlatTypePengyou = 9,           /**< 朋友网 */
            C2DXPlatTypeFacebook = 10,         /**< Facebook */
            C2DXPlatTypeTwitter = 11,          /**< Twitter */
            C2DXPlatTypeEvernote = 12,         /**< 印象笔记 */
            C2DXPlatTypeFoursquare = 13,       /**< Foursquare */
            C2DXPlatTypeGooglePlus = 14,       /**< Google＋ */
            C2DXPlatTypeInstagram = 15,        /**< Instagram */
            C2DXPlatTypeLinkedIn = 16,         /**< LinkedIn */
            C2DXPlatTypeTumblr = 17,           /**< Tumbir */
            C2DXPlatTypeMail = 18,             /**< 邮件分享 */
            C2DXPlatTypeSMS = 19,              /**< 短信分享 */
            C2DXPlatTypeAirPrint = 20,         /**< 打印 */
            C2DXPlatTypeCopy = 21,             /**< 拷贝 */
            C2DXPlatTypeWeixiSession = 22,     /**< 微信好友 */
            C2DXPlatTypeWeixiTimeline = 23,    /**< 微信朋友圈 */
            C2DXPlatTypeQQ = 24,               /**< QQ */
            C2DXPlatTypeInstapaper = 25,       /**< Instapaper */
            C2DXPlatTypePocket = 26,           /**< Pocket */
            C2DXPlatTypeYouDaoNote = 27,       /**< 有道云笔记 */
            C2DXPlatTypeSohuKan = 28,          /**< 搜狐随身看 */
            C2DXPlatTypePinterest = 30,        /**< Pinterest */
            C2DXPlatTypeFlickr = 34,           /**< Flickr */
            C2DXPlatTypeDropbox = 35,          /**< Dropbox */
            C2DXPlatTypeVKontakte = 36,        /**< VKontakte */
            C2DXPlatTypeWeixiFav = 37,         /**< 微信收藏 */
            C2DXPlatTypeYiXinSession = 38,     /**< 易信好友 */
            C2DXPlatTypeYiXinTimeline = 39,    /**< 易信朋友圈 */
            C2DXPlatTypeYiXinFav = 40,         /**< 易信收藏 */
            C2DXPlatTypeAny = 99               /**< 任意平台 */
        };
        
        /**
         *	@brief	内容类型
         */
        enum C2DXContentType
        {
            C2DXContentTypeText = 0, /**< 文本 */
            C2DXContentTypeImage = 1, /**< 图片 */
            C2DXContentTypeNews = 2, /**< 新闻 */
            C2DXContentTypeMusic = 3, /**< 音乐 */
            C2DXContentTypeVideo = 4, /**< 视频 */
            C2DXContentTypeApp = 5, /**< 应用,仅供微信使用 */
            C2DXContentTypeNonGif = 6, /**< 非Gif消息,仅供微信使用 */
            C2DXContentTypeGif = 7, /**< Gif消息,仅供微信使用 */
            C2DXContentTypeFile = 8 /**< 文件消息,仅供微信使用 */
        };
        
        /**
         *	@brief	返回状态
         */
        enum C2DXResponseState
        {
            C2DXResponseStateBegin = 0, /**< 开始 */
            C2DXResponseStateSuccess = 1, /**< 成功 */
            C2DXResponseStateFail = 2, /**< 失败 */
            C2DXResponseStateCancel = 3 /**< 取消 */
        };
        
        /**
         *	@brief	分享菜单指向
         */
        enum C2DXMenuArrowDirection
        {
            C2DXMenuArrowDirectionUp = 1UL << 0, /**< 向上 */
            C2DXMenuArrowDirectionDown = 1UL << 1, /**< 向下 */
            C2DXMenuArrowDirectionLeft = 1UL << 2, /**< 向左 */
            C2DXMenuArrowDirectionRight = 1UL << 3, /**< 向右 */
            C2DXMenuArrowDirectionAny = C2DXMenuArrowDirectionUp | C2DXMenuArrowDirectionDown | C2DXMenuArrowDirectionLeft | C2DXMenuArrowDirectionRight, /**< 任意 */
            C2DXMenuArrowDirectionUnknown = UINT32_MAX /**< 未知 */
        };
        
        /**
         *	@brief	授权返回回调事件
         */
        typedef void(*C2DXAuthResultEvent) (C2DXResponseState state, C2DXPlatType platType, CCDictionary *error);
        
        /**
         *	@brief	获取用户信息返回回调事件
         */
        typedef void(*C2DXGetUserInfoResultEvent) (C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error);
        
        /**
         *	@brief	分享返回回调事件
         */
        typedef void(*C2DXShareResultEvent) (C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error);
    }
}

#endif
