#ifndef _SPACE_PART_H
#define _SPACE_PART_H

#include "PartitionableItem.h"

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
	SpacePart(double fWorldWidth, double fWorldHeight, double fInteractionRadius);
	~SpacePart();

	void put(PartitionableItem*);
	list<PartitionableItem*> * getDirectNeighbours(PartitionableItem*);
	list<PartitionableItem*> * getIndirectNeighbours(PartitionableItem*, int);

private:
	double m_fWorldWidth, m_fWorldHeight, m_fInteractionRadius;
	int m_iNbTilesAbs, m_iNbTilesOrd;
	Partition * m_arrPartitions;
};

#endif
