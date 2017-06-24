//
// Created by drxu on 24.06.2017.
//

#ifndef SET_SET_H
#define SET_SET_H

#include <iterator>

template <typename T>
struct set {
private:
    struct node_base {
        node_base *left = nullptr;
    };

    struct node : node_base {
        node_base *right = nullptr, *parent = nullptr;
        T data;
        node() {}
        node(T const& val, node_base* parent) {
            data = val;
            this->parent = parent;
        }
        ~node() {
            data.~T();
        }
    };

    void clear(node_base* cur_node);
    void deep_copy(node_base* dst, node_base* src, node_base* parent);

public:
    struct iterator {
        friend set;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T const* pointer;
        typedef T const& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        node_base* p;
        iterator(node_base*);
    public:
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        T const& operator*() const;

        friend bool operator==(set<T>::iterator const& a, set<T>::iterator const& b) {
            return a.p == b.p;
        }

        friend bool operator!=(set<T>::iterator const& a, set<T>::iterator const& b) {
            return a.p != b.p;
        }
    };
    typedef iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    node_base* fake_node = new node_base;

    set();
    set(set const&);
    ~set();
    set& operator=(set const&);
    bool empty() const;
    void clear();
    iterator insert(T const& new_node);
    iterator erase(iterator it);
    const_iterator find(T const& val) const;
    const_iterator lower_bound(T const& val) const;
    const_iterator upper_bound(T const& val) const;
    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    void swap(set& other);
};
#endif //SET_SET_H
