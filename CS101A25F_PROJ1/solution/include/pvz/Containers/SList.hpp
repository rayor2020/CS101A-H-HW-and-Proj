#pragma once
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

namespace pvz {

// 单向链表，满足范围 for、std::any_of、remove_if 等基本需求
template <class T>
class SList {
  struct Node {
    T value;
    Node* next;
    Node() : value(), next(nullptr) {} // 允许默认构造（便于算法写法）
    template <class... Args>
    explicit Node(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr) {}
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;

 public:
  SList() = default;
  ~SList() { clear(); }

  SList(const SList&) = delete;
  SList& operator=(const SList&) = delete;

  SList(SList&& other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  SList& operator=(SList&& other) noexcept {
    if (this != &other) {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;
      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // 在尾部原地构造（适合 unique_ptr）
  template <class... Args>
  T& emplace_back(Args&&... args) {
    Node* n = new Node(std::forward<Args>(args)...);
    if (tail_) tail_->next = n; else head_ = n;
    tail_ = n;
    ++size_;
    return tail_->value;
  }

  // push_back 支持拷贝/移动（对 unique_ptr 要用右值或 emplace_back）
  void push_back(const T& v) { emplace_back(v); }
  void push_back(T&& v) { emplace_back(std::move(v)); }

  template <class Pred>
  void remove_if(Pred pred) {
    Node* prev = nullptr;
    Node* cur = head_;
    while (cur) {
      if (pred(cur->value)) {
        Node* del = cur;
        cur = cur->next;
        if (prev) prev->next = cur; else head_ = cur;
        if (del == tail_) tail_ = prev;
        delete del;
        --size_;
      } else {
        prev = cur;
        cur = cur->next;
      }
    }
  }

  void clear() {
    Node* cur = head_;
    while (cur) {
      Node* nxt = cur->next;
      delete cur;
      cur = nxt;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }

  std::size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  // 前向迭代器（支持 range-for / <algorithm>）
  template <class U, bool IsConst>
  class BasicIterator {
    using NodePtr = std::conditional_t<IsConst, const Node*, Node*>;
    NodePtr node_ = nullptr;
    friend class SList;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = U;
    using difference_type = std::ptrdiff_t;
    using pointer   = std::conditional_t<IsConst, const U*, U*>;
    using reference = std::conditional_t<IsConst, const U&, U&>;

    BasicIterator() = default;
    explicit BasicIterator(NodePtr p) : node_(p) {}

    reference operator*()  const { return node_->value; }
    pointer   operator->() const { return std::addressof(node_->value); }

    BasicIterator& operator++() { node_ = node_->next; return *this; }
    BasicIterator operator++(int) { BasicIterator tmp(*this); ++(*this); return tmp; }

    bool operator==(const BasicIterator& o) const { return node_ == o.node_; }
    bool operator!=(const BasicIterator& o) const { return node_ != o.node_; }
  };

  using iterator = BasicIterator<T, false>;
  using const_iterator = BasicIterator<T, true>;

  iterator begin() { return iterator(head_); }
  iterator end()   { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(head_); }
  const_iterator end()   const { return const_iterator(nullptr); }
  const_iterator cbegin() const { return const_iterator(head_); }
  const_iterator cend()   const { return const_iterator(nullptr); }
};

} // namespace pvz
