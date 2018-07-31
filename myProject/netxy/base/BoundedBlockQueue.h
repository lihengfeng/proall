#program once

#include<mutex>


namespace netxy{
	namespace base{
		template<typename T>
		class BoundedBlockQueue 
		{
		public:
			explicit BoundedBlockQueue(int maxSize)
				: mutex_(),
				notEmpty_(mutex_),
				notFull_(mutex_),
				queue_(maxSize)
			{
			}

			void put(const T& x)
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				while (queue_.full())
				{
					notFull_.wait();
				}
				assert(!queue_.full());
				queue_.push_back(x);
				notEmpty_.notify();
			}

			T take()
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				while (queue_.empty())
				{
					notEmpty_.wait();
				}
				assert(!queue_.empty());
				T front(queue_.front());
				queue_.pop_front();
				notFull_.notify();
				return front;
			}

			bool empty() const
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				return queue_.empty();
			}

			bool full() const
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				return queue_.full();
			}

			size_t size() const
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				return queue_.size();
			}

			size_t capacity() const
			{
				std::lock_guard<std::mutex>  lock(mutex_);
				return queue_.capacity();
			}

		private:
			mutable std::mutex         mutex_;
			Condition                  notEmpty_;
			Condition                  notFull_;
			CircularBuffer<T>		   queue_;
		};
	}
}
