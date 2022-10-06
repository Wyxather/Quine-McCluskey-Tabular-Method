#include "Row.h"

Row::Row(std::intmax_t number) noexcept : number{ number }
{
	decToBin(number);
}

auto Row::operator<(const Row& other) const noexcept -> bool
{
	for (decltype(number)::size_type i = 0, size = number.size(); i < size; i++)
		if (number[i] != other.number[i])
			return number[i] < other.number[i];
	return false;
}

auto Row::operator==(const Row& other) const noexcept -> bool
{
	if (this == &other)
		return true;

	if (number.size() != other.number.size())
		return false;

	for (decltype(number)::size_type i = 0, size = number.size(); i < size; i++)
		if (number[i] != other.number[i])
			return false;

	if (binary.size() != other.binary.size())
		return false;

	for (decltype(binary)::size_type i = 0, size = binary.size(); i < size; i++)
		if (binary[i] != other.binary[i])
			return false;

	return true;
}

auto Row::growToFit(std::size_t size) noexcept -> void
{
	while (binary.size() < size)
		binary.emplace_front(0);
}

auto Row::sortNumber() noexcept -> void
{
	std::sort(number.begin(), number.end());
}

auto Row::binaryOneCount() const noexcept -> std::size_t
{
	std::size_t count = 0;
	for (auto&& binary : binary)
		if (binary == 1)
			count++;
	return count;
}

auto Row::findOneBitChanges(const Row& other) const noexcept -> std::size_t
{
	std::size_t pos = -1;
	for (decltype(binary)::size_type i = 0, size = binary.size(); i < size; i++) {
		if (binary[i] != other.binary[i]) {
			if (pos == -1)
				pos = i;
			else
				return -1;
		}
	}
	return pos;
}

auto Row::countOneBitChanges(const Row& other) const noexcept -> std::size_t
{
	std::size_t count = 0;
	for (decltype(binary)::size_type i = 0, size = binary.size(); i < size; i++)
		if (binary[i] != other.binary[i])
			count++;
	return count;
}

auto Row::decToBin(std::intmax_t dec) noexcept -> void
{
	while (dec) {
		(dec & 1) ? binary.emplace_front(1) : binary.emplace_front(0);
		dec >>= 1;
	}
}