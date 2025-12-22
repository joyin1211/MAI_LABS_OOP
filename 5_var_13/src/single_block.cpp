#include "single_block.hpp"

#include <algorithm>
#include <cstddef>
#include <new>
#include <type_traits>

single_block::single_block(std::size_t total_bytes)
    : total_(total_bytes)
{
    buffer = static_cast<std::byte*>(
        ::operator new(total_, std::align_val_t(alignof(std::max_align_t)))
    );

    free_.push_back(Block{0u, total_});
}

single_block::~single_block() {
    ::operator delete(buffer, std::align_val_t(alignof(std::max_align_t)));
    buffer = nullptr;
    total_ = 0;
    free_.clear();
}

std::size_t single_block::align_up(std::size_t value, std::size_t alignment) {
    if (alignment == 0) return value;
    const std::size_t mask = alignment - 1;
    return (value + mask) & ~mask;
}

void* single_block::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (bytes == 0) bytes = 1;
    if ((alignment & (alignment - 1)) != 0) {
        throw std::bad_alloc();
    }
    if (alignment == 0) alignment = alignof(std::max_align_t);

    for (auto it = free_.begin(); it != free_.end(); ++it) {
        const std::size_t block_begin = it->offset;
        const std::size_t block_end   = it->offset + it->size;

        const std::size_t aligned_begin = align_up(block_begin, alignment);
        if (aligned_begin < block_begin) continue;

        const std::size_t alloc_end = aligned_begin + bytes;
        if (alloc_end < aligned_begin) continue;
        if (alloc_end > block_end) continue;

        const std::size_t prefix = aligned_begin - block_begin;
        const std::size_t suffix = block_end - alloc_end;

        auto erase_it = it;
        free_.erase(erase_it);

        if (prefix > 0) free_.push_back(Block{block_begin, prefix});
        if (suffix > 0) free_.push_back(Block{alloc_end, suffix});

        normalize_free_list();
        return buffer + aligned_begin;
    }

    throw std::bad_alloc();
}

void single_block::do_deallocate(void* p, std::size_t bytes, std::size_t /*alignment*/) {
    if (!p) return;
    if (bytes == 0) bytes = 1;

    auto* bp = static_cast<std::byte*>(p);
    if (bp < buffer || bp >= buffer + total_) {
        return;
    }

    const std::size_t offset = static_cast<std::size_t>(bp - buffer);
    free_.push_back(Block{offset, bytes});
    normalize_free_list();
}

bool single_block::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

void single_block::normalize_free_list() {
    free_.sort([](const Block& a, const Block& b) { return a.offset < b.offset; });

    for (auto it = free_.begin(); it != free_.end();) {
        auto next = std::next(it);
        if (next == free_.end()) break;

        const std::size_t it_end = it->offset + it->size;

        if (next->offset <= it_end) {
            const std::size_t next_end = next->offset + next->size;
            const std::size_t new_end = (next_end > it_end) ? next_end : it_end;
            it->size = new_end - it->offset;
            free_.erase(next);
        } else {
            it = next;
        }
    }
}
