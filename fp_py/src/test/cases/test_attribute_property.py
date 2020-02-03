'''
Created on Apr 21, 2013

@author: leo
'''
import unittest
from fruitpunch import Animation
from fruitpunch.attribute_property import AttributeProperty


class TestAttributeProperty(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass


    def testGetSet(self):
        dummyobj = Animation()
        dummyobj.prop = "value"
        
        prop = AttributeProperty(dummyobj, "prop")
        
        self.assertEqual("value", prop.get())
        prop.set("changed")
        self.assertEqual("changed", dummyobj.prop)