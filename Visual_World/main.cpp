#include "type.h"
#include "object.h"
#include "uav.h"
#include "world.h"
#include "env.h"
#include <iostream>
#include <QApplication>
using std::cout;
using std::endl;

void test_Pos_info() {

    Pos_info x;
    Pos content_x(1, 2);
    Pos content_y(3, 4);
    x.positive_pos.insert(content_x);
    Pos_info y = x;
    y.positive_pos.insert(content_y);
    cout << x.positive_pos.size() << endl;

    x.positive_pos.insert(content_x);//error if < assert 0 at end
    cout << x.positive_pos.size() << endl;

    Pos content_z(1, 2);
    set<Pos>::iterator it=x.positive_pos.find(content_z);
    if (it != x.positive_pos.end())
        cout << "found" << endl;
    else
    {
        cout << "not found" << endl;
    }

}
void test_Pos_info_plus() {
    /*Pos_info z;
    if (true) {
        Pos_info x, y;
        Pos content_x(1, 2);
        Pos content_y(3, 4);
        x.positive_pos.insert(content_x);
        y.positive_pos.insert(content_y);
        cout << "========x===========" << endl;
        cout << x.positive_pos.size() << endl;
        //x += y;//error when no overload for ?(=?)
        cout << x.positive_pos.size() << endl;
        cout << "========z===========" << endl;
        cout << z.positive_pos.size() << endl;
        z = x + y;
    }
    cout << z.positive_pos.size() << endl;*/
}
/*
void print_pos(Pos pos) {
    cout << "(" << pos.row << ", " << pos.col << ") ";
}

void print_pos_info(Pos_info pos_info) {
    set<Pos>::iterator it;
    cout << "positive_pos: ";
    it = pos_info.positive_pos.begin();
    while(it != pos_info.positive_pos.end()) {
        print_pos(*it);
        it++;
    }
    cout << '\n';

    cout << "negative_pos: ";
    it = pos_info.negative_pos.begin();
    while(it != pos_info.negative_pos.end()) {
        print_pos(*it);
        it++;
    }
    cout << '\n';

    cout << "object_pos: ";
    it = pos_info.object_pos.begin();
    while(it != pos_info.object_pos.end()) {
        print_pos(*it);
        it++;
    }
    cout << '\n';
}

void print_state(State s) {
    cout << "self_side: " << s.self_side << '\n';
    cout << "self_die: " << s.self_die << '\n';
    cout << "self_pos: ";
    print_pos(s.self_pos), cout << '\n';

    set<Pos>::iterator it;
    print_pos_info(s.comm_info);

    cout << "obstacle_pos: ";
    it = s.obstacle_pos.begin();
    while(it != s.obstacle_pos.end()) {
        print_pos(*it);
        it++;
    }
    cout << '\n';
}
*/
void test_Env_Object_contruction() {
    Env env;
    State *s = env.reset();
//    Action action[UAV_COUNT * 2] = { UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP};
//    //Action action[UAV_COUNT * 2] = { DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN};
//    for(int i = 0; i < 2; i++) {
//        SRDI *srdi = env.step(action);
//        //env.print(); cout << '\n';
//        srdi->print();
//    }
    /*for(int i = 0; i < UAV_COUNT * 2; i++) {
        s[i].print();
    }*/
}


int main(int argc, char *argv[])
{
//    test_Pos_info();//insert and search ok
//    test_Pos_info_plus();//o98k
//    test_Env_Object_contruction();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
