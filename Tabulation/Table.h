#pragma once

#include "Row.h"

struct Table
{
	explicit Table() noexcept = default;
	explicit Table(const std::deque<std::intmax_t>& minTerm) noexcept;

	auto sort() noexcept -> void;

	std::deque<Row> row;

private:
	auto sortRow() noexcept -> void;
};