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
protected:
	Vector2 positon, direction;
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

	friend std::ostream & operator<< (std::ostream &, const Train &);
	friend std::istream & operator>> (std::istream &, Train &);
};

inline std::ostream & operator<< (std::ostream &v , const Train & pT)
{
	return v<<typeid(pT).name()<<std::endl<<pT.averageSpeed<<" "<<pT.capacity<<" "<<pT.delay<<" "<<pT.currentBurden<<" "<<
		pT.direction<<" "<<pT.positon<<" "<<pT.distance<<std::endl;
}

inline std::istream & operator>> (std::istream & v, Train & pT)
{
	return  v>>pT.averageSpeed>>pT.capacity>>pT.delay>>pT.currentBurden>>
		pT.direction>>pT.positon>>pT.distance;
}

class PassengerTrain :public Train
{
public:
	PassengerTrain(const float,const unsigned int,MapElement * const);
	virtual ~PassengerTrain(void);
	void load(const unsigned int );
	void unload(const unsigned int );
	void update();
	virtual const std::string getType()const;

	friend std::ostream & operator<< (std::ostream &, const PassengerTrain &);
	friend std::istream & operator>> (std::istream &, PassengerTrain &);
};

inline std::ostream & operator<< (std::ostream &v , const PassengerTrain & pT)
{
	v<<typeid(pT).name()<<" "<<pT.averageSpeed<<" "<<pT.capacity<<" "<<pT.delay<<" "<<pT.currentBurden<<" "<<
		pT.direction<<" "<<pT.positon<<" "<<pT.distance<<std::endl;
}

inline std::istream & operator>> (std::istream & v, PassengerTrain & pT)
{
	return  v>>pT.averageSpeed>>pT.capacity>>pT.delay>>pT.currentBurden>>
		pT.direction>>pT.positon>>pT.distance;
}

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

	template <char const  * productName, char const *  trainName> 
	friend std::ostream & operator<< (std::ostream &, const FreightTrain<productName,trainName> &);
	template <char const  * productName, char const *  trainName> 
	friend std::istream & operator>> (std::istream &, FreightTrain<productName,trainName> &);
};

template <char const  * productName, char const *  trainName> 
std::ostream & operator<< (std::ostream & v, const FreightTrain<productName,trainName>  & fT)
{
	v<<typeid(pT).name()<<" "<<productName<<" "<<trainName<<" "<<pT.averageSpeed<<" "<<pT.capacity<<" "<<pT.delay<<" "<<pT.currentBurden<<" "<<
		pT.direction<<" "<<pT.positon<<" "<<pT.distance<<std::endl;
}

template <char const  * productName, char const *  trainName> 
std::istream & operator>> (std::istream &, FreightTrain<productName,trainName> &)
{
	return  v>>pT.averageSpeed>>pT.capacity>>pT.delay>>pT.currentBurden>>
		pT.direction>>pT.positon>>pT.distance;
}

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
					getProduct(productName)->remove(true);
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


