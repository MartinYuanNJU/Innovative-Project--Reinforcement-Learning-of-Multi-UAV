#include"uav.h"
#include"world.h"

Uav::Uav(World* world, Pos pos, bool side) {
    this->world = world;
    //srand((int)time(0));//ask wjf&yx who to do this?
    //world->reset(0);
    reset(pos, side);
}

void Uav::reset(Pos pos, bool side) {
    comm_info->clear();
    this->pos = pos;
    this->side = side;
    this->step_cnt = 0;
    this->comm_cnt = 0;
    this->collision_flag = false;
    this->attacked_flag = false;
    this->comm_prob = 100;//default value
    this->last_info = false;
    this->penalty = false;
}

State Uav::get_state() {
    //failure of commication means can get others info but cannot share info to others

    State res(side, is_die(), pos, *comm_info + scan_nearby());
    return res;
}

Pos_info Uav::scan_nearby() {
        Pos_info res;
        res.clear();

        Uav* ptr_u = 0;

        ptr_u = world->positive_uav;
        for (int i = 0; i < UAV_COUNT; i++) {
            if (!((ptr_u + i)->is_die()) && is_nearby((ptr_u + i)->pos))
                res.positive_pos.insert((ptr_u + i)->pos);
        }
        ptr_u = world->negative_uav;
        for (int i = 0; i < UAV_COUNT; i++) {
            if (!((ptr_u + i)->is_die()) && is_nearby((ptr_u + i)->pos))
                res.negative_pos.insert((ptr_u + i)->pos);
        }

        Object* ptr_o = world->object;
        for (int i = 0; i < OBJECT_COUNT; i++) {
            Pos temp = (ptr_o + i)->get_pos();
            if (!(ptr_o + i)->is_detected() && is_nearby(temp))
                res.object_pos.insert(temp);
        }

        return res;
}


int Uav::power_count() {
    int cnt = 0;
    Uav* ptr_u = 0;

    if (side)
        ptr_u = world->negative_uav;
    else
        ptr_u = world->positive_uav;

    for (int i = 0; i < UAV_COUNT; i++) {
        if (!(ptr_u + i)->is_die() && is_nearby((ptr_u + i)->pos))
            cnt++;
    }
    return cnt;
}

void Uav::commit_comm_info() {
    if (last_info || comm_cnt == MAX_COMM_CNT)
        return;

    comm_cnt++;
    //fail to comm
    if ((rand() % 100) > comm_prob)//env&srand?
        return;
    if (is_die() && !last_info)
        last_info = true;

    Pos_info res = scan_nearby();
    if (side)
        res.positive_pos.insert(pos);//step needed?
    else
        res.negative_pos.insert(pos);
    //*comm_info = *comm_info + res;
    comm_info->add(res);
}


void Uav::clear_comm_info() {
    comm_info->clear();
}

//todo:Action one dimension?
void Uav::apply_action(Action action) {
    if(is_die()) return;
    step_cnt++;

    //whether need to mul -1 as to camp
    //todo:verify the direction
    if (action == UP) {
        side ? pos.col++ : pos.col--;
    }else if (action == DOWN) {
        side ? pos.col-- : pos.col++;
    }
    else if (action == LEFT) {
        side ? pos.row-- : pos.row++;
    }
    else if (action == RIGHT) {
        side ? pos.row++ : pos.row--;
    }
}

bool Uav::ob() {
    return (pos.col < 0) || (pos.row < 0) || (pos.col >= WORLD_SIZE) || (pos.row >= WORLD_SIZE);
}

bool Uav::is_die() {
    return collision_flag || attacked_flag || ob();
}


void Uav::set_comm_prob(int p) {
    comm_prob = p;
}

bool Uav::need_comm() {
    Pos_info res = scan_nearby();
    if (!(step_cnt % 20) || res.object_pos.size() || (is_die() && !last_info))
        return true;
    else
        return false;
}

bool Uav::is_nearby(Pos& x) {
    return ((pos.col - x.col) <= SCAN_RANGE) && ((pos.col - x.col) >= -SCAN_RANGE) && ((pos.row - x.row) <= SCAN_RANGE) && ((pos.row - x.row) >= -SCAN_RANGE);
}
