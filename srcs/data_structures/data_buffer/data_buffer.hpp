#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>

class DataBuffer {
public:
    virtual ~DataBuffer() = default;

    virtual void addBytes(const char* data, size_t size) = 0;
    virtual const char* getBytes() const = 0;
    virtual size_t size() const = 0;
};

template <typename T>
class DataBufferImpl : public DataBuffer {
public:
    DataBufferImpl(const T& object);

    void addBytes(const char* data, size_t size) override;
    const char* getBytes() const override;
    size_t size() const override;

    void deserialize(T& object);

private:
    std::vector<char> buffer_;
};

template <typename T>
void serialize(const T& object, DataBuffer& buffer);

template <typename T>
void deserialize(DataBuffer& buffer, T& object);

// General template for the serialization operator (<<)
template <typename T>
std::ostream& operator<<(std::ostream& os, const T& object);

// Specialization for std::string to avoid ambiguity
std::ostream& operator<<(std::ostream& os, const std::string& object);

template <typename T>
std::istream& operator>>(std::istream& is, T& object);

// Specialization for std::string deserialization to avoid ambiguity
std::istream& operator>>(std::istream& is, std::string& object);

#endif  // DATA_BUFFER_HPP
