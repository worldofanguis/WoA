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


/* Class: Singleton
 * Description: this is a template class for inheritance
 *				used to make the access easy to those classes which are created only once
 *
 * Functions: Instance()
 *				used to retrieve the pointer to the class
 */


#pragma once
 
template<class T> 
class Singleton{
public:
	inline static T* Instance(){
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
