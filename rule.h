#ifndef RULE_H_
#define RULE_H_

#include <list>
#include <utility>

#include "global.h"
#include "state.h"


class Rule
{
public:
    Rule(int noX, int noY);
    ~Rule();

    typedef std::list<point, SingletonPool<point>> point_list;

    point_list get_all_move(const state_ptr& state) const;
    point get_random_move(const state_ptr& state) const;

private:
    int no_x, no_y;
};

#endif // RULE_H_
