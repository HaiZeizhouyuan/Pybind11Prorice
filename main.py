#!/usr/bin/env python
# coding=utf-8
import all.build.example as example

a = example.add(2, 4)
print(a)

print(example.mul(3, 5))

print(example.sub())

cat = example.Cat("Tom", "北京", 100)
print(cat._name)
cat._name="Tony"
print(cat._name)
#print(cat.getName())
#cat.setName("Tony")
#print(cat.getName())
print(cat)

print(cat.age)
cat.age = 10
print(cat.age)

cat.hello()

cat.num = 3
print('num:{0}'.format(cat.num))

luk = example.Man("liu long")
print(luk.name)
luk.run()
