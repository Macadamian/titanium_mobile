/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeDropDownObject.h"
#include "TiEventContainerFactory.h"
#include "TiCascadesEventHandler.h"
#include "NativeOptionObject.h"
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
    dropdown_->add(bb::cascades::Option::create().text("Option 1"));
    dropdown_->add(bb::cascades::Option::create().text("Option 2"));
    dropdown_->add(bb::cascades::Option::create().text("Option 3"));
    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setOptions(const char* options[])
{
    unsigned int length = sizeof(options);
    for (unsigned int i = 0; i < length; ++i)
    {
        NativeOptionObject* option = NativeOptionObject::createOption();
        option->setText(options[i]);
        dropdown_->add((bb::cascades::Option*)option->getNativeHandle());
        option->release();
    }

    return NATIVE_ERROR_OK;
}

int NativeDropDownObject::setSelectedIndex(int index)
{
    dropdown_->setSelectedIndex(index);
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
    QObject::connect(dropdown_, SIGNAL(selectedIndexChanged(int selectedIndex)), eventHandler_, SLOT(selectedIndexChanged(int selectedIndex)));
}
