#pragma once
#include "Delay.h"
#include "Product.h"
#include "City.h"
#include "Time.h"

class MapElement;
class City;
class Product;
typedef std::list<Product> Products;


class Train
{
private:
	Vector2 positon, direction;
protected:
	unsigned int capacity, currentBurden;
	MapElement * target;
	Delay delay;
	float averageSpeed, distance;
	Product * const getProduct(const std::string); 
public:
	void goTo(MapElement *const);
	Train * const get(){return this;};
	MapElement * const getTarget()const;
	const bool isReady()const;
	virtual const std::string getType()const = 0;
	virtual void load(const unsigned int )=0;
	virtual void unload(const unsigned int )=0;
	Train(const float,const unsigned int,MapElement * const);
	void draw();
	~Train(void);
};

class PassengerTrain :public Train
{
public:
	PassengerTrain(const float,const unsigned int,MapElement * const);
	virtual ~PassengerTrain(void);
	void load(const unsigned int );
	void unload(const unsigned int );
	virtual const std::string getType()const;
};

inline const std::string PassengerTrain::getType()const
{
	return "Passenger";
}


template <char const  * productName, char const *  trainName> 
class FreightTrain :public Train
{
public:
	FreightTrain(const float averageSpeed,const unsigned int capacity, MapElement * const target);
	virtual ~FreightTrain(void){}
	void load(const unsigned int );
	
	void unload(const unsigned int );
	virtual const std::string getType()const ;
};

template <char const  * productName, char const *  trainName> 
FreightTrain<productName, trainName>::FreightTrain(const float averageSpeed,const unsigned int capacity, MapElement * const target):Train(averageSpeed, capacity,target)
{
}


template <char const  * productName, char const *  trainName> 
void FreightTrain< productName, trainName>::unload(const unsigned int value)
{
	if(delay.isRedy())
	{
		if(typeid(*target)==typeid(City))
		{
			for(unsigned int i =0 ;i<value;++i)
			{
				if(currentBurden>0)
				{
					getProduct(productName)->add();
					currentBurden--;
				}else
					break;
			}
		}
	}
}


template <char const  * productName, char const *  trainName> 
void FreightTrain< productName, trainName>::load(const unsigned int value)
{
	if(delay.isRedy())
	{
		if(typeid(*target)==typeid(City))
		{
			for(unsigned int i =0 ;i<value;++i)
			{
				if(getProduct(productName)->getCount() >0 && currentBurden<capacity)
				{
					getProduct(productName)->remove();
					currentBurden++;
				}else
					break;
			}
		}
	}
}


template <char const  * productName, char const *  trainName> 
inline const std::string FreightTrain< productName, trainName>::getType()const
{
	return trainName;
}


