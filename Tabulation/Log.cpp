#include "Log.h"
#include "Table.h"

Log::Log(const Row& row) noexcept
{
	Log::print(row);
}

Log::Log(const std::deque<const Row*>& rowPtrs) noexcept
{
	for (auto rowPtr : rowPtrs) {
		Log::print(*rowPtr);
		Log::print("---------------------\n");
	}
}

Log::Log(const Table& table) noexcept
{
	Log::print(table);
}

Log::Log(const std::deque<Table>& tables) noexcept
{
	for (auto&& table : tables) {
		Log::print(table);
		Log::print("---------------------\n");
	}
}

Log::Log(const std::map<std::size_t, Table>& tables) noexcept
{
	for (auto&& [count, table] : tables) {
		Log::print(table);
		Log::print("---------------------\n");
	}
}

Log::Log(const std::deque<std::pair<std::intmax_t, std::size_t>>& map) noexcept
{
	Log::print(map);
}

auto Log::print(const Row& row) noexcept -> void
{
	Log::print("(");
	for (auto _begin = row.number.cbegin(), _number = _begin, _end = row.number.cend(); _number != _end; _number++) {
		if (_number != _begin)
			Log::print(", %2jd", *_number);
		else
			Log::print("%2jd", *_number);
	}
	Log::print(") ");

	for (const auto binary : row.binary) {
		if (binary != '-')
			Log::print("%d ", binary);
		else
			Log::print("%c ", binary);
	}
	Log::print("[%s]\n", row.checked ? "true" : "false");
}

auto Log::print(const Table& table) noexcept -> void
{
	for (auto&& row : table.row)
		Log::print(row);
}

auto Log::print(const std::deque<std::pair<std::intmax_t, std::size_t>>& data) noexcept -> void
{
	for (auto&& [num, count] : data)
		Log::print("%jd: %d\n", num, count);
}