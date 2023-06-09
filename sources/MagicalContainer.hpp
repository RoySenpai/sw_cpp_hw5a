/*
 *  Software Systems CPP Course Assignment 5
 *  Copyright (C) 2023  Roy Simanovich
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <set>
#include <vector>
#include <stdexcept>

namespace ariel
{
	class MagicalContainer
	{
		private:
			std::set<int> _elements;
			std::vector<const int *> _elements_ascending_order;
			std::vector<const int *> _elements_sidecross_order;
			std::vector<const int *> _elements_prime_order;

			/*
			 * @brief Checks if a given number is prime.
			 * @param num The number to check.
			 * @return True if the number is prime, false otherwise.
			*/
			static bool _isPrime(int num);

		public:
			/*
			 * @brief Construct a new Magical Container object.
			 * @note The container is empty by default.
			*/
			MagicalContainer() { }

			/*
			 * @brief Add an element to the container.
			 * @param element The element to add.
			 * @note The element is added to the end of the container.
			 * @note If the element already exists in the container, it will not be added.
			*/
			void addElement(int element);

			/*
			 * @brief Remove an element from the container.
			 * @param element The element to remove.
			 * @throw std::invalid_argument If the element does not exist in the container.
			*/
			void removeElement(int element);

			/*
			 * @brief Return the size of the container.
			 * @return The size of the container.
			*/
			size_t size() const {
				return _elements.size();
			}



		class AscendingIterator
		{
			private:
				MagicalContainer& _container;
				size_t _index;

				/*
				 * @brief Construct a new Ascending Iterator object.
				 * @param container The container to iterate over.
				 * @param index The index to start iterating from.
				 * @note The iterator is initialized to the element at the given index in the container.
				*/
				AscendingIterator(MagicalContainer &container, size_t index);

			public:
				/*
				 * @brief Construct a new Ascending Iterator object.
				 * @param container The container to iterate over.
				 * @note The iterator is initialized to the first element in the container.
				*/
				AscendingIterator(MagicalContainer &container);

				/*
				 * @brief Destroy the Ascending Iterator object.
				 * @note Use the default destructor, as the container property is a vector, which has its own destructor.
				*/
				~AscendingIterator() = default;

				/*
				 * @brief Copy constructor.
				 * @param other The iterator to copy.
				*/
				AscendingIterator(const AscendingIterator &other);

				/*
				 * @brief Move constructor.
				 * @param other The iterator to move.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move constructor, as the container property is a vector, which has its own move constructor.
				*/
				AscendingIterator(AscendingIterator &&other) noexcept;
				
				/*
				 * @brief Copy assignment operator.
				 * @param other The iterator to copy.
				 * @return A reference to this iterator.
				*/
				AscendingIterator &operator=(const AscendingIterator &other) {
					if (this != &other)
					{
						_container = other._container;
						_index = other._index;
					}

					return *this;
				}

				/*
				 * @brief Move assignment operator.
				 * @param other The iterator to move.
				 * @return A reference to this iterator.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move assignment operator, as the container property is a vector, which has its own move assignment operator.
				*/
				AscendingIterator &operator=(AscendingIterator &&other) noexcept;
			
				/*
				 * @brief Equality operator, checks if two iterators are equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are equal, false otherwise.
				*/
				bool operator==(const AscendingIterator &other) const {
					return _index == other._index;
				}

				/*
				 * @brief Inequality operator, checks if two iterators are not equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are not equal, false otherwise.
				*/
				bool operator!=(const AscendingIterator &other) const {
					return _index != other._index;
				}

				/*
				 * @brief Less than operator, checks if this iterator is less than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is less than the other iterator, false otherwise.
				*/
				bool operator<(const AscendingIterator &other) const {
					return _index < other._index;
				}

				/*
				 * @brief Greater than operator, checks if this iterator is greater than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is greater than the other iterator, false otherwise.
				*/
				bool operator>(const AscendingIterator &other) const {
					return _index > other._index;
				}

				/*
				 * @brief Dereference operator, returns the element at the current index.
				 * @return The element at the current index (If the index is out of bounds, the behavior is undefined).
				*/
				int operator*() const {
					if (_index > _container._elements_ascending_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}

					return *(_container._elements_ascending_order.at(_index));
				}

				/*
				 * @brief Prefix increment operator, increments the iterator to the next element.
				 * @return A reference to this iterator.
				 * @throw std::out_of_range If the iterator is out of range.
				*/
				AscendingIterator &operator++() {
					if (_index > _container._elements_ascending_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}
					
					++_index;
					return *this;
				}

				/*
				 * @brief Returns an iterator to the first element in the container.
				 * @return An iterator to the first element in the container.
				 * @note If the container is empty, the iterator returned is equal to the iterator returned by end().
				*/
				AscendingIterator begin() {
					return AscendingIterator(_container, 0);
				}

				/*
				 * @brief Returns an iterator to the element after the last element in the container.
				 * @return An iterator to the element after the last element in the container.
				 * @note This iterator is not dereferenceable.
				*/
				AscendingIterator end() const {
					return AscendingIterator(_container, _container._elements_ascending_order.size());
				}
		};

		class PrimeIterator
		{
			private:
				MagicalContainer& _container;
				size_t _index;

				/*
				 * @brief Construct a new Prime Iterator object, with a given index.
				 * @param container The container to iterate over.
				 * @param index The index to initialize the iterator to.
				 * @note The iterator is initialized to the given index.
				*/
				PrimeIterator(MagicalContainer &container, size_t index);

			public:
				/*
				 * @brief Construct a new Prime Iterator object.
				 * @param container The container to iterate over.
				 * @note The iterator is initialized to the first element in the container.
				*/
				PrimeIterator(MagicalContainer &container);

				/*
				 * @brief Destroy the Prime Iterator object.
				 * @note Use the default destructor, as the container property is a vector, which has its own destructor.
				*/
				~PrimeIterator() = default;

				/*
				 * @brief Copy constructor.
				 * @param other The iterator to copy.
				*/
				PrimeIterator(const PrimeIterator &other);

				/*
				 * @brief Move constructor.
				 * @param other The iterator to move.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move constructor, as the container property is a vector, which has its own move constructor.
				*/
				PrimeIterator(PrimeIterator &&other) noexcept;
				
				/*
				 * @brief Copy assignment operator.
				 * @param other The iterator to copy.
				 * @return A reference to this iterator.
				*/
				PrimeIterator &operator=(const PrimeIterator &other) {
					if (this != &other)
					{
						_container = other._container;
						_index = other._index;
					}

					return *this;
				}

				/*
				 * @brief Move assignment operator.
				 * @param other The iterator to move.
				 * @return A reference to this iterator.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move assignment operator, as the container property is a vector, which has its own move assignment operator.
				*/
				PrimeIterator &operator=(PrimeIterator &&other) noexcept;
			
				/*
				 * @brief Equality operator, checks if two iterators are equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are equal, false otherwise.
				*/
				bool operator==(const PrimeIterator &other) const {
					return _index == other._index;
				}

				/*
				 * @brief Inequality operator, checks if two iterators are not equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are not equal, false otherwise.
				*/
				bool operator!=(const PrimeIterator &other) const {
					return _index != other._index;
				}

				/*
				 * @brief Less than operator, checks if this iterator is less than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is less than the other iterator, false otherwise.
				*/
				bool operator<(const PrimeIterator &other) const {
					return _index < other._index;
				}

				/*
				 * @brief Greater than operator, checks if this iterator is greater than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is greater than the other iterator, false otherwise.
				*/
				bool operator>(const PrimeIterator &other) const {
					return _index > other._index;
				}

				/*
				 * @brief Dereference operator, returns the element at the current index.
				 * @return The element at the current index (If the index is out of bounds, the behavior is undefined).
				*/
				int operator*() const {
					if (_index > _container._elements_ascending_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}

					return *(_container._elements_prime_order.at(_index));
				}

				/*
				 * @brief Prefix increment operator, increments the iterator to the next element.
				 * @return A reference to this iterator.
				 * @throw std::out_of_range If the iterator is out of range.
				*/
				PrimeIterator &operator++() {
					if (_index > _container._elements_prime_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}
					
					++_index;
					return *this;
				}

				/*
				 * @brief Returns an iterator to the first element in the container.
				 * @return An iterator to the first element in the container.
				 * @note If the container is empty, the iterator returned is equal to the iterator returned by end().
				*/
				PrimeIterator begin() {
					return PrimeIterator(_container, 0);
				}

				/*
				 * @brief Returns an iterator to the element after the last element in the container.
				 * @return An iterator to the element after the last element in the container.
				 * @note This iterator is not dereferenceable.
				*/
				PrimeIterator end() const {
					return PrimeIterator(_container, _container._elements_prime_order.size());
				}
		};

		class SideCrossIterator
		{
			private:
				MagicalContainer& _container;
				size_t _index;

				/*
				 * @brief Construct a new Side Cross Iterator object, with a given index.
				 * @param container The container to iterate over.
				 * @param index The index to initialize the iterator to.
				 * @note The iterator is initialized to the given index.
				*/
				SideCrossIterator(MagicalContainer &container, size_t index);

			public:
				/*
				 * @brief Construct a new Side Cross Iterator object.
				 * @param cont The container to iterate over.
				 * @note The iterator is initialized to the first element in the container.
				*/
				SideCrossIterator(MagicalContainer &container);

				/*
				 * @brief Destroy the Side Cross Iterator object.
				 * @note Use the default destructor, as the container property is a vector, which has its own destructor.
				*/
				~SideCrossIterator() = default;

				/*
				 * @brief Copy constructor.
				 * @param other The iterator to copy.
				*/
				SideCrossIterator(const SideCrossIterator &other);

				/*
				 * @brief Move constructor.
				 * @param other The iterator to move.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move constructor, as the container property is a vector, which has its own move constructor.
				*/
				SideCrossIterator(SideCrossIterator &&other) noexcept;
				
				/*
				 * @brief Copy assignment operator.
				 * @param other The iterator to copy.
				 * @return A reference to this iterator.
				*/
				SideCrossIterator &operator=(const SideCrossIterator &other) {
					if (this != &other)
					{
						_container = other._container;
						_index = other._index;
					}

					return *this;
				}

				/*
				 * @brief Move assignment operator.
				 * @param other The iterator to move.
				 * @return A reference to this iterator.
				 * @note The other iterator is left in a valid but unspecified state.
				 * @note Use the default move assignment operator, as the container property is a vector, which has its own move assignment operator.
				*/
				SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;
			
				/*
				 * @brief Equality operator, checks if two iterators are equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are equal, false otherwise.
				*/
				bool operator==(const SideCrossIterator &other) const {
					return _index == other._index;
				}

				/*
				 * @brief Inequality operator, checks if two iterators are not equal by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if the iterators are not equal, false otherwise.
				*/
				bool operator!=(const SideCrossIterator &other) const {
					return _index != other._index;
				}

				/*
				 * @brief Less than operator, checks if this iterator is less than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is less than the other iterator, false otherwise.
				*/
				bool operator<(const SideCrossIterator &other) const {
					return _index < other._index;
				}

				/*
				 * @brief Greater than operator, checks if this iterator is greater than the other iterator by comparing their index.
				 * @param other The iterator to compare to.
				 * @return True if this iterator is greater than the other iterator, false otherwise.
				*/
				bool operator>(const SideCrossIterator &other) const {
					return _index > other._index;
				}

				/*
				 * @brief Dereference operator, returns the element at the current index.
				 * @return The element at the current index (If the index is out of bounds, the behavior is undefined).
				*/
				int operator*() const {
					if (_index > _container._elements_ascending_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}
					
					return *(_container._elements_sidecross_order.at(_index));
				}

				/*
				 * @brief Prefix increment operator, increments the iterator to the next element.
				 * @return A reference to this iterator.
				 * @throw std::out_of_range If the iterator is out of range.
				*/
				SideCrossIterator &operator++() {
					if (_index > _container._elements_sidecross_order.size())
					{
						throw std::out_of_range("Iterator out of range");
					}
					
					++_index;
					return *this;
				}

				/*
				 * @brief Returns an iterator to the first element in the container.
				 * @return An iterator to the first element in the container.
				 * @note If the container is empty, the iterator returned is equal to the iterator returned by end().
				*/
				SideCrossIterator begin() {
					return SideCrossIterator(_container, 0);
				}

				/*
				 * @brief Returns an iterator to the element after the last element in the container.
				 * @return An iterator to the element after the last element in the container.
				 * @note This iterator is not dereferenceable.
				*/
				SideCrossIterator end() const {
					return SideCrossIterator(_container, _container._elements_sidecross_order.size());
				}
		};
	};
}