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

#pragma once

#include "../Resource/Resource.h"
#include "../Scene/AnimationDefs.h"

namespace Urho3D
{

class ValueAnimation;
class ValueAnimationInfo;
class ObjectAnimation;
class XMLElement;
class JSONValue;

/// Object animation class, an object animation include one or more attribute animations and theirs wrap mode and speed for an Animatable object.
class URHO3D_API ObjectAnimationPool : public Resource
{
    URHO3D_OBJECT(ObjectAnimationPool, Resource);

public:
    /// Construct.
    ObjectAnimationPool(Context* context);
    /// Destruct.
    virtual ~ObjectAnimationPool() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source) override;
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const override;
    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    bool SaveXML(XMLElement& dest) const;
    /// Load from JSON data. Return true if successful.
    bool LoadJSON(const JSONValue& source);
    /// Save as JSON data. Return true if successful.
    bool SaveJSON(JSONValue& dest) const;

    /// Add object animation.
    void AddObjectAnimation(const String& name, ObjectAnimation* objectAnimation);

    /// Remove object animation.
    void RemoveObjectAnimation(const String& name);

    /// Rename object animation.
    String RenameObjectAnimation(const String& pastname, const String& newName);

    /// Return object animation names in pool.
    Vector<String> GetObjectAnimationNames() const;

    /// Return object animation names in pool.
    ObjectAnimation* GetObjectAnimation(const String& name) const;

    /// Return name from animation ptr in pool.
    String GetObjectAnimationName( ObjectAnimation* objectAnimation ) const;

private:
    /// Send attribute animation added event.
    void SendObjectAnimationAddedEvent(const String& name);
    /// Send attribute animation remove event.
    void SendObjectAnimationRemovedEvent(const String& name);

    /// Name to attribute animation info mapping.
    HashMap<String, SharedPtr<ObjectAnimation> > objectAnimations_;
};

}
