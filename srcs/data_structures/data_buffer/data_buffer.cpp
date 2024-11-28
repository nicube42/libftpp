#include "data_buffer.hpp"

// General template constructor for DataBufferImpl
template <typename T>
DataBufferImpl<T>::DataBufferImpl(const T& object) {
    serialize(object, *this);
}

template <typename T>
void DataBufferImpl<T>::addBytes(const char* data, size_t size) {
    buffer_.insert(buffer_.end(), data, data + size);
}

template <typename T>
const char* DataBufferImpl<T>::getBytes() const {
    return buffer_.data();
}

template <typename T>
size_t DataBufferImpl<T>::size() const {
    return buffer_.size();
}

// General deserialization method
template <typename T>
void DataBufferImpl<T>::deserialize(T& object) {
    std::istringstream stream(std::string(buffer_.begin(), buffer_.end()));
    stream >> object;
}

// Template for serializing to DataBuffer
template <typename T>
void serialize(const T& object, DataBuffer& buffer) {
    std::ostringstream stream;
    stream << object;
    std::string serialized_data = stream.str();
    buffer.addBytes(serialized_data.c_str(), serialized_data.size());
}

// Template for deserializing from DataBuffer
template <typename T>
void deserialize(DataBuffer& buffer, T& object) {
    std::istringstream stream(std::string(buffer.getBytes(), buffer.size()));
    stream >> object;
}

// General template for the serialization operator (<<)
template <typename T>
std::ostream& operator<<(std::ostream& os, const T& object) {
    os.write(reinterpret_cast<const char*>(&object), sizeof(T));
    return os;
}

// Specialization of the serialization operator for std::string
std::ostream& operator<<(std::ostream& os, const std::string& object) {
    os << object;  // Use the standard operator<< for strings
    return os;
}

// General template for the deserialization operator (>>)
template <typename T>
std::istream& operator>>(std::istream& is, T& object) {
    is.read(reinterpret_cast<char*>(&object), sizeof(T));
    return is;
}

// Specialization of the deserialization operator for std::string
std::istream& operator>>(std::istream& is, std::string& object) {
    std::getline(is, object);  // Use standard getline for reading strings
    return is;
}

// Explicit template instantiations
template class DataBufferImpl<int>;
template class DataBufferImpl<float>;
template class DataBufferImpl<std::string>;  // Add other types as necessary
