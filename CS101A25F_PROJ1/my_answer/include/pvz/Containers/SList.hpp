#pragma once
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

namespace pvz {

/**
 * @brief 双向链表容器模板类
 *
 * SList是一个双向链表实现，支持在头部、尾部以及任意位置插入和删除元素。
 * 提供了随机访问迭代器，可以正向和反向遍历链表元素。
 *
 * @tparam T 存储在链表中的元素类型
 */
template <class T>
class SList {
private:
    /**
     * @brief 链表节点结构体
     *
     * 表示链表中的单个节点，包含实际数据以及指向前一个和后一个节点的指针
     */
    struct Node {
        T data; // 节点存储的数据
        Node* next; // 指向下一个节点的指针
        Node* prev; // 指向前一个节点的指针

        /**
         * @brief 构造函数，使用给定值初始化节点
         * @param value 用于初始化节点数据的值
         */
        Node(const T& value)
            : data(value)
            , next(nullptr)
            , prev(nullptr)
        {
        }

        /**
         * @brief 移动构造函数，使用给定值初始化节点
         * @param value 用于初始化节点数据的右值引用
         */
        Node(T&& value)
            : data(std::move(value))
            , next(nullptr)
            , prev(nullptr)
        {
        }
    };

public:
    /**
     * @brief 双向链表迭代器类
     *
     * 支持双向遍历链表的迭代器，实现了标准迭代器接口
     */
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator()
            : m_ptr(nullptr)
        {
        }

        /**
         * @brief 使用节点指针构造迭代器
         * @param ptr 指向节点的指针
         */
        iterator(Node* ptr)
            : m_ptr(ptr)
        {
        }

        /**
         * @brief 拷贝构造函数
         * @param other 要拷贝的迭代器
         */
        iterator(const iterator& other)
            : m_ptr(other.m_ptr)
        {
        }

        /**
         * @brief 前置递增运算符，将迭代器移动到下一个节点
         * @return 当前迭代器的引用
         */
        iterator& operator++()
        {
            m_ptr = m_ptr->next;
            return *this;
        }

        /**
         * @brief 后置递增运算符，返回递增前的迭代器副本
         * @return 递增前的迭代器副本
         */
        iterator operator++(int)
        {
            iterator temp = *this;
            m_ptr = m_ptr->next;
            return temp;
        }

        /**
         * @brief 前置递减运算符，将迭代器移动到前一个节点
         * @return 当前迭代器的引用
         */
        iterator& operator--()
        {
            m_ptr = m_ptr->prev;
            return *this;
        }

        /**
         * @brief 后置递减运算符，返回递减前的迭代器副本
         * @return 递减前的迭代器副本
         */
        iterator operator--(int)
        {
            iterator temp = *this;
            m_ptr = m_ptr->prev;
            return temp;
        }

        /**
         * @brief 解引用运算符，获取当前节点的数据引用
         * @return 当前节点数据的引用
         */
        reference operator*() const
        {
            return m_ptr->data;
        }

        /**
         * @brief 成员访问运算符，获取指向当前节点数据的指针
         * @return 指向当前节点数据的指针
         */
        pointer operator->() const
        {
            return &(m_ptr->data);
        }

        /**
         * @brief 相等比较运算符
         * @param other 要比较的另一个迭代器
         * @return 如果两个迭代器指向同一节点则返回true，否则返回false
         */
        bool operator==(const iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        /**
         * @brief 不等比较运算符
         * @param other 要比较的另一个迭代器
         * @return 如果两个迭代器指向不同节点则返回true，否则返回false
         */
        bool operator!=(const iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }

    private:
        Node* m_ptr; // 指向当前节点的指针
        friend class SList;
    };

    /**
     * @brief 双向链表常量迭代器类
     *
     * 支持双向遍历链表的常量迭代器，保证不会修改链表元素
     */
    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator()
            : m_ptr(nullptr)
        {
        }

        /**
         * @brief 使用节点指针构造常量迭代器
         * @param ptr 指向节点的指针
         */
        const_iterator(Node* ptr)
            : m_ptr(ptr)
        {
        }

        /**
         * @brief 从非常量迭代器构造常量迭代器
         * @param other 要转换的非常量迭代器
         */
        const_iterator(const iterator& other)
            : m_ptr(other.m_ptr)
        {
        }

        /**
         * @brief 拷贝构造函数
         * @param other 要拷贝的常量迭代器
         */
        const_iterator(const const_iterator& other)
            : m_ptr(other.m_ptr)
        {
        }

        /**
         * @brief 前置递增运算符，将迭代器移动到下一个节点
         * @return 当前迭代器的引用
         */
        const_iterator& operator++()
        {
            m_ptr = m_ptr->next;
            return *this;
        }

        /**
         * @brief 后置递增运算符，返回递增前的迭代器副本
         * @return 递增前的迭代器副本
         */
        const_iterator operator++(int)
        {
            const_iterator temp = *this;
            m_ptr = m_ptr->next;
            return temp;
        }

        /**
         * @brief 前置递减运算符，将迭代器移动到前一个节点
         * @return 当前迭代器的引用
         */
        const_iterator& operator--()
        {
            m_ptr = m_ptr->prev;
            return *this;
        }

        /**
         * @brief 后置递减运算符，返回递减前的迭代器副本
         * @return 递减前的迭代器副本
         */
        const_iterator operator--(int)
        {
            const_iterator temp = *this;
            m_ptr = m_ptr->prev;
            return temp;
        }

        /**
         * @brief 解引用运算符，获取当前节点的数据常量引用
         * @return 当前节点数据的常量引用
         */
        reference operator*() const
        {
            return m_ptr->data;
        }

        /**
         * @brief 成员访问运算符，获取指向当前节点数据的常量指针
         * @return 指向当前节点数据的常量指针
         */
        pointer operator->() const
        {
            return &(m_ptr->data);
        }

        /**
         * @brief 相等比较运算符
         * @param other 要比较的另一个常量迭代器
         * @return 如果两个迭代器指向同一节点则返回true，否则返回false
         */
        bool operator==(const const_iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        /**
         * @brief 不等比较运算符
         * @param other 要比较的另一个常量迭代器
         * @return 如果两个迭代器指向不同节点则返回true，否则返回false
         */
        bool operator!=(const const_iterator& other) const
        {
            return m_ptr != other.m_ptr;
        }

    private:
        Node* m_ptr; // 指向当前节点的指针
        friend class SList;
    };

    /**
     * @brief 默认构造函数，创建一个空链表
     */
    SList()
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0)
    {
    }

    /**
     * @brief 拷贝构造函数，从另一个链表创建新链表
     * @param other 要拷贝的链表
     */
    SList(const SList& other)
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0)
    {
        for (const auto& item : other) {
            push_back(item);
        }
    }

    /**
     * @brief 移动构造函数，通过移动另一个链表的内容来创建新链表
     * @param other 要移动的链表
     */
    SList(SList&& other) noexcept
        : m_head(other.m_head)
        , m_tail(other.m_tail)
        , m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    /**
     * @brief 析构函数，释放链表占用的所有资源
     */
    ~SList()
    {
        clear();
    }

    /**
     * @brief 拷贝赋值运算符，将另一个链表的内容拷贝到当前链表
     * @param other 要拷贝的链表
     * @return 当前链表的引用
     */
    SList& operator=(const SList& other)
    {
        if (this != &other) {
            clear();
            for (const auto& item : other) {
                push_back(item);
            }
        }
        return *this;
    }

    /**
     * @brief 移动赋值运算符，将另一个链表的内容移动到当前链表
     * @param other 要移动的链表
     * @return 当前链表的引用
     */
    SList& operator=(SList&& other) noexcept
    {
        if (this != &other) {
            clear();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    /**
     * @brief 返回指向链表第一个元素的迭代器
     * @return 指向链表第一个元素的迭代器
     */
    iterator begin()
    {
        return iterator(m_head);
    }

    /**
     * @brief 返回指向链表第一个元素的常量迭代器
     * @return 指向链表第一个元素的常量迭代器
     */
    const_iterator begin() const
    {
        return const_iterator(m_head);
    }

    /**
     * @brief 返回指向链表末尾后位置的迭代器
     * @return 指向链表末尾后位置的迭代器
     */
    iterator end()
    {
        return iterator(nullptr);
    }

    /**
     * @brief 返回指向链表末尾后位置的常量迭代器
     * @return 指向链表末尾后位置的常量迭代器
     */
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }

    /**
     * @brief 返回指向链表第一个元素的常量迭代器
     * @return 指向链表第一个元素的常量迭代器
     */
    const_iterator cbegin() const
    {
        return const_iterator(m_head);
    }

    /**
     * @brief 返回指向链表末尾后位置的常量迭代器
     * @return 指向链表末尾后位置的常量迭代器
     */
    const_iterator cend() const
    {
        return const_iterator(nullptr);
    }

    /**
     * @brief 检查链表是否为空
     * @return 如果链表为空则返回true，否则返回false
     */
    bool empty() const
    {
        return m_size == 0;
    }

    /**
     * @brief 返回链表中元素的数量
     * @return 链表中元素的数量
     */
    size_t size() const
    {
        return m_size;
    }

    /**
     * @brief 访问链表的第一个元素
     * @return 链表第一个元素的引用
     */
    T& front()
    {
        return m_head->data;
    }

    /**
     * @brief 访问链表的第一个元素（常量版本）
     * @return 链表第一个元素的常量引用
     */
    const T& front() const
    {
        return m_head->data;
    }

    /**
     * @brief 访问链表的最后一个元素
     * @return 链表最后一个元素的引用
     */
    T& back()
    {
        return m_tail->data;
    }

    /**
     * @brief 访问链表的最后一个元素（常量版本）
     * @return 链表最后一个元素的常量引用
     */
    const T& back() const
    {
        return m_tail->data;
    }

    /**
     * @brief 在链表头部插入元素
     * @param value 要插入的元素值
     */
    void push_front(const T& value)
    {
        Node* new_node = new Node(value);
        if (empty()) {
            m_head = m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
        ++m_size;
    }

    /**
     * @brief 在链表头部插入元素（移动版本）
     * @param value 要插入的元素右值引用
     */
    void push_front(T&& value)
    {
        Node* new_node = new Node(std::move(value));
        if (empty()) {
            m_head = m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
        ++m_size;
    }

    /**
     * @brief 在链表尾部插入元素
     * @param value 要插入的元素值
     */
    void push_back(const T& value)
    {
        Node* new_node = new Node(value);
        if (empty()) {
            m_head = m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
    }

    /**
     * @brief 在链表尾部插入元素（移动版本）
     * @param value 要插入的元素右值引用
     */
    void push_back(T&& value)
    {
        Node* new_node = new Node(std::move(value));
        if (empty()) {
            m_head = m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
    }

    /**
     * @brief 删除链表头部的元素
     */
    void pop_front()
    {
        if (empty())
            return;

        Node* node_to_delete = m_head;
        if (m_size == 1) {
            m_head = m_tail = nullptr;
        } else {
            m_head = m_head->next;
            m_head->prev = nullptr;
        }
        delete node_to_delete;
        --m_size;
    }

    /**
     * @brief 删除链表尾部的元素
     */
    void pop_back()
    {
        if (empty())
            return;

        Node* node_to_delete = m_tail;
        if (m_size == 1) {
            m_head = m_tail = nullptr;
        } else {
            m_tail = m_tail->prev;
            m_tail->next = nullptr;
        }
        delete node_to_delete;
        --m_size;
    }

    /**
     * @brief 在指定位置前插入元素
     * @param pos 插入位置的迭代器
     * @param value 要插入的元素值
     * @return 指向新插入元素的迭代器
     */
    iterator insert(iterator pos, const T& value)
    {
        if (pos == begin()) {
            push_front(value);
            return begin();
        } else if (pos == end()) {
            push_back(value);
            return iterator(m_tail);
        } else {
            Node* new_node = new Node(value);
            Node* next_node = pos.m_ptr;
            Node* prev_node = next_node->prev;

            new_node->next = next_node;
            new_node->prev = prev_node;
            prev_node->next = new_node;
            next_node->prev = new_node;

            ++m_size;
            return iterator(new_node);
        }
    }

    /**
     * @brief 在指定位置前插入元素（移动版本）
     * @param pos 插入位置的迭代器
     * @param value 要插入的元素右值引用
     * @return 指向新插入元素的迭代器
     */
    iterator insert(iterator pos, T&& value)
    {
        if (pos == begin()) {
            push_front(std::move(value));
            return begin();
        } else if (pos == end()) {
            push_back(std::move(value));
            return iterator(m_tail);
        } else {
            Node* new_node = new Node(std::move(value));
            Node* next_node = pos.m_ptr;
            Node* prev_node = next_node->prev;

            new_node->next = next_node;
            new_node->prev = prev_node;
            prev_node->next = new_node;
            next_node->prev = new_node;

            ++m_size;
            return iterator(new_node);
        }
    }

    /**
     * @brief 删除指定位置的元素
     * @param pos 要删除元素位置的迭代器
     * @return 指向被删除元素后一个元素的迭代器
     */
    iterator erase(iterator pos)
    {
        if (pos == end())
            return end();

        Node* node_to_delete = pos.m_ptr;
        iterator next_iter(node_to_delete->next);

        if (node_to_delete == m_head) {
            pop_front();
        } else if (node_to_delete == m_tail) {
            pop_back();
        } else {
            node_to_delete->prev->next = node_to_delete->next;
            node_to_delete->next->prev = node_to_delete->prev;
            delete node_to_delete;
            --m_size;
        }

        return next_iter;
    }

    /**
     * @brief 清空链表中的所有元素
     */
    void clear()
    {
        while (!empty()) {
            pop_front();
        }
    }

    /**
     * @brief 删除链表中所有等于指定值的元素
     * @param value 要删除的元素值
     */
    void remove(const T& value)
    {
        iterator it = begin();
        while (it != end()) {
            if (*it == value) {
                it = erase(it);
            } else {
                ++it;
            }
        }
    }

    /**
     * @brief 根据条件删除元素
     * @tparam Predicate 条件判断函数对象类型
     * @param pred 判断是否应删除元素的谓词函数
     */
    template <typename Predicate>
    void remove_if(Predicate pred)
    {
        iterator it = begin();
        while (it != end()) {
            if (pred(*it)) {
                it = erase(it);
            } else {
                ++it;
            }
        }
    }

private:
    Node* m_head; // 指向链表头节点的指针
    Node* m_tail; // 指向链表尾节点的指针
    size_t m_size; // 链表中元素的个数
};

} // namespace pvz