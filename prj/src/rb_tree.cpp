#include <iostream>
#include <string>

#include "rb_tree.hh"

//RBNODE
RBNode::RBNode() {
}

RBNode::RBNode(int _elem, RBNode *_top) {
  elem = _elem;
  top = _top;
  left = nullptr;
  right = nullptr;
}


//RB TREE
RBTree::RBTree() {
  guard.colour = 'B';
  guard.top = &guard;
  guard.left = &guard;
  guard.right = &guard;
  root = &guard;
}


void RBTree::clear(RBNode * _node) {
  if (_node != nullptr) {
    clear(_node -> left);
    clear(_node -> right);
    delete _node;
  }
}


void RBTree::clear() {
  RBNode *node = root;
  if (node != nullptr) {
    clear(node -> left);
    clear(node -> right);
    delete node;
  }
}


RBTree::~RBTree() {
  clear(root);
}

void RBTree::print_tree(RBNode *_node) {
  if (_node == &guard) return;
  print_tree(_node -> left);
  //std::cout << _node -> elem << " ";
  print_tree(_node -> right);
}

void RBTree::print_tree() {
  RBNode *node = root;

  if (node == &guard) return;
  print_tree(node -> left);
  //std::cout << node -> elem << " ";
  print_tree(node -> right);
}


void RBTree::rot_left(RBNode *_node) {
  RBNode *temp, *top;

  temp = _node -> right;
  if (temp != &guard) {
    top = _node -> top;
    _node -> right = temp->left;
    if (_node -> right != &guard) _node -> right -> top = _node;

    temp -> left = _node;
    temp -> top = top;
    _node -> top = temp;

    if (top != &guard) {
      if (top -> left == _node) top -> left = temp;
      else top -> right = temp;
    }
    else root = temp;
  }
}


void RBTree::rot_right(RBNode * _node) {
  RBNode *temp, *top;

  temp = _node -> left;
  if (temp != &guard) {
    top = _node -> top;
    _node -> left = temp -> right;
    if (_node -> left != &guard) _node -> left -> top = _node;

    temp -> right = _node;
    temp -> top = top;
    _node -> top = temp;

    if(top != &guard) {
      if(top -> left == _node) top -> left = temp;
      else top -> right = temp;
    }
    else root = temp;
  }
}


void RBTree::add_elem(int _elem) {
  RBNode *temp1, *temp2;
  temp1 = new RBNode(_elem, root);
  temp1 -> left = &guard;
  temp1 -> right = &guard;

  if (temp1 -> top == &guard) root = temp1;
  else
    while (true) {
      if (_elem < temp1 -> top -> elem) {
	if (temp1 -> top -> left == &guard) {
	  temp1 -> top -> left = temp1;
	  break;
	}
	temp1 -> top = temp1 -> top -> left;
      }
      else {
	if (temp1 -> top -> right == &guard) {
	  temp1 -> top -> right = temp1;
	  break;
	}
	temp1 -> top = temp1 -> top -> right;
      }
    }
  temp1 -> colour = 'R';
  while ((temp1 != root) && (temp1 -> top -> colour == 'R')) {
    if (temp1 -> top == temp1 -> top -> top -> left) {
      temp2 = temp1 -> top -> top -> right;
      if (temp2 -> colour == 'R') {
        temp1 -> top -> colour = 'B';
        temp2 -> colour = 'B';
        temp1 -> top -> top -> colour = 'R';
        temp1 = temp1 -> top -> top;
        continue;
      }
      if (temp1 == temp1 -> top -> right) {
        temp1 = temp1 -> top;
        rot_left(temp1);
      }
      temp1 -> top -> colour = 'B';
      temp1 -> top -> top -> colour = 'R';
      rot_right(temp1 -> top -> top);
      break;
    }
    else {
      temp2 = temp1 -> top -> top -> left;
      if (temp2 -> colour == 'R') {
        temp1 -> top -> colour = 'B';
        temp2 -> colour = 'B';
        temp1 -> top -> top -> colour = 'R';
        temp1 = temp1 -> top -> top;
        continue;
      }
      if (temp1 == temp1 -> top -> left) {
        temp1 = temp1 -> top;
        rot_right(temp1);
      }
      temp1 -> top -> colour = 'B';
      temp1 -> top -> top -> colour = 'R';
      rot_left(temp1 -> top -> top);
      break;
    }
  }
  root -> colour = 'B';
}
