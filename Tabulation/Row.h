#pragma once

#include <deque>
#include <algorithm>

struct Row
{
	explicit Row() noexcept = default;
	explicit Row(std::intmax_t number) noexcept;

	[[nodiscard]] auto operator<(const Row& other) const noexcept -> bool;
	[[nodiscard]] auto operator==(const Row& other) const noexcept -> bool;

	auto growToFit(std::size_t size) noexcept -> void;
	auto sortNumber() noexcept -> void;
	[[nodiscard]] auto binaryOneCount() const noexcept -> std::size_t;
	[[nodiscard]] auto findOneBitChanges(const Row& other) const noexcept -> std::size_t;
	[[nodiscard]] auto countOneBitChanges(const Row& other) const noexcept -> std::size_t;

	bool checked = false;
	std::deque<std::uint8_t> binary;
	std::deque<std::intmax_t> number;

private:
	auto decToBin(std::intmax_t dec) noexcept -> void;
};