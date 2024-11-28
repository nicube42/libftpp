#include "libftpp.hpp"
#include <string>
#include <iostream>
#include <cassert>

void test_int_serialization() {
    std::cout << BLUE << "Test: Serialize and Deserialize int" << RESET << std::endl;

    // Create an original int to serialize
    int original_int = 42;

    // Serialize it into a buffer using the << operator
    DataBufferImpl<int> buffer_int(original_int);

    // Deserialize it back into a new variable
    int deserialized_int;
    std::istringstream input_stream(std::string(buffer_int.getBytes(), buffer_int.size()));
    input_stream >> deserialized_int;

    // Check that the deserialized value is the same as the original
    std::cout << "Original int: " << original_int << ", Deserialized int: " << deserialized_int << std::endl;
    assert(deserialized_int == original_int && "Deserialization of int failed!");

    std::cout << "Test passed!" << std::endl << std::endl;
}

// Helper function to test string serialization and deserialization
void test_string_serialization() {
    std::cout << BLUE << "Test: Serialize and Deserialize std::string" << RESET << std::endl;

    // Create an original string to serialize
    std::string original_str = "Hello, World!";

    // Serialize it into a buffer using the << operator
    DataBufferImpl<std::string> buffer_string(original_str);

    // Deserialize it back into a new string
    std::string deserialized_str;
    std::istringstream input_stream(std::string(buffer_string.getBytes(), buffer_string.size()));
    input_stream >> deserialized_str;

    // Check that the deserialized value matches the original string
    std::cout << "Original string: " << original_str << ", Deserialized string: " << deserialized_str << std::endl;
    assert(deserialized_str == original_str && "Deserialization of string failed!");

    std::cout << "Test passed!" << std::endl << std::endl;
}

// Helper function to test mixed serialization and deserialization
void test_mixed_serialization() {
    std::cout << BLUE << "Test: Serialize and Deserialize mixed types" << RESET << std::endl;

    // Serialize and deserialize an integer
    int original_int = 123;
    DataBufferImpl<int> buffer_int(original_int);
    int deserialized_int;
    std::istringstream input_stream_int(std::string(buffer_int.getBytes(), buffer_int.size()));
    input_stream_int >> deserialized_int;
    assert(deserialized_int == original_int && "Deserialization of int failed!");

    // Serialize and deserialize a string
    std::string original_str = "Goodbye, World!";
    DataBufferImpl<std::string> buffer_string(original_str);
    std::string deserialized_str;
    std::istringstream input_stream_str(std::string(buffer_string.getBytes(), buffer_string.size()));
    input_stream_str >> deserialized_str;
    assert(deserialized_str == original_str && "Deserialization of string failed!");

    // Print results
    std::cout << "Original int: " << original_int << " | Deserialized int: " << deserialized_int << std::endl;
    std::cout << "Original string: " << original_str << " | Deserialized string: " << deserialized_str << std::endl;
    std::cout << "Mixed tests passed!" << std::endl << std::endl;
}

int main() {
	std::cout << CYN << "LIBFTPP" << RESET << std::endl << std::endl;

	std::cout << MAG << "Pool tests" << RESET << std::endl << std::endl;
	std::cout << BLUE << "Create int pool of size 10" << RESET << std::endl;
	Pool<int> pool_int;
	pool_int.resize(10);
	std::cout << BLUE << "Create string pool of size 2" << RESET << std::endl;
	Pool<std::string> pool_string;
	pool_string.resize(2);

	auto integer = pool_int.acquire(42);
	auto string = pool_string.acquire("Hello, World!");
	auto string2 = pool_string.acquire("Hello, World2!");

	std::cout << GREEN << "content of integer is " << *integer << std::endl;
	std::cout << "content of string1 is "<< *string << std::endl;
	std::cout << "content of string2 is "<< *string2 << RESET << std::endl;

	try {
		auto string3 = pool_string.acquire("Hello, World2!");
	} catch (std::runtime_error& e) {
		std::cout << RED << "trying to aquire a string from an empty pool" << RESET << std::endl;
		std::cout << "Error catched is : " << e.what() << std::endl;
	}


	std::cout << std::endl << MAG << "Data_buffer tests" << RESET << std::endl << std::endl;

	test_int_serialization();
	test_string_serialization();
	test_mixed_serialization();
}