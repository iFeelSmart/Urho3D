//
// Copyright (c) 2008-2017 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Resource/XMLFile.h"
#include "../Resource/JSONFile.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/ObjectAnimationPool.h"

#include "../DebugNew.h"

namespace Urho3D
{

ObjectAnimationPool::ObjectAnimationPool(Context* context) :
    Resource(context)
{
}

ObjectAnimationPool::~ObjectAnimationPool()
{
}

void ObjectAnimationPool::RegisterObject(Context* context)
{
    context->RegisterFactory<ObjectAnimationPool>();
}

bool ObjectAnimationPool::BeginLoad(Deserializer& source)
{
    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
        return false;

    return LoadXML(xmlFile.GetRoot());
}

bool ObjectAnimationPool::Save(Serializer& dest) const
{
    XMLFile xmlFile(context_);

    XMLElement rootElem = xmlFile.CreateRoot("objectanimationpool");
    if (!SaveXML(rootElem))
        return false;

    return xmlFile.Save( dest );
}

bool ObjectAnimationPool::LoadXML(const XMLElement& source)
{
    objectAnimations_.Clear();

    XMLElement animEntryElem;
    animEntryElem = source.GetChild("objectanimation");
    while (animEntryElem)
    {
        String name = animEntryElem.GetAttribute("name");

        SharedPtr<ObjectAnimation> objectAnimation(new ObjectAnimation(context_));
        if (!objectAnimation->LoadXML(animEntryElem))
            return false;

        animEntryElem = animEntryElem.GetNext("objectanimation");
        AddObjectAnimation( name, objectAnimation );
    }

    return true;
}

bool ObjectAnimationPool::SaveXML(XMLElement& dest) const
{
    for (HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Begin();
         i != objectAnimations_.End(); ++i)
    {
        XMLElement animEntryElem = dest.CreateChild("objectanimation");
        animEntryElem.SetAttribute("name", i->first_);

        const ObjectAnimation* anim = i->second_;
        if (!anim->SaveXML(animEntryElem))
            return false;
    }

    return true;
}

bool ObjectAnimationPool::LoadJSON(const JSONValue& source)
{
    objectAnimations_.Clear();

    JSONValue objectAnimationPoolValue = source.Get("objectanimationpool");
    if (objectAnimationPoolValue.IsNull())
        return true;
    if (!objectAnimationPoolValue.IsObject())
        return true;

    const JSONObject& objectAnimationPoolObject = objectAnimationPoolValue.GetObject();

    for (JSONObject::ConstIterator it = objectAnimationPoolObject.Begin(); it != objectAnimationPoolObject.End(); it++)
    {
        String name = it->first_;
        JSONValue value = it->second_;
        SharedPtr<ObjectAnimation> objectAnimation(new ObjectAnimation(context_));
        if (!objectAnimation->LoadJSON(value))
            return false;

        AddObjectAnimation(name, objectAnimation);
    }

    return true;
}

bool ObjectAnimationPool::SaveJSON(JSONValue& dest) const
{
    JSONValue objectAnimationsValue;

    for (HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Begin();
         i != objectAnimations_.End(); ++i)
    {
        JSONValue animEntryValue;
        animEntryValue.Set("name", i->first_);

        const ObjectAnimation* objectAnimation = i->second_;
        if (!objectAnimation->SaveJSON(animEntryValue))
            return false;

        objectAnimationsValue.Set(i->first_, animEntryValue);
    }

    dest.Set("objectanimationpool", objectAnimationsValue);
    return true;
}

void ObjectAnimationPool::AddObjectAnimation(const String& name, ObjectAnimation* objectAnimation)
{
    if (!objectAnimation)
        return;

    objectAnimations_[name] = objectAnimation;

    SendObjectAnimationAddedEvent(name);
}

void ObjectAnimationPool::RemoveObjectAnimation(const String& name)
{
    HashMap<String, SharedPtr<ObjectAnimation> >::Iterator i = objectAnimations_.Find(name);
    if (i != objectAnimations_.End())
    {
        SendObjectAnimationRemovedEvent(name);

        objectAnimations_.Erase(i);
    }
}

String ObjectAnimationPool::RenameObjectAnimation(const String& pastname, const String& newName)
{
    if( objectAnimations_.Contains( pastname ) )
    {
        if( !objectAnimations_.Contains( newName ) && !newName.Empty() )
        {
            objectAnimations_[newName] = objectAnimations_[pastname];
            objectAnimations_.Erase(pastname);
            return newName;
        }
    }
    return "";
}

Vector<String> ObjectAnimationPool::GetObjectAnimationNames() const
{
    return objectAnimations_.Keys();
}

ObjectAnimation* ObjectAnimationPool::GetObjectAnimation(const String& name) const
{
    HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Find(name);
    if (i != objectAnimations_.End())
    {
        return i->second_;
    }
    return nullptr;
}

String ObjectAnimationPool::GetObjectAnimationName( ObjectAnimation* objectAnimation ) const
{
    for (HashMap<String, SharedPtr<ObjectAnimation> >::ConstIterator i = objectAnimations_.Begin();
         i != objectAnimations_.End(); ++i)
    {
        if ( objectAnimation == i->second_ )
            return i->first_;
    }
    return "";
}

void ObjectAnimationPool::SendObjectAnimationAddedEvent(const String& name)
{
    using namespace ObjectAnimationAdded;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_OBJECTANIMATIONPOOL] = this;
    eventData[P_OBJECTANIMATIONNAME] = name;
    SendEvent(E_OBJECTANIMATIONADDED, eventData);
}

void ObjectAnimationPool::SendObjectAnimationRemovedEvent(const String& name)
{
    using namespace ObjectAnimationRemoved;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_OBJECTANIMATIONPOOL] = this;
    eventData[P_OBJECTANIMATIONNAME] = name;
    SendEvent(E_OBJECTANIMATIONREMOVED, eventData);
}

}
