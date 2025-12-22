#pragma once

#include <cstddef>
#include <list>
#include <memory_resource>

class single_block final : public std::pmr::memory_resource {
public:
    explicit single_block(std::size_t total_bytes);

    single_block(const single_block&) = delete;
    single_block& operator=(const single_block&) = delete;

    ~single_block() override;

private:
    struct Block {
        std::size_t offset;
        std::size_t size;
    };

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

    static std::size_t align_up(std::size_t value, std::size_t alignment);
    void normalize_free_list();

    std::byte* buffer{nullptr};
    std::size_t total_{0};
    std::list<Block> free_;
};
