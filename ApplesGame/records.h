#pragma once
#include "GameSettings.h"
namespace ApplesGame
{
	struct RecordsTableItem
	{
		std::string name;
		int score = 0;
	};

	struct RecordsTable
	{
		RecordsTableItem entry[NUM_NAMES_IN_TABLE];
	};

	RecordsTable GetNewRecordTable();

	bool CompareEntry(RecordsTableItem first, RecordsTableItem second);

	void AddEntryToTable(RecordsTable& table, RecordsTableItem entry);
}
