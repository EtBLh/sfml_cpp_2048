#pragma once

namespace _2048 {

	class dto{
	private:
        dto();
        
        //dto(dto const&);
        //void operator=(dto const&);
	public:
		int** map;
		int step = 1;
		int max = 2;
		bool is_game_over = false;
		bool won = false;
		int mem[16] = { 0 };
        static dto& get_instance();

        dto(dto const&) = delete;
        void operator=(dto const&) = delete;
	};
}
