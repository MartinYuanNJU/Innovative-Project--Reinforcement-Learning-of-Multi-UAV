#include "env.h"

set<Pos> State::obstacle_pos;

Env::Env() {
    srand((int)time(0));
    world = new World;
    step_cnt = 0;
}

State *Env::reset() {
    step_cnt = 0;

    world->reset();
    world->merge_comm_info();

    State *state = new State[UAV_COUNT * 2];
    for(int i = 0; i < UAV_COUNT; i++) {
        state[i] = world->positive_uav[i].get_state();
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        state[i + UAV_COUNT] = world->negative_uav[i].get_state();
    }

    print();

    return state;   //TODO: need to free manually
}

SRDI *Env::step(Action action[]) {
    step_cnt++;

    Uav *positive_uav = world->positive_uav, *negative_uav = world->negative_uav;

    for(int i = 0; i < OBJECT_COUNT; i++) {
        world->object[i].update();
    }

    for(int i = 0; i < UAV_COUNT; i++) {
        if(!positive_uav[i].is_die()) {
            positive_uav[i].apply_action(action[i]);
        }
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        if(!negative_uav[i].is_die()) {
            negative_uav[i].apply_action(action[UAV_COUNT + i]);
        }
    }

    //collision check
    //collide with block
    for(int i = 0; i < UAV_COUNT; i++) {
        if(world->obstacle_pos->find(positive_uav[i].get_pos()) != world->obstacle_pos->end()) {
            positive_uav[i].collision_flag = true;
        }
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        if(world->obstacle_pos->find(negative_uav[i].get_pos()) != world->obstacle_pos->end()) {
            negative_uav[i].collision_flag = true;
        }
    }

    int positive_attack_reward[UAV_COUNT], negative_attack_reward[UAV_COUNT];
    for(int i = 0; i < UAV_COUNT; i++) {
        positive_attack_reward[i] = negative_attack_reward[i] = 0;
    }

    //at same position
    for(int i = 0; i < UAV_COUNT; i++) {
        for(int j = i + 1; j < UAV_COUNT; j++) {
            if(!positive_uav[i].is_die()
            && !positive_uav[j].is_die()
            && positive_uav[i].get_pos() == positive_uav[j].get_pos()) {
                positive_uav[i].collision_flag = positive_uav[j].collision_flag = true;
            }
            if(!negative_uav[i].is_die()
            && !negative_uav[j].is_die()
            && negative_uav[i].get_pos() == negative_uav[j].get_pos()) {
                negative_uav[i].collision_flag = negative_uav[j].collision_flag = true;
            }
        }
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        for(int j = 0; j < UAV_COUNT; j++) {
            if(!positive_uav[i].is_die()
            && !negative_uav[j].is_die()
            && positive_uav[i].get_pos() == negative_uav[j].get_pos()) {
                process_attack(positive_uav[i], negative_uav[j]);
                if(positive_uav[i].attacked_flag && !negative_uav[j].attacked_flag) {
                    positive_attack_reward[i] = -125;
                    negative_attack_reward[j] = +125;
                }
                if(!positive_uav[i].attacked_flag && negative_uav[j].attacked_flag) {
                    positive_attack_reward[i] = +125;
                    negative_attack_reward[j] = -125;
                }
            }
        }
    }

    //same direction
    for(int i = 0; i < UAV_COUNT; i++) {
        for(int j = i + 1; j < UAV_COUNT; j++) {
            if(!positive_uav[i].is_die()
            && !positive_uav[j].is_die()
            && same_direction(positive_uav[i], action[i], positive_uav[j], action[j])) {
                positive_uav[i].collision_flag = positive_uav[j].collision_flag = true;
            }
            if(!negative_uav[i].is_die()
            && !negative_uav[j].is_die()
            && same_direction(negative_uav[i], action[i+UAV_COUNT], negative_uav[j], action[j+UAV_COUNT])) {
                negative_uav[i].collision_flag = negative_uav[j].collision_flag = true;
            }
        }
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        for(int j = 0; j < UAV_COUNT; j++) {
            if(!positive_uav[i].is_die()
            && !negative_uav[j].is_die()
            && same_direction(positive_uav[i], action[i], negative_uav[j], action[j+UAV_COUNT])) {
                process_attack(positive_uav[i], negative_uav[j]);
                if(positive_uav[i].attacked_flag && !negative_uav[j].attacked_flag) {
                    positive_attack_reward[i] = -125;
                    negative_attack_reward[j] = +125;
                }
                if(!positive_uav[i].attacked_flag && negative_uav[j].attacked_flag) {
                    positive_attack_reward[i] = +125;
                    negative_attack_reward[j] = -125;
                }
            }
        }
    }

    world->merge_comm_info();
    SRDI *srdi = new SRDI;
    //get uav state
    for(int i = 0; i < UAV_COUNT; i++) {
        srdi->state[i] = positive_uav[i].get_state();
    }
    for(int i = 0; i < UAV_COUNT; i++) {
        srdi->state[i + UAV_COUNT] = negative_uav[i].get_state();
    }

    //get reward
    for(int i = 0; i < UAV_COUNT * 2; i++) {
        srdi->reward[i] = 0;
    }
    for(int i = 0; i < UAV_COUNT; i ++) {
        if(!positive_uav[i].penalty && positive_uav[i].is_die()) {
            if(!positive_uav[i].attacked_flag) {
                //uav died for some foolish condition
                srdi->reward[i] = -250;
            }
            positive_uav[i].penalty = true;
        }
        if(!negative_uav[i].penalty && negative_uav[i].is_die()) {
            if(!negative_uav[i].attacked_flag) {
                //uav died for some foolish condition
                srdi->reward[i + UAV_COUNT] = -250;
            }
            negative_uav[i].penalty = true;
        }
    }
    for(int i = 0; i < UAV_COUNT; i ++) {
        if(!positive_uav[i].is_die()) {
            for(int j = 0; j < OBJECT_COUNT; j++) {
                if(world->object[j].detect(positive_uav[i].get_pos())) {
                    //uav found object
                    srdi->reward[i] = 1000;
                }
            }
        }
        if(!negative_uav[i].is_die()) {
            for(int j = 0; j < OBJECT_COUNT; j++) {
                if(world->object[j].detect(positive_uav[i].get_pos())) {
                    //uav found object
                    srdi->reward[i + UAV_COUNT] = 1000;
                }
            }
        }
    }
    for(int i = 0; i < UAV_COUNT; i ++) {
        if(srdi->reward[i] == 0 && !positive_uav[i].is_die()) {
            srdi->reward[i] = -1;
        }
        if(srdi->reward[i + UAV_COUNT] == 0 && !negative_uav[i].is_die()) {
            srdi->reward[i + UAV_COUNT] = -1;
        }
    }
    //add attack reward
    for(int i = 0; i < UAV_COUNT; i++) {
        srdi->reward[i] += positive_attack_reward[i];
        srdi->reward[i + UAV_COUNT] += negative_attack_reward[i];
    }

    //check done
    srdi->done = false;
    srdi->info = "OK";

    if(step_cnt == MAX_STEP_CNT) {
        srdi->done = true;
        srdi->info = "TLE";
    }
    bool all_die = true;
    for(int i = 0; i < UAV_COUNT; i++) {
        if(!positive_uav[i].is_die() || !negative_uav[i].is_die()) {
            all_die = false;
        }
    }
    if(all_die) {
        srdi->done = true;
        srdi->info = "DIE";
    }
    if(world->object[0].is_detected() && world->object[1].is_detected()) {
        srdi->done = true;
        srdi->info = "FINISH";
    }

    print();

    return srdi;    //TODO: need to free manually
}

void Env::process_attack(Uav &a, Uav &b) {
    int apc = a.power_count(), bpc = b.power_count();
    if(apc > bpc) {
        a.attacked_flag = true;
    }
    else if(apc < bpc) {
        b.attacked_flag = true;
    }
}

bool Env::same_direction(Uav &u1, Action a1, Uav &u2, Action a2) {
    return u1.get_pos() == rollback_action(u2, a2) && u2.get_pos() == rollback_action(u1, a1);
}

Pos Env::rollback_action(Uav &u, Action a) {
    Pos pos = u.get_pos();
    bool side = u.get_side();
    if (a == UP) {
        side ? pos.col-- : pos.col++;
    }else if (a == DOWN) {
        side ? pos.col++ : pos.col--;
    }
    else if (a == LEFT) {
        side ? pos.row++ : pos.row--;
    }
    else if (a == RIGHT) {
        side ? pos.row-- : pos.row++;
    }
    return pos;
}

void Env::print() {
    world->print();
}
