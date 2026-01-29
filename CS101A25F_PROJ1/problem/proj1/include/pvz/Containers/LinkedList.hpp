#pragma once
#include <memory>
#include <iterator>
#include <algorithm>
#include <functional>

namespace pvz
{

    /// @brief 双向链表节点
    template <typename T>
    struct Node
    {
        T data;
        std::shared_ptr<Node<T>> prev;
        std::shared_ptr<Node<T>> next;

        Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
    };

    /// @brief 双向链表迭代器
    template <typename T>
    class LinkedListIterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using difference_type = std::ptrdiff_t;

        LinkedListIterator() : m_node(nullptr) {}
        explicit LinkedListIterator(std::shared_ptr<Node<T>> node) : m_node(node) {}

        reference operator*() { return m_node->data; }
        pointer operator->() { return &(m_node->data); }

        LinkedListIterator &operator++()
        {
            if (m_node)
            {
                m_node = m_node->next;
            }
            return *this;
        }

        LinkedListIterator operator++(int)
        {
            LinkedListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        LinkedListIterator &operator--()
        {
            if (m_node)
            {
                m_node = m_node->prev;
            }
            return *this;
        }

        LinkedListIterator operator--(int)
        {
            LinkedListIterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const LinkedListIterator &other) const
        {
            return m_node == other.m_node;
        }

        bool operator!=(const LinkedListIterator &other) const
        {
            return m_node != other.m_node;
        }

    private:
        std::shared_ptr<Node<T>> m_node;
        template <typename U>
        friend class LinkedList;
    };

    /// @brief 双向链表容器（用于替代 std::list）
    template <typename T>
    class LinkedList
    {
    public:
        using iterator = LinkedListIterator<T>;
        using const_iterator = LinkedListIterator<T>;
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;

        LinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

        ~LinkedList()
        {
            clear();
        }

        // 复制构造函数
        LinkedList(const LinkedList &other) : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            for (const auto &item : other)
            {
                push_back(item);
            }
        }

        // 赋值运算符
        LinkedList &operator=(const LinkedList &other)
        {
            if (this != &other)
            {
                clear();
                for (const auto &item : other)
                {
                    push_back(item);
                }
            }
            return *this;
        }

        // 移动构造函数
        LinkedList(LinkedList &&other) noexcept
            : m_head(std::move(other.m_head)), m_tail(std::move(other.m_tail)), m_size(other.m_size)
        {
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        // 移动赋值运算符
        LinkedList &operator=(LinkedList &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                m_head = std::move(other.m_head);
                m_tail = std::move(other.m_tail);
                m_size = other.m_size;
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        // 在末尾添加元素
        void push_back(const T &value)
        {
            auto newNode = std::make_shared<Node<T>>(value);
            if (m_tail)
            {
                m_tail->next = newNode;
                newNode->prev = m_tail;
                m_tail = newNode;
            }
            else
            {
                m_head = m_tail = newNode;
            }
            m_size++;
        }

        // 在开头添加元素
        void push_front(const T &value)
        {
            auto newNode = std::make_shared<Node<T>>(value);
            if (m_head)
            {
                m_head->prev = newNode;
                newNode->next = m_head;
                m_head = newNode;
            }
            else
            {
                m_head = m_tail = newNode;
            }
            m_size++;
        }

        // 删除末尾元素
        void pop_back()
        {
            if (m_tail)
            {
                if (m_tail->prev)
                {
                    m_tail = m_tail->prev;
                    m_tail->next = nullptr;
                }
                else
                {
                    m_head = m_tail = nullptr;
                }
                m_size--;
            }
        }

        // 删除开头元素
        void pop_front()
        {
            if (m_head)
            {
                if (m_head->next)
                {
                    m_head = m_head->next;
                    m_head->prev = nullptr;
                }
                else
                {
                    m_head = m_tail = nullptr;
                }
                m_size--;
            }
        }

        // 删除指定位置的元素
        iterator erase(iterator it)
        {
            if (!it.m_node)
                return end();

            iterator result = iterator(it.m_node->next);

            if (it.m_node->prev)
            {
                it.m_node->prev->next = it.m_node->next;
            }
            else
            {
                m_head = it.m_node->next;
            }

            if (it.m_node->next)
            {
                it.m_node->next->prev = it.m_node->prev;
            }
            else
            {
                m_tail = it.m_node->prev;
            }

            m_size--;
            return result;
        }

        // 根据条件删除元素（支持 lambda）
        template <typename Predicate>
        void remove_if(Predicate pred)
        {
            auto it = begin();
            while (it != end())
            {
                if (pred(*it))
                {
                    it = erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        // 删除所有匹配的元素
        void remove(const T &value)
        {
            remove_if([&value](const T &item)
                      { return item == value; });
        }

        // 在指定位置插入元素
        iterator insert(iterator it, const T &value)
        {
            if (it == end())
            {
                push_back(value);
                return iterator(m_tail);
            }

            auto newNode = std::make_shared<Node<T>>(value);
            newNode->next = it.m_node;
            newNode->prev = it.m_node->prev;

            if (it.m_node->prev)
            {
                it.m_node->prev->next = newNode;
            }
            else
            {
                m_head = newNode;
            }
            it.m_node->prev = newNode;

            m_size++;
            return iterator(newNode);
        }

        // 获取开始迭代器
        iterator begin() { return iterator(m_head); }
        iterator end() { return iterator(nullptr); }

        const_iterator begin() const { return const_iterator(m_head); }
        const_iterator end() const { return const_iterator(nullptr); }

        const_iterator cbegin() const { return const_iterator(m_head); }
        const_iterator cend() const { return const_iterator(nullptr); }

        // 获取首尾元素
        reference front() { return m_head->data; }
        const_reference front() const { return m_head->data; }
        reference back() { return m_tail->data; }
        const_reference back() const { return m_tail->data; }

        // 检查是否为空
        bool empty() const { return m_size == 0; }

        // 获取大小
        size_type size() const { return m_size; }

        // 清空链表
        void clear()
        {
            while (!empty())
            {
                pop_front();
            }
        }

        // 查找元素
        iterator find(const T &value)
        {
            for (auto it = begin(); it != end(); ++it)
            {
                if (*it == value)
                {
                    return it;
                }
            }
            return end();
        }

        // 遍历并执行操作
        template <typename Func>
        void for_each(Func func)
        {
            for (auto &item : *this)
            {
                func(item);
            }
        }

    private:
        std::shared_ptr<Node<T>> m_head;
        std::shared_ptr<Node<T>> m_tail;
        size_t m_size;
    };

} // namespace pvz
