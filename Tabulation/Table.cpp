#include "Table.h"

Table::Table(const std::deque<std::intmax_t>& minTerm) noexcept
{
	for (auto&& m : minTerm)
		row.emplace_back(m);

	decltype(Row::binary)::size_type maxSize = 0;
	for (const auto& r : row)
		if (const auto size = r.binary.size(); size > maxSize)
			maxSize = size;

	for (auto&& r : row)
		r.growToFit(maxSize);
}

auto Table::sort() noexcept -> void
{
	sortRow();
	std::sort(row.begin(), row.end());
}

auto Table::sortRow() noexcept -> void
{
	for (auto&& r : row)
		r.sortNumber();
}