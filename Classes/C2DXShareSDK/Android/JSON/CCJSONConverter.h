//
//  CCJSONConverter.h
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#ifndef __cocos2d_x_jc__CCJSONConverter__
#define __cocos2d_x_jc__CCJSONConverter__

#include "cocos2d.h"
using namespace cocos2d;
#include "CCJSONData.h"
#include "cJSON.h"

#define CCJC_CAST_CCNUMBER(__pDict__,__sKey__) dynamic_cast<CCNumber *>(__pDict__->objectForKey(__sKey__))
#define CCJC_CAST_CCSTRING(__pDict__,__sKey__) dynamic_cast<CCString *>(__pDict__->objectForKey(__sKey__))
#define CCJC_CAST_CCBOOL(__pDict__,__sKey__) dynamic_cast<CCBool *>(__pDict__->objectForKey(__sKey__))
#define CCJC_CAST_CCARRAY(__pDict__,__sKey__) dynamic_cast<CCArray *>(__pDict__->objectForKey(__sKey__))
#define CCJC_CAST_CCDICTIONARY(__pDict__,__sKey__) dynamic_cast<CCDictionary *>(__pDict__->objectForKey(__sKey__))
#define CCJC_CAST_CCNULL(__pDict__,__sKey__) dynamic_cast<CCNull *>(__pDict__->objectForKey(__sKey__))

class CCJSONConverter : public CCObject {
    
public:
    static CCJSONConverter * sharedConverter();
    
    char * strFrom(CCDictionary * dictionary);
    
    CCDictionary * dictionaryFrom(const char * str);
    
private:
    void convertJsonToDictionary(cJSON *json, CCDictionary *dictionary);
    
    void convertDictionaryToJson(CCDictionary *dictionary, cJSON *json);
    
    void convertJsonToArray(cJSON * json, CCArray * array);
    
    void convertArrayToJson(CCArray * array, cJSON * json);
    
    cJSON * getObjJson(CCObject * obj);
    
    CCObject * getJsonObj(cJSON * json);
};

#endif /* defined(__cocos2d_x_jc__CCJSONConverter__) */