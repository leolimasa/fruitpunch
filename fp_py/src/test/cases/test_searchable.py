'''
Created on Feb 16, 2013

@author: leo
'''
import unittest
from fruitpunch.searchable import Searchable
import pydevd

class Base(Searchable):
    def __init__(self):
        self.children = []
    
    def add(self, obj):
        self.children.append(obj)

class Node1(Base):
    pass
   
        
class Node2(Base):
    pass

class Test(unittest.TestCase):


    def setUp(self):
        self.root = Node1()
        self.node2 = Node2()
        self.node3 = Node2()
        self.node4 = Node1()
        self.node5 = Node2()
        
        self.node2.id = "node2"
        self.node3.id = "node3"
        self.node4.intval = 30
        
        self.root.add(self.node2)
        self.root.add(self.node3)
        self.node3.add(self.node4)
        self.node4.add(self.node5)

    def tearDown(self):
        pass


    def testFindBy(self):
        node2 = self.root.find_by("id", "node2")
        self.assertEqual(self.node2, node2)
        
        node4 = self.root.find_by("intval", 30)
        self.assertEqual(self.node4, node4)
        
        self.assertEqual(None, self.root.find_by("id","node5"))
        
        node2 = self.root.find_by("id")
        self.assertEqual(node2, self.node2)
        
    def testFindAllBy(self):
        node6 = Node2()
        node6.id = "node2"
        self.root.add(node6)
        
        node2s = self.root.find_all_by("id", "node2")
        self.assertEqual(self.node2, node2s[0])
        self.assertEqual(node6, node2s[1])
        
        withids = self.root.find_all_by("id")
        self.assertEqual(self.node2, withids[0])
        self.assertEqual(self.node3, withids[1])
        self.assertEqual(node6, withids[2])
        
    def testFindAllByClass(self):
        allNode2 = self.root.find_all_by_class(Node2)
        self.assertEqual(3, len(allNode2))
        self.assertEqual(allNode2[0], self.node2)
        self.assertEqual(allNode2[1], self.node3)
        self.assertEqual(allNode2[2], self.node5)
        
    def testFindByClass(self):
        node2 = self.root.find_by_class(Node2)
        self.assertEqual(self.node2, node2)
        
        node4 = self.root.find_by_class(Node1)
        self.assertEqual(self.node4, node4)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()