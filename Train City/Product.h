#pragma once


class Product
{
private:
	std::string name;
	float price, productionPerSecond, demandPerSecond, count;
public:
	Product(const std::string, const float, const float,const float, const float);
	~Product();

	const std::string getName()const;
	const float getPrice()const;
	const float getCount()const;
	void update();

};


inline const std::string Product::getName()const
{
	return name;
}

inline const float Product::getPrice()const
{
	return price;
}
inline const float Product::getCount()const
{
	return count;
}


