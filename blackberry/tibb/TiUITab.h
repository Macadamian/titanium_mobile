/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUITAB_H_
#define TIUITAB_H_

#include "TiUIBase.h"

/*
 * TiUITab
 *
 * Represents a Titanium Tab object
 *
 * This object can be created by:
 * Titanium.UI.createTab({...});
 */
class TiUITab : public TiUIBase
{
public:
    static TiUITab* createTab(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUITab();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
    static Handle<Value> open_(void* userContext, TiObject* caller, const Arguments& args);

    TiUITab();
    //This class is neither copy-constructible nor assignable
    TiUITab(const TiUITab& obj);
    TiUITab& operator=(const TiUITab& obj);
};

#endif /* TIUITAB_H_ */
