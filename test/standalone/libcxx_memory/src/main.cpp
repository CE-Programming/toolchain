#include <ti/screen.h>
#include <ti/getcsc.h>
#include <cstdio>
#include <memory>
#include <type_traits>
#include <utility>

#define CHECK(expr) do { if (!(expr)) return __LINE__; } while (0)

namespace {

int live = 0;

struct Tracked {
    int value;
    explicit Tracked(int v = 0) : value(v) { ++live; }
    Tracked(const Tracked& other) : value(other.value) { ++live; }
    ~Tracked() { --live; }
};

struct Base {
    virtual ~Base() = default;
    int base = 1;
};

struct Derived : Base {
    Tracked tracked{7};
};

struct CountingDeleter {
    int* count;
    void operator()(Tracked* p) const {
        ++*count;
        delete p;
    }
};

struct SelfAware : std::enable_shared_from_this<SelfAware> {
    Tracked tracked{42};
};

struct Empty {};

static_assert(sizeof(std::unique_ptr<int>) == sizeof(int*));
static_assert(sizeof(std::unique_ptr<int[]>) == sizeof(int*));
static_assert(sizeof(std::unique_ptr<int, CountingDeleter>) == sizeof(int*) + sizeof(CountingDeleter));
static_assert(sizeof(std::shared_ptr<int>) == 2 * sizeof(void*));
static_assert(sizeof(std::weak_ptr<int>) == 2 * sizeof(void*));
static_assert(!std::is_copy_constructible_v<std::unique_ptr<int>>);
static_assert(std::is_nothrow_move_constructible_v<std::unique_ptr<int>>);
static_assert(std::is_convertible_v<std::unique_ptr<Derived>, std::unique_ptr<Base>>);
static_assert(!std::is_convertible_v<std::unique_ptr<Base>, std::unique_ptr<Derived>>);
static_assert(!std::is_convertible_v<std::unique_ptr<Derived[]>, std::unique_ptr<Base[]>>);
static_assert(std::is_convertible_v<std::shared_ptr<Derived>, std::shared_ptr<const Base>>);
static_assert(!std::is_convertible_v<std::shared_ptr<Base>, std::shared_ptr<Derived>>);
static_assert(!std::is_constructible_v<std::shared_ptr<int>, Empty*>);

int test_unique_ptr() {
    {
        std::unique_ptr<Tracked> p = std::make_unique<Tracked>(5);
        CHECK(p && p->value == 5 && live == 1);
        std::unique_ptr<Tracked> q = std::move(p);
        CHECK(!p && q && (*q).value == 5);
        Tracked* raw = q.release();
        CHECK(!q && live == 1);
        q.reset(raw);
        CHECK(q.get() == raw);
        q.reset();
        CHECK(live == 0 && q == nullptr && nullptr == q);
    }
    {
        int count = 0;
        std::unique_ptr<Tracked, CountingDeleter> p(new Tracked(1), CountingDeleter{&count});
        p.reset(new Tracked(2));
        CHECK(count == 1 && live == 1 && p->value == 2);
        p = nullptr;
        CHECK(count == 2 && live == 0);
    }
    {
        int count = 0;
        CountingDeleter deleter{&count};
        {
            std::unique_ptr<Tracked, CountingDeleter&> p(new Tracked(3), deleter);
            CHECK(&p.get_deleter() == &deleter);
        }
        CHECK(count == 1 && live == 0);
    }
    {
        std::unique_ptr<Tracked[]> array = std::make_unique<Tracked[]>(4);
        CHECK(live == 4 && array[3].value == 0);
        array[2].value = 9;
        CHECK(array[2].value == 9);
        array.reset();
        CHECK(live == 0 && !array);
    }
    {
        std::unique_ptr<Base> base = std::make_unique<Derived>();
        CHECK(live == 1 && base->base == 1);
        base.reset();
        CHECK(live == 0);
    }
    {
        std::unique_ptr<Tracked> a = std::make_unique<Tracked>(1);
        std::unique_ptr<Tracked> b = std::make_unique<Tracked>(2);
        Tracked* first = a.get();
        swap(a, b);
        CHECK(b.get() == first && a->value == 2 && b->value == 1);
        CHECK(a != b && !(a == b) && (a < b) != (b < a) && (a <= b) != (a > b));
        CHECK(a > nullptr && !(a < nullptr) && nullptr < a);
    }
    {
        std::unique_ptr<int> p = std::make_unique_for_overwrite<int>();
        *p = 3;
        CHECK(*p == 3);
    }
    CHECK(live == 0);
    return 0;
}

int test_shared_ptr() {
    {
        std::shared_ptr<Tracked> p = std::make_shared<Tracked>(5);
        CHECK(p.use_count() == 1 && p->value == 5 && live == 1);
        {
            std::shared_ptr<Tracked> q = p;
            CHECK(p.use_count() == 2 && q.get() == p.get() && q == p);
        }
        CHECK(p.use_count() == 1);
        std::shared_ptr<Tracked> moved = std::move(p);
        CHECK(!p && p == nullptr && moved.use_count() == 1);
        moved.reset();
        CHECK(live == 0 && moved.use_count() == 0);
    }
    {
        int count = 0;
        {
            std::shared_ptr<Tracked> p(new Tracked(1), CountingDeleter{&count});
            std::shared_ptr<Tracked> q = p;
            CountingDeleter* deleter = std::get_deleter<CountingDeleter>(p);
            CHECK(deleter != nullptr && deleter->count == &count);
            CHECK(std::get_deleter<std::default_delete<Tracked>>(p) == nullptr);
            CHECK(std::get_deleter<CountingDeleter>(std::make_shared<int>(1)) == nullptr);
        }
        CHECK(count == 1 && live == 0);
    }
    {
        std::shared_ptr<Base> base = std::make_shared<Derived>();
        CHECK(live == 1);
        std::shared_ptr<Derived> derived = std::static_pointer_cast<Derived>(base);
        CHECK(derived.use_count() == 2 && derived->tracked.value == 7);
        std::shared_ptr<Base> owner(new Derived);
        CHECK(live == 2);
    }
    CHECK(live == 0);
    {
        std::weak_ptr<Tracked> weak;
        CHECK(weak.expired() && !weak.lock());
        {
            std::shared_ptr<Tracked> p = std::make_shared<Tracked>(3);
            weak = p;
            CHECK(!weak.expired() && weak.use_count() == 1);
            std::shared_ptr<Tracked> locked = weak.lock();
            CHECK(locked.get() == p.get() && p.use_count() == 2);
            std::shared_ptr<Tracked> from_weak(weak);
            CHECK(p.use_count() == 3);
        }
        CHECK(weak.expired() && !weak.lock() && live == 0);
    }
    {
        std::shared_ptr<Derived> p = std::make_shared<Derived>();
        std::weak_ptr<Base> weak_base = std::weak_ptr<Derived>(p);
        CHECK(weak_base.lock().get() == p.get());
        std::shared_ptr<Tracked> member(p, &p->tracked);
        p.reset();
        CHECK(live == 1 && member->value == 7 && member.use_count() == 1);
        CHECK(!weak_base.expired());
    }
    CHECK(live == 0);
    {
        int count = 0;
        std::unique_ptr<Tracked, CountingDeleter> unique(new Tracked(8), CountingDeleter{&count});
        std::shared_ptr<Tracked> shared = std::move(unique);
        CHECK(!unique && shared->value == 8);
        shared.reset();
        CHECK(count == 1 && live == 0);
    }
    {
        int count = 0;
        CountingDeleter deleter{&count};
        std::unique_ptr<Tracked, CountingDeleter&> unique(new Tracked(8), deleter);
        std::shared_ptr<Tracked> shared(std::move(unique));
        shared.reset();
        CHECK(count == 1 && live == 0);
    }
    {
        std::shared_ptr<Tracked[]> array(new Tracked[3]);
        array[1].value = 4;
        CHECK(live == 3 && array[1].value == 4);
    }
    CHECK(live == 0);
    {
        std::shared_ptr<SelfAware> s = std::make_shared<SelfAware>();
        std::shared_ptr<SelfAware> t = s->shared_from_this();
        CHECK(t == s && s.use_count() == 2);
        std::weak_ptr<const SelfAware> w = std::as_const(*s).weak_from_this();
        CHECK(w.lock() == s);
        SelfAware* raw = new SelfAware;
        CHECK(raw->weak_from_this().expired());
        std::shared_ptr<SelfAware> owner(raw);
        CHECK(raw->shared_from_this() == owner && owner.use_count() == 2);
    }
    CHECK(live == 0);
    {
        std::shared_ptr<int> a = std::make_shared<int>(1);
        std::shared_ptr<int> b = std::make_shared<int>(1);
        std::shared_ptr<int> alias(a, a.get());
        std::owner_less<> less;
        CHECK(!less(a, alias) && !less(alias, a));
        CHECK(less(a, b) != less(b, a));
        std::shared_ptr<const int> constant = a;
        CHECK(std::const_pointer_cast<int>(constant) == a);
    }
    {
        int count = 0;
        {
            std::shared_ptr<Tracked> p(nullptr, CountingDeleter{&count});
            CHECK(p.use_count() == 1 && !p);
        }
        CHECK(count == 1);
    }
    {
        std::shared_ptr<void> erased = std::make_shared<Tracked>(6);
        CHECK(live == 1 && std::static_pointer_cast<Tracked>(erased)->value == 6);
        erased = nullptr;
        CHECK(live == 0);
    }
    {
        std::shared_ptr<int> p = std::make_shared_for_overwrite<int>();
        *p = 11;
        CHECK(*p == 11);
    }
    {
        std::shared_ptr<Base> base = std::make_shared<Derived>();
        CHECK(std::dynamic_pointer_cast<Derived>(base) != nullptr);
        CHECK(std::dynamic_pointer_cast<Derived>(std::make_shared<Base>()) == nullptr);
    }
    CHECK(live == 0);
    return 0;
}

int run_tests() {
    int failed = test_unique_ptr();
    if (failed == 0) {
        failed = test_shared_ptr();
    }
    return failed;
}

} // namespace

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        std::printf("Failed test L%d\n", failed_test);
    } else {
        std::printf("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
