/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDropDownObject.h"
#include "TiEventContainerFactory.h"
#include "TiCascadesEventHandler.h"
#include <bb/cascades/DropDown>

NativeDropDownObject::NativeDropDownObject()
{
    dropdown_ = NULL;
}

NativeDropDownObject::~NativeDropDownObject()
{
}

NativeDropDownObject* NativeDropDownObject::createDropDown()
{
    return new NativeDropDownObject();
}

int NativeDropDownObject::getObjectType() const
{
    return N_TYPE_DROPDOWN;
}

int NativeDropDownObject::initialize(TiEventContainerFactory* containerFactory)
{
    dropdown_ = bb::cascades::DropDown::create();
    setControl(dropdown_);
    eventClick_ = containerFactory->createEventContainer();
    eventClick_->setDataProperty("type", "click");
    eventHandler_ = new TiCascadesEventHandler(eventClick_);
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeDropDownObject::getNativeHandle() const
{
    return dropdown_;
}

int NativeDropDownObject::setTitle(const char* title)
{
    QString str = title;
    dropdown_->setTitle(str);
    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "click") == 0)
    {
        eventClick_->addListener(event);
    }
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeDropDownObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(dropdown_, SIGNAL(selectedChanged(bool selected)), eventHandler_, SLOT(setSelected(bool selected)));
}
