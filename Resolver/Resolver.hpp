#ifndef RESOLVER_HPP
#define RESOLVER_HPP

#include <QSharedPointer>

template <typename T, typename ID = int> class Resolver {
public:
	typedef QSharedPointer<T> Pointer;
	virtual ~Resolver() = default;
	virtual Pointer resolve(ID id) const = 0;
};

#endif // RESOLVER_HPP
