'''
Created on Jan 21, 2013

@author: leo
'''
import unittest
from fruitpunch import Element


class ElImpl(Element):
  
    def on_add(self, event):
        self.added = True
        self.rendered = 0
        
    def on_render(self, event):
        self.rendered += 1

class TestCollection(unittest.TestCase):


    def setUp(self):
        self.root = ElImpl()
        self.a = ElImpl()
        self.b = ElImpl()
        self.c = ElImpl()
        
        self.root.add(self.a)
        self.root.add(self.b)
        self.root.add(self.c) 


    def tearDown(self):
        pass


    def testCollection(self):
        self.assertEqual(self.a, self.root.children.get(0))
        self.assertEqual(self.b, self.root.children.get(1))
        self.assertEqual(self.c, self.root.children.get(2))
        
        self.assertEqual(3, self.root.children.get_size())
        
        self.assertEqual(self.a, self.root.children.get_first())
        self.assertEqual(self.c, self.root.children.get_last())
    
    def testIterator(self):
        it = self.root.children.get_iterator()
        it.next()
        self.assertEqual(it.get(), self.a)
        it.next()
        self.assertEqual(it.get(), self.b)
        it.next()
        self.assertEqual(it.get(), self.c)
        
        it.go_to(1)
        self.assertEqual(it.get(), self.b)
        
        it.remove()
        self.assertEqual(it.get(), self.c)
        
    def testOverloads(self):
        children = self.root.children
        self.assertEqual(children[1], self.b)
        i = 0
        for c in children:
            self.assertEqual(c, children[i])
            i += 1


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()