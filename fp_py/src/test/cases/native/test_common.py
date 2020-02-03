'''
Created on Oct 26, 2012

@author: leo
'''
import unittest
from fruitpunch import Event, Observer, Observable, Property
from fruitpunch.native.common.property_event import PropertyEvent

class ObserverImpl(Observer):
    def __init__(self):
        self.triggered = False
        super(ObserverImpl, self).__init__()
    
    def action(self, event):
        self.triggered = True

class Left(Property):
    def set(self, value):
        self.obj.left = value
    def get(self):
        return self.obj.left

class Dummy:
    def __init__(self):
        self.left = 0

class TestCommon(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testEvent(self):
        e = Event("my_event")
        self.assertEqual(e.name, "my_event")
    
    def testObserver(self):
        o = Observable()
        obs = ObserverImpl()
        o.attach_observer("my_event", obs)
        
        self.assertEqual(False, obs.triggered)
        o.notify(Event("my_event"))
        self.assertEqual(True, obs.triggered)
        
    def testProperty(self):
        d = Dummy()
        leftprop = Left()
        leftprop.obj = d
        
        self.assertEqual(0, leftprop.get())
        leftprop.set(10)
        self.assertEqual(10, leftprop.get())
        
        # set through event
        leftprop.set(5)
        self.assertEqual(5, leftprop.get())
        pe = PropertyEvent("set")
        pe.value = 15
        leftprop.notify(pe)
        self.assertEqual(15, leftprop.get())
        self.assertEqual(15, d.left)
        
        # get through event
        leftprop.set(14)
        pe = PropertyEvent("get")
        leftprop.notify(pe)
        self.assertEqual(14, pe.value)
        self.assertEqual(14, d.left)
        
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()