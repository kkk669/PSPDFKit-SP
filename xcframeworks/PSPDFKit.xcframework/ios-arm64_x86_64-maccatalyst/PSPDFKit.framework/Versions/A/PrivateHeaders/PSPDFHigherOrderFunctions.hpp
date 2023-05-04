//
//  Copyright © 2015-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#pragma once

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif
#import <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
#import <algorithm>
#import <functional>
#import <type_traits>
#import <vector>

namespace PSPDF {
// TODO: use PSPDFCore variant

/// Takes an iterable, applies a function to every element,
/// and returns a vector of the results.
/// adapted from https://stackoverflow.com/questions/14945223/map-function-with-c11-constructs
template <typename T, typename Func> auto map(const T &iterable, Func &&func) -> std::vector<decltype(func(std::declval<typename T::value_type> ()))> {
    // Some convenience type definitions
    typedef decltype(func(std::declval<typename T::value_type> ())) value_type;
    typedef std::vector<value_type> result_type;

    // Prepares an output vector of the appropriate size
    result_type res(iterable.size());

    // Let std::transform apply `func` to all elements
    // (use perfect forwarding for the function object)
    std::transform(begin(iterable), end(iterable), res.begin(), std::forward<Func> (func));

    return res;
}

template <typename Func> auto map(id<NSFastEnumeration> collection, Func &&func) -> std::vector<decltype(func(std::declval<id> ()))> {
    std::vector<decltype(func(std::declval<id> ()))> to;
    for (id obj in collection) {
        to.push_back(func(obj));
    }
    return to;
}

// Test to see if a set, map, hash_set or hash_map contains a particular key.
// Returns true if the key is in the collection.
template <typename Collection, typename Key> bool ContainsKey(const Collection &collection, const Key &key) { return collection.find(key) != collection.end(); }

// Test to see if a collection like a vector contains a particular value.
// Returns true if the value is in the collection.
template <typename Collection, typename Value> bool ContainsValue(const Collection &collection, const Value &value) { return std::find(collection.begin(), collection.end(), value) != collection.end(); }

/// A smart pointer that can manage the lifecycle of Core Foundation objects.
template <typename T> class CFPointer {
  public:
    CFPointer() : storage(nullptr) {}

    CFPointer(T pointer) : storage(toStorageType(pointer)) {
        if (storage) {
            CFRetain(storage);
        }
    }

    CFPointer(const CFPointer &other) : storage(other.storage) {
        if (CFTypeRef ptr = storage) {
            CFRetain(ptr);
        }
    }

    CFPointer(CFPointer &&other) : storage(std::exchange(other.storage, nullptr)) {}

    ~CFPointer() {
        if (CFTypeRef pointer = storage) {
            CFRelease(pointer);
        }
    }

    static inline CFPointer<T> adopt(T CF_RELEASES_ARGUMENT ptr);

    T get() const;
    CFPointer &operator=(CFPointer);

  private:
    CFTypeRef storage;

    enum AdoptTag { Adopt };
    CFPointer(T ptr, AdoptTag) : storage(toStorageType(ptr)) {}

    inline CFTypeRef toStorageType(CFTypeRef ptr) const { return (CFTypeRef)ptr; }

    inline T fromStorageType(CFTypeRef pointer) const { return (T)pointer; }

    void swap(CFPointer &);
};

template <typename T> CFPointer<T> CFPointer<T>::adopt(T CF_RELEASES_ARGUMENT ptr) { return CFPointer<T> (ptr, CFPointer<T>::Adopt); }

template <typename T> T CFPointer<T>::get() const { return fromStorageType(storage); }

template <typename T> inline CFPointer<T> &CFPointer<T>::operator=(CFPointer other) {
    swap(other);
    return *this;
}

template <typename T> inline void CFPointer<T>::swap(CFPointer &other) { std::swap(storage, other.storage); }
};
#endif
