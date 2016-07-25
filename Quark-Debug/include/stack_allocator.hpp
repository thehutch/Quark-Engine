#pragma once

#include "memory_block.hpp"

namespace QE
{
	namespace Debug
	{
		template<size_t SIZE>
		class StackAllocator
		{
		public:
			/**
			 * Allocates the specified number of bytes
			 *
			 * @param bytes -   The number of bytes to allocate
			 *
			 * @return A struct containing the memory address and the size of the allocation
			 */
			MemoryBlock Allocate(size_t bytes) noexcept;

			/**
			 * Deallocates the memory at the specified memory address.
			 * Only valid if the specified memory block is the last block to be allocated.
			 *
			 * @param block -   The memory block struct which was returned from the original allocation
			 */
			void Deallocate(const MemoryBlock& block) noexcept;

			/**
			 * Clears all the memory allocations which have been made by this allocator
			 */
			void Clear();
		private:
			uint8_t mData[SIZE];
			uint8_t* mPtr;
		};
	}
}
