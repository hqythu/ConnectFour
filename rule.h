#ifndef RULE_H_
#define RULE_H_

#include <list>
#include <utility>

#include "definition.h"
#include "state.h"
#include "singleton_pool.h"


class Rule
{
public:
    Rule(int noX, int noY);
    ~Rule();

    typedef std::list<point, SingletonPool<point>> point_list;

    point_list get_all_move(const state_ptr& state) const;
    point get_random_move(const state_ptr& state) const;

    bool is_me_win(const state_ptr& state, int x, int y) const;
    bool is_opponent_win(const state_ptr& state, int x, int y) const;
    bool is_tie(const state_ptr& state) const;

private:
    int no_x, no_y;
};

#endif // RULE_H_
