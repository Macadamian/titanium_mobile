/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEDROPDOWNOBJECT_H_
#define NATIVEDROPDOWNOBJECT_H_

#include "NativeControlObject.h"

//forward declaration
namespace bb
{
namespace cascades
{
class DropDown;
}
}

class TiEventContainer;
class DropDownEventHandler;

/*
 * NativeDropDownObject
 *
 * UI: DropDown
 */
class NativeDropDownObject : public NativeControlObject
{
public:
    static NativeDropDownObject* createDropDown();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;
    virtual int setEventHandler(const char* eventName, TiEvent* event);
    virtual int setTitle(TiObject* obj);
    virtual int setOptions(TiObject* obj);
    virtual int setSelectedIndex(TiObject* obj);
    virtual void completeInitialization();

protected:
    virtual ~NativeDropDownObject();

private:
    explicit NativeDropDownObject();
    // Disable copy ctor & assignment operator
    NativeDropDownObject(const NativeDropDownObject& dropdown);
    NativeDropDownObject& operator=(const NativeDropDownObject& dropdown);
    // Class members
    bb::cascades::DropDown* dropdown_;
    TiEventContainer* eventClick_;
    DropDownEventHandler* eventHandler_;
};

//Event handler for button object
class DropDownEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit DropDownEventHandler(TiEventContainer* eventContainer)
    {
        eventContainer_ = eventContainer;
    }
    virtual ~DropDownEventHandler() {}

public slots:
    void selectedIndexChanged(int index)
    {
        eventContainer_->setDataProperty("value", index);
        eventContainer_->fireEvent();
    }

private:
    TiEventContainer* eventContainer_;

    // Disable copy ctor & assignment operator
    DropDownEventHandler(const DropDownEventHandler& eHandler);
    DropDownEventHandler& operator=(const DropDownEventHandler& eHandler);
};

#endif /* NATIVEDROPDOWNOBJECT_H_ */
