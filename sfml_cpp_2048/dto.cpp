#include <stdlib.h>
#include "dto.h"

namespace _2048 {

	dto::dto() {
		//make memory continuous
		this->map = (int**)calloc(4, sizeof(int*));
		for (int i = 0; i < 4; i++) {
			this->map[i] = mem + i*4;
		}
	}

	dto& dto::get_instance(){
		static dto instance;
		return instance;
	}
}