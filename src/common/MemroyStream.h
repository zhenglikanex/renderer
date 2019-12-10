#include <atlcoll.h>
#include "AuroraDef.h"

#include "Noncopyable.h"

namespace aurora
{
	//template<typename T = std::allocator<void>>
	class MemroyStream : public Noncopyable
	{
	public:
		MemroyStream(void* data,uint32_t capacity);
		MemroyStream(uint32_t size);

		~MemroyStream();

	private:
		void* data_;
	};
}