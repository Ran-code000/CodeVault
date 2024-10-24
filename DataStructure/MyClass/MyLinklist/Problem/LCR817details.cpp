//哈希表
// 使用自定义哈希函数
// 如果要存储自定义对象，可以自定义哈希函数和相等比较函数。
struct CustomType {
    int x;
    // ...
};
// 自定义哈希函数
struct CustomHash{
    //这个哈希函数重载了 () 操作符，使得 CustomHash 可以作为哈希函数使用
    size_t operator()(const CustomType& ct) const { return hash<int>()(ct.x);}
    //第一步，hash<int>() 创建一个哈希函数的实例。
    //第二步，使用这个实例的 operator() 方法计算 ct.x 的哈希值。
};

// 自定义相等函数
struct CustomEqual {
    bool operator()(const CustomType& lhs, const CustomType& rhs) const { return lhs.x == rhs.x;}
};
// 使用自定义哈希
unordered_set<CustomType, CustomHash, CustomEqual> customSet;
