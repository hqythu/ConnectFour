#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <random>
#include <memory>
#include <utility>

class TreeNode;
class MCTreeSearch;
class State;
class Rule;

typedef std::shared_ptr<TreeNode> node_ptr;
typedef std::shared_ptr<State> state_ptr;
typedef std::shared_ptr<Rule> rule_ptr;

typedef std::pair<int, int> point;


class Global
{
public:
    static const int ME;
    static const int OPPONENT;

    static std::default_random_engine generator;
};


#endif // GLOBAL_H_
