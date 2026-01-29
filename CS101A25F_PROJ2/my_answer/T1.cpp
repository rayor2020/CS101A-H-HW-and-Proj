#include <iostream>
#include <string>

class HashTable {
    int capacity = 16;
    int size = 0;
    std::string* content;

public:
    HashTable(int capacity = 16)
        : capacity(capacity)
    {
        content = new std::string[capacity]();
    }

    ~HashTable()
    {
        delete[] content;
    }

    // 计算哈希值
    int hash(const std::string& key) const
    {
        return std::hash<std::string> {}(key) % capacity;
    }

    // 插入
    void insert(const std::string& key, bool output = false)
    {
        int home = hash(key);
        int index = home;
        std::string currentKey = key;

        // 如果键已经存在，则返回
        if (find(key) != -1) {
            if (output)
                std::cout << currentKey << " already exists at " << find(key) << std::endl;
            return;
        }

        while (content[index] != "") {
            index = (index + 1) % capacity;

            // 防止以外出现无限循环，增加鲁棒性
            if (index == home) {
                return;
            }
        }

        content[index] = currentKey;
        size++;

        if (output)
            std::cout << currentKey << " inserted at " << index << std::endl;

        return;
    }

    // 扩容
    void resize()
    {
        if ((double)size / capacity > 0.5) {
            int oldCapacity = capacity;
            std::string* oldContent = content;

            // 容量翻倍
            capacity *= 2;
            content = new std::string[capacity]();

            size = 0;

            // 重新插入所有元素
            for (int i = 0; i < oldCapacity; i++) {
                if (oldContent[i] != "") { // 按照索引顺序重新插入
                    insert(oldContent[i]);
                }
            }

            // 清理空间
            delete[] oldContent;
        }
    }

    // 查找
    int find(const std::string& key) const
    {
        int home = hash(key);
        int index = home;
        int age = 0;

        while (1) {
            // 如果当前位置为空，则键不存在
            if (content[index] == "")
                return -1;

            // 如果找到键则返回索引
            if (content[index] == key)
                return index;

            // 移动到下一个位置
            index = (index + 1) % capacity;
            ++age;

            // 防止意外出现无限循环，增加鲁棒性
            if (index == home)
                return -1;
        }

        return -1; // uwu
    }

    // 查找（输出）
    void search(const std::string& key) const
    {
        int index = find(key);
        if (index == -1) {
            std::cout << key << " does not exist" << std::endl;
        } else {
            std::cout << key << " found at " << index << std::endl;
        }
    }

    // 删除键
    void erase(const std::string& key)
    {
        int index = find(key);

        // 键不存在
        if (index == -1) {
            std::cout << key << " does not exist" << std::endl;
            return;
        }

        // 执行移除操作并移动后续元素填补空缺
        content[index] = "";
        size--;
        std::cout << key << " erased at " << index;

        // 向前移动元素直到遇到空槽
        int emptyIndex = index;
        int currentIndex = (index + 1) % capacity;

        bool shouldMove; // 判断是否需要移动
        while (content[currentIndex] != "") {
            // 计算当前元素的哈希值
            int homePos = hash(content[currentIndex]);

            // 环形判断当前元素的home位置是否在在(emptyIndex, currentIndex]区间内，不在则移动
            shouldMove = false;

            if (currentIndex > emptyIndex) { // 没有出现环绕情况
                if (homePos <= emptyIndex || homePos > currentIndex) { // 均在home同一侧
                    shouldMove = true;
                }
            } else { // 判断是否出现环绕情况
                if (homePos <= emptyIndex && homePos > currentIndex) { // currentIndex < homePos <= emptyIndex
                    shouldMove = true;
                }
            }

            if (shouldMove) {
                std::cout << ", moving " << content[currentIndex] << " from " << currentIndex;
                content[emptyIndex] = content[currentIndex];
                content[currentIndex] = "";
                emptyIndex = currentIndex;
            }

            currentIndex = (currentIndex + 1) % capacity;
        }
        std::cout << std::endl;
    }
};

int main()
{
    HashTable ht;
    int op;

    while (std::cin >> op && op != 0) {
        std::string key;
        std::cin >> key;

        switch (op) {
        case 1: // 插入
            ht.insert(key, true);
            break;
        case 2: // 查找
            ht.search(key);
            break;
        case 3: // 删除
            ht.erase(key);
            break;
        }
        ht.resize();
    }

    return 0;
}