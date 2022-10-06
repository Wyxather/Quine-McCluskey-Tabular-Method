#pragma once

#include <deque>
#include <map>

struct Row;
struct Table;

struct Log
{
	explicit Log(const Row& row, bool force = false) noexcept;
	explicit Log(const std::deque<const Row*>& rowPtrs, bool force = false) noexcept;

	explicit Log(const Table& table, bool force = false) noexcept;
	explicit Log(const std::deque<Table>& tables, bool force = false) noexcept;
	explicit Log(const std::map<std::size_t, Table>& tables, bool force = false) noexcept;

	explicit Log(const std::deque<std::pair<std::intmax_t, std::size_t>>& map, bool force = false) noexcept;

	Log(Log&&) = delete;
	Log(const Log&) = delete;
	Log& operator=(Log&&) = delete;
	Log& operator=(const Log&) = delete;

	template <bool force = false, typename ...Args>
	static constexpr auto print(Args&& ...args) noexcept
	{
		if constexpr (force)
			return printf(args...);
#ifndef NDEBUG
		return printf(args...);
#endif
	}

private:
	static auto print(const Row& row, bool force) noexcept -> void;
	static auto print(const Table& table, bool force) noexcept -> void;
	static auto print(const std::deque<std::pair<std::intmax_t, std::size_t>>& data, bool force) noexcept -> void;
};