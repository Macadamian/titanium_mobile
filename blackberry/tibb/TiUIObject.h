/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIOBJECT_H_
#define TIUIOBJECT_H_

#include "TiObject.h"


/*
 * TiUIObject
 *
 * Titanium.UI namespace
 */
class TiUIObject : public TiObject
{
public:
    static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);

protected:
    virtual ~TiUIObject();
    virtual void onCreateStaticMembers();

private:
    TiUIObject();
    TiUIObject(NativeObjectFactory* objectFactory);
    static Handle<Value> createTabGroup_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createWindow_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createLabel_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createButton_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createSlider_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createProgressBar_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createImageView_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createTextField_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createActivityIndicator_(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> createSwitch_(void* userContext, TiObject* caller, const Arguments& args);
    NativeObjectFactory* objectFactory_;
    NativeObject* contentContainer_;
};

#endif /* TIUIOBJECT_H_ */
