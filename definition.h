#ifndef DEFINITION_H_
#define DEFINITION_H_

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


#endif // DEFINITION_H_
