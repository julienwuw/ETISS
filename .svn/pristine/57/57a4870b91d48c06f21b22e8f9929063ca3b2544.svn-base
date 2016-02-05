/*
	Author: Marc Greim

	Copyright (C) 2013 EDA TU München. All rights reserved.

	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

*/
#ifndef RESOURCE_CHECKOUT__H
#define RESOURCE_CHECKOUT__H

#include <vector>


template <typename T>
/**
	@brief simple buffer of allocated objects
*/
class ResourceCheckout {

	private:
		
		std::vector<T*> reslist;
		unsigned pointer;
		
	public:
		ResourceCheckout(unsigned cap = 100){
			reslist.clear();
			for (unsigned i = 0;i<cap;i++){
				reslist.push_back(_new());
			}
			pointer = cap;
		}
		virtual ~ResourceCheckout(){
			for (unsigned i = 0;i<pointer;i++){
				delete reslist[i];
			}
			pointer = 0;
			reslist.clear();
		}
		
		virtual T* _new(){
			return new T();
		}
		
		/**
			@return must always return a valid (non-zero) pointer, preferably the passd one
		*/
		virtual T* reset(T*t){
			return t;
		}

		/**
			@return returns always a valid (non-zero) pointer
		*/
		T* checkout(){
			if (pointer > 0){
				pointer--;
				return reset(reslist[pointer]);
			} else {
				return _new();
			}
		}
		
		/**
			@breif any pointer aquired by checkout should be passed back to checkin; after a checkin call the passed object may no longer be used
		*/
		void checkin(T*t){
		
			if (t==NULL) return;
			
			if (pointer < reslist.size()){
				reslist[pointer] = t;
				pointer++;
			} else {
				delete t;
			}
		}
		
};





















#endif
