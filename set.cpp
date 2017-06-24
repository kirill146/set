//
// Created by drxu on 24.06.2017.
//

#include "set.h"

template <typename T>
set<T>::iterator::iterator(set::node_base* p)
    :p(p)
{}

template <typename T>
typename set<T>::iterator& set<T>::iterator::operator++() {
    if (static_cast<node*>(p)->right != nullptr) {
        p = static_cast<node*>(p)->right;
        while (p->left != nullptr) {
            p = p->left;
        }
    } else {
        while (static_cast<node*>(p)->parent->left != static_cast<node*>(p)) {
            p = static_cast<node*>(p)->parent;
        }
        p = static_cast<node*>(p)->parent;
    }
    return *this;
}

template <typename T>
typename set<T>::iterator& set<T>::iterator::operator--() {
    if (p->left != nullptr) {
        p = p->left;
        while (static_cast<node*>(p)->right != nullptr) {
            p = static_cast<node*>(p)->right;
        }
    } else {
        while (static_cast<node*>(static_cast<node*>(p)->parent)->right != static_cast<node*>(p)) {
            p = static_cast<node*>(p)->parent;
        }
        p = static_cast<node*>(p)->parent;
    }
    return *this;
}

template <typename T>
typename set<T>::iterator set<T>::iterator::operator++(int) {
    iterator res(*this);
    ++*this;
    return res;
}

template <typename T>
typename set<T>::iterator set<T>::iterator::operator--(int) {
    iterator res(*this);
    --*this;
    return res;
}

template <typename T>
T const& set<T>::iterator::operator*() const {
    return static_cast<node*>(p)->data;
}

/*
template <typename U>
bool operator==(set<U>::iterator const& a, set<U>::iterator const& b) {
    return a.p == b.p;
}*/

template <typename T>
typename set<T>::iterator set<T>::insert(T const& new_node) {
    node_base* cur_node = fake_node->left;
    if (cur_node == nullptr) {
        cur_node = new node(new_node, fake_node);
        fake_node->left = cur_node;
        return iterator(cur_node);
    }
    while (true) {
        if (static_cast<node*>(cur_node)->data == new_node) {
            return iterator(cur_node);
        }
        if (new_node < static_cast<node*>(cur_node)->data) {
            if (!cur_node->left) {
                cur_node->left = new node(new_node, cur_node);
                return iterator(cur_node->left);
            } else {
                cur_node = cur_node->left;
            }
        } else {
            if (!static_cast<node*>(cur_node)->right) {
                static_cast<node*>(cur_node)->right = new node(new_node, cur_node);
                return iterator(static_cast<node*>(cur_node)->right);
            } else {
                cur_node = static_cast<node*>(cur_node)->right;
            }
        }
    }
}

#include <iostream>
template <typename T>
void set<T>::print(node_base* cur_node) {
    if (!cur_node) {
        return;
    }
    if (cur_node->left) {
        print(cur_node->left);
    }
    std::cout << static_cast<node*>(cur_node)->data << ' ';
    if (static_cast<node*>(cur_node)->right) {
        print(static_cast<node*>(cur_node)->right);
    }
}

template <typename T>
typename set<T>::const_iterator set<T>::begin() const {
    node_base* cur_node = fake_node;
    while (cur_node->left) {
        cur_node = cur_node->left;
    }
    return const_iterator(cur_node);
}

template <typename T>
typename set<T>::const_iterator set<T>::end() const {
    return const_iterator(fake_node);
}

template <typename T>
typename set<T>::iterator set<T>::erase(set<T>::iterator it) {
    iterator res = it;
    res++;
    node_base* cur_node = it.p;
    node_base* p = static_cast<node*>(cur_node)->parent;
    if (!cur_node->left && !static_cast<node*>(cur_node)->right) {
        if (p->left == cur_node) {
            p->left = nullptr;
        } else {
            static_cast<node*>(p)->right = nullptr;
        }
    } else if (!cur_node->left || !static_cast<node*>(cur_node)->right) {
        if (!cur_node->left) {
            if (p->left == cur_node) {
                p->left = static_cast<node*>(cur_node)->right;
            } else {
                static_cast<node*>(p)->right = static_cast<node*>(cur_node)->right;
            }
            static_cast<node*>(static_cast<node*>(cur_node)->right)->parent = p;
        } else {
            if (p->left == cur_node) {
                p->left = cur_node->left;
            } else {
                static_cast<node*>(p)->right = cur_node->left;
            }
            static_cast<node*>(cur_node->left)->parent = p;
        }
    } else {
        if (!static_cast<node*>(cur_node)->right->left) {
            if (p->left == cur_node) {
                p->left = static_cast<node*>(cur_node)->right;
            } else {
                static_cast<node*>(p)->right = static_cast<node*>(cur_node)->right;
            }
            static_cast<node*>(static_cast<node*>(cur_node)->right)->parent = p;
        } else {
            node_base* next_node = res.p;
            static_cast<node*>(next_node)->parent = p;
            next_node->left = cur_node->left;
            static_cast<node*>(next_node)->right = static_cast<node*>(cur_node)->right;
        }
    }
    delete cur_node;
    return res;
}

template <typename T>
typename set<T>::const_iterator set<T>::find(const T& val) {
    iterator lb = lower_bound(val);
    if (lb == end() || static_cast<node*>(lb.p)->data == val) {
        return lb;
    }
    return end();
}

template <typename T>
typename set<T>::const_iterator set<T>::lower_bound(const T &val) const {
    node_base* cur_node = fake_node->left;
    if (cur_node == nullptr) {
        return iterator(fake_node);
    }
    while (true) {
        if (static_cast<node*>(cur_node)->data == val) {
            return iterator(cur_node);
        }
        if (val < static_cast<node*>(cur_node)->data) {
            if (!cur_node->left) {
                return iterator(cur_node);
            } else {
                cur_node = cur_node->left;
            }
        } else {
            if (!static_cast<node*>(cur_node)->right) {
                return ++iterator(cur_node);
            } else {
                cur_node = static_cast<node*>(cur_node)->right;
            }
        }
    }
}

template <typename T>
typename set<T>::const_iterator set<T>::upper_bound(const T &val) const {
    iterator lb = lower_bound(val);
    if (lb == end() || static_cast<node*>(lb.p)->data != val) {
        return lb;
    }
    return ++lb;
}

template <typename T>
void set<T>::swap(set<T>& other) {
    std::swap(fake_node, other.fake_node);
}

template <typename T>
void set<T>::clear(set<T>::node_base* cur_node) {
    if (cur_node->left) {
        clear(cur_node->left);
    }
    if (static_cast<node*>(cur_node)->right) {
        clear(static_cast<node*>(cur_node)->right);
    }
    delete cur_node;
}

template <typename T>
void set<T>::clear() {
    if (fake_node->left) {
        clear(fake_node->left);
    }
    fake_node->left = nullptr;
}

template <typename T>
set<T>::~set() {
    clear();
}

template <typename T>
set<T>::set(set<T> const& other) {
    if (other.fake_node->left) {
        fake_node->left = new node();
        deep_copy(fake_node->left, other.fake_node->left, fake_node);
    }
}

template <typename T>
void set<T>::deep_copy(set<T>::node_base* dst, set<T>::node_base* src, set<T>::node_base* parent) {
    static_cast<node*>(dst)->data = static_cast<node*>(src)->data;
    static_cast<node*>(dst)->parent = parent;
    if (src->left) {
        dst->left = new node();
        deep_copy(dst->left, src->left, dst);
    }
    if (static_cast<node*>(src)->right) {
        static_cast<node*>(dst)->right = new node();
        deep_copy(static_cast<node*>(dst)->right, static_cast<node*>(src)->right, dst);
    }
}

template <typename T>
set<T>::set() {

}

template <typename T>
set<T>& set<T>::operator=(set<T> const& other) {
    set<T> copy(other);
    swap(copy);
    return *this;
}

template <typename T>
bool set<T>::empty() const {
    return !fake_node->left;
}

template <typename T>
typename set<T>::const_reverse_iterator set<T>::rbegin() const {
    return reverse_iterator(end());
}

template <typename T>
typename set<T>::const_reverse_iterator set<T>::rend() const {
    return reverse_iterator(begin());
}