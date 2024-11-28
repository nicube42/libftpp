#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include <memory>
#include <stdexcept>

template<typename TType>
class Pool {
	public:
		class Object {
			public:
				Object(std::unique_ptr<TType> p_object, Pool* pool) : _p_object(std::move(p_object)), _pool(pool) {}

				TType operator->() {
					return _p_object.get();
				}

				TType& operator*() {
					return *_p_object;
				}

				~Object() {
					if (_p_object) {
						_pool->_pool.push_back(std::move(_p_object));
					}
				}

				Object(const Object&) = delete;
				Object& operator=(const Object&) = delete;

			private:
				std::unique_ptr<TType> _p_object;
				Pool *_pool;
		};

		Pool() = default;

		// Resize the pool to store 'numberOfObjectStored' objects
		void resize(const size_t& numberOfObjectStored) {
			_pool.reserve(numberOfObjectStored);
			while (_pool.size() < numberOfObjectStored) {
				_pool.push_back(std::make_unique<TType>());
			}
		}

		// Acquire an object from the pool with parameters forwarded to TType's constructor
		template<typename... TArgs> class Object acquire(TArgs&&... p_args) {
			if (_pool.empty()) {
				throw std::runtime_error("Pool is empty");
			}

			std::unique_ptr<TType> p_object = std::move(_pool.back());
			_pool.pop_back();
			new (p_object.get()) TType(std::forward<TArgs>(p_args)...);
			return Object(std::move(p_object), this);
		}

	private:
		std::vector<std::unique_ptr<TType>> _pool;
		void release(std::unique_ptr<TType> p_object) {
			_pool.push_back(std::move(p_object));
		}

};

#endif
