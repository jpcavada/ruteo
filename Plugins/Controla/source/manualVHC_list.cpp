#include "manualVHC_list.h"

	manualVHC_list::manualVHC_list() {
		
	}

	void manualVHC_list::addToList(manualVHC* vhc) {
		manualVHC_list::lista_mVHC.push_back(vhc);
	}

	bool manualVHC_list::isInList(VEHICLE* vhc) {
		int id_vhc = qpg_VHC_uniqueID(vhc);			//obtengo el ID del vehiculo que estoy buscando
		for(std::vector<int>::size_type i = 0; i != manualVHC_list::lista_mVHC.size(); i++) {
			int id_aux = qpg_VHC_uniqueID(lista_mVHC.at(i)->vehicle);
			if (id_vhc == id_aux)
				return true;
		}
		return false;
	}
	
	void manualVHC_list::startManualVHC(VEHICLE* vhc) {
		manualVHC *v_aux = new manualVHC(vhc);
		addToList(v_aux);
	}

	manualVHC* manualVHC_list::getManualVHC(VEHICLE* vhc) {
		int id_vhc = qpg_VHC_uniqueID(vhc);			
		for(std::vector<int>::size_type i = 0; i != manualVHC_list::lista_mVHC.size(); i++) {
			int id_aux = qpg_VHC_uniqueID(lista_mVHC.at(i)->vehicle);
			if (id_vhc == id_aux) {
				manualVHC* ret = lista_mVHC.at(i);
				return ret;
			}
		}
		return NULL;
	}
	
	
