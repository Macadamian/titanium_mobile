/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObject.h"

#include "NativeLoggerObject.h"
#include "NativeMessageStrings.h"
#include <stdio.h>


const char* NativeObject::tetCHANGE = "change";
const char* NativeObject::tetCLICK = "click";

// NativeObject

NativeObject::NativeObject()
{
    isInitializationComplete_ = 0;
}

NativeObject::~NativeObject()
{
}

int NativeObject::setPropertyValue(size_t, TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::getPropertyValue(size_t, TiObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::addChildNativeObject(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::initialize()
{
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeObject::getNativeHandle() const
{
    return NULL;
}

int NativeObject::open()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::start()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::stop()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::openWindowOnTab(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

void NativeObject::completeInitialization()
{
    isInitializationComplete_ = true;
}

int NativeObject::scrollToIndex(int)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setActiveTab(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setActiveTab(int index)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::removeChildNativeObject(NativeObject*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

bool NativeObject::isInitializationComplete() const
{
    return isInitializationComplete_;
}

int NativeObject::setEventHandler(const char*, TiEvent*)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::removeEventHandler(int)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setVisibility(bool)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::fireEvent(const char* name, const TiObject*) const
{
    N_WARNING(Native::Msg::Event_handlers_for_are_invalid_for_event_named__ << name);
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::show()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::hide()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::getNextEventId()
{
    static int s_nextEventId = 1;

    // Account for overflow.
    if (s_nextEventId < 1)
    {
        // This event id must start at 1 because 0 is reserved. Since
        // V8 will always cast a value of undefined to zero.
        s_nextEventId = 1;
    }
    return s_nextEventId++;
}

void NativeObject::setupEvents(TiEventContainerFactory*)
{
	// Do nothing in the base class
}
