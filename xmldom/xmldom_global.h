#pragma once

#if defined(XMLDOM_LIBRARY)
#  define XMLDOM_EXPORT Q_DECL_EXPORT
#else
#  define XMLDOM_EXPORT Q_DECL_IMPORT
#endif
#define FORWARD_DECLARE_PRIVATE(className) \
 namespace Internal { class className##Private; }

#include <QSharedPointer>
#define DECLARE_PRIVATE(Class) \
    QScopedPointer<Internal::Class##Private> d_ptr; \
    friend class Internal::Class##Private;

#define DECLARE_PUBLIC(Class)  \
    public: Class##Private(Class *q_ptr): q(q_ptr){ Q_UNUSED(q) } \
    private: Class *q = nullptr;

#define GUARD(cond, action) if (cond) { action; }

#define PROPERTY_IMPLEMENTATION(valueName)\
    if(d_ptr->valueName != value) { \
        d_ptr->valueName = value; \
        emit valueName##Changed(); \
    }


#include <qcompilerdetection.h> // for Q_REQUIRED_RESULT

#include <algorithm>
#include <functional>
#include <tuple>
template<typename T, typename F>
QList<T> toList(const QList<F> &container){
    QList<T> list;
    for(F element: container){
        list.append(dynamic_cast<T>(element));
    }
    return list;
}

template<typename T, typename F, typename P>
QList<T> toList(const QList<F> &container, P converter){
    QList<T> list;
    for(F element: container){
        list.append(converter(element));
    }
    return list;
}

template <typename Container, typename Op>
inline void reverseForeach(const Container &c, const Op &operation)
{
    auto rend = c.rend();
    for (auto it = c.rbegin(); it != rend; ++it)
        operation(*it);
}
template<typename T, typename F>
typename T::value_type findOr(const T &container, typename T::value_type other, F function)
{
    typename T::const_iterator end = container.end();
    typename T::const_iterator begin = container.begin();

    typename T::const_iterator it = std::find_if(begin, end, function);
    if (it == end)
        return other;
    return *it;
}

template<typename T, typename R, typename S>
typename T::value_type findOr(const T &container, typename T::value_type other, R (S::*function)() const)
{
    return findOr(container, other, std::mem_fn(function));
}

// inserter helper function, returns a std::back_inserter for most containers
// and is overloaded for QSet<> to return a QSetInsertIterator
template<typename C>
inline std::back_insert_iterator<C>
inserter(C &container)
{
    return std::back_inserter(container);
}

template <class Container>
class QSetInsertIterator :
    public std::iterator<std::output_iterator_tag,void,void,void,void>
{
protected:
    Container *container;

public:
    typedef Container container_type;
    explicit QSetInsertIterator (Container &x)
        : container(&x) {}
    QSetInsertIterator<Container> &operator=(const typename Container::value_type &value)
    { container->insert(value); return *this; }
    QSetInsertIterator<Container> &operator= (typename Container::value_type &&value)
    { container->insert(std::move(value)); return *this; }
    QSetInsertIterator<Container >&operator*()
    { return *this; }
    QSetInsertIterator<Container> &operator++()
    { return *this; }
    QSetInsertIterator<Container> operator++(int)
    { return *this; }
};

template<typename X>
inline QSetInsertIterator<QSet<X>>
inserter(QSet<X> &container)
{
    return QSetInsertIterator<QSet<X>>(container);
}

template<typename C, typename F>
Q_REQUIRED_RESULT
    C filtered(const C &container, F predicate)
{
    C out;
    std::copy_if(container.begin(), container.end(),
                 inserter(out), predicate);
    return out;
}
