# 实验报告：使用朴素贝叶斯算法进行垃圾邮件分类

***报告人： 崔敬然 75543856***


***笔者为广东某 985 高校学生，在此感谢老师和学长学姐的指导，预祝春节快乐！！！***

（ctrl + shift + v 阅读）

## 1. 实验目的

本实验旨在使用朴素贝叶斯算法对Trec06中文垃圾邮件数据集进行垃圾邮件分类，并评估模型的性能。

具体目标包括：

- 使用朴素贝叶斯算法进行垃圾邮件分类
- 提取邮件正文部分的文本特征，并分析特征数目对模型效果的影响
- 使用精确度（Precision）、召回率（Recall）、准确率（Accuracy）等评估指标，确保模型的表现优异

## 2. 数据集简介

实验使用的数据集来自Trec06中文垃圾邮件数据集，数据集包括三个主要部分：

1. **data** 目录：存放未分词的邮件
2. **data_cut** 目录：存放已分词的邮件
3. **label** 目录：存放每封邮件的标签，标签为“spam”（垃圾邮件）或“ham”（正常邮件）

每封邮件由两部分组成：

- 邮件头（包括发送人、主题等信息）
- 邮件正文（实际内容）

**本实验使用的是已分词的邮件数据，并基于邮件正文进行特征提取**。

## 3. 实验步骤

### 3.1 数据预处理

首先，我们加载邮件数据并提取其正文部分，同时读取标签文件。每封邮件的标签和路径都存储在label文件夹中的文本文件中。我们使用`CountVectorizer`将邮件的词语转换为特征。

#### 代码：

```python
import os
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer

# 数据加载函数
def load_data(data_path, label_path):
    data = []
    labels = []
    with open(label_path, 'r', encoding='utf-8') as f:
        for line in f:
            label, path = line.strip().split()
            with open(os.path.join(data_path, path), 'r', encoding='utf-8') as email:
                email_content = email.read()
            data.append(email_content)
            labels.append(label)
    return data, labels

# 读取数据和标签
data_path = 'data_cut'  # 分词后的邮件目录
label_path = 'label/train-labels.txt'  # 标签路径
data, labels = load_data(data_path, label_path)

# 数据划分为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(data, labels, test_size=0.2, random_state=42)

# 文本特征提取
vectorizer = CountVectorizer(max_features=5000)  # 选择最多5000个特征词
X_train_vec = vectorizer.fit_transform(X_train)
X_test_vec = vectorizer.transform(X_test)


```

### 3.2 模型训练与预测

使用MultinomialNB模型进行训练，并对测试集进行预测。我们使用准确率（Accuracy）、精确率（Precision）、召回率（Recall）、F1得分等指标来评估模型效果。

#### 代码：

```python

from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# 训练朴素贝叶斯模型
nb_model = MultinomialNB()
nb_model.fit(X_train_vec, y_train)

# 在测试集上进行预测
y_pred = nb_model.predict(X_test_vec)

# 计算性能指标
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, pos_label='spam')
recall = recall_score(y_test, y_pred, pos_label='spam')
f1 = f1_score(y_test, y_pred, pos_label='spam')

# 打印评估结果
print(f"Accuracy: {accuracy:.4f}")
print(f"Precision: {precision:.4f}")
print(f"Recall: {recall:.4f}")
print(f"F1 Score: {f1:.4f}")

```

### 3.3 特征数目对模型效果的影响

为了评估词表大小对模型性能的影响，我们分别使用不同的最大特征数（1000, 5000, 10000）来训练和评估模型

#### 代码：

```python

# 测试不同词表大小对模型的影响
feature_sizes = [1000, 5000, 10000]
for size in feature_sizes:
    vectorizer = CountVectorizer(max_features=size)
    X_train_vec = vectorizer.fit_transform(X_train)
    X_test_vec = vectorizer.transform(X_test)
    
    # 训练并评估模型
    nb_model.fit(X_train_vec, y_train)
    y_pred = nb_model.predict(X_test_vec)
    
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, pos_label='spam')
    recall = recall_score(y_test, y_pred, pos_label='spam')
    f1 = f1_score(y_test, y_pred, pos_label='spam')
    
    print(f"Feature size: {size}")
    print(f"Accuracy: {accuracy:.4f}")
    print(f"Precision: {precision:.4f}")
    print(f"Recall: {recall:.4f}")
    print(f"F1 Score: {f1:.4f}")
    print("-" * 50)
```

### 3.4 扩展要求：邮件头信息的使用

邮件头信息有时也有助于判断邮件是否为垃圾邮件。为了扩展模型，我们将邮件头与正文内容结合使用，并重新训练模型进行评估

#### 代码:

```python

# 提取邮件头信息
def extract_email_header(email_path):
    with open(email_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
        headers = []
        for line in lines:
            if line.strip() == '':
                break
            headers.append(line.strip())
    return " ".join(headers)

# 合并邮件头和正文
def load_data_with_headers(data_path, label_path):
    data = []
    labels = []
    headers = []
    with open(label_path, 'r', encoding='utf-8') as f:
        for line in f:
            label, path = line.strip().split()
            email_path = os.path.join(data_path, path)
            email_content = load_email_content(email_path)
            email_header = extract_email_header(email_path)
            data.append(email_content + " " + email_header)  # 合并正文和邮件头
            labels.append(label)
    return data, labels

# 加载并训练模型
data_with_headers, labels = load_data_with_headers(data_path, label_path)
X_train, X_test, y_train, y_test = train_test_split(data_with_headers, labels, test_size=0.2, random_state=42)
X_train_vec = vectorizer.fit_transform(X_train)
X_test_vec = vectorizer.transform(X_test)

# 训练和评估模型
nb_model.fit(X_train_vec, y_train)
y_pred = nb_model.predict(X_test_vec)
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, pos_label='spam')
recall = recall_score(y_test, y_pred, pos_label='spam')
f1 = f1_score(y_test, y_pred, pos_label='spam')

print(f"Accuracy with header info: {accuracy:.4f}")
print(f"Precision with header info: {precision:.4f}")
print(f"Recall with header info: {recall:.4f}")
print(f"F1 Score with header info: {f1:.4f}")
```

## 4. 实验结果

### 4.1 训练与测试结果

![1](https://i-blog.csdnimg.cn/direct/0917c89c75b943389115331711a5f997.png)

### 4.2 特征数目对模型效果的影响

![2](https://i-blog.csdnimg.cn/direct/c42c038185224f5bba89caaa791bc677.png)

### 4.3 邮件头信息的使用

![3](https://i-blog.csdnimg.cn/direct/1590d3ab6aee4ac49e11731e23fa476c.png)

## 5. 结论与展望

本实验通过朴素贝叶斯算法实现了垃圾邮件分类，并达到了较好的分类效果。实验结果表明，增加特征数目和结合邮件头信息都能有效提高模型的性能


