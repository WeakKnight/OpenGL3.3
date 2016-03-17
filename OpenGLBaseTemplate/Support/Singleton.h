#ifndef  _SINGLETON_H_
#define _SINGLETON_H_

template<typename T> 
class Singleton
{
public:

	Singleton()
	{
	
	}
	
	virtual ~Singleton()
	{
	
	}

	static T& getInstance() 
	{
		static T instance;
		return instance;
	}

private:

	Singleton(Singleton const&);							
	Singleton& operator=(Singleton const&);									
};

#endif // _SINGLETON_H_

