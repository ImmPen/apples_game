#include "records.h"
#include "Math.h"
#include <algorithm>

namespace ApplesGame
{
    RecordsTable GetNewRecordTable()
    {
        RecordsTable result;
        for (int i = 0; i < NUM_NAMES_IN_TABLE; i++)
        {
            result.entry[i].name = GetRandomName();
            result.entry[i].score = rand() % 100;
        }
        std::sort(std::begin(result.entry), std::end(result.entry),  CompareEntry);
        return result;
    }
    bool CompareEntry(RecordsTableItem first, RecordsTableItem second)
    {
        return first.score > second.score;
    }
    void AddEntryToTable(RecordsTable& table, RecordsTableItem entry)
    {
        RecordsTableItem* placeForNewEntry = std::lower_bound(
            std::begin(table.entry), std::end(table.entry), entry, CompareEntry);
        if (placeForNewEntry < std::end(table.entry))
        {
            for (RecordsTableItem* i = std::end(table.entry) - 1; i > placeForNewEntry; i--)
            {
                *i = *(i - 1);
            }
            *placeForNewEntry = entry;
        }
    }
}
