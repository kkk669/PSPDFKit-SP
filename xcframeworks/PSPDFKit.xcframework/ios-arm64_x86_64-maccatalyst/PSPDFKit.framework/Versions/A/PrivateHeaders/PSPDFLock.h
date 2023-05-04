//
//  Copyright © 2016-2023 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment+Private.h>
#import <PSPDFKit/PSPDFAvailability.h>
#else
#import "PSPDFEnvironment+Private.h"
#import "PSPDFAvailability.h"
#endif
#include <os/lock.h>
#include <pthread.h>

NS_ASSUME_NONNULL_BEGIN

/// Lock uses os_unfair_lock.
typedef union pspdf_lock_u {
    os_unfair_lock os_lock;
} pspdf_lock, *pspdf_lock_t;

#define PSPDFWithLock(...) \
    PSPDFLock(&_lock);     \
    __VA_ARGS__;           \
    PSPDFUnlock(&_lock);

#define PSPDFLockScope(lock)            \
    PSPDFLock(lock);                    \
    pspdf_defer { PSPDFUnlock(lock); }

/// Initializes the pspdf_lock_t (os_unfair_lock)
PSPDF_TEST_EXPORT void PSPDFLockInit(pspdf_lock_t lock);

/// Locks the pspdf_lock_t lock.
PSPDF_TEST_EXPORT void PSPDFLock(pspdf_lock_t lock);

/// Unlocks the pspdf_lock_t lock.
PSPDF_TEST_EXPORT void PSPDFUnlock(pspdf_lock_t lock);

/// perform `block` while holding lock.
PSPDF_TEST_EXPORT void PSPDFPerformLocked(pspdf_lock_t lock, NS_NOESCAPE dispatch_block_t block);

#ifdef __cplusplus
namespace PSPDF {

/// Simple wrapper around pspdf_lock that complies with the C++ BasicLocking principles.
/// Can be used inside a std::lock_guard<PSPDF::UnfairLock> guard(_lock)
class UnfairLock {
  public:
    UnfairLock() noexcept;
    void lock() noexcept;
    void unlock() noexcept;

  private:
    pspdf_lock _lock;
};
}
#endif

NS_ASSUME_NONNULL_END
