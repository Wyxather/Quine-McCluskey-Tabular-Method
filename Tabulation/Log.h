#pragma once

#include <deque>
#include <map>

struct Row;
struct Table;

struct Log
{
	explicit Log(const Row& row) noexcept;
	explicit Log(const std::deque<const Row*>& rowPtrs) noexcept;

	explicit Log(const Table& table) noexcept;
	explicit Log(const std::deque<Table>& tables) noexcept;
	explicit Log(const std::map<std::size_t, Table>& tables) noexcept;

	explicit Log(const std::deque<std::pair<std::intmax_t, std::size_t>>& map) noexcept;

	Log(Log&&) = delete;
	Log(const Log&) = delete;
	Log& operator=(Log&&) = delete;
	Log& operator=(const Log&) = delete;

	template <typename ...Args>
	static constexpr auto print(Args&& ...args) noexcept { return printf(args...); }

private:
	static auto print(const Row& row) noexcept -> void;
	static auto print(const Table& table) noexcept -> void;
	static auto print(const std::deque<std::pair<std::intmax_t, std::size_t>>& data) noexcept -> void;
};