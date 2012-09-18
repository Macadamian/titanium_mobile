/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeProgressBarObject.h"

NativeProgressBarObject::NativeProgressBarObject(TiObject* tiObject)
    : NativeControlObject(tiObject)
{
    progressIndicator_ = NULL;
}

NativeProgressBarObject::~NativeProgressBarObject()
{
}

int NativeProgressBarObject::getObjectType() const
{
    return N_TYPE_PROGRESSBAR;
}

NativeProgressBarObject* NativeProgressBarObject::createProgressBar(TiObject* tiObject)
{
    return new NativeProgressBarObject(tiObject);
}

int NativeProgressBarObject::initialize()
{
    progressIndicator_ = bb::cascades::ProgressIndicator::create();
    setControl(progressIndicator_);
    return NATIVE_ERROR_OK;
}

int NativeProgressBarObject::setMax(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setToValue(value);
    return NATIVE_ERROR_OK;
}

int NativeProgressBarObject::setMin(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setFromValue(value);
    return NATIVE_ERROR_OK;
}

int NativeProgressBarObject::setValue(TiObject* obj)
{
    float value;
    int error = NativeControlObject::getFloat(obj, &value);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    progressIndicator_->setValue(value);
    return NATIVE_ERROR_OK;
}
