// -----------------------------------------------------------------
// SPACE PARTITION
// -----------------------------------------------------------------
#include "SpacePart.h"


// -----------------------------------------------------------------
// Name : SpacePart
// -----------------------------------------------------------------
SpacePart::SpacePart(double fWidth, double fHeight)
{
	 m_fWidth = fWidth;
	 m_fHeight = fHeight;
	 for (int i = 0; i < SPACE_PART_ROWS * SPACE_PART_ROWS; i++) {
		 m_arrPartitions[i].x = i % SPACE_PART_ROWS;
		 m_arrPartitions[i].y = i / SPACE_PART_ROWS;
	 }
}

// -----------------------------------------------------------------
// Name : put
//	Complexity o(1)
// -----------------------------------------------------------------
void SpacePart::put(PartitionableItem * pItem)
{
	// Determine partition to use (o(1))
	f3d pos = pItem->getPosition();
	int i = (int) (SPACE_PART_ROWS * pos.x / m_fWidth);
	int j = (int) (SPACE_PART_ROWS * pos.y / m_fHeight);
	if (i < 0) {
		i = 0;
	} else if (i >= SPACE_PART_ROWS) {
		i = SPACE_PART_ROWS - 1;
	}
	if (j < 0) {
		j = 0;
	} else if (j >= SPACE_PART_ROWS) {
		j = SPACE_PART_ROWS - 1;
	}

	// Replace previous partition
	Partition * newPartition = &(m_arrPartitions[i + j * SPACE_PART_ROWS]);
	Partition * oldPartition = pItem->getPartition();
	if (newPartition != oldPartition) {
		if (oldPartition != NULL) {
			oldPartition->partition.remove(pItem);
		}
		newPartition->partition.push_back(pItem);
		pItem->setPartition(newPartition);
	}
}

// -----------------------------------------------------------------
// Name : getDirectNeighbours
// -----------------------------------------------------------------
list<PartitionableItem*> * SpacePart::getDirectNeighbours(PartitionableItem * pItem)
{
	return &(pItem->getPartition()->partition);
}

// -----------------------------------------------------------------
// Name : getIndirectNeighbours
// -----------------------------------------------------------------
list<PartitionableItem*> * SpacePart::getIndirectNeighbours(PartitionableItem * pItem, int iteration)
{
	if (iteration >= 4) {
		// skip iteration 4
		iteration++;
	}
	int dx = (iteration % 3) - 1;	// -1, 0, 1, -1, n/a, 1, -1, 0, 1
	int dy = (iteration / 3) - 1;	// -1, -1, -1, 0, n/a, 0, 1, 1, 1
	Partition * p = pItem->getPartition();
	int x = p->x + dx;
	int y = p->y + dy;
	if (x >= 0 && x < SPACE_PART_ROWS && y >= 0 && y < SPACE_PART_ROWS) {
		return &(m_arrPartitions[x + y * SPACE_PART_ROWS].partition);
	} else {
		return NULL;
	}
}
