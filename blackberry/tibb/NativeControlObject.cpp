/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeControlObject.h"

#include "TiObject.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <qtgui/QColor>

#define PROP_SETTING_FUNCTION(NAME)     prop_##NAME

#define PROP_SETTER(NAME)               static int prop_##NAME(NativeControlObject* object, TiObject* obj) \
    {\
        return object->NAME(obj);\
    }

typedef int (*NATIVE_PROPSET_CALLBACK)(NativeControlObject*, TiObject*);

// Prototypes
static vector<NATIVE_PROPSET_CALLBACK> initFunctionMap();

// Statics
static const vector<NATIVE_PROPSET_CALLBACK> s_functionMap = initFunctionMap();


NativeControlObject::NativeControlObject() :
    container_(NULL),
    control_(NULL),
    layout_(NULL),
    left_(0),
    top_(0),
    nextEventId_(1)
{
}

NativeControlObject::~NativeControlObject()
{
}

NAHANDLE NativeControlObject::getNativeHandle() const
{
    return container_;
}

void NativeControlObject::setControl(bb::cascades::Control* control)
{
    if (container_ == NULL)
    {
        container_ = bb::cascades::Container::create();
        container_->setLayout(new bb::cascades::AbsoluteLayout());
        layout_ = new bb::cascades::AbsoluteLayoutProperties;
        container_->setLayoutProperties(layout_);
    }
    container_->add(control);
    control_ = control;
}

int NativeControlObject::getNextEventId()
{
    // Account for overflow.
    if (nextEventId_ < 1)
    {
        // This event id must start at 1 because 0 is reserved. Since
        // V8 will always cast a value of undefined to zero.
        nextEventId_ = 1;
    }
    return nextEventId_++;
}

int NativeControlObject::setVisibility(bool visible)
{
    container_->setVisible(visible);
    return NATIVE_ERROR_OK;
}


// PROP_SETTER creates a static version of functions which
// calls the non-static on method on the NativeControlObject
// class.

PROP_SETTER(setAnchorPoint)
int NativeControlObject::setAnchorPoint(TiObject* obj)
{
    float x;
    float y;
    int error = NativeControlObject::getPoint(obj, &x, &y);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setPivotX(x);
    container_->setPivotY(y);
    return NATIVE_ERROR_OK;
}


PROP_SETTER(setBackgroundColor)
int NativeControlObject::setBackgroundColor(TiObject* obj)
{
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    backgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (container_->isEnabled())
    {
        container_->setBackground(backgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setBackgroundDisableColor)
int NativeControlObject::setBackgroundDisableColor(TiObject* obj)
{
    float r;
    float g;
    float b;
    float a;

    int error = NativeControlObject::getColorComponents(obj, &r, &g, &b, &a);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    disabledBackgroundColor_ = bb::cascades::Color::fromRGBA(r, g, b, a);
    if (!container_->isEnabled())
    {
        container_->setBackground(disabledBackgroundColor_);
    }
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setColor)
int NativeControlObject::setColor(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setData)
int NativeControlObject::setData(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setEnabled)
int NativeControlObject::setEnabled(TiObject* obj)
{
    bool enabled;
    int error = getBoolean(obj, &enabled);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    container_->setEnabled(enabled);
    if (enabled)
    {
        if (backgroundColor_.isValid())
        {
            container_->setBackground(backgroundColor_);
        }
    }
    else
    {
        if (disabledBackgroundColor_.isValid())
        {
            container_->setBackground(disabledBackgroundColor_);
        }
    }
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setFont)
int NativeControlObject::setFont(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setHeight)
int NativeControlObject::setHeight(TiObject* obj)
{
    float height;
    int error = getFloat(obj, &height);
    if (error != NATIVE_ERROR_OK)
    {
        Handle<String> v8str = obj->getValue()->ToString();
        if (v8str.IsEmpty())
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        // TODO: parse height string, e.g., height='100%' height='22px' etc...
        return NATIVE_ERROR_INVALID_ARG;
    }
    container_->setMaxHeight(height);
    container_->setMinHeight(height);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setHintText)
int NativeControlObject::setHintText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setImage)
int NativeControlObject::setImage(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setLabel)
int NativeControlObject::setLabel(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setLeft)
int NativeControlObject::setLeft(TiObject* obj)
{
    float left;
    int error = getFloat(obj, &left);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    ((bb::cascades::Control*)getNativeHandle())->setLeftMargin(left);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setMax)
int NativeControlObject::setMax(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setMin)
int NativeControlObject::setMin(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setOpacity)
int NativeControlObject::setOpacity(TiObject* obj)
{
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    if ((value < 0.0f) || (value > 1.0f))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    control_->setOpacity(value);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setOptions)
int NativeControlObject::setOptions(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setSelectedIndex)
int NativeControlObject::setSelectedIndex(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setText)
int NativeControlObject::setText(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTextAlign)
int NativeControlObject::setTextAlign(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTitle)
int NativeControlObject::setTitle(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setTop)
int NativeControlObject::setTop(TiObject* obj)
{
    float value = 0;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    layout_->setPositionY(value);
    container_->setLayoutProperties(layout_);
    return NATIVE_ERROR_OK;
}

PROP_SETTER(setValue)
int NativeControlObject::setValue(TiObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

PROP_SETTER(setVisible)
int NativeControlObject::setVisible(TiObject* obj)
{
    bool visible;
    int error = getBoolean(obj, &visible);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    return setVisibility(visible);
}

PROP_SETTER(setWidth)
int NativeControlObject::setWidth(TiObject* obj)
{
    float width;
    int error = getFloat(obj, &width);
    if (error != NATIVE_ERROR_OK)
    {
        Handle<String> v8str = obj->getValue()->ToString();
        if (v8str.IsEmpty())
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        // TODO: parse width string, e.g., width='100%' width='22px' etc...
        return NATIVE_ERROR_INVALID_ARG;
    }
    container_->setMaxWidth(width);
    container_->setMinWidth(width);
    return NATIVE_ERROR_OK;
}

// PROP_SETTING_FUNCTION resolves the static name of the function, e.g.,
// PROP_SETTING_FUNCTION(setBackgroundColor) resolves to "prop_setBackgroundColor"

static vector<NATIVE_PROPSET_CALLBACK> initFunctionMap()
{
    vector<NATIVE_PROPSET_CALLBACK> vect;
    vect.resize(N_PROP_LAST);

    vect[N_PROP_UNDEFINED]                         = NULL;
    vect[N_PROP_ANCHOR_POINT]                      = PROP_SETTING_FUNCTION(setAnchorPoint);
    vect[N_PROP_ANIMATED_CENTER_POINT]             = NULL;
    vect[N_PROP_AUTO_LINK]                         = NULL;
    vect[N_PROP_BACKGROUND_COLOR]                  = PROP_SETTING_FUNCTION(setBackgroundColor);
    vect[N_PROP_BACKGROUND_DISABLED_COLOR]         = PROP_SETTING_FUNCTION(setBackgroundDisableColor);
    vect[N_PROP_BACKGROUND_DISABLED_IMAGE]         = NULL;
    vect[N_PROP_BACKGROUND_FOCUSED_COLOR]          = NULL;
    vect[N_PROP_BACKGROUND_FOCUSED_IMAGE]          = NULL;
    vect[N_PROP_BACKGROUND_GRADIANT]               = NULL;
    vect[N_PROP_BACKGROUND_IMAGE]                  = NULL;
    vect[N_PROP_BACKGROUND_LEFT_CAP]               = NULL;
    vect[N_PROP_BACKGROUND_PADDING_BOTTOM]         = NULL;
    vect[N_PROP_BACKGROUND_PADDING_LEFT]           = NULL;
    vect[N_PROP_BACKGROUND_PADDING_RIGHT]          = NULL;
    vect[N_PROP_BACKGROUND_PADDING_TOP]            = NULL;
    vect[N_PROP_BACKGROUND_REPEAT]                 = NULL;
    vect[N_PROP_BACKGROUND_SELECTED_COLOR]         = NULL;
    vect[N_PROP_BACKGROUND_SELECTED_IMAGE]         = NULL;
    vect[N_PROP_BACKGROUND_TOP_CAP]                = NULL;
    vect[N_PROP_BORDER_COLOR]                      = NULL;
    vect[N_PROP_BORDER_RADIUS]                     = NULL;
    vect[N_PROP_BORDER_WIDTH]                      = NULL;
    vect[N_PROP_BOTTOM]                            = NULL;
    vect[N_PROP_CENTER]                            = NULL;
    vect[N_PROP_CHILDREN]                          = NULL;
    vect[N_PROP_COLOR]                             = PROP_SETTING_FUNCTION(setColor);
    vect[N_PROP_ENABLED]                           = PROP_SETTING_FUNCTION(setEnabled);
    vect[N_PROP_ELLIPSIZE]                         = NULL;
    vect[N_PROP_FOCUSABLE]                         = NULL;
    vect[N_PROP_FONT]                              = PROP_SETTING_FUNCTION(setFont);
    vect[N_PROP_HEIGHT]                            = PROP_SETTING_FUNCTION(setHeight);
    vect[N_PROP_HIGHLIGHTED_COLOR]                 = NULL;
    vect[N_PROP_HINT_TEXT]                         = PROP_SETTING_FUNCTION(setHintText);
    vect[N_PROP_HTML]                              = NULL;
    vect[N_PROP_IMAGE]                             = PROP_SETTING_FUNCTION(setImage);
    vect[N_PROP_KEEP_SCREEN_ON]                    = NULL;
    vect[N_PROP_LABEL]                             = PROP_SETTING_FUNCTION(setLabel);
    vect[N_PROP_LAYOUT]                            = NULL;
    vect[N_PROP_LEFT]                              = PROP_SETTING_FUNCTION(setLeft);
    vect[N_PROP_MAX]                               = PROP_SETTING_FUNCTION(setMax);
    vect[N_PROP_MIN]                               = PROP_SETTING_FUNCTION(setMin);
    vect[N_PROP_MINIMUM_FONT_SIZE]                 = NULL;
    vect[N_PROP_OPACITY]                           = PROP_SETTING_FUNCTION(setOpacity);
    vect[N_PROP_OPTIONS]                           = PROP_SETTING_FUNCTION(setOptions);
    vect[N_PROP_RIGHT]                             = NULL;
    vect[N_PROP_SELECTED_INDEX]                    = PROP_SETTING_FUNCTION(setSelectedIndex);
    vect[N_PROP_SHADOW_COLOR]                      = NULL;
    vect[N_PROP_SHADOW_OFFSET]                     = NULL;
    vect[N_PROP_SIZE]                              = NULL;
    vect[N_PROP_SOFT_KEYBOARD_ON_FOCUS]            = NULL;
    vect[N_PROP_TEXT]                              = PROP_SETTING_FUNCTION(setText);
    vect[N_PROP_TEXT_ALIGN]                        = PROP_SETTING_FUNCTION(setTextAlign);
    vect[N_PROP_TEXT_ID]                           = NULL;
    vect[N_PROP_TITLE]                             = PROP_SETTING_FUNCTION(setTitle);
    vect[N_PROP_TOP]                               = PROP_SETTING_FUNCTION(setTop);
    vect[N_PROP_TOUCH_ENABLED]                     = NULL;
    vect[N_PROP_TRANSFORM]                         = NULL;
    vect[N_PROP_VALUE]                             = PROP_SETTING_FUNCTION(setValue);
    vect[N_PROP_VISIBLE]                           = PROP_SETTING_FUNCTION(setVisible);
    vect[N_PROP_WIDTH]                             = PROP_SETTING_FUNCTION(setWidth);
    vect[N_PROP_WORD_WRAP]                         = NULL;
    vect[N_PROP_ZINDEX]                            = NULL;
    vect[N_PROP_DATA]                              = PROP_SETTING_FUNCTION(setData);
    return vect;
}


int NativeControlObject::setPropertyValue(size_t propertyNumber, TiObject* obj)
{
    if ((propertyNumber >= s_functionMap.size())
            || (s_functionMap[propertyNumber] == NULL))
    {
        return NATIVE_ERROR_NOTSUPPORTED;
    }
    return (s_functionMap[propertyNumber])(this, obj);
}

int NativeControlObject::getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a)
{
    QString qcolorString;
    int error = getString(obj, qcolorString);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    if (!QColor::isValidColor(qcolorString))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    QColor qcolor(qcolorString);
    qreal qr, qg, qb, qa;
    qcolor.getRgbF(&qr, &qg, &qb, &qa);
    *r = qr;
    *g = qg;
    *b = qb;
    *a = qa;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getBoolean(TiObject* obj, bool* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsBoolean()) && (!v8value->IsBooleanObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Boolean> b = v8value->ToBoolean();
    *value = b->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getString(TiObject* obj, QString& str)
{
    Handle<Value> value = obj->getValue();
    if (value.IsEmpty())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (!value->IsString())
    {
        value = obj->getValue()->ToString();
    }
    Handle<String> v8string = Handle<String>::Cast(value);
    String::Utf8Value v8UtfString(v8string);
    const char* cStr = *v8UtfString;
    str = cStr;
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getFloat(TiObject* obj, float* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (float)num->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getInteger(TiObject* obj, int* value)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || ((!v8value->IsNumber()) && (!v8value->IsNumberObject()) && (!v8value->IsInt32())))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Number> num = Handle<Number>::Cast(v8value);
    *value = (int)num->Value();
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getStringArray(TiObject* obj, QVector<QString>& value)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsArray())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Array> array = Handle<Array>::Cast(v8value);
    unsigned int uiLength = array->Length();
    for (unsigned int i = 0; i < uiLength; ++i)
    {
        Handle<Value> item = array->Get(Integer::New(i));
        if (item.IsEmpty() || ((!item->IsString()) && (!item->IsStringObject())))
        {
            return NATIVE_ERROR_INVALID_ARG;
        }
        String::Utf8Value v8UtfString(Handle<String>::Cast(item));
        const char* cStr = *v8UtfString;
        value.append(cStr);
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getPoint(TiObject* obj, float* x, float* y)
{
    Handle<Value> v8value = obj->getValue();
    if ((v8value.IsEmpty()) || (!v8value->IsObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> v8obj = Handle<Object>::Cast(v8value);
    Handle<Value> v8x = v8obj->Get(String::New("x"));
    if ((v8x.IsEmpty()) || (!v8x->IsNumber()) || (!v8x->IsNumberObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Value> v8y = v8obj->Get(String::New("y"));
    if ((v8y.IsEmpty()) || (!v8y->IsNumber()) || (!v8y->IsNumberObject()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    if (x != NULL)
    {
        *x = (float)v8x->ToNumber()->Value();
    }
    if (y != NULL)
    {
        *y = (float)v8y->ToNumber()->Value();
    }
    return NATIVE_ERROR_OK;
}

int NativeControlObject::getMapObject(TiObject* obj, QMap<QString, QString>& props)
{
    Handle<Value> v8value = obj->getValue();
    if (v8value.IsEmpty() || !v8value->IsObject())
    {
        return NATIVE_ERROR_INVALID_ARG;
    }
    Handle<Object> object = Handle<Object>::Cast(v8value);
    Handle<Array> keys = object->GetPropertyNames();

    for (unsigned int i = 0; i < keys->Length(); i++)
    {
        v8::Handle<v8::String> key = keys->Get(v8::Integer::New(i))->ToString();
        v8::String::Utf8Value keyStr(key);
        v8::Handle<v8::String> value = object->Get(key)->ToString();
        v8::String::Utf8Value valueStr(value);
        QString strKey = QString::fromUtf8(*keyStr);
        QString strValue = QString::fromUtf8(*valueStr);

        props.insert(strKey, strValue);
    }

    return NATIVE_ERROR_OK;
}

int NativeControlObject::getDictionaryData(TiObject* obj, QVector<QPair<QString, QString> >& dictionary)
{
    Handle<Value> value = obj->getValue();
    if (value.IsEmpty() || (!value->IsArray()))
    {
        return NATIVE_ERROR_INVALID_ARG;
    }

    Handle<Array> array = Handle<Array>::Cast(value);
    uint32_t length = array->Length();
    dictionary.reserve(length);
    //traverse through the dictionary elements
    for (uint32_t i = 0; i < length; ++i)
    {
        Local<Value> el = array->Get(i);
        if (el->IsObject())
        {
            Local<Array> propAr = el->ToObject()->GetPropertyNames();
            uint32_t arLenght = propAr->Length();
            for (uint32_t j = 0; j < arLenght; ++j)
            {
                Handle<String> propString = Handle<String>::Cast(propAr->Get(j));
                String::Utf8Value propNameUTF(propString);
                QString key = QString::fromUtf8(*propNameUTF);
                Local<Value> propValue = el->ToObject()->Get(propString);
                Local<String> valueStr = propValue->ToString();
                String::Utf8Value valueUTF(valueStr);
                QString val = QString::fromUtf8(*valueUTF);
                dictionary.push_back(QPair<QString, QString>(key, val));
            }
        }
        else
        {
            //if the element of the dictionary is not object, it means dictionary contains invalid data
            return NATIVE_ERROR_INVALID_ARG;
        }
    }
    return NATIVE_ERROR_OK;
}
