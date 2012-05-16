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
class QVector<class T>;

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
    virtual int setOptions(TiObject* obj);
    virtual int setSelectedIndex(TiObject* obj);
    static int _getColorComponents(TiObject* obj, float* r, float* g, float* b, float* a);
    static int _getBoolean(TiObject* obj, bool* value);
    static int _getString(TiObject* obj, QString& str);
    static int _getFloat(TiObject* obj, float* value);
    static int _getStringArray(TiObject* obj, QVector<QString>& value);
    static int _getInteger(TiObject* obj, int* value);

protected:
    NativeControlObject();
    virtual ~NativeControlObject();
    virtual bb::cascades::Control* getControl() const;
    virtual void setControl(bb::cascades::Control* control);

private:
    bb::cascades::Control* control_;
};

#endif /* NATIVECONTROLOBJECT_H_ */
