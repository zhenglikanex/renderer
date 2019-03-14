#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

namespace aurora
{
	class Noncopyable
	{
	public:
		Noncopyable(){}
		~Noncopyable(){}

		Noncopyable(const Noncopyable&) = delete;
		Noncopyable(Noncopyable&&) = delete;

		const Noncopyable& operator=(const Noncopyable&) = delete;
		const Noncopyable& operator=(Noncopyable&&) = delete;
	};
}

#endif
