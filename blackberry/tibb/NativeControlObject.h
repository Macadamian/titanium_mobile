/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVECONTROLOBJECT_H_
#define NATIVECONTROLOBJECT_H_

#include "NativeObject.h"
#include <bb/cascades/Control>

/*
 * NativeControlObject
 *
 * Base class for all UI controls
 */

class TiObject;
class QString;

class NativeControlObject : public NativeObject
{
public:
    virtual int setPropertyValue(int propertyNumber, TiObject* obj);

    virtual int setBackgroundColor(TiObject* obj);
    virtual int setColor(TiObject* obj);
    virtual int setLabel(TiObject* obj);
    virtual int setMax(TiObject* obj);
    virtual int setMin(TiObject* obj);
    virtual int setText(TiObject* obj);
    virtual int setTextAlign(TiObject* obj);
    virtual int setTop(TiObject* obj);
    virtual int setTitle(TiObject* obj);
    virtual int setValue(TiObject* obj);
    virtual int setVisible(TiObject* obj);
    static int getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a);
    static int getBoolean(TiObject* obj, bool* value);
    static int getString(TiObject* obj, QString& str);
    static int getFloat(TiObject* obj, float* value);
    virtual int setTop(float top);
protected:
    NativeControlObject();
    virtual ~NativeControlObject();
    virtual bb::cascades::Control* getControl() const;
    virtual void setControl(bb::cascades::Control* control);

private:
    bb::cascades::Control* control_;
};

#endif /* NATIVECONTROLOBJECT_H_ */
