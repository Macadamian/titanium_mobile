/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVETOGGLEBUTTONOBJECT_H_
#define NATIVETOGGLEBUTTONOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class ToggleButton;
}
}

class TiEventContainer;
class TiCascadesEventHandler;

/*
 * NativeToggleButtonObject
 *
 * UI: Toggle Button
 */

class NativeToggleButtonObject : public NativeControlObject
{
public:
    static NativeToggleButtonObject* createToggleButton();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual void completeInitialization();
    virtual int setValue(TiObject* value);

protected:
    virtual ~NativeToggleButtonObject();

private:
    explicit NativeToggleButtonObject();
    // Disable copy ctor & assignment operator
    NativeToggleButtonObject(const NativeToggleButtonObject& toggleButton);
    NativeToggleButtonObject& operator=(const NativeToggleButtonObject& toggleButton);
    bb::cascades::ToggleButton* toggleButton_;

    TiEventContainer* eventStateChanged_;
    TiCascadesEventHandler* eventHandler_;
};

#endif /* NATIVETOGGLEBUTTONOBJECT_H_ */
