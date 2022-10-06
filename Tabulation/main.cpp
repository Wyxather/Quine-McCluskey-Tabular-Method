#include "Table.h"
#include "Log.h"

auto operator+(const std::deque<std::intmax_t>& a, const std::deque<std::intmax_t>& b) noexcept
{
	auto r = a;
	r.insert(r.end(), b.cbegin(), b.cend());
	return r;
}

auto main() -> int
{
	constexpr auto solutionSymbol{ 'A' };
	std::deque<std::intmax_t> minTerm{ 0, 1, 9, 15, 24, 29, 30 };
	std::deque<std::intmax_t> dontCare{ 8, 11, 31 };

	// step 1
	Table step1{ minTerm + dontCare };
	{
		step1.sort();
		Log::print("----step1----\n");
		Log{ step1 };
		Log::print("\n\n");
	}

	// step 2
	std::map<std::size_t, Table> step2;
	{
		for (auto&& row : step1.row) {
			auto&& table = step2[row.binaryOneCount()];
			table.row.emplace_back(row);
			table.sort();
		}

		Log::print("----step2----\n");
		Log{ step2 };
		Log::print("\n\n");
	}

	//step 3
	std::deque<std::deque<Table>> step3;
	{
		auto&& curTableGroup = step3.emplace_back();

		for (auto _tableGroup = step2.begin(), _tableGroupEnd = step2.end(); _tableGroup != _tableGroupEnd; _tableGroup++) {

			auto _tableGroup2 = std::next(_tableGroup);
			if (_tableGroup2 == _tableGroupEnd)
				break;

			auto createTable = true;

			for (auto&& row : _tableGroup->second.row) {

				for (auto&& row2 : _tableGroup2->second.row) {

					if (const auto pos = row.findOneBitChanges(row2); pos != -1) {

						auto&& newTable = createTable ? curTableGroup.emplace_back() : curTableGroup.back();
						auto&& newRow = newTable.row.emplace_back();

						newRow.number.insert(newRow.number.end(), row.number.cbegin(), row.number.cend());
						newRow.number.insert(newRow.number.end(), row2.number.cbegin(), row2.number.cend());
						newRow.binary.insert(newRow.binary.end(), row.binary.cbegin(), row.binary.cend());
						newRow.binary[pos] = '-';

						createTable = false;
						row.checked = row2.checked = true;
					}
				}
			}
		}

		for (auto&& table : curTableGroup)
			table.sort();

		Log{ curTableGroup };
		Log::print("\n\n");
	}
	{
		const auto minimize = [&]() noexcept {

			auto&& previousTableGroup = step3.back();
			auto&& curTableGroup = step3.emplace_back();

			for (auto _tableGroup = previousTableGroup.begin(), _tableGroupEnd = previousTableGroup.end(); _tableGroup != _tableGroupEnd; _tableGroup++) {

				auto _tableGroup2 = std::next(_tableGroup);
				if (_tableGroup2 == _tableGroupEnd)
					break;

				auto createTable = true;

				for (auto&& row : _tableGroup->row) {

					for (auto&& row2 : _tableGroup2->row) {

						if (const auto pos = row.findOneBitChanges(row2); pos != -1) {

							auto&& newTable = createTable ? curTableGroup.emplace_back() : curTableGroup.back();
							auto&& newRow = newTable.row.emplace_back();

							newRow.number.insert(newRow.number.end(), row.number.cbegin(), row.number.cend());
							newRow.number.insert(newRow.number.end(), row2.number.cbegin(), row2.number.cend());
							newRow.binary.insert(newRow.binary.end(), row.binary.cbegin(), row.binary.cend());
							newRow.binary[pos] = '-';

							createTable = false;
							row.checked = row2.checked = true;
						}
					}
				}
			}

			for (auto&& table : curTableGroup)
				table.sort();

			Log{ curTableGroup };
			Log::print("\n");

			const auto isThereCheckedRow = std::find_if(previousTableGroup.cbegin(), previousTableGroup.cend(),
				[](const Table& table) noexcept {
					for (auto&& row : table.row)
						if (row.checked)
							return true;
					return false;
				}) != previousTableGroup.cend();

				return isThereCheckedRow;
		};

		while (true) {
			if (!minimize())
				break;
		}
	}

	Log::print("-----Step3-------\n");
	for (auto&& tableGroup : step3)
		Log{ tableGroup };
	Log::print("\n\n");

	Table primeImpl;
	{
		for (auto&& [count, table] : step2)
			for (auto&& row : table.row)
				if (!row.checked)
					primeImpl.row.insert(primeImpl.row.end(), row);

		for (auto _tableGroup = step3.cbegin(), _tableGroupEnd = std::prev(step3.cend()); _tableGroup != _tableGroupEnd; _tableGroup++)
			for (auto&& table : *_tableGroup)
				for (auto&& row : table.row)
					if (!row.checked)
						primeImpl.row.insert(primeImpl.row.end(), row);

		for (auto&& table : *std::prev(step3.cend()))
			primeImpl.row.insert(primeImpl.row.end(), table.row.cbegin(), table.row.cend());

		primeImpl.row.erase(std::unique(primeImpl.row.begin(), primeImpl.row.end()), primeImpl.row.end());

		Log::print<true>("----Prime Implicants----\n");
		Log{ primeImpl, true };
		Log::print<true>("\n\n");
	}

	std::deque<std::pair<std::intmax_t, std::size_t>> primeImplOccurance;
	{
		std::map<std::intmax_t, std::size_t> map;
		for (auto&& min : minTerm)
			for (auto&& row : primeImpl.row)
				for (auto&& num : row.number)
					if (min == num)
						map[min] += 1;

		for (auto&& [number, occurance] : map)
			primeImplOccurance.emplace_back(number, occurance);

		std::sort(primeImplOccurance.begin(), primeImplOccurance.end(),
			[](const std::pair<std::intmax_t, std::size_t>& a, const std::pair<std::intmax_t, std::size_t>& b) noexcept {
				if (a.second != b.second)
					return a.second < b.second;
				return a.first < b.first;
			});

		Log::print("----Occurance----\n");
		Log{ primeImplOccurance };
		Log::print("\n\n");
	}

	std::deque<const Row*> essentialPrimeImpl;
	{
		for (auto p = primeImplOccurance.begin(); p != primeImplOccurance.end(); p = primeImplOccurance.begin()) {

			Row* bestRow;
			auto bestSim = 0;

			for (auto&& row : primeImpl.row) {

				auto isThereCurPrime = false;
				for (auto&& num : row.number) {
					if (num == p->first) {
						isThereCurPrime = true;
						break;
					}
				}

				if (!isThereCurPrime)
					continue;

				auto sim = 1;
				for (auto&& num : row.number) {

					if (num == p->first)
						continue;

					const auto found = std::find_if(primeImplOccurance.cbegin(), primeImplOccurance.cend(),
						[&](const std::pair<std::intmax_t, std::size_t>& data) noexcept {
							return data.first == num;
						}) != primeImplOccurance.cend();

						if (found)
							sim++;
				}

				if (sim > bestSim) {
					bestSim = sim;
					bestRow = &row;
				}
			}

			primeImplOccurance.erase(p);
			primeImplOccurance.erase(std::remove_if(primeImplOccurance.begin(), primeImplOccurance.end(),
				[&](const std::pair<std::intmax_t, std::size_t>& data) noexcept {
					for (auto&& num : bestRow->number)
						if (num == data.first)
							return true;
					return false;
				}), primeImplOccurance.end());

			essentialPrimeImpl.emplace_back(bestRow);
		}

		Log::print<true>("----Essential Prime Implicants----\n");
		Log{ essentialPrimeImpl, true };
		Log::print<true>("\n\n");
	}

	{
		Log::print<true>("----Solution----\n");
		for (auto _row = essentialPrimeImpl.cbegin(), _rowEnd = essentialPrimeImpl.cend(); _row != _rowEnd; _row++) {
			auto row = *_row;

			if (_row != essentialPrimeImpl.cbegin())
				Log::print<true>(" + ");

			for (decltype(row->binary)::size_type i = 0, size = row->binary.size(); i < size; i++) {
				const auto str = solutionSymbol + i;

				switch (row->binary[i]) {
				case 1: Log::print<true>("%c", str);
					break;
				case 0: Log::print<true>("%c%c", str, '\'');
					break;
				}
			}
		}
		Log::print<true>("\n\n");
	}

	return 0;
}