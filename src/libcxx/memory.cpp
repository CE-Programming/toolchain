#include <memory>

namespace std {

void __shared_weak_count::__release_shared(__shared_weak_count* cntrl) noexcept {
    if (cntrl && --cntrl->__shared_owners_ == 0) {
        cntrl->__manager_(cntrl, nullptr);
        __release_weak(cntrl);
    }
}

void __shared_weak_count::__release_weak(__shared_weak_count* cntrl) noexcept {
    if (cntrl && --cntrl->__weak_owners_ == 0) {
        ::operator delete(cntrl);
    }
}

__shared_weak_count* __shared_weak_count::__lock(__shared_weak_count* cntrl) noexcept {
    if (cntrl && cntrl->__shared_owners_ != 0) {
        ++cntrl->__shared_owners_;
        return cntrl;
    }
    return nullptr;
}

const void* __shared_weak_count::__noop_manager(__shared_weak_count*, const void*) noexcept {
    return nullptr;
}

} // namespace std
