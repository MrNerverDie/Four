//
//  CCJSONConverter.cpp
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#include "CCJSONConverter.h"

static CCJSONConverter _sharedConverter;

CCJSONConverter * CCJSONConverter::sharedConverter()
{
    static bool firstUse = true;
    if (firstUse)
    {
        firstUse = false;
    }
    return &_sharedConverter;
}

char * CCJSONConverter::strFrom(CCDictionary *dictionary)
{
    CCAssert(dictionary, "CCJSONConverter:can not convert a null pointer");
    cJSON * json = cJSON_CreateObject();
    convertDictionaryToJson(dictionary, json);
    char* returnStr = cJSON_Print(json);
    cJSON_Delete(json);
    return returnStr;
}

CCDictionary * CCJSONConverter::dictionaryFrom(const char *str)
{
    cJSON * json = cJSON_Parse(str);
    if (!json || json->type!=cJSON_Object) {
        if (json) {
            cJSON_Delete(json);
        }
        return NULL;
    }
    CCAssert(json && json->type==cJSON_Object, "CCJSONConverter:wrong json format");
    CCDictionary * dictionary = new CCDictionary();
    convertJsonToDictionary(json, dictionary);
    cJSON_Delete(json);
    return dictionary;
}

void CCJSONConverter::convertJsonToDictionary(cJSON *json, CCDictionary *dictionary)
{
    dictionary->removeAllObjects();
    cJSON * j = json->child;
    while (j) {
        CCObject * obj = getJsonObj(j);
        dictionary->setObject(obj, j->string);
        j = j->next;
    }
}

void CCJSONConverter::convertDictionaryToJson(CCDictionary *dictionary, cJSON *json)
{
    CCDictElement * pElement = NULL;
    CCDICT_FOREACH(dictionary, pElement){
        CCObject * obj = pElement->getObject();
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToObject(json, pElement->getStrKey(), jsonItem);
    }
}

void CCJSONConverter::convertJsonToArray(cJSON * json, CCArray * array)
{
    array->removeAllObjects();
    int size = cJSON_GetArraySize(json);
    for (int i=0; i<size; i++) {
        cJSON * jsonItem = cJSON_GetArrayItem(json, i);
        CCObject * objItem = getJsonObj(jsonItem);
        array->addObject(objItem);
    }
}

void CCJSONConverter::convertArrayToJson(CCArray * array, cJSON * json)
{
    CCObject * obj = NULL;
    CCARRAY_FOREACH(array, obj){
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToArray(json, jsonItem);
    }
}

cJSON * CCJSONConverter::getObjJson(CCObject * obj)
{
    std::string s = typeid(*obj).name();
    if(s.find("CCDictionary")!=std::string::npos){
        cJSON * json = cJSON_CreateObject();
        convertDictionaryToJson((CCDictionary *)obj, json);
        return json;
    }else if(s.find("CCArray")!=std::string::npos){
        cJSON * json = cJSON_CreateArray();
        convertArrayToJson((CCArray *)obj, json);
        return json;
    }else if(s.find("CCString")!=std::string::npos){
        CCString * s = (CCString *)obj;
        cJSON * json = cJSON_CreateString(s->getCString());
        return json;
    }else if(s.find("CCNumber")!=std::string::npos){
        CCNumber * n = (CCNumber *)obj;
        cJSON * json = cJSON_CreateNumber(n->getDoubleValue());
        return json;
    }else if(s.find("CCNull")!=std::string::npos){
        cJSON * json = cJSON_CreateNull();
        return json;
    }
    CCLog("CCJSONConverter encountered an unrecognized type");
    return NULL;
}

CCObject * CCJSONConverter::getJsonObj(cJSON * json)
{
    switch (json->type) {
        case cJSON_Object:
        {
            CCDictionary * dictionary = new CCDictionary();
            convertJsonToDictionary(json, dictionary);
            return dictionary;
        }
        case cJSON_Array:
        {
            CCArray * array = new CCArray();
            convertJsonToArray(json, array);
            return array;
        }
        case cJSON_String:
        {
            CCString * string = new CCString(json->valuestring);
            return string;
        }
        case cJSON_Number:
        {
            CCNumber * number = new CCNumber(json->valuedouble);
            return number;
        }
        case cJSON_True:
        {
            CCNumber * boolean = new CCNumber(1);
            return boolean;
        }
        case cJSON_False:
        {
            CCNumber * boolean = new CCNumber(0);
            return boolean;
        }
        case cJSON_NULL:
        {
            CCNull * null = new CCNull();
            return null;
        }
        default:
        {
            CCLog("CCJSONConverter encountered an unrecognized type");
            return NULL;
        }
    }
}
