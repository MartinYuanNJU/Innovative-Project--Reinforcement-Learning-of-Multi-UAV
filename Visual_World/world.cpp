#include "world.h"

World::World() {
    for(int i = 0; i < UAV_COUNT; i++) {
        positive_uav[i].set_world_comm(this, &positive_comm_info);
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        negative_uav[i].set_world_comm(this, &negative_comm_info);
    }
    //set obstacle pos
    Pos red_block_pos[RANDOM_BLOCK_COUNT_ONESIDE]={{35, 16}, {18, 15}, {30, 4}, {6, 14}, {31, 18}, {31, 11}, {41, 15}, {17, 12}, {18, 11}, {11, 19}, {20, 12}, {6, 15}, {37, 8}, {42, 8}, {38, 7}, {8, 7}, {23, 1}, {14, 16}, {15, 8}, {10, 12}, {34, 1}, {32, 11}, {29, 2}, {8, 17}, {33, 19}};
    Pos blue_block_pos[RANDOM_BLOCK_COUNT_ONESIDE];
    for(int i=0;i<RANDOM_BLOCK_COUNT_ONESIDE;i++)
    {
        blue_block_pos[i].row=49-red_block_pos[i].row;
        blue_block_pos[i].col=49-red_block_pos[i].col;
        State::obstacle_pos.insert({red_block_pos[i].row,red_block_pos[i].col});
        State::obstacle_pos.insert({blue_block_pos[i].row,blue_block_pos[i].col});
    }
    for(int i=0;i<SETTLED_BLOCK_COUNT_ONESIDE;i++)
    {
        State::obstacle_pos.insert({i,20});
        State::obstacle_pos.insert({i,29});
        State::obstacle_pos.insert({WORLD_SIZE-1-i,20});
        State::obstacle_pos.insert({WORLD_SIZE-1-i,29});
    }
    obstacle_pos = &State::obstacle_pos;

    reset();
}

void World::generate_row_col(int &selectrow,int &selectcol)
{
    int random=(int)random_(20);
    if(random==1)
        selectcol=1;
    else if(random>=2&&random<=3)
        selectcol=2;
    else if(random>=4&&random<=6)
        selectcol=3;
    else if(random>=7&&random<=10)
        selectcol=4;
    else if(random>=11&&random<=14)
        selectcol=5;
    else if(random>=15&&random<=17)
        selectcol=6;
    else if(random>=18&&random<=19)
        selectcol=7;
    else
        selectcol=8;
    random=(int)random_(110);
    if(random==1)
        selectrow=1;
    else if(random>=2&&random<=3)
        selectrow=2;
    else if(random>=4&&random<=6)
        selectrow=3;
    else if(random>=7&&random<=10)
        selectrow=4;
    else if(random>=11&&random<=15)
        selectrow=5;
    else if(random>=16&&random<=21)
        selectrow=6;
    else if(random>=22&&random<=28)
        selectrow=7;
    else if(random>=29&&random<=36)
        selectrow=8;
    else if(random>=37&&random<=45)
        selectrow=9;
    else if(random>=46&&random<=55)
        selectrow=10;
    else if(random>=56&&random<=65)
        selectrow=11;
    else if(random>=66&&random<=74)
        selectrow=12;
    else if(random>=75&&random<=82)
        selectrow=13;
    else if(random>=83&&random<=89)
        selectrow=14;
    else if(random>=90&&random<=95)
        selectrow=15;
    else if(random>=96&&random<=100)
        selectrow=16;
    else if(random>=101&&random<=104)
        selectrow=17;
    else if(random>=105&&random<=107)
        selectrow=18;
    else if(random>=108&&random<=109)
        selectrow=19;
    else
        selectrow=20;
}

void World::reset()
{
    //reset uav pos
    for(int i = 0; i < UAV_COUNT; i++) {
        Pos pos;
        pos.col = 0, pos.row = 3 + i * WORLD_SIZE / UAV_COUNT;
        positive_uav[i].reset(pos, true);
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        Pos pos;
        pos.col = WORLD_SIZE - 1, pos.row = 3 + i * WORLD_SIZE / UAV_COUNT;
        negative_uav[i].reset(pos, false);
    }

    //reset object pos
    int selectrow,selectcol;
    generate_row_col(selectrow, selectcol);
    object[0].reset({selectrow-1,selectcol+20});
    generate_row_col(selectrow, selectcol);
    object[1].reset({selectrow+29,selectcol+20});
}

void World::merge_comm_info()
{
    positive_uav[0].clear_comm_info();
    negative_uav[0].clear_comm_info();
    for(int i = 0; i < UAV_COUNT; i++) {
        if(positive_uav[i].need_comm()) {
            positive_uav[i].commit_comm_info();
        }
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        if(negative_uav[i].need_comm()) {
            negative_uav[i].commit_comm_info();
        }
    }
}

void World::print()
{
//    cout << "positive_pos: ";
//    for(int i = 0; i < UAV_COUNT; i++) {
//        positive_uav[i].get_state().self_pos.print();
//    }
//    cout << '\n';

//    cout << "positive_die: ";
//    for(int i = 0; i < UAV_COUNT; i++) {
//        cout << positive_uav[i].is_die() << ' ';
//    }
//    cout << '\n';

//    cout << "positive_comm_info:\n";
//    positive_comm_info.print();
//    cout << '\n';

//    cout << "negative_pos: ";
//    for(int i = 0; i < UAV_COUNT; i++) {
//        negative_uav[i].get_state().self_pos.print();
//    }
//    cout << '\n';

//    cout << "negative_die: ";
//    for(int i = 0; i < UAV_COUNT; i++) {
//        cout << negative_uav[i].is_die() << ' ';
//    }
//    cout << '\n';

//    cout << "negative_comm_info:\n";
//    negative_comm_info.print();
//    cout << '\n';

//    cout << "object_pos: ";
//    for(int i = 0; i < OBJECT_COUNT; i++) {
//        object[i].get_pos().print();
//    }
//    cout << '\n';

//    cout << "obstacle_pos: ";
//	set<Pos>::iterator it;
//	it = obstacle_pos->begin();
//	while (it != obstacle_pos->end()) {
//		it->print();
//		it++;
//	}
//	cout << '\n';

//    w->show();
//    w->printWorld(this);
//    a->exec();
//    a->exit();
}


/*{16, 35}, {15, 18}, {4, 30}, {14, 6}, {18, 31}, {11, 31}, {15, 41}, {12, 17}, {11, 18}, {19, 11}, {12, 20}, {15, 6}, {8, 37}, {8, 42}, {7, 38}, {7, 8}, {1, 23}, {16, 14}, {8, 15}, {12, 10}, {1, 34}, {11, 32}, {2, 29}, {17, 8}, {19, 33}*/
