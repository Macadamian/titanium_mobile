/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeTextFieldObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/TextField>
#include <QString>

NativeTextFieldObject::NativeTextFieldObject()
{
    textField_ = NULL;
}

NativeTextFieldObject::~NativeTextFieldObject()
{
}

int NativeTextFieldObject::getObjectType() const
{
    return N_TYPE_TEXT_FIELD;
}

NativeTextFieldObject* NativeTextFieldObject::createTextField()
{
    return new NativeTextFieldObject;
}

int NativeTextFieldObject::initialize(TiEventContainerFactory* containerFactory)
{
    textField_ = bb::cascades::TextField::create();
    setTextControl(textField_);
    TiEventContainer* eventFieldChanged = containerFactory->createEventContainer();
    eventFieldChanged->setDataProperty("type", tetCHANGE);
    events_.insert(tetCHANGE, new EventPair(eventFieldChanged, new TextFieldEventHandler(eventFieldChanged)));
    return NATIVE_ERROR_OK;
}

int NativeTextFieldObject::setHintText(TiObject* obj)
{
    QString strHint;
    int error = NativeControlObject::getString(obj, strHint);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    textField_->setHintText(strHint);
    return NATIVE_ERROR_OK;
}

void NativeTextFieldObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(textField_, SIGNAL(textChanging(QString)), events_[tetCHANGE]->handler, SLOT(textChanging(QString)));
}
