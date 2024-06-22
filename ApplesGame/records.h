#pragma once
#include "constants.h"
namespace ApplesGame
{
	struct RecordEntry
	{
		std::string name;
		int score;
	};
	struct RecordsTable
	{
		RecordEntry entry[NUM_NAMES_IN_TABLE];
	};

	RecordsTable GetNewRecordTable();

	bool compareEntry(RecordEntry first, RecordEntry second);

	void addEntryToTable(RecordsTable& table, RecordEntry entry);
}
