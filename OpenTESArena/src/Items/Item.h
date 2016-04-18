#ifndef ITEM_H
#define ITEM_H

#include <string>

// I wanted to try and avoid using an abstract Item class, but in any case, this
// class should be used to try and bring together several elements, like the weight 
// or value of an item.

enum class ItemType;

class Item
{
public:
	Item();
	virtual ~Item();

	// This would be better to implement later, so members aren't missed via 
	// programmer error.
	// std::unique_ptr<Item> clone()...

	virtual ItemType getItemType() const = 0;
	virtual double getWeight() const = 0;
	virtual int getGoldValue() const = 0;
	virtual std::string getDisplayName() const = 0;

	// getTooltip()? How would it be split into colored sentences? Maybe a vector 
	// of TextLines. If unidentified, the text will be much reduced.

	// isQuestItem()?
};

#endif