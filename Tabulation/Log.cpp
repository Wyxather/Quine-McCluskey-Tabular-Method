#include "Log.h"
#include "Table.h"

Log::Log(const Row& row, bool force) noexcept
{
	Log::print(row, force);
}

Log::Log(const std::deque<const Row*>& rowPtrs, bool force) noexcept
{
	for (auto rowPtr : rowPtrs) {
		Log::print(*rowPtr, force);
		if (force)
			Log::print<true>("---------------------\n");
		else
			Log::print("---------------------\n");
	}
}

Log::Log(const Table& table, bool force) noexcept
{
	Log::print(table, force);
}

Log::Log(const std::deque<Table>& tables, bool force) noexcept
{
	for (auto&& table : tables) {
		Log::print(table, force);
		if (force)
			Log::print<true>("---------------------\n");
		else
			Log::print("---------------------\n");
	}
}

Log::Log(const std::map<std::size_t, Table>& tables, bool force) noexcept
{
	for (auto&& [count, table] : tables) {
		Log::print(table, force);
		if (force)
			Log::print<true>("---------------------\n");
		else
			Log::print("---------------------\n");
	}
}

Log::Log(const std::deque<std::pair<std::intmax_t, std::size_t>>& map, bool force) noexcept
{
	Log::print(map, force);
}

auto Log::print(const Row& row, bool force) noexcept -> void
{
	if (force) {
		Log::print<true>("(");
		for (auto _begin = row.number.cbegin(), _number = _begin, _end = row.number.cend(); _number != _end; _number++) {
			if (_number != _begin)
				Log::print<true>(", %2jd", *_number);
			else
				Log::print<true>("%2jd", *_number);
		}
		Log::print<true>(") ");

		for (const auto binary : row.binary) {
			if (binary != '-')
				Log::print<true>("%d ", binary);
			else
				Log::print<true>("%c ", binary);
		}
		Log::print<true>("[%s]\n", row.checked ? "true" : "false");
	}
	else {
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
}

auto Log::print(const Table& table, bool force) noexcept -> void
{
	for (auto&& row : table.row)
		Log::print(row, force);
}

auto Log::print(const std::deque<std::pair<std::intmax_t, std::size_t>>& data, bool force) noexcept -> void
{
	if (force) {
		for (auto&& [num, count] : data)
			Log::print<true>("%jd: %d\n", num, count);
	}
	else {
		for (auto&& [num, count] : data)
			Log::print("%jd: %d\n", num, count);
	}
}