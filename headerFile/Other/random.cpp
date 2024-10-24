<random> 是 C++ 标准库中的一个头文件, 包含了一系列生成随机数的工具, 包括随机数引擎和分布
它提供了一种灵活且功能强大的方式来生成随机数, 适用于各种应用场景

1. 随机数引擎
随机数引擎生成伪随机数序列, 不同的引擎具有不同的特性和用途, 常见的引擎包括: 

default_random_engine
mt19937
ranlux24_base
示例: 

#include <iostream>
#include <random>

int main() {
    // 使用默认随机数引擎
    default_random_engine defaultEngine;
    cout << "Default engine random number: " << defaultEngine() << endl;

    // 使用Mersenne Twister引擎
    mt19937 mtEngine;
    cout << "MT19937 engine random number: " << mtEngine() << endl;

    // 使用Ranlux24_base引擎
    ranlux24_base ranluxEngine;
    cout << "Ranlux24_base engine random number: " << ranluxEngine() << endl;

    return 0;
}

2. 随机数分布
随机数分布定义了随机数的生成范围和概率分布常见的分布包括: 
均匀分布: uniform_int_distribution、uniform_real_distribution
正态分布: normal_distribution
伯努利分布: bernoulli_distribution
示例: 

#include <iostream>
#include <random>

int main() {
    default_random_engine engine;

    // 均匀整数分布
    uniform_int_distribution<int> uniformIntDist(1, 100);
    cout << "Uniform int distribution: " << uniformIntDist(engine) << endl;

    // 均匀实数分布
    uniform_real_distribution<double> uniformRealDist(0.0, 1.0);
    cout << "Uniform real distribution: " << uniformRealDist(engine) << endl;

    // 正态分布
    normal_distribution<double> normalDist(0.0, 1.0);
    cout << "Normal distribution: " << normalDist(engine) << endl;

    // 伯努利分布
    bernoulli_distribution bernoulliDist(0.5);
    cout << "Bernoulli distribution: " << bernoulliDist(engine) << endl;

    return 0;
}

3. 随机数种子
随机数种子用于初始化随机数引擎, 使生成的随机数序列具有可重复性

示例: 

#include <iostream>
#include <random>

int main() {
    // 使用时间戳作为种子
    random_device rd;
    default_random_engine engine(rd());

    uniform_int_distribution<int> dist(1, 100);
    cout << "Random number with random seed: " << dist(engine) << endl;

    // 使用固定种子
    default_random_engine engineFixed(12345);
    cout << "Random number with fixed seed: " << dist(engineFixed) << endl;

    return 0;
}

4. 随机数生成范围
可以指定随机数生成的范围, 通过分布对象的参数设置

#include <iostream>
#include <random>

int main() {
    default_random_engine engine;

    // 生成 [10, 20] 范围内的整数
    uniform_int_distribution<int> distInt(10, 20);
    cout << "Random integer in [10, 20]: " << distInt(engine) << endl;

    // 生成 [0.5, 2.5] 范围内的实数
    uniform_real_distribution<double> distReal(0.5, 2.5);
    cout << "Random real number in [0.5, 2.5]: " << distReal(engine) << endl;

    return 0;
}

5. 随机选择
可以使用随机数生成器从容器中随机选择元素

示例: 

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

int main() {
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    random_device rd;
    mt19937 engine(rd());

    // 随机打乱顺序
    shuffle(data.begin(), data.end(), engine);

    cout << "Shuffled data: ";
    for (int n : data) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}

6. 自定义分布
可以通过自定义分布生成符合特定概率的随机数

示例: 

#include <iostream>
#include <random>

int main() {
    default_random_engine engine;
    piecewise_constant_distribution<double> dist(
        {0, 1, 2, 3, 4},  // 分段点
        {0.1, 0.2, 0.3, 0.4} // 每段的概率密度
    );

    cout << "Piecewise constant distribution: " << dist(engine) << endl;

    return 0;
}
总结
以上示例涵盖了 <random> 头文件的主要用法, 包括随机数引擎, 随机数分布, 种子, 随机数生成范围, 随机选择和自定义分布
