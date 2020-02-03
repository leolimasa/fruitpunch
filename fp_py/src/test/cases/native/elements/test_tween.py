'''
Created on Nov 3, 2012

@author: leo
'''
import unittest
from fruitpunch import Tween, Property, Animation

class Value(Property):
    def __init__(self):
        super(Value, self).__init__()
        self.value = 0
        
    def get(self):
        return self.value
    
    def set(self, val):
        self.value = val

class TestTween(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testRenderFrame(self):
        t = Tween()
        t.start_value = 10
        t.end_value = 19
        t.start_frame = 0
        t.duration = 10
        t.prop = Value()
        
        self.assertEqual(0, t.prop.get())
        t.render_single(2)
        self.assertEqual(12, t.prop.get())
        
    def testCreateProperty(self):
        inst = Animation()
        inst.myprop = 0
        
        # Basic test
        t = Tween()
        t.start_value = 10
        t.end_value = 19
        t.start_frame = 0
        t.duration = 10
        t.instance = inst
        t.attribute = "myprop"
        t.create_property()
        
        self.assertEqual(0, t.prop.get())
        t.render_single(2)
        self.assertEqual(12, t.prop.get())
        
        # If we already have a property, it should use that instead
        t = Tween()
        prop = Value()
        t.prop = prop
        t.start_value = 10
        t.end_value = 19
        t.start_frame = 0
        t.duration = 10
        t.create_property()
        
        self.assertEqual(prop, t.prop)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()