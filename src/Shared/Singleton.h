/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 */
 
 
#pragma once
 
template<class T> 
class Singleton{
public:
	static T* Instance(){
	if (_instance == 0) 
		_instance = new T;
return _instance;
}
protected:
	Singleton() {}
private:
	static T* _instance;
};

template <class T>
T* Singleton<T>::_instance = 0;
