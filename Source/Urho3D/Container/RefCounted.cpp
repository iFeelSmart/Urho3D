//
// Copyright (c) 2008-2018 the Urho3D project.
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

#include "../Container/RefCounted.h"

#include "../DebugNew.h"

namespace Urho3D
{

RefCounted::RefCounted() :
    refCount_(new RefCount())
{
    // Hold a weak ref to self to avoid possible double delete of the refcount

    refCount_->mutex.Acquire();
    (refCount_->weakRefs_)++;
    refCount_->mutex.Release();
}

RefCounted::~RefCounted()
{
    volatile int iWeakRef;

    refCount_->mutex.Acquire();

    assert(refCount_);
    assert(refCount_->refs_ == 0);
    assert(refCount_->weakRefs_ > 0);

    // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
    refCount_->refs_ = -1;
    (refCount_->weakRefs_)--;
    iWeakRef = refCount_->weakRefs_;
    if (!iWeakRef)
        delete refCount_;
    else
        refCount_->mutex.Release();

    refCount_ = nullptr;
}

void RefCounted::AddRef()
{
    refCount_->mutex.Acquire();

    assert(refCount_->refs_ >= 0);

    (refCount_->refs_)++;

    refCount_->mutex.Release();
}

void RefCounted::ReleaseRef()
{
    volatile int iRefAfterDecr;

    refCount_->mutex.Acquire();

    assert(refCount_->refs_ > 0);
    (refCount_->refs_)--;
    iRefAfterDecr = refCount_->refs_;
    if (!iRefAfterDecr)
        delete this;
    else
        refCount_->mutex.Release();
}

int RefCounted::Refs() const
{
    volatile int iCount;

    refCount_->mutex.Acquire();

    iCount = refCount_->refs_;

    refCount_->mutex.Release();

    return iCount;
}

int RefCounted::WeakRefs() const
{
    volatile int iCount;

    // Subtract one to not return the internally held reference
    refCount_->mutex.Acquire();

    iCount = refCount_->weakRefs_ - 1;

    refCount_->mutex.Release();

    return iCount;
}

}
