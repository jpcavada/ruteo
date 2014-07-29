#pragma once
#include <vector>
#include "manualVHC.h"

class manualVHC_list {

	private:
			std::vector <manualVHC*> lista_mVHC; 	
	
	protected:
		void addToList(manualVHC* vhc);

	public:
		manualVHC_list();
		void startManualVHC(VEHICLE* vhc);

		bool isInList(VEHICLE* vhc);
		manualVHC* getManualVHC(VEHICLE* vhc);

};