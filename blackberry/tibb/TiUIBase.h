/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBASE_H_
#define TIUIBASE_H_

#include "TiProxy.h"
#include <vector>

using namespace std;

class TiCascadesApp;

/*
 * TiUIBase
 *
 * Titanium base class for all UI objects such as windows, labels, buttons, etc...
 */
class TiUIBase : public TiProxy
{
public:
    virtual void setParametersFromObject(void* userContext, Local<Object> obj);
    virtual bool isUIObject() const;
    virtual void setTiMappingProperties(const TiProperty* props, int propertyCount);

protected:
    TiUIBase(const char* name);
    TiUIBase();
    virtual ~TiUIBase();
    virtual bool canAddMembers() const;
    virtual void onCreateStaticMembers();
    Persistent<Object> createConfig_;
    vector<ObjectEntry> childControls_;

private:
    static VALUE_MODIFY _valueModify(int propertyNumber, TiObject* value, void* context);
    static Handle<Value> _getChildren(void* userContext);
    static Handle<Value> _hide(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _remove(void* userContext, TiObject* caller, const Arguments& args);
    static Handle<Value> _show(void* userContext, TiObject* caller, const Arguments& args);

protected:
    static Handle<Value> _add(void* userContext, TiObject* caller, const Arguments& args);

private:
    // fields
    NativeObject* nativeObject_;
    NativeObjectFactory* nativeObjectFactory_;

};

#endif /* TIUIBASE_H_ */
