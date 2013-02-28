#ifndef _SPACE_PART_H
#define _SPACE_PART_H

#include "PartitionableItem.h"

#define SPACE_PART_ROWS					10
#define NB_INDIRECT_NEIGHBOURS_ZONES	8

class Partition
{
public:
	list<PartitionableItem*> partition;
	int x, y;
};

class SpacePart
{
public:
	SpacePart(double fWidth, double fHeight);
	void put(PartitionableItem*);
	list<PartitionableItem*> * getDirectNeighbours(PartitionableItem*);
	list<PartitionableItem*> * getIndirectNeighbours(PartitionableItem*, int);

private:
	double m_fWidth, m_fHeight;
	Partition m_arrPartitions[SPACE_PART_ROWS*SPACE_PART_ROWS];
};

#endif
