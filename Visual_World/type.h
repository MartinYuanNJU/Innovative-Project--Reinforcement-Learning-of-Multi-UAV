#ifndef __TYPE_H__
#define __TYPE_H__

#include "macro.h"
#include <string>
#include <set>
#include <iostream>

using std::set;
using std::string;
using std::cout;

struct Pos {
    int row;
    int col;

    Pos() { row = -1; col = -1; }

    Pos(int row, int col) {
        this->row = row;
        this->col = col;
    }

    bool operator <(const Pos &pos) const {
        if (pos.row != row) { return row < pos.row; }
        else if (pos.col != col) { return col < pos.col; }
        else return false;// assert(0);
    }

    bool operator ==(const Pos& pos) const {
        return (row == pos.row && col == pos.col);
    }

    void print() const {
        cout << "(" << row << ", " << col << ") ";
    }
};

struct Pos_info {
    set<Pos> positive_pos;
    set<Pos> negative_pos;
    set<Pos> object_pos;
    void clear() {
        positive_pos.clear();
        negative_pos.clear();
        object_pos.clear();
    }
    Pos_info operator +(const Pos_info& right) const { //TODO:: need to redesign
        Pos_info res = *this;
        set<Pos>::iterator it;
        it = right.positive_pos.begin();
        while (it != right.positive_pos.end()) {
            res.positive_pos.insert({*it});
            it++;
        }
        it = right.negative_pos.begin();
        while (it != right.negative_pos.end()) {
            res.negative_pos.insert(*it);
            it++;
        }
        it = right.object_pos.begin();
        while (it != right.object_pos.end()) {
            res.object_pos.insert(*it);
            it++;
        }
        return res;
    }

    void add(const Pos_info& right) {
        set<Pos>::iterator it;
        it= right.positive_pos.begin();
        while (it != right.positive_pos.end()) {
            this->positive_pos.insert(*it);
            it++;
        }
        it = right.negative_pos.begin();
        while (it != right.negative_pos.end()) {
            this->negative_pos.insert(*it);
            it++;
        }
        it = right.object_pos.begin();
        while (it != right.object_pos.end()) {
            this->object_pos.insert(*it);
            it++;
        }
    }

    void print() const {
        set<Pos>::iterator it;
        cout << "positive_pos: ";
        it = positive_pos.begin();
        while (it != positive_pos.end()) {
            it->print();
            it++;
        }
        cout << '\n';

        cout << "negative_pos: ";
        it = negative_pos.begin();
        while (it != negative_pos.end()) {
            it->print();
            it++;
        }
        cout << '\n';

        cout << "object_pos: ";
        it = object_pos.begin();
        while (it != object_pos.end()) {
            it->print();
            it++;
        }
        cout << '\n';
    }

};

struct State {
    bool self_side;
    bool self_die;
    Pos self_pos;
    Pos_info comm_info;
    static set<Pos> obstacle_pos;

    State(){}
    State(bool self_side, bool self_die, Pos self_pos, Pos_info comm_info) {
        //TODO: the obstacle_pos is supposed to be initialed at the very beginning, ok: in World's construction function
        this->self_side = self_side;
        this->self_die = self_die;
        this->self_pos = self_pos;
        this->comm_info = comm_info;//todo:test whether point to the same place
    }

    void print() const {
        cout << "self_side: " << self_side << '\n';
        cout << "self_die: " << self_die << '\n';
        cout << "self_pos: ";
        self_pos.print(), cout << '\n';

        comm_info.print();

//        cout << "obstacle_pos: ";
//        set<Pos>::iterator it;
//        it = obstacle_pos.begin();
//        while (it != obstacle_pos.end()) {
//            it->print();
//            it++;
//        }
//        cout << '\n';
    }
};

enum Action { UP, DOWN, LEFT, RIGHT };

struct SRDI {
    State state[UAV_COUNT * 2];
    int reward[UAV_COUNT * 2];
    bool done;
    string info;

    void print() const {
        cout << "state: \n";
        for(int i = 0; i < UAV_COUNT * 2; i ++) {
            state[i].print();
        }
        cout << "reward: ";
        for(int i = 0; i < UAV_COUNT * 2; i ++) {
            cout << reward[i] << " ";
        }
        cout << '\n';
        cout << "done: " << done << '\n';
        cout << "info: " << info << '\n';
    }
};

#endif
