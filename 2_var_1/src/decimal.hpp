#include <string>
#include <initializer_list>

class Decimal {
private:
    unsigned char *digits;
    size_t size;
    size_t capacity;
    
    void removeLeadingZeroes();

    int compare (const Decimal &other) const;
public:
    Decimal();
    Decimal(const size_t n, unsigned char t = '0');
    Decimal(const std::initializer_list<unsigned char> &t);
    Decimal(const std::string &t);

    Decimal(const Decimal& other);
    Decimal(Decimal&& other) noexcept;

    virtual ~Decimal() noexcept;

    Decimal& operator=(const Decimal& other) = delete;

    Decimal copy() const;

    Decimal add(const Decimal &first, const Decimal &second) const;
    Decimal addTo(const Decimal &other) const;
    Decimal sub(const Decimal &first, const Decimal &second) const;
    Decimal subTo(const Decimal &other) const;

    bool isLess(const Decimal &other) const;
    bool isGreater(const Decimal &other) const;
    bool isEqual(const Decimal &other) const;

    size_t getSize() const;
    std::string toString() const;
};